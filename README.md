# flash_cc2531
flash CC2531 USB dongle from your Raspberry, without Arduino nor CC Debugger.

## prerequisites
A Raspberry Pi 3 with raspbian and [wiringPi](http://wiringpi.com/) installed.

## Getting Started

Download flash_cc2531 on your raspberry:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Connect the following pins of the debug port to the GPIO port :
1. pin 1 (GND)	  -->	pin 39 (GND)
2. pin 7 (reset)	-->	pin 35 (GPIO24)
3. pin 3 (DC)	  -->	pin 35 (GPIO27)
4. pin 4 (DD)	  -->	pin 35 (GPIO28)

and insert the usb dongle in a port.

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

To flash file to cc2531 :
```bash
./cc_write CC2531ZNP-Pro.hex
```
(takes around 3 minutes).


## License

This project is licensed under the GPL v3 license (see COPYING).

