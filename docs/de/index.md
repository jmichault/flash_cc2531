---
lang: de
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 'Das Essenzielle!'
title: 'Die Hauptsache'
---

# _flash\_cc2531_
Mit _flash\_cc2531_ können Sie Ihren CC2531 USB-Stick von Ihrem _Raspberry_aus programmieren, ohne dass Sie _Arduino_ oder _CC Debugger_benötigen.

## Voraussetzungen
Sie benötigen entweder _Raspberry_ oder _Odroid-c2_.  
Sie benötigen, um den Debug-Port des Schlüssels mit den Ports _GPIO_ von _Raspberry_zu verbinden, z. B. Kabel _CC_ und vier Leitungen _Dupont_ (, siehe weiter10 °).   
[WiringPi](http://wiringpi.com/) muss installiert sein (Wenn es nicht vorinstalliert ist, können Sie es normalerweise mit `sudo apt install wiringpi`installieren, andernfalls siehe Website [ _Gordon_](http://wiringpi.com/) oder [diese alternative Stelle](https://github.com/WiringPi/WiringPi)).  

Ich habe _flash\_cc2531_ auf _Raspberry Pi 3_ mit _raspbian_projiziert, aber bei anderen Modellen wurde über erfolgreiche Programmierung berichtet:
* auf pi 4, Sie benötigen Version 2.52 von10 °):  [Installation _Verkabelung Pi_ 2,52 von _Gordons Website_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* auf pi 1 und pi 2 benötigen Sie [, um andere Stifte](#uzi_aliajn_pinglojn)zu verwenden.  

* Wahrscheinlich müssen Sie jedoch die Zeitbasisoption ( _"-m"_ )einstellen.



## Bereit

Laden Sie _flash\_cc2531_ auf Ihre _raspberry_herunter:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Verbinden Sie die folgenden Pins vom Debugging-Port mit dem GPIO-Port:
1. Pin 1 ( _GND_ ) -> Pin 39 ( _GND_ )
zweiter Stift 7 ( _reset_ ) -> Stift 35 ( _wPi 24, BCM19_ ))
3. Spindel 3 ( _DC_ ) -> Stift 36 ( _wPi 27, BCM16_ )
4. Spindel 4 ( _DD_ ) -> Spindel 38 ( _wPi 28, BCM20_ )

und stecken Sie den USB-Stick in einen Anschluss.

Download-Kabel _CC_ und 4 Leitungen _Dupont_ von Frau zu Frau sind perfekt für diesen Zweck:
![Foto des Schlüssels und der _Himbeere_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)°)
Dies ist meine Lieblingswahl, aber wenn Sie kein Kabel haben _CC_ , können Sie die Kabel _Dupont_ auch direkt auf den Schlüssel löten: siehe zum Beispiel die Website [ )_mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) oder [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


versuchen Sie dies:
```bash
cd flash_cc2531
./cc_chipid
```
Es muss zurückkehren:
```
  ID = b524.
```
Wenn Sie 0000 oder ffff sehen, stimmt etwas nicht:
* Überprüfen Sie zuerst Ihre Verkabelung.
* versuchen Sie dann eine höhere Basiszeit, zum Beispiel mit `./cc_chipid -m 100`oder `./cc_chipid -m 160` oder `./cc_chipid -m 300`.
* Wenn nichts davon funktioniert, versuchen Sie es erneut mit `make`.


## verwenden
So speichern Sie den Inhalt des Flash-Speichers in der Datei save.hex:
```bash
./cc_read save.hex
```
(dauert ca. 1 Minute).

So löschen Sie den Flash-Speicher:
```bash
./cc_erase
```
**Hinweis:** Sie **müssen** vor dem Schreiben löschen (, es sei denn, Sie wissen wirklich, was Sie tun werden).

So programmieren Sie die Datei auf der Taste _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dauert ca. 3 Minuten).

<a id ="Verwenden Sie_aliajn_Stifte"></ a>
## Verwenden Sie andere Stifte
Alle Befehle akzeptieren die folgenden Argumente:
* _-c_ Stift: Ändern Sie den Stift _DC_ (standardmäßig 27)
* _-d_ Stift: Stift wechseln _DD_ )(Standard 28)
* _-r_ Stift: Stift wechseln _reset_ (standardmäßig 24)
* _-m_ : Ändern Sie standardmäßig den Multiplikator der Verzögerung und damit die Basiszeit (: automatische Einstellung)

Die verwendete Pin-Nummerierung ist die von _wiringPi_. Verwenden Sie `gpio readall` , um das Layout in Ihrer Spalte _Raspberry_ ( _wPi_)anzuzeigen.

Wenn Sie beispielsweise die Stifte 3, 11 und 13 verwenden möchten:  
Verbinden Sie die folgenden Pins von einem Debugging-Port mit einem Gate _GPIO_:
1. Pin 1 ( _GND_ ) -> Pin 14 ( )_GND_ )
2. Stift 7 ( _reset_ ) -> Stift 3 ( _wPi 8, BCM2_ )
3. Pin 3 ( _DC_ ) -> Pin 11 ( _wPi 0, BCM17_ )
4. Stift 4 ( _DD_ ) -> Stift 13 ( )_wPi 2, BCM27_ )

und jetzt können Sie ID lesen, speichern, löschen und Flash-Speicher mit den folgenden Befehlen schreiben:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Sie können auch die Standardwerte in _CCDebugger.h_ ändern und die Programme mit `make`kompilieren.

## Was ist, wenn es nicht funktioniert?

1. Stoppen Sie alle anderen Programme.

2. Stellen Sie die Prozessorgeschwindigkeit vor dem Programmieren ein. Beispiel:  

```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. Verwenden Sie die Option -m, um die verwendeten Zeitlimits zu erhöhen. Beispiel:  

```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. Kompilieren Sie das Programm erneut mit `make`.



## Lizenz

Dieses Projekt ist unter der GPL v3 (lizenziert (siehe 2 °).
