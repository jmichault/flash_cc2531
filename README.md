# flash_cc2531
flash CC2531 USB dongle from your Raspberry, without Arduino nor CC Debugger.

## prerequisites
You need a Raspberry with [wiringPi](http://wiringpi.com/) installed.  
I have designed flash_cc2531 on a Raspberry Pi 3 with raspbian, but successful flashes have been reported on pi 1 and pi 2 : see sections [use other pins](#use-other-pins) and [what to try if it doesn't work](#what-to-try-if-it-doesnt-work).

## Getting Started

Download flash_cc2531 on your raspberry:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Connect the following pins of the debug port to the GPIO port :
1. pin 1 (GND)	  -->	pin 39 (GND)
2. pin 7 (reset)	-->	pin 35 (wPi 24, BCM19)
3. pin 3 (DC)	  -->	pin 36 (wPi 27, BCM16)
4. pin 4 (DD)	  -->	pin 38 (wPi 28, BCM20)

and insert the usb dongle in a port.

A downloader cable CC and 4 Dupont line Female to Female are perfect for this purpose :

![](https://github.com/jmichault/files/blob/master/Raspberry-CC2531.jpg)

test by running :
```bash
cd flash_cc2531
./cc_chipid
```
it should return :
```
  ID = b524.
```
If you see 0000 or ffff, something is wrong and you should probably check your wiring.

## Usage
To save the content of the flash to save.hex file :
```bash
./cc_read save.hex
```
(takes around 1 minute).

To erase the flash :
```bash
./cc_erase
```
**Note :** You **must** erase before writing.

To flash file to cc2531 :
```bash
./cc_write CC2531ZNP-Pro.hex
```
(takes around 3 minutes).

## Use other pins
all commands accept following arguments :
```bash
        -c pin : change pin_DC (default 27)
	-d pin : change pin_DD (default 28)
	-r pin : change reset pin (default 24)
  	-m : change multiplier for time delay (default auto)
```
the pin numbering used is that of wiringPi. Use "gpio readall" to have the layout on your pi (wPi column).

example, if you want to use pins 3, 11 and 13 : 
Connect the following pins of the debug port to the GPIO port :
1. pin 1 (GND)	  -->	pin 14 (GND)
2. pin 7 (reset)	-->	pin 3 (wPi 8, BCM2)
3. pin 3 (DC)	  -->	pin 11 (wPi 0, BCM17)
4. pin 4 (DD)	  -->	pin 13 (wPi 2, BCM27)

and now you can read chip id, save flash content, erase flash, and write flash with following commands :
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Pro.hex
```

You can also change default values in CCDebugger.h and recompile executables with make.

## what to try if it doesn't work?
1. stop all other programs before flash.
2. fix the cpu speed before flash. Example :
```bash
sudo bash
echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
exit
```
3. use the -m option to increase time delays used. Example :
```bash
./cc_write -m 300 CC2531ZNP-Pro.hex
```
4. executables are compiled on my raspbian distribition, you can try to recompile for your distribution with make.

## License

This project is licensed under the GPL v3 license (see COPYING).

