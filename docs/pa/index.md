---
lang: pa
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: ਜ਼ਰੂਰੀ!
title: 'ਮੁੱਖ ਗੱਲ'
---

# _flash\_cc2531_
 _flash\_cc2531_ ਤੁਹਾਨੂੰ _Arduino_ ਜਾਂ _CC Debugger_ਦੀ ਜ਼ਰੂਰਤ ਤੋਂ ਬਗੈਰ, ਆਪਣੇ ਸੀਸੀ 2531 ਯੂ ਐਸ ਬੀ ਸਟਿਕਸ ਨੂੰ ਆਪਣੇ _Raspberry_ਤੋਂ ਪ੍ਰੋਗਰਾਮ ਕਰਨ ਦੀ ਆਗਿਆ ਦਿੰਦਾ ਹੈ.

## ਜਰੂਰੀ
ਤੁਹਾਨੂੰ ਜਾਂ ਤਾਂ _Raspberry_ ਜਾਂ _Odroid-c2_ਦੀ ਜ਼ਰੂਰਤ ਹੈ.  
ਤੁਹਾਨੂੰ ਕੀ ਚਾਹੀਦਾ ਹੈ ਕਿ ਕੀ ਦੇ ਡੀਬੱਗ ਪੋਰਟ ਨੂੰ ( _Raspberry_ਦੇ ਪੋਰਟਾਂ _GPIO_ ਨਾਲ ਜੋੜਨਾ ਹੈ, ਉਦਾਹਰਣ ਲਈ ਇੱਕ ਕੇਬਲ _CC_ ਅਤੇ ਚਾਰ ਲਾਈਨਾਂ _Dupont_ (ਹੋਰ ਵੇਖੋ).   
[ _WiringPi_ ](http://wiringpi.com/) ਲਾਜ਼ਮੀ ਤੌਰ 'ਤੇ ਸਥਾਪਤ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ \(ਜੇ ਇਹ ਪਹਿਲਾਂ ਤੋਂ ਸਥਾਪਤ ਨਹੀਂ ਹੈ, ਤਾਂ ਤੁਸੀਂ ਆਮ ਤੌਰ' ਤੇ ਇਸ ਨੂੰ `sudo apt install wiringpi`)ਨਾਲ ਸਥਾਪਤ ਕਰ ਸਕਦੇ ਹੋ, ਨਹੀਂ ਤਾਂ [ _Gordon_ ](http://wiringpi.com/) ਜਾਂ [ਇਸ ਵਿਕਲਪਕ ਸਾਈਟ](https://github.com/WiringPi/WiringPi) \).  
ਅੰਤ ਵਿੱਚ ਤੁਹਾਨੂੰ ਪ੍ਰੋਗਰਾਮ ਦੀ ਜ਼ਰੂਰਤ ਹੈ:

* ਆਮ ਤੌਰ 'ਤੇ ਜਿਗਬੀ ਕੋਆਰਡੀਨੇਟਰ: [ ਵਰਜ਼ਨ 1.2 (ਸਿਫਾਰਿਸ਼ ਕੀਤੇ)](https://github.com/Koenkk/Z-Stack-firmware/raw/master/coordinator/Z-Stack_Home_1.2/bin/default/) ਜਾਂ [ਵਰਜ਼ਨ 3.0](https://github.com/Koenkk/Z-Stack-firmware/tree/master/coordinator/Z-Stack_3.0.x/bin)


* ਜਾਂ ਜ਼ਿੱਗੀ ਰਾ rouਟਰ: [ਜ਼ਿੱਗਬੀ ਰਾ rouਟਰ 1.2](https://github.com/Koenkk/Z-Stack-firmware/tree/master/router/CC2531/bin)




ਮੈਂ _flash\_cc2531_  _Raspberry Pi 3_ ਤੇ _raspbian_ਦਾ ਅਨੁਮਾਨ ਲਗਾਇਆ, ਪਰ ਸਫਲ ਪ੍ਰੋਗ੍ਰਾਮਿੰਗ ਦੀ ਰਿਪੋਰਟ ਦੂਜੇ ਮਾਡਲਾਂ 'ਤੇ ਦਿੱਤੀ ਗਈ:  
 * ਪੀਆਈ 4 ਤੇ ਤੁਹਾਨੂੰ _wiringpi_ ਵਰਜ਼ਨ 2.52 ਦੀ ਜ਼ਰੂਰਤ ਹੋਏਗੀ:  [ _Gordon_ ](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)ਵੈਬਸਾਈਟਦੇ 2.52 _wiringPi_ ਸਥਾਪਤ ਕਰੋ.



 * ਪਾਈ 1 ਅਤੇ ਪਾਈ 2 'ਤੇ ਤੁਹਾਨੂੰ ਹੋਰ ਪਿੰਨ](#uzi_aliajn_pinglojn)ਵਰਤਣ ਲਈ [ਦੀ ਜ਼ਰੂਰਤ ਹੋਏਗੀ.


 * ਹਾਲਾਂਕਿ, ਤੁਹਾਨੂੰ ਸ਼ਾਇਦ ਟਾਈਮ ਬੇਸ ਵਿਕਲਪ ( _"-m"_ )ਨਿਰਧਾਰਤ ਕਰਨ ਦੀ ਜ਼ਰੂਰਤ ਹੋਏਗੀ.



## ਤਿਆਰ ਕੀਤਾ

ਆਪਣੇ _raspberry_ ਤੇ _flash\_cc2531_ ਡਾ Downloadਨਲੋਡ ਕਰੋ:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```

ਡੀਬੱਗ ਪੋਰਟ ਤੋਂ ਹੇਠ ਲਿਖੀਆਂ ਪਿੰਨਾਂ ਨੂੰ ਜੀਪੀਆਈਓ ਪੋਰਟ ਨਾਲ ਜੋੜੋ:

 1. ਪਿੰਨ 1 ( _GND_ ) -> ਪਿੰਨ 39 ( _GND_ )


 2. ਪਿੰਨ 7 ( _reset_ ) -> ਪਿੰਨ 35 ( _wPi 24, BCM19_ )


 3. ਪਿੰਨ 3 ( _DC_ ) -> ਪਿੰਨ 36 ( _wPi 27, BCM16_ )


 4. ਪਿੰਨ 4 ( _DD_ ) -> ਪਿੰਨ 38 ( _wPi 28, BCM20_ )



ਅਤੇ ਇੱਕ ਪੋਰਟ ਵਿੱਚ USB ਕੁੰਜੀ ਪਾਓ.

ਡਾਉਨਲੋਡ ਕੇਬਲ _CC_ ਅਤੇ 4 ਲਾਈਨਾਂ _Dupont_ toਰਤ ਤੋਂ Femaleਰਤ ਇਸ ਮਕਸਦ ਲਈ ਸਹੀ ਹਨ:
![ਕੁੰਜੀ ਦੀ ਫੋਟੋ ਅਤੇ (° 7 ()](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg))
ਇਹ ਮੇਰਾ ਮਨਪਸੰਦ ਵਿਕਲਪ ਹੈ, ਪਰ ਜੇ ਤੁਹਾਡੇ ਕੋਲ ਕੇਬਲ _CC_ ਨਹੀਂ ਹੈ ਤਾਂ ਤੁਸੀਂ ਕੁੰਜੀ ਤੇ ਕੇਬਲ _Dupont_ ਨੂੰ ਸਿੱਧੇ ਤੌਰ 'ਤੇ ਵੀ ਸੌਂਡਰ ਕਰ ਸਕਦੇ ਹੋ: ਉਦਾਹਰਣ ਲਈ ਵੈਬਸਾਈਟ [ ਦੇਖੋ_lemariva.com_ ](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ਜਾਂ [ _notenoughtech.com_ ](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger )


ਇਸਨੂੰ ਅਜ਼ਮਾਓ:
```bash
cd flash_cc2531
./cc_chipid
```
ਇਹ ਵਾਪਸ ਆਉਣਾ ਚਾਹੀਦਾ ਹੈ:
```
  ID = b524.
```
ਜੇ ਤੁਸੀਂ ਵੇਖਦੇ ਹੋ 0000 ਜਾਂ ffff ਕੁਝ ਅਸਫਲ::  
 * ਪਹਿਲਾਂ ਆਪਣੀ ਤਾਰਾਂ ਦੀ ਜਾਂਚ ਕਰੋ.


 * ਫਿਰ ਉੱਚ ਬੇਸ ਟਾਈਮ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰੋ, ਉਦਾਹਰਣ ਵਜੋਂ `./cc_chipid -m 100`, ਜਾਂ `./cc_chipid -m 160` ਜਾਂ `./cc_chipid -m 300`ਨਾਲ.


 * ਜੇ ਇਸ ਵਿੱਚੋਂ ਕੋਈ ਵੀ ਕੰਮ ਨਹੀਂ ਕਰਦਾ ਹੈ, `make`ਨਾਲ ਦੁਬਾਰਾ ਕੰਪਾਇਲ ਕਰਨ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰੋ.




## ਵਰਤੋਂ
ਫਲੈਸ਼ ਮੈਮੋਰੀ ਦੇ ਭਾਗ ਸੇਵ.ਹੇਕਸ ਫਾਈਲ ਵਿੱਚ ਸੇਵ ਕਰਨ ਲਈ:
```bash
./cc_read save.hex
```
(ਤਕਰੀਬਨ 1 ਮਿੰਟ)ਰਹਿੰਦਾ ਹੈ.

ਫਲੈਸ਼ ਮੈਮੋਰੀ ਨੂੰ ਸਾਫ ਕਰਨ ਲਈ:
```bash
./cc_erase
```
**ਨੋਟ:** ਤੁਹਾਨੂੰ** ਲਾਜ਼ਮੀ ਤੌਰ 'ਤੇ** ਮਿਟਾਉਣਾ ਚਾਹੀਦਾ ਹੈ (ਜਦ ਤੱਕ ਤੁਹਾਨੂੰ ਅਸਲ ਵਿੱਚ ਪਤਾ ਨਹੀਂ ਹੁੰਦਾ ਕਿ ਤੁਸੀਂ ਕੀ ਕਰਨ ਜਾ ਰਹੇ ਹੋ).

ਕੁੰਜੀ _CC2531_'ਤੇ ਫਾਈਲ _CC2531ZNP-Prod.hex_ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰਨ ਲਈ:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(ਲਗਭਗ 3 ਮਿੰਟ)ਰਹਿੰਦੀ ਹੈ.

<a id="uzi_aliajn_pinglojn"></a>
ਲਗਭਗ 3 ਮਿੰਟ"ਰਹਿੰਦੀ ਹੈ._
## ਹੋਰ ਪਿੰਨ ਦੀ ਵਰਤੋਂ ਕਰੋ

ਸਾਰੀਆਂ ਕਮਾਂਡਾਂ ਹੇਠ ਲਿਖੀਆਂ ਦਲੀਲਾਂ ਨੂੰ ਸਵੀਕਾਰਦੀਆਂ ਹਨ:

 * _-c_ ਪਿੰਨ: ਪਿੰਨ ਬਦਲੋ _DC_ (ਮੂਲ ਰੂਪ ਵਿੱਚ 27)


 * _-d_ ਪਿੰਨ: ਡਿਫੌਲਟ 28)ਦੁਆਰਾ ਪਿੰਨ _DD_ (ਬਦਲੋ


 * _-r_ ਪਿੰਨ: ਡਿਫੌਲਟ 24)ਦੁਆਰਾ ਪਿੰਨ _reset_ (ਬਦਲੋ


 * _-m_ : ਦੇਰੀ ਗੁਣਕ ਬਦਲੋ, ਅਤੇ ਇਸਲਈ ਮੂਲ ਸਮਾਂ (ਮੂਲ ਰੂਪ ਵਿੱਚ: ਆਟੋਮੈਟਿਕ ਵਿਵਸਥ)



ਵਰਤੀ ਜਾਂਦੀ ਪਿੰਨ ਨੰਬਰਿੰਗ _wiringPi_ਦੀ ਹੈ. ਆਪਣੇ _Raspberry_ (ਕਾਲਮ _wPi_ )ਵਿਚ ਖਾਕਾ ਲੈਣ ਲਈ `gpio readall` ਵਰਤੋ.

ਉਦਾਹਰਣ ਦੇ ਲਈ, ਜੇ ਤੁਸੀਂ ਪਿੰਨ 3, 11 ਅਤੇ 13 ਵਰਤਣਾ ਚਾਹੁੰਦੇ ਹੋ:  
ਇੱਕ ਡੀਬੱਗ ਪੋਰਟ ਤੋਂ ਹੇਠਾਂ ਦਿੱਤੇ ਪਿੰਨਾਂ ਨੂੰ ਇੱਕ ਦਰਵਾਜ਼ੇ ਨਾਲ ਜੋੜੋ (° 1 Connect):

 1. ਪਿੰਨ 1 ( _GND_ ) -> ਪਿੰਨ 14 ( _GND_ )


 2. ਪਿੰਨ 7 ( _reset_ ) -> ਪਿੰਨ 3 ( _wPi 8, BCM2_ )


 3. ਪਿੰਨ 3 ( _DC_ ) -> ਪਿੰਨ 11 ( _wPi 0, BCM17_ )


 4. ਪਿੰਨ 4 ( _DD_ ) -> ਪਿੰਨ 13 ( _wPi 2, BCM27_ )



ਅਤੇ ਹੁਣ ਤੁਸੀਂ ਹੇਠਾਂ ਦਿੱਤੀਆਂ ਕਮਾਂਡਾਂ ਨਾਲ ID ਪੜ੍ਹ ਸਕਦੇ ਹੋ, ਸੇਵ ਕਰ ਸਕਦੇ ਹੋ, ਡਿਲੀਟ ਕਰ ਸਕਦੇ ਹੋ ਅਤੇ ਫਲੈਸ਼ ਮੈਮੋਰੀ ਲਿਖ ਸਕਦੇ ਹੋ:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

ਤੁਸੀਂ ਮੂਲ ਮੁੱਲਾਂ ਨੂੰ _CCDebugger.h_ ਵਿੱਚ ਵੀ ਬਦਲ ਸਕਦੇ ਹੋ ਅਤੇ ਪ੍ਰੋਗਰਾਮਾਂ ਨੂੰ (° 3 programs) ਨਾਲ ਕੰਪਾਈਲ ਕਰ ਸਕਦੇ ਹੋ.

## ਕੀ ਜੇ ਇਹ ਕੰਮ ਨਹੀਂ ਕਰਦਾ?

1. ਹੋਰ ਸਾਰੇ ਪ੍ਰੋਗਰਾਮਾਂ ਨੂੰ ਰੋਕੋ.


2. ਪ੍ਰੋਗਰਾਮਿੰਗ ਤੋਂ ਪਹਿਲਾਂ ਪ੍ਰੋਸੈਸਰ ਦੀ ਗਤੀ ਨਿਰਧਾਰਤ ਕਰੋ. ਉਦਾਹਰਣ:


   ```bash
   sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
   ```
3. ਸਮੇਂ ਦੀ ਸੀਮਾ ਨੂੰ ਵਧਾਉਣ ਲਈ -m ਵਿਕਲਪ ਦੀ ਵਰਤੋਂ ਕਰੋ. ਉਦਾਹਰਣ:


   ```bash
   ./cc_write -m 300 CC2531ZNP-Prod.hex
   ```
4. (rec 1 °) ਨਾਲ ਪ੍ਰੋਗਰਾਮ ਦੁਬਾਰਾ ਕੰਪਾਈਲ ਕਰੋ.



## ਲਾਇਸੈਂਸ

ਇਹ ਪ੍ਰੋਜੈਕਟ ਜੀਪੀਐਲ ਵੀ 3 ( ਦੇਖੋ _COPYING_ )ਦੇ ਅਧੀਨ ਲਾਇਸੰਸਸ਼ੁਦਾ ਹੈ.
