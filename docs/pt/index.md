---
lang: pt
lang-niv: auto
lang-ref: 001-ĉefa-afero
layout: page
slug: 'O essencial!'
title: 'A coisa principal'
---

# _flash\_cc2531_
 _flash\_cc2531_ permite que você programe seu stick USB CC2531 a partir de seu _Raspberry_, sem a necessidade de _Arduino_ ou _CC Debugger_.

## Pré-requisitos
Você precisa de _Raspberry_ ou _Odroid-c2_.  
Você precisa do que conectar a porta de depuração da chave às portas _GPIO_ de _Raspberry_, por exemplo, cabo _CC_ e quatro linhas _Dupont_ (veja mais).   
[WiringPi](http://wiringpi.com/) deve ser instalado (se não estiver pré-instalado, você geralmente pode instalá-lo com `sudo apt install wiringpi`, caso contrário, consulte o site [ _Gordon_](http://wiringpi.com/) ou [este esse site alternativo](https://github.com/WiringPi/WiringPi)).  

Eu projetei _flash\_cc2531_ em a _Raspberry Pi 3_ com _raspbian_, mas outros modelos foram relatados para programas de sucesso:
* em pi 4, você precisará da versão 2.52 de (zzz10 ):  [) instalar _fiação Pi_ 2.52 do _site de Gordon_](http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/)  
* no pi 1 e no pi 2 você precisará[para usar outros pinos](#uzu_aliajn_pinglojn).  




* de qualquer forma, você provavelmente precisará definir a opção de base de tempo ( _"-m"_ ).





## Preparado

Baixe _flash\_cc2531_ para seu _raspberry_:
```bash
git clone https://github.com/jmichault/flash_cc2531.git
```
Conecte os seguintes pinos da porta de depuração à porta GPIO:

1. pino 1 ( _GND_ ) -> pino 39 ( _GND_ )


2. pino 7 ( _reset_ ) -> pino 35 ( _wPi 24, BCM19_ )


3. pino 3 ( _DC_ ) -> pino 36 ( _wPi 27, BCM16_ )


4. pino 4 ( _DD_ ) -> pino 38 ( _wPi 28, BCM20_ )



e insira a chave USB em uma porta.

Un câble de téléchargement _CC_ et 4 lignes _Dupont_ Femelle à Femelle sont parfaits à cet effet:
![photo de la clé et de la _framboise_](https://github.com/jmichault/files/raw/master/Raspberry-CC2531.jpg)
C'est mon option préférée, mais si vous n'avez pas de câble _CC_ vous pouvez aussi souder directement les câbles _Dupont_ sur la clé : voir par exemple le site [ _mariva.com_](https://lemariva.com/blog/2019/08/zigbee-flashing-cc2531-using-raspberry-pi-without-cc-debugger) ou [ _notenoughtech.com_](https://notenoughtech.com/home-automation/flashing-cc2531-without-cc-debugger/)


tente isto:
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


## usar
Para salvar o conteúdo da memória flash no arquivo save.hex:
```bash
./cc_read save.hex
```
(dure environ 1 minute).

Para apagar a memória flash:
```bash
./cc_erase
```
**Remarque:** Vous **devez** effacer avant d'écrire (sauf si vous savez vraiment ce que vous allez faire).

Para programar o arquivo na chave _CC2531_:
```bash
./cc_write CC2531ZNP-Prod.hex
```
(dure environ 3 minutes).

<a id ="usar_aliajn_pinos"></ a>
## Use outros pinos
todos os comandos aceitam os seguintes argumentos:
* _-c_ pino: alterar pino _DC_ (padrão 27)
* _-d_ pino: alterar pino _DD_ )(padrão 28)
* _-r_ pino: alterar pino _reset_ (padrão 24)
* _-m_ : alterar o multiplicador do atraso e, portanto, o básico tempo (padrão: ajuste automático)

a numeração de pinos usada é a de _wiringPi_. Use `gpio readall` para ter o layout em sua coluna _Raspberry_ ( _wPi_).

Por exemplo, se você quiser usar os pinos 3, 11 e 13: 
Conecte os seguintes pinos da porta de depuração à porta _GPIO_:
1.pin 1 ( _GND_ ) ) -> ) pino 14 ( _GND_ )
2. pino 7 ( _reset_ ) -> pino 3 ( _wPi 8, BCM2_ )
3. pino 3 ( _DC_ ) -> pino 11 ( _wPi 0, BCM17_ )
4.pin 4 ( _DD_ ) -> pino 13 ( ( zzz42) wPi 2, BCM27_ )

e agora você pode ler ID, salvar, excluir e gravar memória flash com os seguintes comandos:
```bash
./cc_chipid -r 8 -c 0 -d 2
./cc_read -r 8 -c 0 -d 2 save.hex
./cc_erase -r 8 -c 0 -d 2
./cc_write -r 8 -c 0 -d 2 CC2531ZNP-Prod.hex
```

Vous pouvez également changer les valeurs par défaut dans _CCDebugger.h_ puis compiler les programmes avec `make`.

## e se não funcionar?

1. pare todos os outros programas.


2. defina a velocidade do processador antes de programar. Exemplo:  


```bash
sudo echo performance >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. utilisez l'option -m pour augmenter les délais utilisés. Exemple:  


```bash
./cc_write -m 300 CC2531ZNP-Prod.hex
```
4. recompilez le logiciel avec `make`.



## Licença

Este projeto está licenciado sob a GPL v3 (, consulte _COPYING_).
