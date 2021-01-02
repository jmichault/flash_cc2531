---
lang: ms
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 'Yang penting!'
title: 'Perkara utama'
---

# _flash\_cc2531_
 _flash\_cc2531_ membolehkan anda memprogram stik USB CC2531 dari _Raspberry_anda, tanpa memerlukan _Arduino_ atau _CC Debugger_.

## Prasyarat
Anda memerlukan _Raspberry_ atau _Odroid-c2_.  
Anda memerlukan apa yang hendak menghubungkan port debug kunci ke port _GPIO_ dari _Raspberry_, misalnya kabel _CC_ dan empat baris _Dupont_ (lihat lebih jauh).   
[WiringPi](http://wiringpi.com/) mesti dipasang (jika tidak diprapasang, biasanya anda boleh memasangnya dengan `sudo apt install wiringpi`, jika tidak, lihat laman web [ _Gordon_](http://wiringpi.com/) atau [ini laman web alternatif itu](https://github.com/WiringPi/WiringPi)).  

Saya mengunjurkan _flash\_cc2531_ pada _Raspberry Pi 3_ dengan _raspbian_, tetapi model lain telah dilaporkan untuk program yang berjaya:
* pada pi 4, anda memerlukan versi 2.52 dari (zzz10 ): (zzz12 ) pasang _pendawaian Pi_ 2.52 dari _laman web Gordon_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* pada pi 1 dan pi 2 anda akan memerlukan[untuk menggunakan pin lain](#uzu_aliajn_pinglojn).  




* bagaimanapun anda mungkin perlu menetapkan pilihan asas masa ( _"-m"_ ).





## Bersedia

Muat turun _flash\_cc2531_ ke _raspberry_anda:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Sambungkan pin berikut dari port debug ke port GPIO:

1. pin 1 ( _GND_ ) -> pin 39 ( _GND_ )


2. pin 7 ( _reset_ ) -> pin 35 ( _wPi 24, BCM19_ )


3. pin 3 ( _DC_ ) -> pin 36 ( _wPi 27, BCM16_ )


4. pin 4 ( _DD_ ) -> pin 38 ( _wPi 28, BCM20_ )



dan masukkan kekunci USB ke dalam port.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


cubalah ini:
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


## menggunakan
Untuk menyimpan kandungan memori flash ke fail save.hex:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

Untuk memadamkan memori kilat:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

Untuk memprogram fail pada kekunci _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="penggunaan_aliajn_pin"></ a>
## Gunakan pin lain
semua arahan menerima argumen berikut:
* _-c_ pin: pin pin _DC_ (default 27)
* _-d_ pin: change pin _DD_ )(lalai 28)
* _-r_ pin: pin perubahan _reset_ (lalai 24)
* _-m_ : menukar pengganda kelewatan, dan oleh itu asas masa (lalai: pelarasan automatik)

penomboran pin yang digunakan ialah nombor _wiringPi_. Gunakan `gpio readall` untuk mempunyai susun atur di lajur _Raspberry_ ( _wPi_)anda.

Sebagai contoh, jika anda ingin menggunakan pin 3, 11 dan 13: 
Sambungkan pin berikut dari port debug ke pintu _GPIO_:
1. pin 1 ( _GND_ ) ) -> ) pin 14 ( _GND_ )
2. pin 7 ( _reset_ ) -> pin 3 ( _wPi 8, BCM2_ )
3. pin 3 ( _DC_ ) -> pin 11 ( _wPi 0, BCM17_ )
4. pin 4 ( _DD_ ) -> pin 13 ( ( zzz42) wPi 2, BCM27_ )

dan sekarang anda boleh membaca ID, menyimpan, menghapus dan menulis memori kilat dengan arahan berikut:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## bagaimana jika ia tidak berfungsi?

1. hentikan semua program lain.


2. tetapkan kelajuan pemproses sebelum pengaturcaraan. Contoh:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## Lesen

Projek ini dilesenkan di bawah GPL v3 (lihat _COPYING_).
