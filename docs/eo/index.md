---
lang: eo
lang-niv: homa
lang-ref: 001-ĉefa-afero
layout: page
slug: 'La esenca!'
title: 'La ĉefa afero'
---

# _flash\_cc2531_
 _flash\_cc2531_ permesas al vi programi vian CC2531 USB-bastonon de via _Raspberry_, sen bezono aŭ de _Arduino_ aŭ de _CC Debugger_.

## Antaŭkondiĉoj
Vi bezonas aŭ _Raspberry_ aŭ _Odroid-c2_.  
Vi bezonas kion por konekti la elpurigan havenon de la ŝlosilo al la havenoj _GPIO_ de _Raspberry_, ekzemple unu kablo _CC_ kaj kvar linioj _Dupont_ (vidu plu).   
[ _WiringPi_ ](http://wiringpi.com/) devas esti instalita (se ĝi ne estas antaŭinstalita, vi kutime povas instali ĝin per `sudo apt install wiringpi`), alie vidu [la retejon de _Gordon_ ](http://wiringpi.com/) aŭ [ĉi tiun alternativan retejon](https://github.com/WiringPi/WiringPi)).  

Mi projektis _flash\_cc2531_ sur _Raspberry Pi 3_ kun _raspbian_, sed sukcesa programado estis raportita pri aliaj modeloj:  
 * sur pi 4 vi bezonos version 2.52 de _wiringpi_ :  [instalu _wiringPi_ 2.52 de _Gordon_ ](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)retejo


 * sur pi 1 kaj pi 2 vi bezonos [uzi aliajn pinglojn](#uzi_aliajn_pinglojn).

 * ĉiuokaze vi probable bezonos agordi la tempan bazan opcion ( _"-m"_ ).


## Preparado

Elŝutu _flash\_cc2531_ al via _raspberry_ :
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```

Konektu la jenajn pinglojn de la debug-haveno al la GPIO-haveno:

 1. pinglo 1 ( _GND_ ) -> pinglo 39 ( _GND_ )

 2. pinglo 7 ( _reset_ ) -> pinglo 35 ( _wPi 24, BCM19_ )

 3. pinglo 3 ( _DC_ ) -> pinglo 36 ( _wPi 27, BCM16_ )

 4. pinglo 4 ( _DD_ ) -> pinglo 38 ( _wPi 28, BCM20_ )


kaj enmetu la USB-ŝlosilon en havenon.

Elŝuta kablo _CC_ kaj 4 linioj _Dupont_ ino al ino estas perfektaj por ĉi tiu celo:
![foto de la ŝlosilo kaj la _raspberry_ ](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
Ĉi tiu estas mia plej ŝatata opcio, sed se vi ne havas kablon _CC_ vi ankaŭ povas rekte luti la kablojn _Dupont_ sur la ŝlosilo: vidu ekzemple la retejon [ _lemariva.com_ ](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) aŭ [ _notenoughtech.com_ ](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


provu per ĉi tio:
```bash
cd flash_cc2531
./cc_chipid
```
Ĝi devas reveni:
```
  ID = b524.
```
Se vi vidas 0000 aŭ ffff io fiaskas:  
 * unue kontrolu vian kabligon.

 * tiam provu pli altan bazan tempon, ekzemple kun `./cc_chipid -m 100`, aŭ `./cc_chipid -m 160` aŭ `./cc_chipid -m 300`.

 * se neniu el tio funkcias, provu rekompili kun `make`.



## uzado
Por konservi la enhavon de la fulmmemoro en la dosiero save.hex:
```bash
./cc_read save.hex
```
(daŭras ĉirkaŭ 1 minuton).

Por viŝi fulmmemoron:
```bash
./cc_erase
```
**Noto:** Vi **devas** forviŝi antaŭ skribado (krom se vi vere scias, kion vi faros).

Por programi la dosieron sur la ŝlosilo _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(daŭras ĉirkaŭ 3 minutojn).

<a id="uzi_aliajn_pinglojn"></a>
## Uzi aliajn pinglojn

ĉiuj ordonoj akceptas la jenajn argumentojn:

 * _-c_ pinglo: ŝanĝu la pinglon _DC_ (defaŭlte 27)

 * _-d_ pinglo: ŝanĝu la pinglon _DD_ (defaŭlte 28)

 * _-r_ pinglo: ŝanĝu la pinglon _reset_ (defaŭlte 24)

 * _-m_ : ŝanĝu la prokrastan multiplikaton, kaj do la bazan tempon (defaŭlte: aŭtomata ĝustigo)


la pinglonumerado uzata estas tiu de _wiringPi_. Uzu `gpio readall` por havi la aranĝon en via _Raspberry_ (kolumno _wPi_ ).

Ekzemple, se vi volas uzi pinglojn 3, 11 kaj 13:  
Konekti la jenajn pinglojn de elpuriga haveno al pordo _GPIO_:

 1. pinglo 1 ( _GND_ ) -> pinglo 14 ( _GND_ )

 2. pinglo 7 ( _reset_ ) -> pinglo 3 ( _wPi 8, BCM2_ )

 3. pinglo 3 ( _DC_ ) -> pinglo 11 ( _wPi 0, BCM17_ )

 4. pinglo 4 ( _DD_ ) -> pinglo 13 ( _wPi 2, BCM27_ )


kaj nun vi povas legi identigilon, konservi, forigi kaj skribi fulmmemoron per la jenaj komandoj:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vi ankaŭ povas ŝanĝi la defaŭltajn valorojn en _CCDebugger.h_ kaj kompili la programojn per `make`.

## kio se ĝi ne funkcias?

1. ĉesu ĉiujn aliajn programojn.

2. agordu la rapidon de la procesoro antaŭ programado. Ekzemplo:

   ```bash
   sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
   ```
3. uzu la opcion -m por pliigi la uzatajn tempolimojn. Ekzemplo:

   ```bash
   ./cc_write -m 300 CC2531ZNP-Prod.hex
   ```
4. rekompili la programon per `make`.


## Permesilo

Ĉi tiu projekto estas rajtigita laŭ GPL v3 ( vidu _COPYING_ ).
