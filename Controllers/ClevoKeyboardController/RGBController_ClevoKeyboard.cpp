/*---------------------------------------------------------*\
| RGBController_ClevoKeyboard.cpp                           |
|                                                           |
|   RGBController for Clevo per-key RGB keyboard (ITE 8291) |
|                                                           |
|   Kyle Cascade (kyle@cascade.family)          16 Jan 2026 |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/

#include "RGBController_ClevoKeyboard.h"
#include "KeyboardLayoutManager.h"
#include <iostream>
#include <string>
#include <sstream>

/**------------------------------------------------------------------*\
    @name CLEVO Keyboard
    @category Keyboard
    @type USB
    @save :x:
    @direct :white_check_mark:
    @effects :white_check_mark:
    @detectors DetectClevoKeyboardControllers
    @comment Per-key RGB keyboard on CLEVO laptops using ITE 8291 controller.
\*-------------------------------------------------------------------*/

RGBController_ClevoKeyboard::RGBController_ClevoKeyboard(ClevoKeyboardController* controller_ptr)
{
    controller                      = controller_ptr;

    name                            = "CLEVO Keyboard";
    vendor                          = "CLEVO Computers";
    type                            = DEVICE_TYPE_KEYBOARD;
    description                     = "CLEVO Laptop Keyboard";
    location                        = controller->GetDeviceLocation();
    serial                          = controller->GetSerialString();
    version                         = controller->GetFirmwareVersion();

    mode Direct;
    Direct.name                     = "Direct";
    Direct.value                    = CLEVO_KEYBOARD_MODE_DIRECT;
    Direct.flags                    = MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_BRIGHTNESS;
    Direct.brightness_min           = CLEVO_KEYBOARD_BRIGHTNESS_MIN;
    Direct.brightness_max           = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Direct.brightness               = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Direct.color_mode               = MODE_COLORS_PER_LED;
    modes.push_back(Direct);

    mode Rainbow;
    Rainbow.name                    = "Rainbow";
    Rainbow.value                   = CLEVO_KEYBOARD_MODE_RAINBOW;
    Rainbow.flags                   = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS;
    Rainbow.speed_min               = CLEVO_KEYBOARD_SPEED_MAX;
    Rainbow.speed_max               = CLEVO_KEYBOARD_SPEED_MIN;
    Rainbow.speed                   = 0x05;
    Rainbow.brightness_min          = CLEVO_KEYBOARD_BRIGHTNESS_MIN;
    Rainbow.brightness_max          = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Rainbow.brightness              = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Rainbow.color_mode              = MODE_COLORS_NONE;
    modes.push_back(Rainbow);

    mode Wave;
    Wave.name                       = "Wave";
    Wave.value                      = CLEVO_KEYBOARD_MODE_WAVE;
    Wave.flags                      = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_DIRECTION_LR | MODE_FLAG_HAS_DIRECTION_UD | MODE_FLAG_HAS_MODE_SPECIFIC_COLOR;
    Wave.speed_min                  = CLEVO_KEYBOARD_SPEED_MAX;
    Wave.speed_max                  = CLEVO_KEYBOARD_SPEED_MIN;
    Wave.speed                      = 0x05;
    Wave.brightness_min             = CLEVO_KEYBOARD_BRIGHTNESS_MIN;
    Wave.brightness_max             = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Wave.brightness                 = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Wave.direction                  = MODE_DIRECTION_LEFT;
    Wave.colors_min                 = 1;
    Wave.colors_max                 = 1;
    Wave.colors.resize(1);
    Wave.color_mode                 = MODE_COLORS_MODE_SPECIFIC;
    modes.push_back(Wave);

    mode Breathing;
    Breathing.name                  = "Breathing";
    Breathing.value                 = CLEVO_KEYBOARD_MODE_BREATH;
    Breathing.flags                 = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_MODE_SPECIFIC_COLOR;
    Breathing.speed_min             = CLEVO_KEYBOARD_SPEED_MAX;
    Breathing.speed_max             = CLEVO_KEYBOARD_SPEED_MIN;
    Breathing.speed                 = 0x05;
    Breathing.brightness_min        = CLEVO_KEYBOARD_BRIGHTNESS_MIN;
    Breathing.brightness_max        = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Breathing.brightness            = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Breathing.colors_min            = 1;
    Breathing.colors_max            = 1;
    Breathing.colors.resize(1);
    Breathing.color_mode            = MODE_COLORS_MODE_SPECIFIC;
    modes.push_back(Breathing);

    mode Reactive;
    Reactive.name                   = "Reactive";
    Reactive.value                  = CLEVO_KEYBOARD_MODE_REACTIVE;
    Reactive.flags                  = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_MODE_SPECIFIC_COLOR;
    Reactive.speed_min              = CLEVO_KEYBOARD_SPEED_MAX;
    Reactive.speed_max              = CLEVO_KEYBOARD_SPEED_MIN;
    Reactive.speed                  = 0x05;
    Reactive.brightness_min         = CLEVO_KEYBOARD_BRIGHTNESS_MIN;
    Reactive.brightness_max         = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Reactive.brightness             = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Reactive.colors_min             = 1;
    Reactive.colors_max             = 1;
    Reactive.colors.resize(1);
    Reactive.color_mode             = MODE_COLORS_MODE_SPECIFIC;
    modes.push_back(Reactive);

    mode Ripple;
    Ripple.name                     = "Ripple";
    Ripple.value                    = CLEVO_KEYBOARD_MODE_RIPPLE;
    Ripple.flags                    = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_MODE_SPECIFIC_COLOR;
    Ripple.speed_min                = CLEVO_KEYBOARD_SPEED_MAX;
    Ripple.speed_max                = CLEVO_KEYBOARD_SPEED_MIN;
    Ripple.speed                    = 0x05;
    Ripple.brightness_min           = CLEVO_KEYBOARD_BRIGHTNESS_MIN;
    Ripple.brightness_max           = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Ripple.brightness               = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Ripple.colors_min               = 1;
    Ripple.colors_max               = 1;
    Ripple.colors.resize(1);
    Ripple.color_mode               = MODE_COLORS_MODE_SPECIFIC;
    modes.push_back(Ripple);

    mode Marquee;
    Marquee.name                    = "Marquee";
    Marquee.value                   = CLEVO_KEYBOARD_MODE_MARQUEE;
    Marquee.flags                   = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_MODE_SPECIFIC_COLOR;
    Marquee.speed_min               = CLEVO_KEYBOARD_SPEED_MAX;
    Marquee.speed_max               = CLEVO_KEYBOARD_SPEED_MIN;
    Marquee.speed                   = 0x05;
    Marquee.brightness_min          = CLEVO_KEYBOARD_BRIGHTNESS_MIN;
    Marquee.brightness_max          = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Marquee.brightness              = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Marquee.colors_min              = 1;
    Marquee.colors_max              = 1;
    Marquee.colors.resize(1);
    Marquee.color_mode              = MODE_COLORS_MODE_SPECIFIC;
    modes.push_back(Marquee);

    mode Raindrop;
    Raindrop.name                   = "Raindrop";
    Raindrop.value                  = CLEVO_KEYBOARD_MODE_RAINDROP;
    Raindrop.flags                  = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_MODE_SPECIFIC_COLOR;
    Raindrop.speed_min              = CLEVO_KEYBOARD_SPEED_MAX;
    Raindrop.speed_max              = CLEVO_KEYBOARD_SPEED_MIN;
    Raindrop.speed                  = 0x05;
    Raindrop.brightness_min         = CLEVO_KEYBOARD_BRIGHTNESS_MIN;
    Raindrop.brightness_max         = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Raindrop.brightness             = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Raindrop.colors_min             = 1;
    Raindrop.colors_max             = 1;
    Raindrop.colors.resize(1);
    Raindrop.color_mode             = MODE_COLORS_MODE_SPECIFIC;
    modes.push_back(Raindrop);

    mode Aurora;
    Aurora.name                     = "Aurora";
    Aurora.value                    = CLEVO_KEYBOARD_MODE_AURORA;
    Aurora.flags                    = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_MODE_SPECIFIC_COLOR;
    Aurora.speed_min                = CLEVO_KEYBOARD_SPEED_MAX;
    Aurora.speed_max                = CLEVO_KEYBOARD_SPEED_MIN;
    Aurora.speed                    = 0x05;
    Aurora.brightness_min           = CLEVO_KEYBOARD_BRIGHTNESS_MIN;
    Aurora.brightness_max           = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Aurora.brightness               = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Aurora.colors_min               = 1;
    Aurora.colors_max               = 1;
    Aurora.colors.resize(1);
    Aurora.color_mode               = MODE_COLORS_MODE_SPECIFIC;
    modes.push_back(Aurora);

    mode Spark;
    Spark.name                      = "Spark";
    Spark.value                     = CLEVO_KEYBOARD_MODE_SPARK;
    Spark.flags                     = MODE_FLAG_HAS_SPEED | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_MODE_SPECIFIC_COLOR;
    Spark.speed_min                 = CLEVO_KEYBOARD_SPEED_MAX;
    Spark.speed_max                 = CLEVO_KEYBOARD_SPEED_MIN;
    Spark.speed                     = 0x05;
    Spark.brightness_min            = CLEVO_KEYBOARD_BRIGHTNESS_MIN;
    Spark.brightness_max            = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Spark.brightness                = CLEVO_KEYBOARD_BRIGHTNESS_MAX;
    Spark.colors_min                = 1;
    Spark.colors_max                = 1;
    Spark.colors.resize(1);
    Spark.color_mode                = MODE_COLORS_MODE_SPECIFIC;
    modes.push_back(Spark);

    mode Off;
    Off.name                        = "Off";
    Off.value                       = 0xFF;
    Off.flags                       = 0;
    Off.color_mode                  = MODE_COLORS_NONE;
    modes.push_back(Off);

    SetupZones();
}

RGBController_ClevoKeyboard::~RGBController_ClevoKeyboard()
{
    for(unsigned int zone_idx = 0; zone_idx < zones.size(); zone_idx++)
    {
        if(zones[zone_idx].matrix_map != nullptr)
        {
            delete[] zones[zone_idx].matrix_map->map;
            delete zones[zone_idx].matrix_map;
        }
    }

    delete controller;
}

void RGBController_ClevoKeyboard::SetupZones()
{
    /*---------------------------------------------------------*\
    | Create keyboard layout using KeyboardLayoutManager        |
    \*---------------------------------------------------------*/
    KeyboardLayoutManager new_kb(KEYBOARD_LAYOUT_ISO_QWERTY,
                                 clevo_keyboard_layout.base_size,
                                 clevo_keyboard_layout.key_values);

    new_kb.ChangeKeys(clevo_keyboard_layout);

    /*---------------------------------------------------------*\
    | Create a matrix zone for the keyboard                     |
    \*---------------------------------------------------------*/
    zone keyboard_zone;

    keyboard_zone.name              = ZONE_EN_KEYBOARD;
    keyboard_zone.type              = ZONE_TYPE_MATRIX;
    keyboard_zone.leds_count        = new_kb.GetKeyCount();
    keyboard_zone.leds_min          = keyboard_zone.leds_count;
    keyboard_zone.leds_max          = keyboard_zone.leds_count;

    /*---------------------------------------------------------*\
    | Set up the matrix map using KLM dimensions                |
    \*---------------------------------------------------------*/
    keyboard_zone.matrix_map            = new matrix_map_type;
    keyboard_zone.matrix_map->height    = new_kb.GetRowCount();
    keyboard_zone.matrix_map->width     = new_kb.GetColumnCount();
    keyboard_zone.matrix_map->map       = new unsigned int[keyboard_zone.matrix_map->height * keyboard_zone.matrix_map->width];

    new_kb.GetKeyMap(keyboard_zone.matrix_map->map, KEYBOARD_MAP_FILL_TYPE_COUNT);

    zones.push_back(keyboard_zone);

    /*---------------------------------------------------------*\
    | Create LEDs from the KeyboardLayoutManager data           |
    \*---------------------------------------------------------*/
    for(unsigned int led_idx = 0; led_idx < keyboard_zone.leds_count; led_idx++)
    {
        led new_led;

        new_led.name    = new_kb.GetKeyNameAt(led_idx);

        new_led.value   = GetCorrectHWValue(new_led.name);

        leds.push_back(new_led);
    }


        SetupColors();

    /*---------------------------------------------------------*\
    | Create buffer map to translate OpenRGB LED order to       |
    | hardware LED order. The hardware expects 126 color values |
    | indexed by LED position (0-125).                          |
    \*---------------------------------------------------------*/
    null_color = 0x00000000;
    buffer_map.resize(CLEVO_KEYBOARD_NUM_LEDS, &null_color);

    for(size_t led_idx = 0; led_idx < leds.size(); led_idx++)
    {
        buffer_map[leds[led_idx].value] = &colors[led_idx];
    }
}

unsigned int RGBController_ClevoKeyboard::GetCorrectHWValue(const std::string& key_name)
{
    // F-row
    if(key_name == "Key: Escape") return 105;
    if(key_name == "Key: F1") return 106;
    if(key_name == "Key: F2") return 107;
    if(key_name == "Key: F3") return 108;
    if(key_name == "Key: F4") return 109;
    if(key_name == "Key: F5") return 110;
    if(key_name == "Key: F6") return 111;
    if(key_name == "Key: F7") return 112;
    if(key_name == "Key: F8") return 113;
    if(key_name == "Key: F9") return 114;
    if(key_name == "Key: F10") return 115;
    if(key_name == "Key: F11") return 116;
    if(key_name == "Key: F12") return 117;
    if(key_name == "Key: Print Screen") return 118;
    if(key_name == "Key: `") return 84;
    if(key_name == "Key: 1") return 85;
    if(key_name == "Key: 2") return 86;
    if(key_name == "Key: 3") return 87;
    if(key_name == "Key: 4") return 88;
    if(key_name == "Key: 5") return 89;
    if(key_name == "Key: 6") return 90;
    if(key_name == "Key: 7") return 91;
    if(key_name == "Key: 8") return 92;
    if(key_name == "Key: 9") return 93;
    if(key_name == "Key: 0") return 94;
    if(key_name == "Key: -") return 95;
    if(key_name == "Key: =") return 96;
    if(key_name == "Key: Backspace") return 98;
    if(key_name == "Key: Insert") return 119;
    if(key_name == "Key: Home") return 121;
    if(key_name == "Key: Page Up") return 123;
    if(key_name == "Key: Delete") return 120;
    if(key_name == "Key: End") return 122;
    if(key_name == "Key: Page Down") return 124;
    if(key_name == "Key: Tab") return 63;
    if(key_name == "Key: Q") return 65;
    if(key_name == "Key: W") return 66;
    if(key_name == "Key: E") return 67;
    if(key_name == "Key: R") return 68;
    if(key_name == "Key: T") return 69;
    if(key_name == "Key: Y") return 70;
    if(key_name == "Key: U") return 71;
    if(key_name == "Key: I") return 72;
    if(key_name == "Key: O") return 73;
    if(key_name == "Key: P") return 74;
    if(key_name == "Key: [") return 75;
    if(key_name == "Key: ]") return 76;
    if(key_name == "Key: Caps Lock") return 42;
    if(key_name == "Key: A") return 44;
    if(key_name == "Key: S") return 45;
    if(key_name == "Key: D") return 46;
    if(key_name == "Key: F") return 47;
    if(key_name == "Key: G") return 48;
    if(key_name == "Key: H") return 49;
    if(key_name == "Key: J") return 50;
    if(key_name == "Key: K") return 51;
    if(key_name == "Key: L") return 52;
    if(key_name == "Key: ;") return 53;
    if(key_name == "Key: '") return 54;
    if(key_name == "Key: #") return 55;
    if(key_name == "Key: Enter") return 77;
    if(key_name == "Key: Left Shift") return 22;
    if(key_name == "Key: \\ (ISO)") return 23;
    if(key_name == "Key: Z") return 24;
    if(key_name == "Key: X") return 25;
    if(key_name == "Key: C") return 26;
    if(key_name == "Key: V") return 27;
    if(key_name == "Key: B") return 28;
    if(key_name == "Key: N") return 29;
    if(key_name == "Key: M") return 30;
    if(key_name == "Key: ,") return 31;
    if(key_name == "Key: .") return 32;
    if(key_name == "Key: /") return 33;
    if(key_name == "Key: Right Shift") return 35;
    if(key_name == "Key: Left Control") return 0;
    if(key_name == "Key: Left Fn") return 2;
    if(key_name == "Key: Left Windows") return 3;
    if(key_name == "Key: Left Alt") return 4;
    if(key_name == "Key: Space") return 7;
    if(key_name == "Key: Right Alt") return 10;
    if(key_name == "Key: Right Control") return 12;
    if(key_name == "Key: Up Arrow") return 14;
    if(key_name == "Key: Left Arrow") return 13;
    if(key_name == "Key: Down Arrow") return 18;
    if(key_name == "Key: Right Arrow") return 15;
    if(key_name == "Key: Num Lock") return 99;
    if(key_name == "Key: Number Pad /") return 100;
    if(key_name == "Key: Number Pad *") return 101;
    if(key_name == "Key: Number Pad -") return 102;
    if(key_name == "Key: Number Pad +") return 81;
    if(key_name == "Key: Number Pad 7") return 78;
    if(key_name == "Key: Number Pad 8") return 79;
    if(key_name == "Key: Number Pad 9") return 80;
    if(key_name == "Key: Number Pad 6") return 59;
    if(key_name == "Key: Number Pad 4") return 57;
    if(key_name == "Key: Number Pad 5") return 58;
    if(key_name == "Key: Number Pad 1") return 36;
    if(key_name == "Key: Number Pad 2") return 37;
    if(key_name == "Key: Number Pad 3") return 38;
    if(key_name == "Key: Number Pad Enter") return 39;
    if(key_name == "Key: Number Pad 0") return 16;
    if(key_name == "Key: Number Pad .") return 17;
    return 0;
}


void RGBController_ClevoKeyboard::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_ClevoKeyboard::DeviceUpdateLEDs()
{
    /*---------------------------------------------------------*\
    | Build color data array using buffer map and send to device|
    | The buffer_map translates from hardware LED index to the  |
    | corresponding color pointer for that LED.                 |
    \*---------------------------------------------------------*/
    unsigned char color_data[CLEVO_KEYBOARD_NUM_LEDS * 3];

    for(int i = 0; i < CLEVO_KEYBOARD_NUM_LEDS; i++)
    {
        color_data[i * 3 + 0] = RGBGetRValue(*buffer_map[i]);
        color_data[i * 3 + 1] = RGBGetGValue(*buffer_map[i]);
        color_data[i * 3 + 2] = RGBGetBValue(*buffer_map[i]);
    }

    controller->SendColors(color_data, modes[active_mode].brightness);
}

void RGBController_ClevoKeyboard::UpdateZoneLEDs(int /*zone*/)
{
    DeviceUpdateLEDs();
}

void RGBController_ClevoKeyboard::UpdateSingleLED(int /*led*/)
{
    DeviceUpdateLEDs();
}

void RGBController_ClevoKeyboard::DeviceUpdateMode()
{
    unsigned char mode_value = modes[active_mode].value;

    /*---------------------------------------------------------*\
    | Handle Off mode                                           |
    \*---------------------------------------------------------*/
    if(mode_value == 0xFF)
    {
        controller->TurnOff();
        return;
    }

    /*---------------------------------------------------------*\
    | Handle Direct (per-key) mode                              |
    \*---------------------------------------------------------*/
    if(mode_value == CLEVO_KEYBOARD_MODE_DIRECT)
    {
        DeviceUpdateLEDs();
        return;
    }

    /*---------------------------------------------------------*\
    | Handle built-in effect modes                              |
    \*---------------------------------------------------------*/
    unsigned char brightness = modes[active_mode].brightness;
    unsigned char speed      = modes[active_mode].speed;
    unsigned char behaviour  = 0x00;

    /*---------------------------------------------------------*\
    | Set direction for wave mode                               |
    \*---------------------------------------------------------*/
    if(mode_value == CLEVO_KEYBOARD_MODE_WAVE)
    {
        switch(modes[active_mode].direction)
        {
            case MODE_DIRECTION_LEFT:
                behaviour = CLEVO_KEYBOARD_DIRECTION_LEFT;
                break;
            case MODE_DIRECTION_RIGHT:
                behaviour = CLEVO_KEYBOARD_DIRECTION_RIGHT;
                break;
            case MODE_DIRECTION_UP:
                behaviour = CLEVO_KEYBOARD_DIRECTION_UP;
                break;
            case MODE_DIRECTION_DOWN:
                behaviour = CLEVO_KEYBOARD_DIRECTION_DOWN;
                break;
        }
    }

    /*---------------------------------------------------------*\
    | Set mode color if applicable                              |
    \*---------------------------------------------------------*/
    if(modes[active_mode].colors.size() > 0)
    {
        unsigned char red   = RGBGetRValue(modes[active_mode].colors[0]);
        unsigned char green = RGBGetGValue(modes[active_mode].colors[0]);
        unsigned char blue  = RGBGetBValue(modes[active_mode].colors[0]);

        controller->SetModeColor(1, red, green, blue);
    }

    controller->SetMode(mode_value, brightness, speed, behaviour);
}

