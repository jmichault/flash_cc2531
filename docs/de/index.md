---
lang: de
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 'Das Essenzielle!'
title: 'Die Hauptsache'
---

# _flash\_cc2531_
Mit _flash\_cc2531_ können Sie Ihren CC2531-USB-Stick von Ihrem _Raspberry_aus programmieren, ohne dass Sie _Arduino_ oder _CC Debugger_benötigen.

## Voraussetzung
Sie benötigen entweder _Raspberry_ oder _Odroid-c2_.  
Sie benötigen, um den Debug-Port des Schlüssels mit den Ports _GPIO_ von _Raspberry_zu verbinden, z. B. ein Kabel _CC_ und vier Leitungen _Dupont_ (, siehe weiter).   
[ _WiringPi_ ](http://wiringpi.com/) muss installiert werden \(Wenn es nicht vorinstalliert ist, können Sie es normalerweise mit `sudo apt install wiringpi`)installieren, andernfalls siehe [die Stelle von _Gordon_ ](http://wiringpi.com/) oder [dieser alternativen Stelle](https://github.com/WiringPi/WiringPi) \).  
Schließlich benötigen Sie das Programm:

* allgemein ZigBee-Koordinator: [ Version 1.2 (empfohlen)](https://github.com/Koenkk/Z-Stack-firmware/raw/master/coordinator/Z-Stack_Home_1.2/bin/default/) oder [Version 3.0](https://github.com/Koenkk/Z-Stack-firmware/tree/master/coordinator/Z-Stack_3.0.x/bin)


* oder ZigBee-Router: [ZigBee-Router 1,2](https://github.com/Koenkk/Z-Stack-firmware/tree/master/router/CC2531/bin)




Ich habe _flash\_cc2531_ auf _Raspberry Pi 3_ mit _raspbian_projiziert, aber bei anderen Modellen wurde über erfolgreiche Programmierung berichtet:  
 * auf pi 4 benötigen sie version 2.52 von _wiringpi_ :  [install _wiringPi_ 2.52 von _Gordon_ ](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)website



 * auf pi 1 und pi 2 benötigen Sie [, um andere Stifte](#uzi_aliajn_pinglojn)zu verwenden.


 * Wahrscheinlich müssen Sie jedoch die Zeitbasisoption ( _"-m"_ )einstellen.



## Bereit

Laden Sie _flash\_cc2531_ auf Ihre _raspberry_ herunter:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```

Verbinden Sie die folgenden Pins vom Debug-Port mit dem GPIO-Port:

 1. Pin 1 ( _GND_ ) -> Pin 39 ( _GND_ )


 2. Pin 7 ( _reset_ ) -> Pin 35 ( _wPi 24, BCM19_ )


 3. Pin 3 ( _DC_ ) -> Pin 36 ( _wPi 27, BCM16_ )


 4. Pin 4 ( _DD_ ) -> Pin 38 ( _wPi 28, BCM20_ )



und stecken Sie den USB-Stick in einen Anschluss.

Download-Kabel _CC_ und 4 Leitungen _Dupont_ von Buchse zu Buchse eignen sich perfekt für diesen Zweck:
![Foto des Schlüssels und des _raspberry_ ](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg))
Dies ist meine Lieblingsoption, aber wenn Sie kein Kabel _CC_ haben, können Sie die Kabel _Dupont_ auch direkt auf den Schlüssel löten: siehe zum Beispiel die Website [ _lemariva.com_ ](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) oder [ _notenoughtech.com_ ](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger )


versuchen Sie dies:
```bash
cd flash_cc2531
./cc_chipid
```
Es muss zurückkehren:
```
  ID = b524.
```
Wenn Sie 0000 oder ffff sehen, schlägt etwas fehl:  
 * Überprüfen Sie zuerst Ihre Verkabelung.


 * Versuchen Sie dann eine höhere Basiszeit, zum Beispiel mit `./cc_chipid -m 100`oder `./cc_chipid -m 160` oder `./cc_chipid -m 300`.


 * Wenn dies nicht funktioniert, versuchen Sie es erneut mit `make`.




## Verwendung
So speichern Sie den Inhalt des Flash-Speichers in der Datei save.hex:
```bash
./cc_read save.hex
```
(dauert ca. 1 Minute).

So löschen Sie einen Flash-Speicher:
```bash
./cc_erase
```
**Hinweis:** Sie **müssen** vor dem Schreiben löschen (, es sei denn, Sie wissen wirklich, was Sie tun werden).

So programmieren Sie die Datei _CC2531ZNP-Prod.hex_ auf der Taste _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dauert ca. 3 Minuten).

<a id="uzi_aliajn_pinglojn"></a>
dauert ca. 3 Minuten"._
## Verwenden Sie andere Stifte

Alle Befehle akzeptieren die folgenden Argumente:

 * _-c_ Stift: Ändern Sie den Stift _DC_ (standardmäßig um 27)


 * _-d_ Stift: Ändern Sie den Stift _DD_ (standardmäßig 28)


 * _-r_ Stift: Ändern Sie den Stift _reset_ (standardmäßig um 24)


 * _-m_ : Ändern Sie standardmäßig den Verzögerungsmultiplikator und damit die Basiszeit (: automatische Anpassung)



Die verwendete Pin-Nummerierung ist die von _wiringPi_. Verwenden Sie `gpio readall` , um das Layout in Ihrer Spalte _Raspberry_ ( _wPi_ )anzuzeigen.

Wenn Sie beispielsweise die Stifte 3, 11 und 13 verwenden möchten:  
Verbinden Sie die folgenden Stifte von einem Debug-Port mit einer Tür _GPIO_:

 1. Pin 1 ( _GND_ ) -> Pin 14 ( _GND_ )


 2. Pin 7 ( _reset_ ) -> Pin 3 ( _wPi 8, BCM2_ )


 3. Pin 3 ( _DC_ ) -> Pin 11 ( _wPi 0, BCM17_ )


 4. Pin 4 ( _DD_ ) -> Pin 13 ( _wPi 2, BCM27_ )



und jetzt können Sie ID lesen, speichern, löschen und Flash-Speicher mit den folgenden Befehlen schreiben:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Sie können auch die Standardwerte auf _CCDebugger.h_ ändern und die Programme mit `make`kompilieren.

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

Dieses Projekt ist unter der GPL v3 ( lizenziert, siehe _COPYING_ ).
