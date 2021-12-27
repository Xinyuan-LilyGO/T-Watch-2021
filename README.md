<h1 align = "center">🌟 T-Watch-2021🌟</h1>

## Pinout
![image](https://github.com/Xinyuan-LilyGO/T-Watch-2021/blob/main/image/T-WATCH2021-V1.0-en.jpg)

![image](https://github.com/Xinyuan-LilyGO/T-Watch-2021/blob/main/image/T-WATCH2021-V1.1-en.jpg)

![image](https://github.com/Xinyuan-LilyGO/T-Watch-2021/blob/main/image/image5.jpg)


## Version update log
- Added V1.1 version, mainly adding RTC alarm clock interrupt, focusing all interrupts on the IO32 pin.date : 2021-12-15


## 快速开始:
1. 安装[VSCODE](https://code.visualstudio.com/)和[Python](https://www.python.org/)
2. 在VSCODE扩展中搜索PlatformIO插件并安装。
3. 安装完成，重新加载后，左下角会多一个小房子图标，点击后即可显示Platformio IDE主页
4. 点击文件->打开文件夹->选择software文件夹，点击左下角(√)符号进行编译 (→)代表上传.

-------------------------------------------------

## Quick start:

1. Install[VSCODE](https://code.visualstudio.com/)and[Python](https://www.python.org/)
2. Search for the PlatformIO plug-in in the VSCODE extension and install it.
3. After the installation is complete and the reload is completed, there will be a small house icon in the lower left corner. Click to display the Platformio IDE home page
4. Go to file - > Open folder - > Select the software folder and click the (√) symbol in the lower left corner to compile (→) for upload.

|  Product  |                                                            Product  Link                                                            |
| :-------: | :---------------------------------------------------------------------------------------------------------------------------------: |
| T-Watch-2021 | [Taobao](https://item.taobao.com/item.htm?spm=a1z10.3-c-s.w4002-23579470099.9.7787566ddFhogE&id=652090352252) |



## Library 

1. Copy the `TWatch_2021_Library` folder to the `D:\Users\Your account\Documents\Arduino\libraries `directory.
2. Select in Arduino -> Tools
- board -> ESP32 Dev Module 
- Arduino Runs on -> Core 1
- port -> Need to check the corresponding port in the task management area, remember to install the driver
- Flash Mode -> QIO
- Flash Size -> 8MB
- PSRAM -> Enable 

Other options are default or can be customized

3. File -> Examples -> `TWatch_2021_Library` -> basicUnit

4. The configuration file macro definition of this library is mainly in the `TWatch_config.h` and `TWatch2021_V1.h` files in the library.

5. Most of the examples are only used as hardware function demonstrations. This library only completes some initialization work and some demonstrations. For more advanced gameplay, please see `TWatch_hal.h`, to understand how to initialize, after being familiar with it, you can completely leave this library for more advanced gameplay

## To do
1. ~~Need to port V8 version of LVGL GUI support.~~
2. Add more sample programs.
3. Add WIFI and BLE fast interface.



### Update log

2021.12.27

- Released the V1.1 version of the watch motherboard, mainly adding alarm interrupts, adjusting the position of the screen cable and vibration current limit, and optimizing the overall sleep power consumption
- Fix motion interruption correction, add raise hand, single click, double click interrupt..
- Add LVGL support
- Add V0.0.2 version library

2021.10.19 
- Add V0.0.1 version library
