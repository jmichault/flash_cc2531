
#ifndef CCDEBUGGER_H
#define CCDEBUGGER_H

#define CC_ERROR_NONE           0
#define CC_ERROR_NOT_ACTIVE     1
#define CC_ERROR_NOT_DEBUGGING  2
#define CC_ERROR_NOT_WIRED      3


  int cc_init( int pinRST, int pinDC, int pinDD );
  void cc_delay( unsigned char d );

  uint8_t cc_error();

  ////////////////////////////
  // High-Level interaction
  ////////////////////////////
  void cc_setActive( uint8_t on );

  /**
   * Enter debug mode
   */
  uint8_t cc_enter();

  /**
   * Exit from debug mode
   */
  uint8_t cc_exit();

  /**
   * Execute a CPU instructuion
   */
  uint8_t cc_exec( uint8_t oc0 );
  uint8_t cc_execi( uint8_t oc0, unsigned short c0 );
  uint8_t cc_exec2( uint8_t oc0, uint8_t oc1 );
  uint8_t cc_exec3( uint8_t oc0, uint8_t oc1, uint8_t oc2 );

  /**
   * Return chip ID
   */
  unsigned short cc_getChipID();

  /**
   * Return PC
   */
  unsigned short cc_getPC();

  /**
   * Return debug status
   */
  uint8_t cc_getStatus();

   /**
   * resume program exec
   */
  uint8_t cc_resume();

  /**
   * halt program exec
   */
  uint8_t cc_halt();

  /**
   * Step a single instruction
   */
  uint8_t cc_step();

  /**
   * Get debug configuration
   */
  uint8_t cc_getConfig();

  /**
   * Set debug configuration
   */
  uint8_t cc_setConfig( uint8_t config );

  /**
   * Massive erasure on the chip
   */
  uint8_t cc_chipErase();

  ////////////////////////////
  // Low-level interaction
  ////////////////////////////

  /**
   * Write to the debugger
   */
  uint8_t cc_write( uint8_t data );

  /**
   * Wait until we are ready to read & Switch to read mode
   */
  uint8_t cc_switchRead( uint8_t maxWaitCycles );

  /**
   * Switch to write mode
   */
  uint8_t cc_switchWrite();

  /**
   * Read from the debugger
   */
  uint8_t cc_read();

  /**
   * Update the debug instruction table
   */
  uint8_t cc_updateInstructionTable( uint8_t newTable[16] );

  /**
   * Get the instruction table version
   */
  uint8_t cc_getInstructionTableVersion();



#endif

