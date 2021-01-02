---
lang: eo
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 'La esenca!'
title: 'La ĉefa afero'
---

# _flash\_cc2531_
 _flash\_cc2531_ permesas al vi programi vian CC2531 USB-bastonon de via _Raspberry_, sen bezono de _Arduino_ aŭ _CC Debugger_.

## Antaŭkondiĉoj
Vi bezonas aŭ _Raspberry_ aŭ _Odroid-c2_.  
Vi bezonas kion por konekti la elpurigan havenon de la ŝlosilo al la havenoj _GPIO_ de _Raspberry_, ekzemple kablo _CC_ kaj kvar linioj _Dupont_ (vidu plu).   
[WiringPi](http://wiringpi.com/) devas esti instalita (se ĝi ne estas antaŭinstalita, vi kutime povas instali ĝin per `sudo apt install wiringpi`, alie vidu retejon [ _Gordon_](http://wiringpi.com/) aŭ [ĉi tiu alternativa retejo](https://github.com/WiringPi/WiringPi)).  

Mi projektis _flash\_cc2531_ sur a _Raspberry Pi 3_ kun _raspbian_, sed pri sukcesaj programoj oni raportis pri aliaj modeloj:
* sur pi 4, vi bezonos version 2.52 de (zzz10 ):  [instalu _drataron Pi_ 2.52 de _retejo de Gordon_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* sur pi 1 kaj pi 2 vi bezonos[uzi aliajn pinglojn](#uzu_aliajn_pinglojn).  



* ĉiuokaze vi probable bezonos agordi la tempan bazan opcion ( _"-m"_ ).




## Preparado

Elŝutu _flash\_cc2531_ al via _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Konektu la jenajn pinglojn de la debug-haveno al la GPIO-haveno:

1. pinglo 1 ( _GND_ ) -> pinglo 39 ( _GND_ )

2. pinglo 7 ( _reset_ ) -> pinglo 35 ( _wPi 24, BCM19_ )

3. pinglo 3 ( _DC_ ) -> pinglo 36 ( _wPi 27, BCM16_ )

4. pinglo 4 ( _DD_ ) -> pinglo 38 ( _wPi 28, BCM20_ )


kaj enmetu la USB-ŝlosilon en havenon.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


provu per ĉi tio:
```bash
cd flash_cc2531
./cc_chipid
```
Ça doit retourner:
```
  ID = b524.
```
Si vous voyez 0000 ou ffff quelque chose ne va pas:
* vérifiez d'abord votre câblage.
* puis essayez un temps de base plus élevé, par exemple avec `./cc_chipid -m 100`, ou `./cc_chipid -m 160` ou `./cc_chipid -m 300`.
* si rien de tout cela ne fonctionne, essayez de recompiler avec `make`.


## uzi
Pour enregistrer le contenu de la mémoire flash dans le fichier save.hex:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

Por viŝi flash-memoron:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

Por programi la dosieron sur la ŝlosilo _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="uzu_aliajn_pinglojn"></ a>
## Uzu aliajn pinglojn
ĉiuj komandoj akceptas la jenajn argumentojn:
* _-c_ pinglo: ŝanĝi pinglon _DC_ (defaŭlte 27)
* _-d_ pinglo: ŝanĝi pinglon _DD_ )(defaŭlta 28)
* _-r_ pinglo: ŝanĝi pinglon _reset_ (defaŭlte 24)
* _-m_ : ŝanĝi la multiplikanton de la malfruo, kaj do la baza tempo (defaŭlte: aŭtomata ĝustigo)

la pingla numerado uzata estas tiu de _wiringPi_. Uzu `gpio readall` por havi la aranĝon en via _Raspberry_ (kolumno _wPi_).

Ekzemple, se vi volas uzi pinglojn 3, 11 kaj 13: 
Konektu la jenajn pinglojn de debughaveno al pordego _GPIO_:
1.pino 1 ( _GND_ ) ) -> pinglo 14 ( _GND_ )
2. pinglo 7 ( _reset_ ) -> pinglo 3 ( _wPi 8, BCM2_ )
3. pinglo 3 ( _DC_ ) -> pinglo 11 ( _wPi 0, BCM17_ )
4.pin 4 ( _DD_ ) -> pinglo 13 ( )_wPi 2, BCM27_ )

kaj nun vi povas legi identigilon, konservi, forigi kaj skribi flash-memoron per la jenaj komandoj:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## kio se ĝi ne funkcias?

1. ĉesu ĉiujn aliajn programojn.

2. agordi la rapidon de la procesoro antaŭ programado. Ekzemplo:  

```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  

```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.


## Permesilo

Ĉi tiu projekto estas rajtigita laŭ GPL v3 (vidu _COPYING_).
