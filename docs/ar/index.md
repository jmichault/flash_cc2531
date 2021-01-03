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
أنت بحاجة إلى ما لتوصيل منفذ التصحيح الخاص بالمفتاح بالمنافذ _GPIO_ من _Raspberry_، على سبيل المثال الكبل _CC_ وأربعة خطوط _Dupont_ (انظر أيضًا10 درجة).   
[يجب تثبيت WiringPi](http://wiringpi.com/)  (إذا لم يكن مثبتًا مسبقًا ، يمكنك عادةً تثبيته بـ `sudo apt install wiringpi`، وإلا انظر موقع الويب [ _Gordon_](http://wiringpi.com/) أو [هذا الموقع البديل](https://github.com/WiringPi/WiringPi)).  

لقد توقعت _flash\_cc2531_ على _Raspberry Pi 3_ مع _raspbian_، ولكن تم الإبلاغ عن البرمجة الناجحة في الطرز الأخرى:
* في pi 4 ، ستحتاج إلى الإصدار 2.52 من10 °):  [تثبيت _الأسلاك Pi_ 2.52 من _موقع جوردون_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* في pi 1 و pi 2 ستحتاج [لاستخدام دبابيس أخرى](#uzi_aliajn_pinglojn).  

* ومع ذلك ، ربما تحتاج إلى ضبط خيار القاعدة الزمنية ( _"-m"_ ).



## أعدت

تنزيل _flash\_cc2531_ إلى _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
قم بتوصيل المسامير التالية من منفذ التصحيح بمنفذ GPIO:
1. pin 1 ( _GND_ ) -> pin 39 ( _GND_ )
دبوس ثاني 7 ( _reset_ ) -> دبوس 35 ( _wPi 24, BCM19_ ))
3. المغزل 3 ( _DC_ ) -> دبوس 36 ( _wPi 27, BCM16_ )
4. المغزل 4 ( _DD_ ) -> المغزل 38 ( _wPi 28, BCM20_ )(° 41 درجة)

وأدخل مفتاح USB في المنفذ.

تحميل كابل _CC_ و 4 خطوط _Dupont_ أنثى إلى أنثى مثالية لهذا الغرض:
![صورة المفتاح و _التوت_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)°)
هذا هو خياري المفضل ، ولكن إذا لم يكن لديك كابل _CC_ ، فيمكنك أيضًا لحام الكابلات مباشرة _Dupont_ على المفتاح: انظر على سبيل المثال موقع الويب [ )_mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) أو [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


جرب هذا:
```bash
cd flash_cc2531
./cc_chipid
```
يجب أن تعود:
```
  ID = b524.
```
إذا رأيت 0000 أو ffff ، هناك شيء خاطئ:
* تحقق أولاً من الأسلاك.
* ثم جرب وقت أساس أعلى ، على سبيل المثال مع `./cc_chipid -m 100`أو `./cc_chipid -m 160` أو `./cc_chipid -m 300`.
* إذا لم ينجح أي من ذلك ، فحاول إعادة التحويل البرمجي باستخدام `make`. (° 18 درجة)


## استعمال
لحفظ محتويات ذاكرة الفلاش في ملف save.hex:
```bash
./cc_read save.hex
```
(تدوم حوالي دقيقة واحدة).

لمسح ذاكرة الفلاش:
```bash
./cc_erase
```
**ملاحظة:** يجب عليك **** حذفها قبل الكتابة (ما لم تكن تعرف حقًا ما الذي ستفعله).

لبرمجة الملف على المفتاح _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(تدوم حوالي 3 دقائق).

<معرف ="استخدم_aliajn_دبابيس"></ a>
## استخدم دبابيس أخرى
تقبل جميع الأوامر الوسيطات التالية:
* _-c_ دبوس: تغيير الدبوس _DC_ (افتراضيًا 27)
* _-d_ دبوس: تغيير الدبوس _DD_ )(الافتراضي 28)
* _-r_ دبوس: تغيير الدبوس _reset_ (بشكل افتراضي 24)
* _-m_ : قم بتغيير مضاعف التأخير ، وبالتالي الوقت الأساسي (افتراضيًا: الضبط التلقائي)

رقم التعريف الشخصي المستخدم هو _wiringPi_. استخدم `gpio readall` للحصول على التخطيط في العمود _Raspberry_ ( _wPi_).

على سبيل المثال ، إذا كنت تريد استخدام المسامير 3 و 11 و 13:  
قم بتوصيل المسامير التالية من منفذ تصحيح الأخطاء إلى بوابة _GPIO_:
1. دبوس 1 ( _GND_ ) -> دبوس 14 ( )_GND_ )
2. دبوس 7 ( _reset_ ) -> دبوس 3 ( _wPi 8, BCM2_ )
3. دبوس 3 ( _DC_ ) -> دبوس 11 ( _wPi 0, BCM17_ )
4. دبوس 4 ( _DD_ ) -> دبوس 13 ( )_wPi 2 ، BCM27_ )

والآن يمكنك قراءة المعرف وحفظ وحذف وكتابة ذاكرة فلاش بالأوامر التالية:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

يمكنك أيضًا تغيير القيم الافتراضية في _CCDebugger.h_ وتجميع البرامج بـ `make`.

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

هذا المشروع مُرخص بموجب GPL v3 ((انظر 2 °).
