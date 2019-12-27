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

void helpo()
{
  fprintf(stderr,"usage : cc_erase [-d pin_DD] [-c pin_DC] [-r pin_reset]\n"); 
  fprintf(stderr,"	-c : change pin_DC (default 27)\n");
  fprintf(stderr,"	-d : change pin_DD (default 28)\n");
  fprintf(stderr,"	-r : change reset pin (default 24)\n");
  fprintf(stderr,"	-m : change multiplier for time delay (default auto)\n");
}

int main(int argc,char *argv[])
{
  int opt;
  int rePin=-1;
  int dcPin=-1;
  int ddPin=-1;
  int setMult=-1;
  while( (opt=getopt(argc,argv,"m:d:c:r:h?")) != -1)
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
     case 'h' : // helpo
     case '?' : // helpo
      helpo();
      exit(0);
      break;
    }
  }
  // initialize GPIO and debugger
  cc_init(rePin,dcPin,ddPin);
  if(setMult>0) cc_setmult(setMult);
  // enter debug mode
  cc_enter();
  // get ChipID :
  uint16_t res;
  res = cc_getChipID();
  printf("  ID = %04x.\n",res);
  // erase flash
  res = cc_chipErase();
  printf("  erase result = %04x.\n",res);
  cc_setActive(false);

}
