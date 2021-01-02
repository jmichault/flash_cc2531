---
lang: ar
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: الأساسي!
title: 'الشيء الرئيسي'
---

# _flash\_cc2531_
 _flash\_cc2531_ يسمح لك ببرمجة CC2531 USB stick الخاص بك من _Raspberry_، دون الحاجة إلى _Arduino_ أو _CC Debugger_.

## المتطلبات الأساسية
تحتاج إما _Raspberry_ أو _Odroid-c2_.  
أنت بحاجة إلى ما لتوصيل منفذ التصحيح الخاص بالمفتاح بالمنافذ _GPIO_ من _Raspberry_، على سبيل المثال الكبل _CC_ وأربعة خطوط _Dupont_ (انظر أيضًا).   
[يجب تثبيت WiringPi](http://wiringpi.com/)  (إذا لم يكن مثبتًا مسبقًا ، يمكنك عادةً تثبيته باستخدام `sudo apt install wiringpi`، وإلا راجع موقع الويب [ _Gordon_](http://wiringpi.com/) أو [هذا هذا الموقع البديل](https://github.com/WiringPi/WiringPi)).  

لقد قمت بإسقاط _flash\_cc2531_ على _Raspberry Pi 3_ باستخدام _raspbian_، ولكن تم الإبلاغ عن نماذج أخرى للبرامج الناجحة:
* على pi 4 ، ستحتاج إلى الإصدار 2.52 من (zzz10 ): (zzz12 ) تثبيت _الأسلاك Pi_ 2.52 من _موقع جوردون_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* في pi 1 و pi 2 ، ستحتاج إلى[لاستخدام دبابيس أخرى](#uzu_aliajn_pinglojn).  




* على أي حال ، ربما تحتاج إلى ضبط خيار قاعدة الوقت ( _"-m"_ ).





## أعدت

قم بتنزيل _flash\_cc2531_ إلى _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
قم بتوصيل المسامير التالية من منفذ التصحيح بمنفذ GPIO:

1. دبوس 1 ( _GND_ ) -> دبوس 39 ( _GND_ )


2. دبوس 7 ( _reset_ ) -> دبوس 35 ( _wPi 24, BCM19_ )


3. دبوس 3 ( _DC_ ) -> دبوس 36 ( _wPi 27, BCM16_ )


4. دبوس 4 ( _DD_ ) -> دبوس 38 ( _wPi 28, BCM20_ )



وأدخل مفتاح USB في المنفذ.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


جرب هذا:
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


## استعمال
لحفظ محتويات ذاكرة الفلاش في ملف save.hex:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

لمسح ذاكرة الفلاش:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

لبرمجة الملف على المفتاح _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<معرف ="استخدم_aliajn_دبابيس"></ a>
## استخدم دبابيس أخرى
تقبل جميع الأوامر الوسيطات التالية:
* _-c_ pin: تغيير دبوس _DC_ (الافتراضي 27)
* _-d_ pin: تغيير دبوس _DD_ )(الافتراضي 28)
* _-r_ دبوس: تغيير دبوس _reset_ (الافتراضي 24)
* _-m_ : قم بتغيير مضاعف التأخير ، وبالتالي الأساسي الوقت (الافتراضي: الضبط التلقائي)

رقم التعريف الشخصي المستخدم هو _wiringPi_. استخدم `gpio readall` للحصول على التخطيط في عمود _Raspberry_ ( _wPi_).

على سبيل المثال ، إذا كنت تريد استخدام المسامير 3 و 11 و 13: 
قم بتوصيل المسامير التالية من منفذ التصحيح إلى البوابة _GPIO_:
1.pin 1 ( _GND_ ) ) -> ) دبوس 14 ( _GND_ )
2. دبوس 7 ( _reset_ ) -> دبوس 3 ( _wPi 8, BCM2_ )
3. دبوس 3 ( _DC_ ) -> دبوس 11 ( _wPi 0, BCM17_ )
4.pin 4 ( _DD_ ) -> دبوس 13 ( ( zzz42) wPi 2 ، BCM27_ )

والآن يمكنك قراءة المعرف وحفظ وحذف وكتابة ذاكرة فلاش بالأوامر التالية:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## ماذا لو لم يعمل؟

1. وقف جميع البرامج الأخرى.


2. اضبط سرعة المعالج قبل البرمجة. مثال:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## رخصة

هذا المشروع مُرخص بموجب GPL v3 (انظر _COPYING_).
