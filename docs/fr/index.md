---
lang: fr
lang-niv: fonto
lang-ref: 001-ĉefa-afero
layout: page
slug: "L'essentiel!"
title: "L'essentiel"
---

# _flash\_cc2531_
 _flash\_cc2531_ vous permet de programmer votre clé USB CC2531 à partir de votre _Raspberry_, sans avoir besoin d'un _Arduino_ ou d'un _CC Debugger_.

## Prérequis
Vous avez besoin d'un _Raspberry_ ou d'un _Odroid-c2_.  
Vous avez besoin de quoi connecter le port de débogage de la clé aux ports _GPIO_ du _Raspberry_, par exemple un câble _CC_ et quatre lignes _Dupont_ (voir plus loin).   
[ _WiringPi_ ](http://wiringpi.com/) doit être installé (s'il n'est pas pré-installé, vous pouvez généralement l'installer avec `sudo apt install wiringpi`, sinon voir [le site Web de _Gordon_ ](http://wiringpi.com/) ou [ce site alternatif](https://github.com/WiringPi/WiringPi)).  

J'ai conçu _flash\_cc2531_ sur un _Raspberry Pi 3_ avec _raspbian_, mais des programmations réussies ont été signalées sur d'autres modèles:  
 * sur pi 4, vous aurez besoin de la version 2.52 de _wiringpi_ :  [installer _wiringPi_ 2.52 depuis le site Web de _Gordon_ ](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)

 * sur pi 1 et pi 2, vous devrez [utiliser d'autres broches](#uzi_aliajn_pinglojn).
 * dans tous les cas, vous devrez probablement ajuster l'option de base de temps ( _"-m"_ ).

## Préparation

Téléchargez _flash\_cc2531_ sur votre _raspberry_ :
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```

Connectez les broches suivantes du port de débogage au port GPIO:

 1. broche 1 ( _GND_ ) -> broche 39 ( _GND_ )
 2. broche 7 ( _reset_ ) -> broche 35 ( _wPi 24, BCM19_ )
 3. broche 3 ( _DC_ ) -> broche 36 ( _wPi 27, BCM16_ )
 4. broche 4 ( _DD_ ) -> broche 38 ( _wPi 28, BCM20_ )

et insérez la clé USB dans un port.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet :
![photo de la clé et du _raspberry_ ](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _lemariva.com_ ](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_ ](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


testez en exécutant ceci :
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


## utilisation
Pour enregistrer le contenu de la mémoire flash dans le fichier save.hex:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

Pour effacer la mémoire flash:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

Pour programmer le fichier _CC2531ZNP-Prod.hex_ sur la clé _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id="uzi_aliajn_pinglojn"></a>
## Utiliser d'autres broches

toutes les commandes acceptent les arguments suivants:

 * _-c_ broche : change la broche _DC_ (par défaut 27)
 * _-d_ broche : change la broche _DD_ (par défaut 28)
 * _-r_ broche : change la broche _reset_ (par défaut 24)
 * _-m_ : change le multiplicateur du délai, et donc le temps de base (par défaut : ajustement automatique)

la numérotation des broches utilisée est celle de _wiringPi_. Utilisez `gpio readall` pour avoir la disposition dans votre _Raspberry_ (colonne _wPi_ ).

Par exemple, si vous souhaitez utiliser les broches 3, 11 et 13:  
Connectez les broches suivantes d'un port de débogage à une porte _GPIO_:

 1. broche 1 ( _GND_ ) -> broche 14 ( _GND_ )
 2. broche 7 ( _reset_ ) -> broche 3 ( _wPi 8, BCM2_ )
 3. broche 3 ( _DC_ ) -> broche 11 ( _wPi 0, BCM17_ )
 4. broche 4 ( _DD_ ) -> broche 13 ( _wPi 2, BCM27_ )

et maintenant vous pouvez lire l'ID, sauvegarder , effacer et écrire la mémoire flash avec les commandes suivantes:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## et si ça ne marche pas?

1. arrêtez tous les autres programmes.
2. fixez la vitesse du processeur avant la programmation. Exemple:
   ```bash
   sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
   ```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:
   ```bash
   ./cc_write -m 300 CC2531ZNP-Prod.hex
   ```
4. recompilez le logiciel avec `make`.

## Licence

Ce projet est sous licence GPL v3 ( voir _COPYING_ ).
