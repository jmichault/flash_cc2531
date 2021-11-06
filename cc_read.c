/***********************************************************************
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
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "CCDebugger.h"

static int vorte=0;

void writeHexLine(FILE * fic,uint8_t *buf, int len,int offset)
{
int i=0;
  for(i=0 ; i<len ; i++)
    if(buf[i] != 0xff) break;
  if(i==len) return;
  int sum=len+(offset&0xff)+((offset>>8)&0xff);
  fprintf(fic,":%02X%04X00",len,offset);
  for(int i=0 ; i<len;i++)
  {
    fprintf(fic,"%02X",buf[i]);
    sum += buf[i];
  }
  fprintf(fic,"%02X\n",(-sum)&0xff);
}

uint8_t buf1[1024];
uint8_t buf2[1024];

void read1k(int bank,uint16_t offset,uint8_t * buf)
{
    // get FMAP
    uint8_t res = cc_exec2(0xE5, 0xC7); 
    // select bank 
    res = (res & 0xF8) | (bank & 0x07);
    res = cc_exec3(0x75, 0xC7, res); // MOV direct,#data
    // Setup DPTR
    cc_execi( 0x90, 0x8000+offset ); // MOV DPTR,#data16
    for(int i=0 ; i<1024 ;i++)
    {
      res = cc_exec  ( 0xE0 ); // MOVX A,@DPTR
      buf[i] = res;
      res = cc_exec  ( 0xA3 ); // INC DPTR
    }
}

void helpo()
{
  fprintf(stderr,"usage : cc_read [-d pin_DD] [-c pin_DC] [-r pin_reset] out_file\n"); 
  fprintf(stderr,"	-c : change pin_DC (default 27)\n");
  fprintf(stderr,"	-d : change pin_DD (default 28)\n");
  fprintf(stderr,"	-r : change reset pin (default 24)\n");
  fprintf(stderr,"	-m : change multiplier for time delay (default auto)\n");
  fprintf(stderr,"	-v : verbose\n");
}

int main(int argc,char *argv[])
{
  int opt;
  int rePin=-1;
  int dcPin=-1;
  int ddPin=-1;
  int setMult=-1;
  while( (opt=getopt(argc,argv,"vm:d:c:r:h?")) != -1)
  {
    switch(opt)
    {
     case 'm' : 
      setMult=atoi(optarg);
      break;
     case 'd' : // DD pinglo
      ddPin=atoi(optarg);
      break;
     case 'c' : // DC pinglo
      dcPin=atoi(optarg);
      break;
     case 'r' : // restarigi pinglo
      rePin=atoi(optarg);
      break;
     case 'v' : // vorte
      vorte++;
      break;
     case 'h' : // helpo
     case '?' : // helpo
      helpo();
      exit(0);
      break;
    }
  }
  if( optind >= argc ) { helpo(); exit(1); }
  FILE * ficout = fopen(argv[optind],"w");
  if(!ficout) { fprintf(stderr," Can't open file %s.\n",argv[optind]); exit(1); }
  //  initialize GPIO ports
  cc_init(rePin,dcPin,ddPin);
  if(vorte) fprintf(stderr," auto mult selected : %d\n", cc_getmult());
  if(setMult>0) cc_setmult(setMult);
  // enter debug mode
  cc_enter();
  // get ChipID :
  uint16_t ID;
  ID = cc_getChipID();
  printf("  ID = %04x.\n",ID);

  uint16_t offset=0;
  uint8_t bank=0;
  int progress=1;
  int nbread=0;
  for( bank=0 ; bank<8 ; bank++)
  {
    printf(".");fflush(stdout);
    if(! (bank&1))
    {
      uint8_t sum=2+4+(bank/2);
      fprintf(ficout,":02000004%04X%02X\n",bank/2,(-sum)&255 );
    }
    offset=0;
    int len=0;
    uint8_t buf[17];
    for ( uint16_t i=0 ; i<32 ; i++ )
    {
      int provo=0;
      do
      {
        read1k(bank,i*1024, buf1);
        read1k(bank,i*1024, buf2);
        provo++;
        if (provo %3 ==0)
        {
	  // increase mult
          int mult=cc_getmult();
	  mult= mult+mult/10+1;
          cc_setmult(mult);
          if(vorte) fputc( '.',stderr);
	  if(provo>3 && mult>setMult) setMult=mult;
        }
        nbread++;
        //if(memcmp(buf1,buf2,1024))
	//  {printf("x");fflush(stdout);}
      } while(memcmp(buf1,buf2,1024));
      if(provo==1)
      {
	// reduce mult
        int mult=cc_getmult();
	mult= mult-mult/20;
	if(setMult && mult<setMult) mult=setMult;
        cc_setmult(mult);
      }
      for(uint16_t j=0 ; j<64 ; j++)
	writeHexLine(ficout,buf1+j*16, 16,(bank&1)*32*1024+ i*1024+j*16);
      printf("\r reading %dk/256k",progress++);fflush(stdout);
    }
  }
  if(vorte) fprintf(stderr,"\nnbread=%d\n final mult : %d\n",nbread,cc_getmult());
  fprintf(ficout,":00000001FF\n");
  // exit from debug 
  cc_setActive(false);
  // reboot
  cc_reset();
  fclose(ficout);

}
