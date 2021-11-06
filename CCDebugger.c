/***********************************************************************
 * Copyright (c) 2014-2016 Ioannis Charalampidis
 * Copyright (c) 2015 Simon Schulz - github.com/fishpepper
  Copyright © 2019 Jean Michault.
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*************************************************************************/

#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "CCDebugger.h"

  /**
   * Switch reset pin
   */
  void cc_setDDDirection( uint8_t direction );

  /**
   * Software-overridable instruction table that can be used
   * for supporting other CCDebug-Compatible chips purely by software
   */
  uint8_t      instr[16];

  /**
   * Local properties
   */
  int       pinRST= PIN_RST;
  int       pinDC= PIN_DC;
  int       pinDD= PIN_DD;
  uint8_t      errorFlag=0;
  uint8_t      ddIsOutput=false;
  uint8_t      inDebugMode=false;
  uint8_t   cc_active=false;


/**
 * Instruction table indices
 */
#define INSTR_VERSION   0
#define I_HALT          1
#define I_RESUME        2
#define I_RD_CONFIG     3
#define I_WR_CONFIG     4
#define I_DEBUG_INSTR_1 5
#define I_DEBUG_INSTR_2 6
#define I_DEBUG_INSTR_3 7
#define I_GET_CHIP_ID   8
#define I_GET_PC        9
#define I_READ_STATUS   10
#define I_STEP_INSTR    11
#define I_CHIP_ERASE    12

#define I_SET_HW_BRKPNT    13
#define I_GET_BM    14
#define I_BURST_WRITE    15

void cc_delay_calibrate( );
int cc_init( int pRST, int pDC, int pDD )
{
  if(pRST>=0) pinRST=pRST;
  if(pDC>=0) pinDC=pDC;
  if(pDD>=0) pinDD=pDD;

  if(wiringPiSetup() == -1){
    printf("no wiring pi detected\n");
    return 0;
  }
  cc_delay_calibrate();

  // Prepare CC Pins
  pinMode(pinDC,        OUTPUT);
  pinMode(pinDD,      OUTPUT);
  pinMode(pinRST,       OUTPUT);
  digitalWrite(pinDC,   LOW);
  digitalWrite(pinDD, LOW);
  digitalWrite(pinRST,  LOW);

  // Prepare default direction
  cc_setDDDirection(INPUT);

  // Default CCDebug instruction set for CC254x
  instr[INSTR_VERSION]    = 1;
  instr[I_HALT]           = 0x40;
  instr[I_RESUME]         = 0x48;
  instr[I_RD_CONFIG]      = 0x20;
  instr[I_WR_CONFIG]      = 0x18;
  instr[I_DEBUG_INSTR_1]  = 0x51;
  instr[I_DEBUG_INSTR_2]  = 0x52;
  instr[I_DEBUG_INSTR_3]  = 0x53;
  instr[I_GET_CHIP_ID]    = 0x68;
  instr[I_GET_PC]         = 0x28;
  instr[I_READ_STATUS]    = 0x30;
  instr[I_STEP_INSTR]     = 0x58;
  instr[I_CHIP_ERASE]     = 0x10;

  // We are active by default
  cc_active = true;

};

/**
 * Activate/Deactivate debugger
 */
void cc_setActive( uint8_t on )
{

  // Reset error flag
  errorFlag = CC_ERROR_NONE;

  // Continue only if active
  if (on == cc_active) return;
  cc_active = on;

  if (on) {

    // Prepare CC Pins
    pinMode(pinDC,        OUTPUT);
    pinMode(pinDD,      OUTPUT);
    pinMode(pinRST,       OUTPUT);
    digitalWrite(pinDC,   LOW);
    digitalWrite(pinDD, LOW);
    digitalWrite(pinRST,  LOW);

    // Default direction is INPUT
    cc_setDDDirection(INPUT);

  } else {

    // Before deactivating, exit debug mode
    if (inDebugMode)
      cc_exit();

    // Put everything in inactive mode
    pinMode(pinDC,        INPUT);
    pinMode(pinDD,      INPUT);
    pinMode(pinRST,       INPUT);
    digitalWrite(pinDC,   LOW);
    digitalWrite(pinDD, LOW);
    digitalWrite(pinRST,  LOW);

  }
}

/**
 * Return the error flag
 */
uint8_t cc_error()
{
  return errorFlag;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////                     LOW LEVEL FUNCTIONS                     ////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/**
 * Delay a particular number of cycles
 */
struct timespec tp={0,0};
static int cc_delay_mult=80;
void cc_delay( unsigned int d )
{
  volatile unsigned int i = cc_delay_mult*d;
  while( i-- );
//tp.tv_nsec=40*d;
//nanosleep(&tp,NULL);

}

void cc_setmult(int mult)
{
  if(mult>0)
    cc_delay_mult=mult;
  else
    cc_delay_mult=cc_delay_mult+cc_delay_mult/10+1;
}

int cc_getmult()
{
  return cc_delay_mult;
}

/* provas konsideri la rapidecon de la procesoro */
void cc_delay_calibrate( )
{
  long time0=micros();
  cc_delay(200);
  cc_delay(200);
  cc_delay(200);
  cc_delay(200);
  cc_delay(200);
  long time1=micros();
  cc_delay_mult=cc_delay_mult*600/(time1-time0);
}

/**
 * Enter debug mode
 */
uint8_t cc_enter()
{
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  // =============

  // Reset error flag
  errorFlag = CC_ERROR_NONE;

  // Enter debug mode
  digitalWrite(pinRST, LOW);
  cc_delay(200);
  digitalWrite(pinDC, HIGH);
  cc_delay(3);
  digitalWrite(pinDC, LOW);
  cc_delay(3);
  digitalWrite(pinDC, HIGH);
  cc_delay(3);
  digitalWrite(pinDC, LOW);
  cc_delay(4);
  digitalWrite(pinRST, HIGH);
  cc_delay(200);

  // We are now in debug mode
  inDebugMode = 1;

  // =============

  // Success
  return 0;

};

/**
 * Write a uint8_t to the debugger
 */
uint8_t cc_write( uint8_t data )
{
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  };
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }
  // =============

  uint8_t cnt;

  // Make sure DD is on output
  cc_setDDDirection(OUTPUT);

  // Sent uint8_ts
  for (cnt = 8; cnt; cnt--) {

    // First put data bit on bus
    if (data & 0x80)
      digitalWrite(pinDD, HIGH);
    else
      digitalWrite(pinDD, LOW);

    // Place clock on high (other end reads data)
    digitalWrite(pinDC, HIGH);

    // Shift & Delay
    data <<= 1;
    cc_delay(2);

    // Place clock down
    digitalWrite(pinDC, LOW);
    cc_delay(2);

  }

  // =============
  return 0;
}

/**
 * Wait until input is ready for reading
 */
uint8_t cc_switchRead(uint8_t maxWaitCycles)
{
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }
  // =============

  uint8_t cnt;
  uint8_t didWait = 0;

  // Switch to input
  cc_setDDDirection(INPUT);

  // Wait at least 83 ns before checking state t(dir_change)
  cc_delay(2);

  // Wait for DD to go LOW (Chip is READY)
  while (digitalRead(pinDD) == HIGH) {

    // Do 8 clock cycles
    for (cnt = 8; cnt; cnt--) {
      digitalWrite(pinDC, HIGH);
      cc_delay(2);
      digitalWrite(pinDC, LOW);
      cc_delay(2);
    }

    // Let next function know that we did wait
    didWait = 1;

    // Check if we ran out if wait cycles
    if (!--maxWaitCycles) {

      // If we are waiting for too long, we have lost the chip,
      // so also assume we are out of debugging mode
      errorFlag = CC_ERROR_NOT_WIRED;
      inDebugMode = 0;


      return 0;
    }
  }

  // Wait t(sample_wait)
  if (didWait) cc_delay(2);

  // =============
  return 0;
}

/**
 * Switch to output
 */
uint8_t cc_switchWrite()
{
  cc_setDDDirection(OUTPUT);
  return 0;
}

/**
 * Read an input uint8_t
 */
uint8_t cc_read()
{
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  // =============

  uint8_t cnt;
  uint8_t data = 0;

  // Switch to input
  cc_setDDDirection(INPUT);

  // Send 8 clock pulses if we are HIGH
  for (cnt = 8; cnt; cnt--) {
    digitalWrite(pinDC, HIGH);
    cc_delay(2);

    // Shift and read
    data <<= 1;
    if (digitalRead(pinDD) == HIGH)
      data |= 0x01;

    digitalWrite(pinDC, LOW);
    cc_delay(2);
  }

  // =============
  return data;
}

/**
 * Switch reset pin
 */
void cc_setDDDirection( uint8_t direction )
{

  // Switch direction if changed
  if (direction == ddIsOutput) return;
  ddIsOutput = direction;

  // Handle new direction
  if (ddIsOutput) {
    digitalWrite(pinDD, LOW); // Disable pull-up
    pinMode(pinDD, OUTPUT);   // Enable output
    digitalWrite(pinDD, LOW); // Switch to low
  } else {
    digitalWrite(pinDD, LOW); // Disable pull-up
    pinMode(pinDD, INPUT);    // Disable output
    digitalWrite(pinDD, LOW); // Don't use output pull-up
  }

}

void cc_reset()
{
  pinMode(pinDC, INPUT);
  pinMode(pinDD, INPUT);
  pinMode(pinRST, OUTPUT);
  cc_delay(200);
  pinMode(pinRST, LOW);
  cc_delay(500);
  pinMode(pinRST, INPUT);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////                    HIGH LEVEL FUNCTIONS                     ////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


/**
 * Exit from debug mode
 */
uint8_t cc_exit()
{
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_RESUME] ); // RESUME
  cc_switchRead(250);
  bAns = cc_read(); // debug status
  cc_switchWrite();

  inDebugMode = 0;

  return 0;
}
/**
 * Get debug configuration
 */
uint8_t cc_getConfig() {
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_RD_CONFIG] ); // RD_CONFIG
  cc_switchRead(250);
  bAns = cc_read(); // Config
  cc_switchWrite();

  return bAns;
}

/**
 * Set debug configuration
 */
uint8_t cc_setConfig( uint8_t config ) {
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_WR_CONFIG] ); // WR_CONFIG
  cc_write( config );
  cc_switchRead(250);
  bAns = cc_read(); // Config
  cc_switchWrite();

  return bAns;
}

/**
 * Invoke a debug instruction with 1 opcode
 */
uint8_t cc_exec( uint8_t oc0 )
{
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_DEBUG_INSTR_1] ); // DEBUG_INSTR + 1b
  cc_write( oc0 );
  cc_switchRead(250);
  bAns = cc_read(); // Accumulator
  cc_switchWrite();

  return bAns;
}

/**
 * Invoke a debug instruction with 2 opcodes
 */
uint8_t cc_exec2( uint8_t oc0, uint8_t oc1 )
{
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_DEBUG_INSTR_2] ); // DEBUG_INSTR + 2b
  cc_write( oc0 );
  cc_write( oc1 );
  cc_switchRead(250);
  bAns = cc_read(); // Accumulator
  cc_switchWrite();

  return bAns;
}

/**
 * Invoke a debug instruction with 3 opcodes
 */
uint8_t cc_exec3( uint8_t oc0, uint8_t oc1, uint8_t oc2 )
{
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_DEBUG_INSTR_3] ); // DEBUG_INSTR + 3b
  cc_write( oc0 );
  cc_write( oc1 );
  cc_write( oc2 );
  cc_switchRead(250);
  bAns = cc_read(); // Accumulator
  cc_switchWrite();

  return bAns;
}

/**
 * Invoke a debug instruction with 1 opcode + 16-bit immediate
 */
uint8_t cc_execi( uint8_t oc0, unsigned short c0 )
{
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_DEBUG_INSTR_3] ); // DEBUG_INSTR + 3b
  cc_write( oc0 );
  cc_write( (c0 >> 8) & 0xFF );
  cc_write(  c0 & 0xFF );
  cc_switchRead(250);
  bAns = cc_read(); // Accumulator
  cc_switchWrite();

  return bAns;
}

/**
 * Return chip ID
 */
unsigned short cc_getChipID() {
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  unsigned short bAns;
  uint8_t bRes;

  cc_write( instr[I_GET_CHIP_ID] ); // GET_CHIP_ID
  cc_switchRead(250);

  bRes = cc_read(); // High order
  bAns = bRes << 8;
  bRes = cc_read(); // Low order
  bAns |= bRes;
  cc_switchWrite();

  return bAns;
}

/**
 * Return PC
 */
unsigned short cc_getPC() {
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  unsigned short bAns;
  uint8_t bRes;

  cc_write( instr[I_GET_PC] ); // GET_PC
  cc_switchRead(250);
  bRes = cc_read(); // High order
  bAns = bRes << 8;
  bRes = cc_read(); // Low order
  bAns |= bRes;
  cc_switchWrite();

  return bAns;
}

/**
 * Return debug status
 */
uint8_t cc_getStatus() {
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_READ_STATUS] ); // READ_STATUS
  cc_switchRead(250);
  bAns = cc_read(); // debug status
  cc_switchWrite();

  return bAns;
}

/**
 * Step instruction
 */
uint8_t cc_step() {
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_STEP_INSTR] ); // STEP_INSTR
  cc_switchRead(250);
  bAns = cc_read(); // Accumulator
  cc_switchWrite();

  return bAns;
}

/**
 * resume instruction
 */
uint8_t cc_resume() {
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_RESUME] ); //RESUME
  cc_switchRead(250);
  bAns = cc_read(); // Accumulator
  cc_switchWrite();

  return bAns;
}

/**
 * halt instruction
 */
uint8_t cc_halt() {
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  }
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_HALT] ); //HALT
  cc_switchRead(250);
  bAns = cc_read(); // Accumulator
  cc_switchWrite();

  return bAns;
}

/**
 * Mass-erase all chip configuration & Lock Bits
 */
uint8_t cc_chipErase()
{
  if (!cc_active) {
    errorFlag = CC_ERROR_NOT_ACTIVE;
    return 0;
  };
  if (!inDebugMode) {
    errorFlag = CC_ERROR_NOT_DEBUGGING;
    return 0;
  }

  uint8_t bAns;

  cc_write( instr[I_CHIP_ERASE] ); // CHIP_ERASE
  cc_switchRead(250);
  bAns = cc_read(); // Debug status
  cc_switchWrite();

  return bAns;
}

/**
 * Update the debug instruction table
 */
uint8_t cc_updateInstructionTable( uint8_t newTable[16] )
{
  // Copy table entries
  for (uint8_t i=0; i<16; i++)
    instr[i] = newTable[i];
  // Return the new version
  return instr[INSTR_VERSION];
}

/**
 * Get the instruction table version
 */
uint8_t cc_getInstructionTableVersion()
{
  // Return version of instruction table
  return instr[INSTR_VERSION];
}
