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

int vorte=0;

uint8_t buffer[601];
uint8_t data[260];
uint8_t buf1[1024];
uint8_t buf2[1024];

struct page
{
uint32_t minoffset,maxoffset;
uint8_t datas[2048];
} Pages[128];



void readXDATA(uint16_t offset,uint8_t *bytes, int len)
{
  cc_execi(0x90, offset ); //MOV DPTR,#data16
  for ( int i=0 ; i<len;i++)
  {
    bytes[i] = cc_exec(0xE0);	//MOVX A,@DPTR
    cc_exec(0xA3);	// INC DPTR
  }
}

void writeXDATA(uint16_t offset,uint8_t *bytes, int len)
{
  cc_execi(0x90,offset); //MOV DPTR,#data16
  for ( int i=0 ; i<len;i++)
  {
    cc_exec2(0x74,bytes[i]); // MOV A,#data
    cc_exec(0xF0);	//MOVX @DPTR,A
    cc_exec(0xA3);	// INC DPTR
  }
}

void readPage(int page,uint8_t *buf)
{
  uint8_t bank=page>>4;
  // get FMAP
  uint8_t res = cc_exec2(0xE5, 0xC7);
  // select bank
  res = (res & 0xF8) | (bank & 0x07);
  res = cc_exec3(0x75, 0xC7, res); // MOV direct,#data
  // calculer l'adresse de destination
  uint32_t offset = ((page&0xf)<<11) + Pages[page].minoffset;
  // Setup DPTR
  cc_execi( 0x90, 0x8000+offset ); // MOV DPTR,#data16
  for(int i=Pages[page].minoffset ; i<=Pages[page].maxoffset ;i++)
  {
    res = cc_exec  ( 0xE0 ); // MOVX A,@DPTR
    buf[i] = res;
    res = cc_exec  ( 0xA3 ); // INC DPTR
  }
}

uint8_t verif1[2048];
uint8_t verif2[2048];

int verifPage(int page)
{
  for(int i=Pages[page].minoffset ; i<=Pages[page].maxoffset ;i++)
  {
    if(verif1[i] != Pages[page].datas[i])
    {
      if(vorte) fprintf(stderr,"\nerror at 0x%x, 0x%x instead of 0x%x\n",i,verif1[i],Pages[page].datas[i]);
      return 1;
    }
  }
  return 0;
}

int writePage(int page)
{
  uint8_t bank=page>>4;
  // get FMAP
  uint8_t res = cc_exec2(0xE5, 0xC7);
  // select bank
  res = (res & 0xF8) | (bank & 0x07);
  res = cc_exec3(0x75, 0xC7, res); // MOV direct,#data
  // calculer l'adresse de destination
  // round minoffset because FADDR is a word address
  Pages[page].minoffset = (Pages[page].minoffset & 0xfffffffc);
  // round maxoffset to write entire words
  Pages[page].maxoffset = (Pages[page].maxoffset |0x3);
  uint32_t offset = ((page&0xf)<<11) + Pages[page].minoffset;

  uint32_t len = Pages[page].maxoffset-Pages[page].minoffset+1;
  //FIXME : sometimes incorrect length is wrote
  //if(len&0xf && (Pages[page].minoffset+len<2032)) len= (len&0x7f0)+16;
  // configure DMA-0 pour DEBUG --> RAM
  uint8_t dma_desc0[8];
  dma_desc0[0] = 0x62;// src[15:8]
  dma_desc0[1] = 0x60;// src[7:0]
  dma_desc0[2] = 0x00;// dest[15:8]
  dma_desc0[3] = 0x00;// dest[7:0]
  dma_desc0[4] = (len>>8)&0xff;
  dma_desc0[5] = (len&0xff);
  dma_desc0[6] = 0x1f; //wordsize=0,tmode=0,trig=0x1F
  dma_desc0[7] = 0x19;//srcinc=0,destinc=1,irqmask=1,m8=0,priority=1
  writeXDATA( 0x1000, dma_desc0, 8 );
  cc_exec3( 0x75, 0xD4, 0x00);
  cc_exec3( 0x75, 0xD5, 0x10);

  // configure DMA-1 pour RAM --> FLASH
  uint8_t dma_desc1[8];
  dma_desc1[0] = 0x00;// src[15:8]
  dma_desc1[1] = 0x00;// src[7:0]
  dma_desc1[2] = 0x62;// dest[15:8]
  dma_desc1[3] = 0x73;// dest[7:0]
  dma_desc1[4] = (len>>8)&0xff;
  dma_desc1[5] = (len&0xff);
  dma_desc1[6] = 0x12; //wordsize=0,tmode=0,trig=0x12
  dma_desc1[7] = 0x42;//srcinc=1,destinc=0,irqmask=1,m8=0,priority=2
  writeXDATA( 0x1008, dma_desc1, 8 );
  cc_exec3( 0x75, 0xD2, 0x08);
  cc_exec3( 0x75, 0xD3, 0x10);
  // clear flash status
  readXDATA(0x6270, &res, 1);
  res &=0x1F;
  writeXDATA(0x6270, &res, 1);
  // clear DMAIRQ 0 et 1
  res = cc_exec2(0xE5, 0xD1);
  res &= ~1;
  res &= ~2;
  cc_exec3(0x75,0xD1,res);
  // disarm DMA Channel 0 et 1
  res = cc_exec2(0xE5, 0xD6);
  res &= ~1;
  res &= ~2;
  cc_exec3(0x75,0xD6,res);
  // Upload to RAM through DMA-0
  // arm DMA channel 0 :
  res = cc_exec2(0xE5, 0xD6);
  res |= 1;
  cc_exec3(0x75,0xD6,res);
  cc_delay(200);
  // transfert de données en mode burst
  cc_write(0x80|( (len>>8)&0x7) );
  cc_write(len&0xff);
  for(int i=0 ; i<len ;i++)
    cc_write(Pages[page].datas[i+Pages[page].minoffset]);
  // wait DMA end :
  do
  {
    cc_delay(100);
    res = cc_exec2(0xE5, 0xD1);
    res &= 1;
  } while (res==0);
  // Clear DMA IRQ flag
  res = cc_exec2(0xE5, 0xD1);
  res &= ~1;
  cc_exec3(0x75,0xD1,res);

  // disarm DMA Channel 1
  res = cc_exec2(0xE5, 0xD6);
  res &= ~2;
  cc_exec3(0x75,0xD6,res);
  // écrire l'adresse de destination dans FADDRH FADDRL
  offset = ((page&0xff)<<11) + Pages[page].minoffset;
  res=(offset>>2)&0xff;
  writeXDATA( 0x6271, &res,1);
  res=(offset>>10)&0xff;
  writeXDATA( 0x6272, &res,1);
  // arm DMA channel 1 :
  res = cc_exec2(0xE5, 0xD6);
  res |= 2;
  cc_exec3(0x75,0xD6,res);
  cc_delay(200);
  // lancer la copie vers la FLASH
  readXDATA(0x6270, &res, 1);
  res |= 2;
  writeXDATA(0x6270, &res, 1);
  // wait DMA end :
  int provo=0;
  do
  {
    sleep(1);
    provo++;
    if(provo >10)
    {
      fprintf(stderr,"\nflash error... Have you erased before write ?\n");
      exit(1);
    }
    res = cc_exec2(0xE5, 0xD1);
    res &= 2;
  } while (res==0);
  // vérifie qu'il n'y a pas eu de flash abort
  readXDATA(0x6270, &res, 1);
  if (res&0x20)
  {
    fprintf(stderr,"\n flash error !!!\n");
    exit(1);
  }
  
}

void helpo()
{
  fprintf(stderr,"usage : cc_write [-d pin_DD] [-c pin_DC] [-r pin_reset] file_to_flash\n"); 
  fprintf(stderr,"	-c : change pin_DC (default 27)\n");
  fprintf(stderr,"	-d : change pin_DD (default 28)\n");
  fprintf(stderr,"	-r : change reset pin (default 24)\n");
  fprintf(stderr,"	-m : change multiplier for time delay (default auto)\n");
}

int main(int argc,char *argv[])
{
  int opt;
  int rePin=24;
  int dcPin=27;
  int ddPin=28;
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
 FILE * ficin = fopen(argv[optind],"r");
  if(!ficin) { fprintf(stderr," Can't open file %s.\n",argv[optind]); exit(1); }
  // on initialise les ports GPIO et le debugger
  cc_init(rePin,dcPin,ddPin);
  if(vorte) fprintf(stderr," auto mult selected : %d\n", cc_getmult());
  if(setMult>0)
    cc_setmult(setMult);
  else // for write, higher mult is better
    cc_setmult((cc_getmult()*3)/2);
  // entrée en mode debug
  cc_enter();
  // envoi de la commande getChipID :
  uint16_t ID;
  ID = cc_getChipID();
  printf("  ID = %04x.\n",ID);

  for (int page=0 ; page<128 ; page++)
  {
    memset(Pages[page].datas,0xff,2048);
    Pages[page].minoffset=0xffff;
    Pages[page].maxoffset=0;
  }
  
  uint16_t ela=0; // extended linear address
  uint32_t sla=0; // start linear address
  // read hex file
  int line=0;
  int maxpage=0;
  while(fgets(buffer,600,ficin))
  {
   int sum=0,cksum,type;
   uint32_t addr,len;
    line++;
    if(line%10==0) { printf("\r  reading line %d.",line);fflush(stdout); }
    if(buffer[0] != ':') { fprintf(stderr,"incorrect hex file ( : missing)\n"); exit(1); }
    if(strlen(buffer)<3 ) { fprintf(stderr,"incorrect hex file ( incomplete line)\n"); exit(1); }
    if(!sscanf(buffer+1,"%02x",&len)) { fprintf(stderr,"incorrect hex file (incorrect length\n"); exit(1); }
    if(strlen(buffer)<(11 + (len * 2))) { fprintf(stderr,"incorrect hex file ( incomplete line)\n"); exit(1); }
    if(!sscanf(buffer+3,"%04x",&addr)) { fprintf(stderr,"incorrect hex file (incorrect addr)\n"); exit(1); }
    if(!sscanf(buffer+7,"%02x",&type)) { fprintf(stderr,"incorrect hex file (incorrect record type\n"); exit(1); }
    if(type == 4)
    {
      if(!sscanf(buffer+9,"%04hx",&ela)) { fprintf(stderr,"incorrect hex file (incorrect extended addr)\n"); exit(1); }
      sla=ela<<16;
      continue;
    }
    if(type == 5)
    {
      if(!sscanf(buffer+9,"%08x",&sla)) { fprintf(stderr,"incorrect hex file (incorrect extended addr)\n"); exit(1); }
      ela = sla>>16;
      continue;
    }
    if(type==1) // EOF
    {
      break;
    }
    if(type) { fprintf(stderr,"incorrect hex file (record type %d not implemented\n",type); exit(1); }
    sum = (len & 255) + ((addr >> 8) & 255) + (addr & 255) + (type & 255);
    int i;
    for( i=0 ; i<len ; i++)
    {
      if(!sscanf(buffer+9+2*i,"%02hhx",&data[i])) { fprintf(stderr,"incorrect hex file (incorrect data)\n"); exit(1); }
      sum+=data[i];
    }
    if(!sscanf(buffer+9+2*i,"%02x",&cksum)) { fprintf(stderr,"incorrect hex file line %d (incorrect checksum)\n",line); exit(1); }
    if ( ((sum & 255) + (cksum & 255)) & 255 ) { fprintf(stderr,"incorrect hex file line %d (bad checksum) %x %x\n",line,(-sum)&255,cksum); exit(1); }
    // stock datas
    int page= (sla+addr)>>11;
    if (page>maxpage) maxpage=page;
    uint16_t start=(sla+addr)&0x7ff;
    if(start+len> 2048) // some datas are for next page
    { //copy end of datas to next page
      if (page+1>maxpage) maxpage=page+1;
      memcpy(&Pages[page+1].datas[0]
		,data+2048-start,(start+len-2048));
      if(0 < Pages[page+1].minoffset) Pages[page+1].minoffset=0;
      if( (start+len-2048-1) > Pages[page].maxoffset) Pages[page].maxoffset=start+len-2048-1;
      len=2048-start;
    }
    memcpy(&Pages[page].datas[start]
		,data,len);
    if(start < Pages[page].minoffset) Pages[page].minoffset=start;
    if( (start+len-1) > Pages[page].maxoffset) Pages[page].maxoffset=start+len-1;
  }
  printf("\n  file loaded (%d lines read).\n",line);


  // activer DMA
  uint8_t conf=cc_getConfig();
  conf &= ~0x4;
  cc_setConfig(conf);
  int provo=0;
  for (int page=0 ; page <= maxpage ; page++)
  {
    provo++;
    if(Pages[page].maxoffset<Pages[page].minoffset) continue;
    printf("\rwriting page %3d/%3d.",page+1,maxpage+1);
    fflush(stdout);
    writePage(page);
    // lire les données et les vérifier
    memset(verif1,0xff,2048);
    readPage(page,verif1);
    if(verifPage(page))
    {
      printf(".");
      memset(verif2,0xff,2048);
      readPage(page,verif2);
      if(memcmp(verif1,verif2,2048))
      {
	// increase mult
        int mult=cc_getmult();
	mult= mult+mult/10+1;
        cc_setmult(mult);
        if(vorte) fprintf(stderr,"increase mult\n");
	memcpy(verif1,verif2,2048);
	if(verifPage(page)) page--;
      }
      else
        page--;
      if(provo>10)
      {
        fprintf(stderr,"verification error... Have you erased before write ?\n");
	exit(1);
      }
    }
    else
     provo=0;
  }
  printf("\n");
  if(vorte) fprintf(stderr,"\n final mult : %d\n",cc_getmult());
  printf(" flash OK.\n");

  // sortie du mode debug et désactivation :
  cc_setActive(false);
  // reboot
  cc_reset();
  fclose(ficin);

}

