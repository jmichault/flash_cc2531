---
lang: en
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 'The essential!'
title: 'The main thing'
---

# _flash\_cc2531_
 _flash\_cc2531_ allows you to program your CC2531 USB stick from your _Raspberry_, without the need for _Arduino_ or _CC Debugger_.

## Prerequisites
You need either _Raspberry_ or _Odroid-c2_.  
You need what to connect the debug port of the key to the ports _GPIO_ of _Raspberry_, for example cable _CC_ and four lines _Dupont_ (see further).   
[WiringPi](http://wiringpi.com/) must be installed (if it is not pre-installed, you can usually install it with `sudo apt install wiringpi`, otherwise see website [ _Gordon_](http://wiringpi.com/) or [this that alternative site](https://github.com/WiringPi/WiringPi)).  

I projected _flash\_cc2531_ on a _Raspberry Pi 3_ with _raspbian_, but other models have been reported for successful programs:
* on pi 4, you will need version 2.52 of (zzz10 ): (zzz12 ) install _wiring Pi_ 2.52 from _Gordon's website_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* on pi 1 and pi 2 you will need[to use other pins](#uzu_aliajn_pinglojn).  




* anyway you will probably need to set the time base option ( _"-m"_ ).





## Prepared

Download _flash\_cc2531_ to your _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Connect the following pins from the debug port to the GPIO port:

1. pin 1 ( _GND_ ) -> pin 39 ( _GND_ )


2. pin 7 ( _reset_ ) -> pin 35 ( _wPi 24, BCM19_ )


3. pin 3 ( _DC_ ) -> pin 36 ( _wPi 27, BCM16_ )


4. pin 4 ( _DD_ ) -> pin 38 ( _wPi 28, BCM20_ )



and insert the USB key into a port.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


try this:
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


## use
To save the contents of the flash memory to the save.hex file:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

To erase flash memory:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

To program the file on the key _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="use_aliajn_pins"></ a>
## Use other pins
all commands accept the following arguments:
* _-c_ pin: change pin _DC_ (default 27)
* _-d_ pin: change pin _DD_ )(default 28)
* _-r_ pin: change pin _reset_ (default 24)
* _-m_ : change the multiplier of the delay, and therefore the basic time (default: automatic adjustment)

the pin numbering used is that of _wiringPi_. Use `gpio readall` to have the layout in your _Raspberry_ (column _wPi_).

For example, if you want to use pins 3, 11 and 13: 
Connect the following pins from debug port to gate _GPIO_:
1.pin 1 ( _GND_ ) ) -> ) pin 14 ( _GND_ )
2. pin 7 ( _reset_ ) -> pin 3 ( _wPi 8, BCM2_ )
3. pin 3 ( _DC_ ) -> pin 11 ( _wPi 0, BCM17_ )
4.pin 4 ( _DD_ ) -> pin 13 ( ( zzz42) wPi 2, BCM27_ )

and now you can read ID, save, delete and write flash memory with the following commands:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## what if it doesn't work?

1. stop all other programs.


2. set the processor speed before programming. Example:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## License

This project is licensed under the GPL v3 (see _COPYING_).
