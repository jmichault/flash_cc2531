---
lang: zh
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 重要的！
title: 最主要的
---

# _flash\_cc2531_
 _flash\_cc2531_ 允许您从 _Raspberry_对CC2531 USB记忆棒进行编程，而无需 _Arduino_ 或 _CC Debugger_。

## 先决条件
您需要 _Raspberry_ 或 _Odroid-c2_。  
您需要将钥匙的调试端口连接到 _Raspberry_的端口 _GPIO_ 的工具，例如电缆 _CC_ 和四根线 _Dupont_ (，请参见)。   
[如果未预先安装，则必须安装WiringPi](http://wiringpi.com/)  (，通常可以用 `sudo apt install wiringpi`进行安装，否则请访问网站 [ _戈登_](http://wiringpi.com/) 或 [这个替代位置](https://github.com/WiringPi/WiringPi))。  

我将 _Raspberry Pi 3_ 与 _raspbian_投影在 _flash\_cc2531_ 上，但是在其他型号上报告了成功的编程：在pi 4上的
* ，您将需要版本2.52的 _wiringpi_ ：  [安装 _接线Pi_ 从 _2.52戈登网站_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* 在pi 1和pi 2上，您需要 [使用其他引脚](#uzi_aliajn_pinglojn)。  

* 但是，您可能需要设置时基选项 ( _"-m"_ )。



## 准备好的

将 _flash\_cc2531_ 下载到您的 _raspberry_：
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
将以下引脚从调试端口连接到GPIO端口：
1.引脚1 ( _GND_ ) -> 引脚39 ( _GND_ )
第二针7 ( _reset_ ) -> 针35 ( _wPi 24, BCM19_ ）)
3.主轴3 ( _DC_ ) -> 销36 ( _wPi 27, BCM16_ )
4.主轴4 ( _DD_ ) -> 主轴38 ( _wPi 28, BCM20_ )

并将USB密钥插入端口。

下载电缆 _CC_ 和4条线 _Dupont_ 母对母非常适合此目的：
![键的照片和 _覆盆子_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)°）
这是我最喜欢的选择，但是如果没有电缆 _CC_ ，也可以直接在键上焊接电缆 _Dupont_ ：例如，参见网站 [ ）_mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) 或 [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


试试这个：
```bash
cd flash_cc2531
./cc_chipid
```
它必须返回：
```
  ID = b524.
```
如果看到0000或ffff，则出问题了：
* 首先检查接线。
* ，然后尝试更高的基准时间，例如 `./cc_chipid -m 100`或 `./cc_chipid -m 160` 或 `./cc_chipid -m 300`。
* 如果这些都不起作用，请尝试使用 `make`重新编译。


## 采用
要将闪存的内容保存在save.hex文件中：
```bash
./cc_read save.hex
```
(持续约1分钟)。

擦除闪存：
```bash
./cc_erase
```
**注：** 除非 (，否则您 **必须** 删除，除非您真的知道要做什么)。

要将文件编程在键上 _CC2531_：
```bash
./cc_write CC2531ZNP-Prod.hex
```
(持续约3分钟)。

<id ="使用_aliajn_销"></ a>
## 使用其他别针
所有命令均接受以下参数：
* _-c_ 插针：默认情况下更改插针 _DC_ (27)
* _-d_ 引脚：更改引脚 _DD_ )(默认28)
* _-r_ 引脚：更改引脚（°默认为21°）(24)
* _-m_ ：更改延迟的乘数，因此默认为基准时间 (：自动调整)

使用的针脚编号是 _wiringPi_。使用 `gpio readall` 将布局放在 _Raspberry_ (列 _wPi_)中。

例如，如果要使用引脚3、11和13：  
将以下引脚从调试端口连接到门 _GPIO_：
1.引脚1 ( _GND_ ) -> 引脚14 ( ）_GND_ )
2.插针7 ( _reset_ ) -> 插针3 ( _wPi 8, BCM2_ )
3.针脚3 ( _DC_ ) -> 针脚11 ( _wPi 0, BCM17_ )
4.插针4 ( _DD_ ) -> 插针13 ( )_wPi 2， BCM27_ )

现在您可以使用以下命令读取ID，保存，删除和写入闪存：
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

您还可以将默认值更改为 _CCDebugger.h_ ，并使用 `make`编译程序。

## 如果不起作用怎么办？

1. 停止所有其他程序。

2. 在编程之前设置处理器速度。示例：  

```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. 使用-m选项可以增加使用的时间限制。示例：  

```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. 用 `make`重新编译程序。



## 执照

该项目已获得GPL v3许可 (（请参见2°）。
