---
lang: ja
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 必需品！
title: 重要なこと
---

# _flash\_cc2531_
 _flash\_cc2531_ を使用すると、 _Arduino_ または _CC Debugger_を必要とせずに、 _Raspberry_からCC2531USBスティックをプログラムできます。

## 前提条件
 _Raspberry_ または _Odroid-c2_のいずれかが必要です。  
キーのデバッグポートを _Raspberry_のポート _GPIO_ に接続するものが必要です。たとえば、ケーブル _CC_ と4本の線 _Dupont_ (を参照してください)。   
[WiringPi](http://wiringpi.com/) が事前にインストールされていない場合は、インストールする必要があります (。通常は `sudo apt install wiringpi`を使用してインストールできます。それ以外の場合は、Webサイト [ _Gordon_](http://wiringpi.com/) または [を参照してください。その代替サイト](https://github.com/WiringPi/WiringPi))。  

 _flash\_cc2531_ を _raspbian_で _Raspberry Pi 3_ に投影しましたが、成功したプログラムについて他のモデルが報告されています：pi 4の
* ：（ zzz10）zzz10 )のバージョン2.52が必要です：（zzz12 ） _ゴードンのウェブサイト_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  から _配線Pi_ 2.52をインストールします
* pi1とpi2では、他のピン](#uzu_aliajn_pinglojn)を使用するために[が必要になります。  




* とにかく、おそらくタイムベースオプション ( _"-m"_ )を設定する必要があります。





## 準備

 _flash\_cc2531_ を _raspberry_にダウンロードします：
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
次のピンをデバッグポートからGPIOポートに接続します。

1. ピン1 ( _GND_ ) -> ピン39 ( _GND_ )


2. ピン7 ( _reset_ ) -> ピン35 ( _wPi 24, BCM19_ )


3. ピン3 ( _DC_ ) -> ピン36 ( _wPi 27, BCM16_ )


4. ピン4 ( _DD_ ) -> ピン38 ( _wPi 28, BCM20_ )



USBキーをポートに挿入します。

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


これを試してください：
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


## 使用する
フラッシュメモリの内容をsave.hexファイルに保存するには：
```bash
./cc_read save.hex
```
(dure environ 1 minute).

フラッシュメモリを消去するには：
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

キー _CC2531_でファイルをプログラムするには：
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="use_aliajn_pins"></ a>
## 他のピンを使用する
すべてのコマンドは次の引数を受け入れます：
* _-c_ ピン：ピンの変更 _DC_ (デフォルト27)
* _-d_ ピン：ピンの変更 _DD_ )(デフォルト28)
* _-r_ ピン：ピンの変更 _reset_ (デフォルト24)
* _-m_ ：遅延の乗数を変更するため、基本時間 (デフォルト：自動調整)

使用されるピン番号は _wiringPi_のピン番号です。 `gpio readall` を使用して、 _Raspberry_ (列 _wPi_)にレイアウトを配置します。

たとえば、ピン3、11、および13を使用する場合： 
次のピンをデバッグポートからゲート _GPIO_に接続します。
1。ピン1 ( _GND_ ) ) -> ）ピン14 ( _GND_ )
2。ピン7 ( _reset_ ) -> ピン3 ( _wPi 8, BCM2_ )
3。ピン3 ( _DC_ ) -> ピン11 ( _wPi 0, BCM17_ )
4。ピン4 ( _DD_ ) -> ピン13 ( （ zzz42）wPi 2、BCM27_ )

これで、次のコマンドを使用して、IDの読み取り、保存、削除、およびフラッシュメモリの書き込みを行うことができます。
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## それが機能しない場合はどうなりますか？

1. 他のすべてのプログラムを停止します。


2. プログラミングする前にプロセッサ速度を設定します。例：  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## ライセンス

このプロジェクトは、GPL v3 (でライセンスされています（zzz2を参照）。
