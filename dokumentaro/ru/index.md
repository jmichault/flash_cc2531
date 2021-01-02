---
lang: ru
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: Жизненноважный!
title: Главное
---

# _flash\_cc2531_
 _flash\_cc2531_ позволяет вам программировать USB-накопитель CC2531 с вашего _Raspberry_без необходимости _Arduino_ или _CC Debugger_.

## Предпосылки
Вам понадобится _Raspberry_ или _Odroid-c2_.  
Вам нужно, что бы подключить порт отладки ключа к портам _GPIO_ из _Raspberry_, например кабель _CC_ и четыре линии _Dupont_ (см. Далее).   
[WiringPi](http://wiringpi.com/) должен быть установлен (, если он не предустановлен, вы обычно можете установить его с помощью `sudo apt install wiringpi`, в противном случае см. веб-сайт [ _Gordon_](http://wiringpi.com/) или [this этот альтернативный сайт](https://github.com/WiringPi/WiringPi)).  

Я проецировал _flash\_cc2531_ на _Raspberry Pi 3_ с помощью _raspbian_, но сообщалось о других моделях для успешных программ:
* на pi 4, вам понадобится версия 2.52 из (zzz10 ):  [) install _wiring Pi_ 2.52 с _сайта Гордона_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* на pi 1 и pi 2 вам понадобится[для использования других контактов](#uzu_aliajn_pinglojn).  




* в любом случае вам, вероятно, потребуется установить опцию временной развертки ( _"-m"_ ).





## Подготовлено

Загрузите _flash\_cc2531_ на свой _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Подключите следующие контакты от порта отладки к порту GPIO:

1. контакт 1 ( _GND_ ) -> контакт 39 ( _GND_ )


2. контакт 7 ( _reset_ ) -> контакт 35 ( _wPi 24, BCM19_ )


3. контакт 3 ( _DC_ ) -> контакт 36 ( _wPi 27, BCM16_ )


4. контакт 4 ( _DD_ ) -> контакт 38 ( _wPi 28, BCM20_ )



и вставьте USB-ключ в порт.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


попробуйте это:
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


## использовать
Чтобы сохранить содержимое флэш-памяти в файл save.hex:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

Чтобы стереть флэш-память:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

Чтобы запрограммировать файл на ключ _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="использовать_aliajn_контакты"></ a>
## Используйте другие булавки
все команды принимают следующие аргументы:
* _-c_ pin: изменить вывод _DC_ (по умолчанию 27)
* _-d_ pin: сменить вывод _DD_ )(по умолчанию 28)
* _-r_ pin: изменить вывод _reset_ (default 24)
* _-m_ : изменить множитель задержки, и, следовательно, основной время (по умолчанию: автоматическая настройка)

Используемая нумерация выводов соответствует _wiringPi_. Используйте `gpio readall` , чтобы разместить макет в столбце _Raspberry_ ( _wPi_).

Например, если вы хотите использовать контакты 3, 11 и 13: 
Подключите следующие контакты от порта отладки к шлюзу _GPIO_:
1.pin 1 ( _GND_ ) ) -> ) контакт 14 ( _GND_ )
2. контакт 7 ( _reset_ ) -> контакт 3 ( _wPi 8, BCM2_ )
3. контакт 3 ( _DC_ ) -> контакт 11 ( _wPi 0, BCM17_ )
4. контакт 4 ( _DD_ ) -> контакт 13 ( ( zzz42) wPi 2, BCM27_ )

и теперь вы можете читать ID, сохранять, удалять и записывать флеш-память с помощью следующих команд:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## что если это не сработает?

1. остановите все другие программы.


2. перед программированием установите скорость процессора. Пример:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## Лицензия

Этот проект находится под лицензией GPL v3 (см. _COPYING_).
