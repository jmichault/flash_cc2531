---
lang: zh
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 重要的！
title: 最主要的
---

# _flash\_cc2531_
 _flash\_cc2531_ 允许您从 _Raspberry_编程CC2531 USB记忆棒，而无需 _Arduino_ 或 _CC Debugger_。

## 先决条件
您需要 _Raspberry_ 或 _Odroid-c2_。  
您需要将密钥的调试端口连接到 _Raspberry_的端口 _GPIO_ 的设备，例如电缆 _CC_ 和四根线 _Dupont_ (，请参见)。   
[必须预先安装（ringz15）WiringPi](http://wiringpi.com/) ，通常可以使用 `sudo apt install wiringpi`进行安装，否则请访问网站 [ _Gordon_](http://wiringpi.com/) 或 [该替代网站](https://github.com/WiringPi/WiringPi))。  

我将 _flash\_cc2531_ 投影到具有 _raspbian_的 _Raspberry Pi 3_ 上，但是已经报告了成功执行程序的其他模型：pi 4上的
* ，您将需要2.52版的 (zzz10 )：（zzz12 ）从 _Gordon网站_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  安装 _接线Pi_ 2.52
* 在pi 1和pi 2上，您需要[使用其他引脚](#uzu_aliajn_pinglojn)。  




* 无论如何，您可能需要设置时基选项 ( _"-m"_ )。





## 准备好的

将 _flash\_cc2531_ 下载到您的 _raspberry_：
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
将以下引脚从调试端口连接到GPIO端口：

1. 针1 ( _GND_ ) -> 针39 ( _GND_ )


2. 针脚7 ( _reset_ ) -> 针脚35 ( _wPi 24, BCM19_ )


3. 针3 ( _DC_ ) -> 针36 ( _wPi 27, BCM16_ )


4. 针脚4 ( _DD_ ) -> 针脚38 ( _wPi 28, BCM20_ )



并将USB密钥插入端口。

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


试试这个：
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


## 采用
要将闪存的内容保存到save.hex文件：
```bash
./cc_read save.hex
```
(dure environ 1 minute).

删除闪存：
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

要对密钥 _CC2531_上的文件进行编程，请执行以下操作：
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="使用_aliajn_引脚"></一个>
## 使用其他别针
所有命令均接受以下参数：
* _-c_ 引脚：更改引脚 _DC_ (默认27)
* _-d_ 引脚：更改引脚 _DD_ )(默认28)
* _-r_ 引脚：更改引脚 _reset_ (默认24)
* _-m_ ：更改延迟的乘数，因此基本时间 (默认值：自动调整)

使用的引脚编号是 _wiringPi_的引脚编号。使用 `gpio readall` 在 _Raspberry_ (列 _wPi_)中具有布局。

例如，如果要使用引脚3、11和13： 
将以下引脚从调试端口连接到门 _GPIO_：
1.pin 1 ( _GND_ ) ) -> ）针14 ( _GND_ )
2.针7 ( _reset_ ) -> 针3 ( _wPi 8, BCM2_ )
3.针3 ( _DC_ ) -> 引脚11 ( _wPi 0, BCM17_ )
4.pin 4 ( _DD_ ) -> 引脚13 ( （ zPi42）wPi 2，BCM27（bzzz43）（bzz44）（bzz45）

现在，您可以使用以下命令读取ID，保存，删除和写入闪存：
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## 如果不起作用怎么办？

1. 停止所有其他程序。


2. 在编程之前设置处理器速度。示例：  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## 执照

此项目已获得GPL v3 (许可，请参阅 _COPYING_)。
