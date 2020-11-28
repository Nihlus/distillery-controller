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

#include "abstractions/Screen.h"

Screen::Screen
(
    uint8_t sclkPin,
    uint8_t mosiPin,
    uint8_t dcPin,
    uint8_t csPin,
    uint8_t rstPin,
    uint8_t width,
    uint8_t height
) noexcept :
    _sclkPin(sclkPin),
    _mosiPin(mosiPin),
    _dcPin(dcPin),
    _csPin(csPin),
    _rstPin(rstPin),
    _width(width),
    _height(height),
    _lcd(_width, _height, &SPI, _csPin, _dcPin, _rstPin)
{
}

void Screen::initialize(uint32_t frequency)
{
    _lcd.begin(frequency);
}

void Screen::clear()
{
    _lcd.fillScreen(colours::Black);
}

Adafruit_GFX& Screen::getSurface() noexcept
{
    return _lcd;
}
