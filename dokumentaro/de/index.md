---
lang: de
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 'Das Essenzielle!'
title: 'Die Hauptsache'
---

# _flash\_cc2531_
Mit _flash\_cc2531_ können Sie Ihren CC2531-USB-Stick von Ihrem _Raspberry_aus programmieren, ohne _Arduino_ oder _CC Debugger_zu benötigen.

## Voraussetzungen
Sie benötigen entweder _Raspberry_ oder _Odroid-c2_.  
Sie benötigen, um den Debug-Port des Schlüssels mit den Ports _GPIO_ von _Raspberry_zu verbinden, z. B. Kabel _CC_ und vier Leitungen _Dupont_ (, siehe weiter).   
[WiringPi](http://wiringpi.com/) muss installiert sein (. Wenn es nicht vorinstalliert ist, können Sie es normalerweise mit `sudo apt install wiringpi`installieren, andernfalls siehe Website [ _Gordon_](http://wiringpi.com/) oder [diese alternative Seite](https://github.com/WiringPi/WiringPi)).  

Ich habe _flash\_cc2531_ mit _raspbian_auf ein _Raspberry Pi 3_ projiziert, aber für erfolgreiche Programme wurden andere Modelle gemeldet:
* auf pi 4 benötigen Sie Version 2.52 von (zzz10 ):  [) Installieren Sie die _Verkabelung Pi_ 2.52 von _Gordons Website_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* Auf pi 1 und pi 2 benötigen Sie[, um andere Pins](#uzu_aliajn_pinglojn)zu verwenden.  




* Auf jeden Fall müssen Sie wahrscheinlich die Zeitbasisoption ( _"-m"_ )einstellen.





## Bereit

Laden Sie _flash\_cc2531_ auf Ihr _raspberry_herunter:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Verbinden Sie die folgenden Pins vom Debug-Port mit dem GPIO-Port:

1. Pin 1 ( _GND_ ) -> Pin 39 ( _GND_ )


2. Pin 7 ( _reset_ ) -> Pin 35 ( _wPi 24, BCM19_ )


3. Pin 3 ( _DC_ ) -> Pin 36 ( _wPi 27, BCM16_ )


4. Pin 4 ( _DD_ ) -> Pin 38 ( _wPi 28, BCM20_ )



und stecken Sie den USB-Stick in einen Anschluss.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


versuche dies:
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


## verwenden
So speichern Sie den Inhalt des Flash-Speichers in der Datei save.hex:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

So löschen Sie den Flash-Speicher:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

So programmieren Sie die Datei auf dem Schlüssel _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="benutze_aliajn_Stifte"></ a>
## Verwenden Sie andere Stifte
Alle Befehle akzeptieren die folgenden Argumente:
* _-c_ Pin: Pin ändern _DC_ (Standard 27)
* _-d_ Pin: Pin ändern _DD_ )(Standard 28)
* _-r_ Pin: Pin _reset_ (ändern Standard 24)
* _-m_ : Ändern Sie den Multiplikator der Verzögerung und damit den Basiswert Zeit (Standard: automatische Anpassung)

Die verwendete Pin-Nummerierung ist die von _wiringPi_. Verwenden Sie `gpio readall` , um das Layout in Ihrer Spalte _Raspberry_ ( _wPi_)zu haben.

Wenn Sie beispielsweise die Pins 3, 11 und 13 verwenden möchten: 
Verbinden Sie die folgenden Pins vom Debug-Port mit dem Gate _GPIO_:
1. Pin 1 ( _GND_ ) ) -> ) Pin 14 ( _GND_ )
2. Pin 7 ( _reset_ ) -> Pin 3 ( _wPi 8, BCM2_ )
3. Pin 3 ( _DC_ ) -> Pin 11 ( _wPi 0, BCM17_ )
4.pin 4 ( _DD_ ) -> Pin 13 ( ( zzz42) wPi 2, BCM27_ )

und jetzt können Sie ID lesen, Flash-Speicher speichern, löschen und mit den folgenden Befehlen schreiben:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## Was ist, wenn es nicht funktioniert?

1. Stoppen Sie alle anderen Programme.


2. Stellen Sie die Prozessorgeschwindigkeit vor dem Programmieren ein. Beispiel:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## Lizenz

Dieses Projekt ist unter der GPL v3 (lizenziert (siehe _COPYING_)).
