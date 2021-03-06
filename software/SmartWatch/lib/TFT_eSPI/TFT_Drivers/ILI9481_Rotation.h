// This is the command sequence that rotates the ILI9481 driver coordinate frame

// #ifdef TFT_MAD_BGR
// #undef TFT_MAD_BGR
// #define TFT_MAD_BGR 0
// #endif

writecommand(TFT_MADCTL);
rotation = m % 4;
switch (rotation)
{
case 0: // Portrait
    writedata(TFT_MAD_BGR | TFT_MAD_SS);
    _width  = _init_width;
    _height = _init_height;
    break;
case 1: // Landscape (Portrait + 90)
    writedata(TFT_MAD_MV | TFT_MAD_BGR);
    _width  = _init_height;
    _height = _init_width;
    break;
case 2: // Inverter portrait
    writedata(TFT_MAD_BGR | TFT_MAD_GS);
    _width  = _init_width;
    _height = _init_height;
    break;
case 3: // Inverted landscape
    writedata(TFT_MAD_MV | TFT_MAD_BGR | TFT_MAD_SS | TFT_MAD_GS);
    _width  = _init_height;
    _height = _init_width;
    break;
}
