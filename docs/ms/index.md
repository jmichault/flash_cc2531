---
lang: ms
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 'Yang penting!'
title: 'Perkara utama'
---

# _flash\_cc2531_
 _flash\_cc2531_ membolehkan anda memprogram stik USB CC2531 anda dari _Raspberry_, tanpa memerlukan _Arduino_ atau _CC Debugger_.

## Prasyarat
Anda memerlukan _Raspberry_ atau _Odroid-c2_.  
Anda memerlukan apa yang menghubungkan port debug kunci ke port _GPIO_  _Raspberry_, misalnya kabel _CC_ dan empat baris _Dupont_ (lihat lebih jauh).   
[WiringPi](http://wiringpi.com/) mesti dipasang (jika tidak dipasang sebelumnya, anda biasanya boleh memasangnya dengan `sudo apt install wiringpi`, jika tidak, lihat laman web [ _Gordon_](http://wiringpi.com/) atau [laman alternatif ini](https://github.com/WiringPi/WiringPi)).  

Saya mengunjurkan _flash\_cc2531_ pada _Raspberry Pi 3_ dengan _raspbian_, tetapi pengaturcaraan yang berjaya dilaporkan pada model lain:
* pada pi 4, anda memerlukan versi 2.52 dari _wiringpi_ :  [pasang _Pi pendawaian_ 2.52 dari _laman web Gordon_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* pada pi 1 dan pi 2 anda memerlukan [untuk menggunakan pin lain](#uzi_aliajn_pinglojn).  

* namun, anda mungkin perlu menetapkan pilihan asas masa ( _"-m"_ ).



## Bersedia

Muat turun _flash\_cc2531_ ke _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Sambungkan pin berikut dari port debugging ke port GPIO:
1. pin 1 ( _GND_ ) -> pin 39 ( _GND_ )
pin kedua 7 ( _reset_ ) -> pin 35 ( _wPi 24, BCM19_ ))
3. gelendong 3 ( _DC_ ) -> pin 36 ( _wPi 27, BCM16_ )
4. gelendong 4 ( _DD_ ) -> gelendong 38 ( _wPi 28, BCM20_ )

dan masukkan kekunci USB ke dalam port.

Muat turun kabel _CC_ dan 4 baris _Dupont_ Perempuan ke Wanita sangat sesuai untuk tujuan ini:
![foto kunci dan raspberry __](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)°)
Ini adalah pilihan kegemaran saya, tetapi jika anda tidak mempunyai kabel _CC_ , anda juga boleh menyolder kabel secara langsung _Dupont_ pada kunci: lihat misalnya laman web [ )_mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) atau [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


cuba ini:
```bash
cd flash_cc2531
./cc_chipid
```
Ia mesti kembali:
```
  ID = b524.
```
Sekiranya anda melihat 0000 atau ffff ada yang tidak kena:
* periksa dahulu pendawaian anda.
* kemudian cuba masa asas yang lebih tinggi, misalnya dengan `./cc_chipid -m 100`, atau `./cc_chipid -m 160` atau `./cc_chipid -m 300`.
* Sekiranya tidak ada yang berfungsi, cuba kumpulkan semula dengan `make`.


## menggunakan
Untuk menyimpan kandungan memori flash ke fail save.hex:
```bash
./cc_read save.hex
```
(berlangsung sekitar 1 minit).

Untuk memadamkan memori kilat:
```bash
./cc_erase
```
**Catatan:** Anda **mesti** hapus sebelum menulis (kecuali anda benar-benar tahu apa yang akan anda lakukan).

Untuk memprogram fail pada kekunci _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(berlangsung sekitar 3 minit).

<a id ="menggunakan_aliajn_pin"></ a>
## Gunakan pin lain
semua arahan menerima hujah berikut:
* _-c_ pin: pin perubahan _DC_ (secara lalai 27)
(° Pin 10 °)_-d_ : pin ubah _DD_ )(lalai 28)
* _-r_ pin: ubah pin _reset_ (secara lalai 24)
* _-m_ : ubah pengganda kelewatan, dan oleh itu masa asas (secara lalai: pelarasan automatik)

penomboran pin yang digunakan ialah _wiringPi_. Gunakan `gpio readall` untuk mempunyai susun atur di ruangan _Raspberry_ ( _wPi_).

Contohnya, jika anda ingin menggunakan pin 3, 11 dan 13:  
Sambungkan pin berikut dari port debugging ke pintu _GPIO_:
1. pin 1 ( _GND_ ) -> pin 14 ( )_GND_ )
2. pin 7 ( _reset_ ) -> pin 3 ( _wPi 8, BCM2_ )
3. pin 3 ( _DC_ ) -> pin 11 ( _wPi 0, BCM17_ )
4. pin 4 ( _DD_ ) -> pin 13 ( )_wPi 2, BCM27_ )

dan sekarang anda boleh membaca ID, menyimpan, memadam dan menulis memori kilat dengan arahan berikut:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Anda juga boleh menukar nilai lalai ke _CCDebugger.h_ dan menyusun program dengan `make`.

## bagaimana jika ia tidak berfungsi?

1. hentikan semua program lain.

2. tetapkan kelajuan pemproses sebelum pengaturcaraan. Contoh:  

```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. gunakan pilihan -m untuk meningkatkan had masa yang digunakan. Contoh:  

```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. menyusun semula program dengan `make`.



## Lesen

Projek ini dilesenkan di bawah GPL v3 ((lihat 2 °).
