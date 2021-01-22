---
lang: en
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 'The essential!'
title: 'The main thing'
---

# _flash\_cc2531_
 _flash\_cc2531_ allows you to program your CC2531 USB stick from yours _Raspberry_, without the need for either _Arduino_ or _CC Debugger_.

## Prerequisite
You need either _Raspberry_ or _Odroid-c2_.  
You need what to connect the debug port of the key to the ports _GPIO_ of _Raspberry_, for example one cable _CC_ and four lines _Dupont_ (see further).   
[ _WiringPi_ ](http://wiringpi.com/) must be installed \(if it is not pre-installed, you can usually install it with `sudo apt install wiringpi`), otherwise see [the site of _Gordon_ ](http://wiringpi.com/) or [this alternative site](https://github.com/WiringPi/WiringPi) \).  
Finally you need the program:

* generally zigbee coordinator: [ version 1.2 (recommended)](https://github.com/Koenkk/Z-Stack-firmware/raw/master/coordinator/Z-Stack_Home_1.2/bin/default/) or [version 3.0](https://github.com/Koenkk/Z-Stack-firmware/tree/master/coordinator/Z-Stack_3.0.x/bin)


* or zigbee router: [zigbee router 1.2](https://github.com/Koenkk/Z-Stack-firmware/tree/master/router/CC2531/bin)




I projected _flash\_cc2531_ on _Raspberry Pi 3_ with _raspbian_, but successful programming was reported on other models:  
 * on pi 4 you will need version 2.52 of _wiringpi_ :  [install _wiringPi_ 2.52 of _Gordon_ ](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)website



 * on pi 1 and pi 2 you will need [to use other pins](#uzi_aliajn_pinglojn).


 * however, you will probably need to set the time base option ( _"-m"_ ).



## Preparation

Download _flash\_cc2531_ to your _raspberry_ :
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```

Connect the following pins from the debug port to the GPIO port:

 1. pin 1 ( _GND_ ) -> pin 39 ( _GND_ )


 2. pin 7 ( _reset_ ) -> pin 35 ( _wPi 24, BCM19_ )


 3. pin 3 ( _DC_ ) -> pin 36 ( _wPi 27, BCM16_ )


 4. pin 4 ( _DD_ ) -> pin 38 ( _wPi 28, BCM20_ )



and insert the USB key into a port.

Download cable _CC_ and 4 lines _Dupont_ Female to Female are perfect for this purpose:
![photo of the key and the _raspberry_ ](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
This is my favorite option, but if you don't have a cable _CC_ you can also directly solder the cables _Dupont_ on the key: see for example the website [ _lemariva.com_ ](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) or [ _notenoughtech.com_ ](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger )


try this:
```bash
cd flash_cc2531
./cc_chipid
```
It must return:
```
  ID = b524.
```
If you see 0000 or ffff something fails:  
 * first check your wiring.


 * then try a higher base time, for example with `./cc_chipid -m 100`, or `./cc_chipid -m 160` or `./cc_chipid -m 300`.


 * if none of this works, try recompiling with `make`.




## usage
To save the contents of the flash memory to the save.hex file:
```bash
./cc_read save.hex
```
(lasts about 1 minute).

To clear a flash memory:
```bash
./cc_erase
```
**Note:** You **must** delete before writing (unless you really know what you are going to do).

To program the file _CC2531ZNP-Prod.hex_ on the key _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(lasts about 3 minutes).

<a id="uzi_aliajn_pinglojn"></a>
lasts about 3 minutes"._
## Use other pins

all commands accept the following arguments:

 * _-c_ pin: change the pin _DC_ (by default 27)


 * _-d_ pin: change the pin _DD_ (by default 28)


 * _-r_ pin: change the pin _reset_ (by default 24)


 * _-m_ : change the delay multiplier, and therefore the base time (by default: automatic adjustment)



the pin numbering used is that of _wiringPi_. Use `gpio readall` to have the layout in your _Raspberry_ (column _wPi_ ).

For example, if you want to use pins 3, 11 and 13:  
Connect the following pins from a debug port to a door _GPIO_:

 1. pin 1 ( _GND_ ) -> pin 14 ( _GND_ )


 2. pin 7 ( _reset_ ) -> pin 3 ( _wPi 8, BCM2_ )


 3. pin 3 ( _DC_ ) -> pin 11 ( _wPi 0, BCM17_ )


 4. pin 4 ( _DD_ ) -> pin 13 ( _wPi 2, BCM27_ )



and now you can read ID, save, delete and write flash memory with the following commands:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

You can also change the default values ​​to _CCDebugger.h_ and compile the programs with `make`.

## what if it doesn't work?

1. stop all other programs.


2. set the processor speed before programming. Example:


   ```bash
   sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
   ```
3. use the -m option to increase the time limits used. Example:


   ```bash
   ./cc_write -m 300 CC2531ZNP-Prod.hex
   ```
4. recompile the program with `make`.



## License

This project is licensed under the GPL v3 ( see _COPYING_ ).
