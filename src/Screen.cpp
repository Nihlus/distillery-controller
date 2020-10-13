//
//  Screen.cpp.c
//
//  Author:
//       Jarl Gullberg <jarl.gullberg@gmail.com>
//
//  Copyright (c) 2020 Jarl Gullberg
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <Wire.h>

#include "Screen.h"

Screen::Screen(uint8_t dataPin, uint8_t clockPin, uint8_t i2cAddress, uint8_t width, uint8_t height) noexcept :
    _dataPin(dataPin),
    _clockPin(clockPin),
    _i2cAddress(i2cAddress),
    _width(width),
    _height(height),
    _lcd(_width, _height, &Wire, -1),
    _yellowZone(_lcd, 0, 0, 128, 12),
    _blueZone(_lcd, 0, 12, 128, 52)
{
}

GraphicsZone& Screen::getYellowZone() noexcept
{
    return _yellowZone;
}

GraphicsZone& Screen::getBlueZone() noexcept
{
    return _blueZone;
}

void Screen::initialize()
{
    _lcd.begin(SSD1306_SWITCHCAPVCC, _i2cAddress);
}

void Screen::clear()
{
    _lcd.clearDisplay();
}

void Screen::display()
{
    _lcd.display();
}
