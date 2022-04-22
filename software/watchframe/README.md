<h1 align = "center">🌟 Watchframe🌟</h1>

# Introduction
### This example introduces an Arduino based watch framework. Concept of having watch faces, settings, independent apps. Enable developers to contribute their own code to this framework. Hope to play a role in attracting jade.

>### 1. How to install it? <br>
>Add TWatch_2021_Library to `Arduino->Library`. Uncomment the corresponding model in `TWatch_2021_Library/src/TWatch_config.h`. Open `watchframe.ino` and choose to upload as shown.

>### 2. How to add my application code in the menu interface?<br>
> There are three folders in `src/Utils`. Corresponding dial interface files, application files and widget files respectively. There are blank demo examples in the watch face and application folder, which are used to teach how to create your own application/watch face.
At the end of the addition, you need to add a registration event in PageManager/PageManager.cpp. The dial is on line `59` and the application is on line `74`.

### This routine will be continuously updated and maintained. I hope players will actively contribute to the code, in order to further improve the watch framework. Hope you have fun.

>## Log:
> 2022-04-22:Adding example for the first time.--Mikcy.