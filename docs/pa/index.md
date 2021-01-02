---
lang: pa
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: ਜ਼ਰੂਰੀ!
title: 'ਮੁੱਖ ਗੱਲ'
---

# _flash\_cc2531_
 _flash\_cc2531_ ਤੁਹਾਨੂੰ _Arduino_ ਜਾਂ _CC Debugger_ਦੀ ਜ਼ਰੂਰਤ ਤੋਂ ਬਗੈਰ, ਤੁਹਾਡੇ _Raspberry_ਤੋਂ ਤੁਹਾਡੇ CC2531 USB ਸਟਿਕ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰਨ ਦੀ ਆਗਿਆ ਦਿੰਦਾ ਹੈ.

## ਜਰੂਰੀ ਹੈ
ਤੁਹਾਨੂੰ ਜਾਂ ਤਾਂ _Raspberry_ ਜਾਂ _Odroid-c2_ਦੀ ਜ਼ਰੂਰਤ ਹੈ.  
ਤੁਹਾਨੂੰ ਕੀ ਚਾਹੀਦਾ ਹੈ ਕਿ ਕੁੰਜੀ ਦੇ ਡੀਬੱਗ ਪੋਰਟ ਨੂੰ _GPIO_ (zZ3) ਦੇ ਪੋਰਟਾਂ ਨਾਲ ਜੋੜਨਾ ਹੈ, ਉਦਾਹਰਣ ਲਈ ਕੇਬਲ _CC_ ਅਤੇ ਚਾਰ ਲਾਈਨਾਂ _Dupont_ (ਅੱਗੇ ਵੇਖੋ).   
[ਵਾਇਰਿੰਗਪੀ](http://wiringpi.com/) ਲਾਜ਼ਮੀ ਤੌਰ 'ਤੇ ਸਥਾਪਤ ਹੋਣੀ ਚਾਹੀਦੀ ਹੈ (ਜੇ ਇਹ ਪਹਿਲਾਂ ਤੋਂ ਸਥਾਪਤ ਨਹੀਂ ਹੈ, ਤਾਂ ਤੁਸੀਂ ਆਮ ਤੌਰ' ਤੇ ਇਸ ਨੂੰ `sudo apt install wiringpi`ਨਾਲ ਸਥਾਪਤ ਕਰ ਸਕਦੇ ਹੋ, ਨਹੀਂ ਤਾਂ ਵੈਬਸਾਈਟ [ _ਗੋਰਡਨ_](http://wiringpi.com/) ਜਾਂ [ਇਸ ਨੂੰ ਵੇਖੋ. ਉਹ ਵਿਕਲਪਕ ਸਾਈਟ](https://github.com/WiringPi/WiringPi)).  

ਮੈਂ ਇੱਕ _flash\_cc2531_ ਤੇ _flash\_cc2531_ ਤੇ _raspbian_ਦਾ ਅਨੁਮਾਨ ਲਾਇਆ ਹੈ, ਪਰ ਸਫਲ ਪ੍ਰੋਗਰਾਮਾਂ ਲਈ ਹੋਰ ਮਾਡਲਾਂ ਦੀ ਰਿਪੋਰਟ ਕੀਤੀ ਗਈ ਹੈ: ) _ਵਾਇਰਿੰਗ ਪਾਈ_ 2.52 _ਗੋਰਡਨ ਦੀ ਵੈਬਸਾਈਟ_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  ਤੋਂ ਸਥਾਪਤ ਕਰੋ.
* pi 1 ਅਤੇ pi 2 'ਤੇ ਤੁਹਾਨੂੰ ਹੋਰ ਪਿੰਨ](#uzu_aliajn_pinglojn)ਵਰਤਣ ਲਈ[ਦੀ ਜ਼ਰੂਰਤ ਹੋਏਗੀ.  




* ਵੈਸੇ ਵੀ ਤੁਹਾਨੂੰ ਸ਼ਾਇਦ ਟਾਈਮ ਬੇਸ ਵਿਕਲਪ ( _"-m"_ )ਨਿਰਧਾਰਤ ਕਰਨ ਦੀ ਜ਼ਰੂਰਤ ਹੋਏਗੀ.





## ਤਿਆਰ ਕੀਤਾ

ਆਪਣੇ _raspberry_ਤੇ _flash\_cc2531_ ਡਾਉਨਲੋਡ ਕਰੋ:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
ਡੀਬੱਗ ਪੋਰਟ ਤੋਂ ਹੇਠ ਲਿਖੀਆਂ ਪਿੰਨਾਂ ਨੂੰ ਜੀਪੀਆਈਓ ਪੋਰਟ ਨਾਲ ਜੋੜੋ:

1. ਪਿੰਨ 1 ( _GND_ ) -> ਪਿੰਨ 39 ( _GND_ )


2. ਪਿੰਨ 7 ( _reset_ ) -> ਪਿੰਨ 35 ( _wPi 24, BCM19_ )


3. ਪਿੰਨ 3 ( _DC_ ) -> ਪਿੰਨ 36 ( _wPi 27, BCM16_ )


4. ਪਿੰਨ 4 ( _DD_ ) -> ਪਿੰਨ 38 ( _wPi 28, BCM20_ )



ਅਤੇ ਇੱਕ ਪੋਰਟ ਵਿੱਚ USB ਕੁੰਜੀ ਪਾਓ.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


ਇਸ ਨੂੰ ਅਜ਼ਮਾਓ:
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


## ਵਰਤਣ
ਫਲੈਸ਼ ਮੈਮੋਰੀ ਦੇ ਭਾਗਾਂ ਨੂੰ ਸੇਵ.ਹੇਕਸ ਫਾਈਲ ਵਿੱਚ ਸੇਵ ਕਰਨ ਲਈ:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

ਫਲੈਸ਼ ਮੈਮੋਰੀ ਨੂੰ ਮਿਟਾਉਣ ਲਈ:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

ਕੁੰਜੀ 'ਤੇ ਫਾਈਲ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰਨ ਲਈ _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<ਇੱਕ id ="ਵਰਤੋਂ_aliajn_ਪਿੰਨ"></ a>
## ਹੋਰ ਪਿੰਨ ਦੀ ਵਰਤੋਂ ਕਰੋ
ਸਾਰੀਆਂ ਕਮਾਂਡਾਂ ਹੇਠ ਲਿਖੀਆਂ ਦਲੀਲਾਂ ਨੂੰ ਸਵੀਕਾਰਦੀਆਂ ਹਨ:
* _-c_ ਪਿੰਨ: ਬਦਲੋ ਪਿੰਨ _DC_ (ਮੂਲ 27)
* _-d_ ਪਿੰਨ: ਬਦਲੋ ਪਿੰਨ _DD_ )(ਡਿਫਾਲਟ 28)
* _-r_ ਪਿੰਨ: ਬਦਲੋ ਪਿੰਨ _reset_ (ਡਿਫਾਲਟ 24)
* _-m_ : ਦੇਰੀ ਦੇ ਗੁਣਕ ਨੂੰ ਬਦਲੋ, ਅਤੇ ਇਸ ਲਈ ਮੁ theਲਾ ਟਾਈਮ (ਡਿਫੌਲਟ: ਆਟੋਮੈਟਿਕ ਐਡਜਸਟਮੈਂਟ)

ਵਰਤੀ ਜਾਂਦੀ ਪਿੰਨ ਨੰਬਰਿੰਗ _wiringPi_ਦੀ ਹੈ. ਆਪਣੇ _Raspberry_ (ਕਾਲਮ _wPi_)ਵਿੱਚ ਖਾਕਾ ਲੈਣ ਲਈ `gpio readall` ਵਰਤੋ.

ਉਦਾਹਰਣ ਦੇ ਲਈ, ਜੇ ਤੁਸੀਂ ਪਿੰਨਸ 3, 11 ਅਤੇ 13 ਵਰਤਣਾ ਚਾਹੁੰਦੇ ਹੋ: 
ਹੇਠਾਂ ਦਿੱਤੇ ਪਿੰਨ ਨੂੰ ਡੀਬੱਗ ਪੋਰਟ ਤੋਂ ਗੇਟ _GPIO_ਨਾਲ ਜੋੜੋ:
1.ਪਿਨ 1 ( _GND_ ) ) -> ) ਪਿੰਨ 14 ( _GND_ )
2. ਪਿੰਨ 7 ( _reset_ ) -> ਪਿੰਨ 3 ( _wPi 8, BCM2_ )
3. ਪਿੰਨ 3 ( _DC_ ) -> ਪਿੰਨ 11 ( _wPi 0, BCM17_ )
4.pin 4 ( _DD_ ) -> ਪਿੰਨ 13 ( ( zzz42) ਡਬਲਯੂਪੀਆਈ 2, ਬੀਸੀਐਮ 27_ )

ਅਤੇ ਹੁਣ ਤੁਸੀਂ ਹੇਠਾਂ ਦਿੱਤੀਆਂ ਕਮਾਂਡਾਂ ਨਾਲ ID ਨੂੰ ਪੜ੍ਹ ਸਕਦੇ ਹੋ, ਸੇਵ ਕਰ ਸਕਦੇ ਹੋ, ਡਿਲੀਟ ਕਰ ਸਕਦੇ ਹੋ ਅਤੇ ਫਲੈਸ਼ ਮੈਮੋਰੀ ਲਿਖ ਸਕਦੇ ਹੋ:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## ਕੀ ਜੇ ਇਹ ਕੰਮ ਨਹੀਂ ਕਰਦਾ?

1. ਹੋਰ ਸਾਰੇ ਪ੍ਰੋਗਰਾਮਾਂ ਨੂੰ ਰੋਕੋ.


2. ਪ੍ਰੋਗਰਾਮਿੰਗ ਤੋਂ ਪਹਿਲਾਂ ਪ੍ਰੋਸੈਸਰ ਦੀ ਗਤੀ ਨਿਰਧਾਰਤ ਕਰੋ. ਉਦਾਹਰਣ:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## ਲਾਇਸੈਂਸ

ਇਹ ਪ੍ਰੋਜੈਕਟ GPL v3 (ਦੇਖੋ _COPYING_)ਦੇ ਅਧੀਨ ਲਾਇਸੰਸਸ਼ੁਦਾ ਹੈ.
