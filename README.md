# MorningClock

## 背景

没事就来做个闹钟吧！

fork from [MorningRing](https://github.com/morningtzh/MorningRing)

## 系统设计

### 实体部分

- ESP32-s3开发板
- WS2812 点阵屏
- INMP441 远场麦克风
- PCM5102 DAC
- 来个喇叭

## 软件部分

软件分为上位机和单片机系统。

单片机系统主要是点阵屏控制，易用性方面需要增加wifi链接 / 蓝牙连接 / OTA升级功能。另外经历足够的情况下增加小程序简易控制功能。

- 单片机系统
   - 系统功能
      - WI-FI连接
      - 蓝牙连接
      - OTA升级
      - WEB简易控制端
   - 点阵屏控制
      - UI模块
