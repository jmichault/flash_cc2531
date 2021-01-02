---
lang: hi
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: आवश्यक!
title: 'सबसे ज़रूरी चीज़'
---

# _flash\_cc2531_
 _flash\_cc2531_ आपको _Arduino_ या _CC Debugger_की आवश्यकता के बिना, अपने CC2531 USB स्टिक को अपने _Raspberry_से प्रोग्राम करने की अनुमति देता है।

## आवश्यक शर्तें
आपको या तो _Raspberry_ या _Odroid-c2_की आवश्यकता है।  
आपको कुंजी के डिबग पोर्ट _GPIO_  _Raspberry_के पोर्ट से कनेक्ट करने की आवश्यकता है, उदाहरण के लिए केबल _CC_ और चार लाइनें _Dupont_ (आगे देखें)।   
[WiringPi](http://wiringpi.com/) को स्थापित किया जाना चाहिए (यदि यह पूर्व-स्थापित नहीं है, तो आप इसे आमतौर पर `sudo apt install wiringpi`के साथ स्थापित कर सकते हैं, अन्यथा वेबसाइट [ _गॉर्डन_](http://wiringpi.com/) या [देखें वह वैकल्पिक साइट](https://github.com/WiringPi/WiringPi))।  

मैंने _Raspberry Pi 3_ के साथ _Raspberry Pi 3_ पर अनुमान लगाया _raspbian_, लेकिन सफल कार्यक्रमों के लिए अन्य मॉडल बताए गए हैं:
* pi 4 पर, आपको संस्करण (zzz10 )के संस्करण 2.52 की आवश्यकता होगी:  [) स्थापित करें _वायरिंग पाई_ 2.52 _से गॉर्डन की वेबसाइट_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* pi 1 और pi 2 पर आपको अन्य पिन](#uzu_aliajn_pinglojn)का उपयोग करने की आवश्यकता होगी[।  




* वैसे भी आपको समय आधार विकल्प ( _"-m"_ )सेट करने की आवश्यकता होगी।





## तैयार

डाउनलोड करें _flash\_cc2531_ अपने _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
डिबग पोर्ट से GPIO पोर्ट के लिए निम्नलिखित पिन कनेक्ट करें:

1. पिन 1 ( _GND_ ) -> पिन 39 ( _GND_ )


2. पिन 7 ( _reset_ ) -> पिन 35 ( _wPi 24, BCM19_ )


3. पिन 3 ( _DC_ ) -> पिन 36 ( _wPi 27, BCM16_ )


4. पिन 4 ( _DD_ ) -> पिन 38 ( _wPi 28, BCM20_ )



और USB कुंजी को एक पोर्ट में डालें।

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


इसे आज़माएँ:
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


## उपयोग
Save.hex फ़ाइल में फ्लैश मेमोरी की सामग्री को बचाने के लिए:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

फ्लैश मेमोरी को मिटाने के लिए:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

फ़ाइल को कुंजी पर रखने के लिए _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="उपयोग_aliajn_पिन"></ a>
## अन्य पिन का उपयोग करें
सभी आदेश निम्नलिखित तर्क स्वीकार करते हैं:
* _-c_ पिन: चेंज पिन _DC_ (डिफॉल्ट 27)
* _-d_ पिन: चेंज पिन _DD_ )(डिफ़ॉल्ट 28)
* _-r_ पिन: चेंज पिन _reset_ (डिफ़ॉल्ट 24)
* * _-m_ : देरी के गुणक को बदल दें, और इसलिए बुनियादी परिवर्तन समय (डिफ़ॉल्ट: स्वचालित समायोजन)

पिन नंबरिंग का उपयोग किया जाता है _wiringPi_। अपने _Raspberry_ (कॉलम _wPi_)में लेआउट रखने के लिए `gpio readall` का उपयोग करें।

उदाहरण के लिए, यदि आप पिन 3, 11 और 13 का उपयोग करना चाहते हैं: 
डिबग पोर्ट से गेट _GPIO_से निम्नलिखित पिन कनेक्ट करें:
1.pin 1 ( _GND_ ) ) -> ) पिन 14 ( _GND_ )
2. पिन 7 ( _reset_ ) - पिन 3 ( _wPi 8, BCM2_ ))3. पिन 3 ( _DC_ ) -> पिन ११ ( _wPi 0, BCM17_ )(४५३५) ४.पिन ४ ( _DD_ ) -> पिन १३ ( (() zzz42) wPi 2, BCM27_ )

और अब आप निम्नलिखित कमांड के साथ फ्लैश मेमोरी को आईडी पढ़ सकते हैं, बचा सकते हैं, हटा सकते हैं और लिख सकते हैं:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## क्या होगा अगर यह काम नहीं करता है?

1. अन्य सभी प्रोग्राम बंद करें।


2. प्रोग्रामिंग से पहले प्रोसेसर की गति निर्धारित करें। उदाहरण:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## लाइसेंस

यह परियोजना GPL v3 (देखें _COPYING_)के तहत लाइसेंस प्राप्त है।
