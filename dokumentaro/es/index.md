---
lang: es
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: '¡Lo esencial!'
title: 'Lo esencial'
---

# _flash\_cc2531_
 _flash\_cc2531_ le permite programar su memoria USB CC2531 desde su _Raspberry_, sin la necesidad de _Arduino_ o _CC Debugger_.

## Prerrequisitos
Necesita _Raspberry_ o _Odroid-c2_.  
Necesita que conectar el puerto de depuración de la llave a los puertos _GPIO_ de _Raspberry_, por ejemplo cable _CC_ y cuatro líneas _Dupont_ (ver más adelante).   
[WiringPi](http://wiringpi.com/) debe estar instalado (si no está preinstalado, normalmente puede instalarlo con `sudo apt install wiringpi`; de lo contrario, consulte el sitio web [ _Gordon_](http://wiringpi.com/) o [this ese sitio alternativo](https://github.com/WiringPi/WiringPi)).  

Proyecté _flash\_cc2531_ en un _Raspberry Pi 3_ con _raspbian_, pero se han informado otros modelos para programas exitosos:
* en pi 4, necesitará la versión 2.52 de (zzz10 ): (zzz12 ) instalar _cableado Pi_ 2.52 desde _sitio web de Gordon_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* en pi 1 y pi 2 necesitará[para usar otros pines](#uzu_aliajn_pinglojn).  




* de todos modos probablemente necesitará establecer la opción de base de tiempo ( _"-m"_ ).





## Preparado

Descarga _flash\_cc2531_ a tu _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Conecte los siguientes pines del puerto de depuración al puerto GPIO:

1. pin 1 ( _GND_ ) -> pin 39 ( _GND_ )


2. patilla 7 ( _reset_ ) -> patilla 35 ( _wPi 24, BCM19_ )


3. patilla 3 ( _DC_ ) -> patilla 36 ( _wPi 27, BCM16_ )


4. patilla 4 ( _DD_ ) -> patilla 38 ( _wPi 28, BCM20_ )



e inserte la llave USB en un puerto.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


prueba esto:
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


## utilizar
Para guardar el contenido de la memoria flash en el archivo save.hex:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

Para borrar la memoria flash:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

Para programar el archivo en la tecla _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="use_aliajn_pines"></ a>
## Usa otros pines
todos los comandos aceptan los siguientes argumentos:
* _-c_ pin: cambiar pin _DC_ (predeterminado 27)
* _-d_ pin: cambiar pin _DD_ )(predeterminado 28)
* _-r_ pin: cambiar pin _reset_ (predeterminado 24)
* _-m_ : cambiar el multiplicador del retardo, y por lo tanto el básico tiempo (predeterminado: ajuste automático)

la numeración de pines utilizada es la de _wiringPi_. Utilice `gpio readall` para tener el diseño en su columna _Raspberry_ ( _wPi_).

Por ejemplo, si desea utilizar los pines 3, 11 y 13: 
Conecte los siguientes pines del puerto de depuración a la puerta _GPIO_:
1.pin 1 ( _GND_ ) ) -> ) pin 14 ( _GND_ )
2. pin 7 ( _reset_ ) -> pin 3 ( _wPi 8, BCM2_ )
3. pin 3 ( _DC_ ) -> patilla 11 ( _wPi 0, BCM17_ )
4.pin 4 ( _DD_ ) -> patilla 13 ( ( zzz42) wPi 2, BCM27_ )

y ahora puede leer ID, guardar, borrar y escribir memoria flash con los siguientes comandos:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## ¿y si no funciona?

1. detenga todos los demás programas.


2. establezca la velocidad del procesador antes de programar. Ejemplo:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## Licencia

Este proyecto tiene la licencia GPL v3 (, consulte _COPYING_).
