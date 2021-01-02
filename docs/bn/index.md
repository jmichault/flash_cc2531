---
lang: bn
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: অপরিহার্য!
title: 'প্রধান বিষয়'
---

# _flash\_cc2531_
 _flash\_cc2531_ আপনাকে _Arduino_ বা _CC Debugger_প্রয়োজন ছাড়াই আপনার _Raspberry_থেকে আপনার সিসি 2531 ইউএসবি স্টিকটি প্রোগ্রাম করার অনুমতি দেয়।

## পূর্বশর্ত
আপনার দরকার হয় _Raspberry_ বা _Odroid-c2_।  
কীটির ডিবাগ পোর্টটি _Raspberry_(zZ3) এর পোর্টগুলির সাথে সংযুক্ত করার জন্য আপনার প্রয়োজন, উদাহরণস্বরূপ কেবল _CC_ এবং চারটি লাইন _Dupont_ (আরও দেখুন)।   
[ওয়্যারিংপি](http://wiringpi.com/) অবশ্যই ইনস্টল করা উচিত (এটি প্রাক ইনস্টল না করা থাকলে আপনি সাধারণত এটি `sudo apt install wiringpi`দিয়ে ইনস্টল করতে পারেন, অন্যথায় ওয়েবসাইট দেখুন [ _গর্ডন_](http://wiringpi.com/) বা [এটি বিকল্প সাইট](https://github.com/WiringPi/WiringPi))।  

আমি _flash\_cc2531_ একটি _flash\_cc2531_ এর সাথে _raspbian_প্রজেক্ট করেছি, তবে অন্যান্য মডেলগুলি সফল প্রোগ্রামগুলির জন্য রিপোর্ট করা হয়েছে:
* পাই 4 এ, আপনার সংস্করণ 2.52 (zzz10 )প্রয়োজন হবে:  [) _তারের পাই_ 2.52 _গর্ডনের ওয়েবসাইট_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  থেকে ইনস্টল করুন
* পাই 1 এবং পাই 2 তে আপনার অন্যান্য পিনগুলি](#uzu_aliajn_pinglojn)ব্যবহার করার জন্য[প্রয়োজন হবে।  




* যাইহোক আপনাকে সম্ভবত সময় বেস বিকল্প ( _"-m"_ )সেট করতে হবে।





## প্রস্তুত

আপনার _raspberry_এ _flash\_cc2531_ ডাউনলোড করুন:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
ডিবাগ বন্দর থেকে জিপিআইও বন্দরে নিম্নলিখিত পিনগুলি সংযুক্ত করুন:

1. পিন 1 ( _GND_ ) -> পিন 39 ( _GND_ )


2. পিন 7 ( _reset_ ) -> পিন 35 ( _wPi 24, BCM19_ )


3. পিন 3 ( _DC_ ) -> পিন 36 ( _wPi 27, BCM16_ )


4. পিন 4 ( _DD_ ) -> পিন 38 ( _wPi 28, BCM20_ )



এবং একটি পোর্টে ইউএসবি কী sertোকান।

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


এটি চেষ্টা করুন:
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


## ব্যবহার
Save.hex ফাইলটিতে ফ্ল্যাশ মেমরির বিষয়বস্তু সংরক্ষণ করতে:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

ফ্ল্যাশ মেমরিটি মুছতে:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

কীতে ফাইলটি প্রোগ্রাম করতে _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<একটি আইডি ="ব্যবহার_aliajn_পিন"></ এ>
## অন্যান্য পিন ব্যবহার করুন
সমস্ত কমান্ড নিম্নলিখিত আর্গুমেন্ট গ্রহণ করে:
* _-c_ পিন: পরিবর্তন পিন _DC_ (ডিফল্ট 27)
* _-d_ পিন: পরিবর্তন পিন _DD_ )(ডিফল্ট 28)
* _-r_ পিন: পরিবর্তন পিন _reset_ (ডিফল্ট 24)
* _-m_ : বিলম্বের গুণক পরিবর্তন করুন, এবং সেইজন্য বেসিক সময় (ডিফল্ট: স্বয়ংক্রিয় সমন্বয়)

ব্যবহৃত পিন নম্বরটি হ'ল _wiringPi_। আপনার _Raspberry_ (কলাম _wPi_)এর লেআউট থাকতে `gpio readall` ব্যবহার করুন।

উদাহরণস্বরূপ, আপনি পিন 3, 11 এবং 13 ব্যবহার করতে চান: 
নিম্নলিখিত পিনগুলি ডিবাগ পোর্ট থেকে গেটে _GPIO_সাথে সংযুক্ত করুন:
1. পিন 1 ( _GND_ ) ) -> ) পিন 14 ( _GND_ )
2. পিন 7 ( _reset_ ) -> পিন 3 ( _wPi 8, BCM2_ )
3. পিন 3 ( _DC_ ) -> পিন 11 ( _wPi 0, BCM17_ )
4.pin 4 ( _DD_ ) -> পিন 13 ( ( zzz42) wPi 2, বিসিএম 27_ )

এবং এখন আপনি নিম্নলিখিত কমান্ডগুলি সহ আইডি পড়তে, সংরক্ষণ করতে, মুছতে এবং লিখতে পারেন:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## যদি এটি কাজ না করে?

1. অন্যান্য সমস্ত প্রোগ্রাম বন্ধ করুন।


2. প্রোগ্রামিংয়ের আগে প্রসেসরের গতি সেট করুন। উদাহরণ:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## লাইসেন্স

এই প্রকল্পটি জিপিএল ভি 3 (দেখুন _COPYING_)এর অধীনে লাইসেন্সযুক্ত।
