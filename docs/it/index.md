---
lang: it
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: "L'essenziale!"
title: 'La stessa cosa'
---

# _flash\_cc2531_
 _flash\_cc2531_ ti permette di programmare la tua chiavetta USB CC2531 dalla tua _Raspberry_, senza bisogno di _Arduino_ o _CC Debugger_.

## Prerequisiti
È necessario _Raspberry_ o _Odroid-c2_.  
È necessario cosa collegare la porta di debug della chiave alle porte _GPIO_ di _Raspberry_, ad esempio cavo _CC_ e quattro linee _Dupont_ (vedi oltre).   
[CablaggioPi](http://wiringpi.com/) deve essere installato (se non è preinstallato, normalmente è possibile installarlo con `sudo apt install wiringpi`, altrimenti vedi sito web [ _Gordon_](http://wiringpi.com/) o [questo sito alternativo](https://github.com/WiringPi/WiringPi)).  

Ho proiettato _flash\_cc2531_ su _Raspberry Pi 3_ con _raspbian_, ma la corretta programmazione è stata riportata su altri modelli:  
 * su pi 4 sarà necessaria la versione 2.52 di _wiringpi_ :  [installa _cablaggio Pi_ 2.52 del _sito web di Gordon_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)



 * su pi 1 e pi 2 avrai bisogno di [per usare altri pin](#uzi_aliajn_pinglojn).


 * tuttavia, probabilmente sarà necessario impostare l'opzione della base dei tempi ( _"-m"_ ).



## Preparato

Scarica _flash\_cc2531_ nel tuo _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```

Collega i seguenti pin dalla porta di debug alla porta GPIO:

 1. perno 1 ( _GND_ ) -> perno 39 ( _GND_ )


 2. perno 7 ( _reset_ ) -> perno 35 ( _wPi 24, BCM19_ )


 3. perno 3 ( _DC_ ) -> perno 36 ( _wPi 27, BCM16_ )


 4. perno 4 ( _DD_ ) -> perno 38 ( _wPi 28, BCM20_ )



e inserire la chiave USB in una porta.

Il cavo di download _CC_ e 4 linee _Dupont_ Femmina a Femmina sono perfette per questo scopo:
![foto della chiave e _lampone_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)°)
Questa è la mia scelta preferita, ma se non hai un cavo _CC_ puoi anche saldare i cavi _Dupont_ direttamente sulla chiave: vedi ad esempio il sito web [ )_lemariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) o [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


prova questo:
```bash
cd flash_cc2531
./cc_chipid
```
Deve tornare:
```
  ID = b524.
```
Se vedi 0000 o ffff qualcosa non funziona:  
 * prima controlla il tuo cablaggio.


 * quindi provare un tempo base più alto, ad esempio con `./cc_chipid -m 100`, o `./cc_chipid -m 160` o `./cc_chipid -m 300`.


 * se niente di tutto questo funziona, prova a ricompilare con `make`.




## utilizzo
Per salvare il contenuto della memoria flash nel file save.hex:
```bash
./cc_read save.hex
```
(dura circa 1 minuto).

Per cancellare una memoria flash:
```bash
./cc_erase
```
**Nota:** Devi **cancellare** prima di scrivere (a meno che tu non sappia veramente cosa intendi fare).

Per programmare il file sulla chiave _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dura circa 3 minuti).

<a id ="utilizzare_aliajn_perni"></ a>
## Usa altri pin

tutti i comandi accettano i seguenti argomenti:

 * _-c_ pin: cambia il pin _DC_ (di default 27)


 * _-d_ pin: cambia il pin _DD_ (di default 28)


 * _-r_ pin: cambia il pin _reset_ (di default 24)


 * _-m_ : modifica il moltiplicatore del ritardo, e quindi il tempo base (di default: regolazione automatica)



la numerazione dei pin utilizzata è quella di _wiringPi_. Usa `gpio readall` per avere il layout nella tua colonna _Raspberry_ ( _wPi_).

Ad esempio, se si desidera utilizzare i pin 3, 11 e 13:  
Collegare i seguenti pin da una porta di debug a una porta _GPIO_:

 1. perno 1 ( _GND_ ) -> perno 14 ( _GND_ )


 2. perno 7 ( _reset_ ) -> perno 3 ( _wPi 8, BCM2_ )


 3. perno 3 ( _DC_ ) -> perno 11 ( _wPi 0, BCM17_ )


 4. perno 4 ( _DD_ ) -> perno 13 ( _wPi 2, BCM27_ )



e ora puoi leggere ID, salvare, cancellare e scrivere la memoria flash con i seguenti comandi:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

È inoltre possibile modificare i valori predefiniti in _CCDebugger.h_ e compilare i programmi con `make`.

## cosa succede se non funziona?

1. interrompere tutti gli altri programmi.


2. impostare la velocità del processore prima della programmazione. Esempio:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilizzare l'opzione -m per aumentare i limiti di tempo utilizzati. Esempio:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. ricompilare il programma con `make`.



## Licenza

Questo progetto ha la licenza GPL v3 ((vedi 2 °).
