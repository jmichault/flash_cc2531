---
lang: it
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: "L'essenziale!"
title: 'La stessa cosa'
---

# _flash\_cc2531_
 _flash\_cc2531_ ti consente di programmare la tua chiavetta USB CC2531 dal tuo _Raspberry_, senza la necessità di _Arduino_ o _CC Debugger_.

## Prerequisiti
Hai bisogno di _Raspberry_ o _Odroid-c2_.  
Hai bisogno di cosa connettere la porta di debug della chiave alle porte _GPIO_ di _Raspberry_, ad esempio cavo _CC_ e quattro linee _Dupont_ (vedi oltre).   
[WiringPi](http://wiringpi.com/) deve essere installato (se non è preinstallato, normalmente è possibile installarlo con `sudo apt install wiringpi`, altrimenti consultare il sito web [ _Gordon_](http://wiringpi.com/) o [questo quel sito alternativo](https://github.com/WiringPi/WiringPi)).  

Ho proiettato _flash\_cc2531_ su a _Raspberry Pi 3_ con _raspbian_, ma sono stati segnalati altri modelli per programmi riusciti:
* su pi 4, sarà necessaria la versione 2.52 di (zzz10 ): (zzz12 ) installa _il cablaggio Pi_ 2.52 dal sito web di _Gordon_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* su pi 1 e pi 2 avrai bisogno di[per usare altri pin](#uzu_aliajn_pinglojn).  




* in ogni caso probabilmente dovrai impostare l'opzione della base dei tempi ( _"-m"_ ).





## Preparato

Scarica _flash\_cc2531_ sul tuo _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Collega i seguenti pin dalla porta di debug alla porta GPIO:

1. pin 1 ( _GND_ ) -> pin 39 ( _GND_ )


2. pin 7 ( _reset_ ) -> pin 35 ( _wPi 24, BCM19_ )


3. pin 3 ( _DC_ ) -> pin 36 ( _wPi 27, BCM16_ )


4. pin 4 ( _DD_ ) -> pin 38 ( _wPi 28, BCM20_ )



e inserire la chiave USB in una porta.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


prova questo:
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


## uso
Per salvare il contenuto della memoria flash nel file save.hex:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

Per cancellare la memoria flash:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

Per programmare il file sulla chiave _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="usa_aliajn_pin"></ a>
## Usa altri pin
tutti i comandi accettano i seguenti argomenti:
* _-c_ pin: cambia pin _DC_ (default 27)
* _-d_ pin: cambia pin _DD_ )(default 28)
* _-r_ pin: cambia pin _reset_ (default 24)
* _-m_ : cambia il moltiplicatore del ritardo, e quindi il basic time (default: regolazione automatica)

la numerazione dei pin utilizzata è quella di _wiringPi_. Usa `gpio readall` per avere il layout nella tua colonna _Raspberry_ ( _wPi_).

Ad esempio, se si desidera utilizzare i pin 3, 11 e 13: 
Collegare i seguenti pin dalla porta di debug al gate _GPIO_:
1.pin 1 ( _GND_ ) ) -> ) pin 14 ( _GND_ )
2. pin 7 ( _reset_ ) -> pin 3 ( _wPi 8, BCM2_ )
3. pin 3 ( _DC_ ) -> pin 11 ( _wPi 0, BCM17_ )
4.pin 4 ( _DD_ ) -> pin 13 ( ( zzz42) wPi 2, BCM27_ )

e ora puoi leggere ID, salvare, eliminare e scrivere la memoria flash con i seguenti comandi:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## cosa succede se non funziona?

1. interrompere tutti gli altri programmi.


2. impostare la velocità del processore prima della programmazione. Esempio:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## Licenza

Questo progetto è concesso in licenza con GPL v3 (vedi _COPYING_).
