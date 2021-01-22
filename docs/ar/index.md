---
lang: ar
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: الأساسي!
title: 'الشيء الرئيسي'
---

# _flash\_cc2531_
 _flash\_cc2531_ يسمح لك ببرمجة CC2531 USB stick الخاص بك _Raspberry_، دون الحاجة إلى _Arduino_ أو _CC Debugger_.

## المتطلبات المسبقة
تحتاج إما _Raspberry_ أو _Odroid-c2_.  
أنت بحاجة إلى ما لتوصيل منفذ التصحيح الخاص بالمفتاح بالمنافذ _GPIO_ من _Raspberry_، على سبيل المثال كابل واحد _CC_ وأربعة خطوط _Dupont_ (انظر أيضًا). يجب تثبيت   
[ _WiringPi_ ](http://wiringpi.com/)  \(إذا لم يكن مثبتًا مسبقًا ، يمكنك عادةً تثبيته بـ `sudo apt install wiringpi`)، وإلا انظر20 °) موقع _Gordon_ ](http://wiringpi.com/) أو [هذا الموقع البديل](https://github.com/WiringPi/WiringPi) \). (° 29 درجة)  
أخيرًا تحتاج البرنامج:

* بشكل عام منسق زيجبي: [ الإصدار 1.2 (موصى به)](https://github.com/Koenkk/Z-Stack-firmware/raw/master/coordinator/Z-Stack_Home_1.2/bin/default/) أو [الإصدار 3.0](https://github.com/Koenkk/Z-Stack-firmware/tree/master/coordinator/Z-Stack_3.0.x/bin)


* أو جهاز التوجيه zigbee: [zigbee router 1.2](https://github.com/Koenkk/Z-Stack-firmware/tree/master/router/CC2531/bin)




لقد توقعت _flash\_cc2531_ على _Raspberry Pi 3_ مع _raspbian_، لكن تم الإبلاغ عن برمجة ناجحة في الطرز الأخرى:  
 * في pi 4 ، ستحتاج إلى الإصدار 2.52 من _wiringpi_ :  [تثبيت _wiringPi_ 2.52 من _Gordon_ ](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)موقع ويب



 * في pi 1 و pi 2 ستحتاج [لاستخدام دبابيس أخرى](#uzi_aliajn_pinglojn).


 * ومع ذلك ، ربما تحتاج إلى ضبط خيار القاعدة الزمنية ( _"-m"_ ).



## أعدت

تنزيل _flash\_cc2531_ إلى _raspberry_ :
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```

قم بتوصيل المسامير التالية من منفذ التصحيح بمنفذ GPIO:

 1. دبوس 1 ( _GND_ ) -> دبوس 39 ( _GND_ )


 2. دبوس 7 ( _reset_ ) -> دبوس 35 ( _wPi 24, BCM19_ )


 3. دبوس 3 ( _DC_ ) -> دبوس 36 ( _wPi 27, BCM16_ )


 4. دبوس 4 ( _DD_ ) -> دبوس 38 ( _wPi 28, BCM20_ )



وأدخل مفتاح USB في المنفذ.

تحميل كابل _CC_ و 4 خطوط _Dupont_ من أنثى إلى أنثى مثالية لهذا الغرض:
![صورة المفتاح و _raspberry_ ](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg))
هذا هو خياري المفضل ، ولكن إذا لم يكن لديك كابل _CC_ ، فيمكنك أيضًا لحام الكابلات مباشرة _Dupont_ على المفتاح: انظر على سبيل المثال موقع الويب [ _lemariva.com_ ](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) أو [ _notenoughtech.com_ ](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger )


جرب هذا:
```bash
cd flash_cc2531
./cc_chipid
```
يجب أن تعود:
```
  ID = b524.
```
إذا رأيت 0000 أو ffff فشل شيء ما:  
 * تحقق أولاً من الأسلاك الخاصة بك.


 * ثم جرب وقت أساسي أعلى ، على سبيل المثال مع `./cc_chipid -m 100`أو `./cc_chipid -m 160` أو `./cc_chipid -m 300`.


 * إذا لم ينجح أي من هذا ، فحاول إعادة التحويل البرمجي باستخدام `make`.




## الاستخدام
لحفظ محتويات ذاكرة الفلاش في ملف save.hex:
```bash
./cc_read save.hex
```
(تدوم حوالي دقيقة واحدة).

لمسح ذاكرة فلاش:
```bash
./cc_erase
```
**ملاحظة:** يجب عليك **** حذفها قبل الكتابة (ما لم تكن تعرف حقًا ما الذي ستفعله).

لبرمجة الملف _CC2531ZNP-Prod.hex_ على المفتاح _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(تدوم حوالي 3 دقائق).

<a id="uzi_aliajn_pinglojn"></a>
تدوم حوالي 3 دقائق"._
## استخدم دبابيس أخرى

تقبل جميع الأوامر الوسيطات التالية:

 * _-c_ دبوس: تغيير الدبوس _DC_ (افتراضيًا 27)


 * _-d_ دبوس: قم بتغيير الدبوس _DD_ (افتراضيًا 28)


 * _-r_ دبوس: قم بتغيير الدبوس _reset_ (افتراضيًا 24)


 * _-m_ : قم بتغيير مضاعف التأخير ، وبالتالي الوقت الأساسي (افتراضيًا: الضبط التلقائي)



رقم التعريف الشخصي المستخدم هو _wiringPi_. استخدم `gpio readall` للحصول على التخطيط في العمود _Raspberry_ ( _wPi_ ).

على سبيل المثال ، إذا كنت تريد استخدام المسامير 3 و 11 و 13:  
قم بتوصيل المسامير التالية من منفذ التصحيح بالباب _GPIO_:

 1. دبوس 1 ( _GND_ ) -> دبوس 14 ( _GND_ )


 2. دبوس 7 ( _reset_ ) -> دبوس 3 ( _wPi 8, BCM2_ )


 3. دبوس 3 ( _DC_ ) -> دبوس 11 ( _wPi 0, BCM17_ )


 4. دبوس 4 ( _DD_ ) -> دبوس 13 ( _wPi 2, BCM27_ )



والآن يمكنك قراءة المعرف وحفظ وحذف وكتابة ذاكرة فلاش بالأوامر التالية:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

يمكنك أيضًا تغيير القيم الافتراضية إلى _CCDebugger.h_ وتجميع البرامج باستخدام `make`.

## ماذا لو لم يعمل؟

1. وقف جميع البرامج الأخرى.


2. اضبط سرعة المعالج قبل البرمجة. مثال:


   ```bash
   sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
   ```
3. استخدم الخيار -m لزيادة الحدود الزمنية المستخدمة. مثال:


   ```bash
   ./cc_write -m 300 CC2531ZNP-Prod.hex
   ```
4. أعد ترجمة البرنامج باستخدام `make`.



## رخصة

هذا المشروع مُرخص بموجب GPL v3 ( انظر _COPYING_ ).
