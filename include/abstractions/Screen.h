//
//  Screen.h
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

#ifndef DISTILLERY_CONTROLLER_SCREEN_H
#define DISTILLERY_CONTROLLER_SCREEN_H

#include <stdint.h>
#include <Adafruit_SSD1351.h>
#include <graphics/GraphicsZone.h>

/**
 * Contains various colours supported by the screen.
 */
namespace colours
{
    constexpr uint16_t Black = 0x0000;
    constexpr uint16_t Blue = 0x001F;
    constexpr uint16_t Red = 0xF800;
    constexpr uint16_t Green = 0x07E0;
    constexpr uint16_t Cyan = 0x07FF;
    constexpr uint16_t Magenta = 0xF81F;
    constexpr uint16_t Yellow = 0xFFE0;
    constexpr uint16_t White = 0xFFFF;
};

/**
 * Represents an abstraction of an LCD screen.
 */
class Screen
{
    /**
     * Holds the clock pin of the LCD screen.
     */
    uint8_t _sclkPin;

    /**
     * Holds the data pin of the LCD screen.
     */
    uint8_t _mosiPin;

    /**
     * Holds the DC select pin of the LCD screen.
     */
    uint8_t _dcPin;

    /**
     * Holds the CS select pin of the LCD screen.
     */
    uint8_t _csPin;

    /**
     * Holds the reset pin of the LCD screen.
     */
    uint8_t _rstPin;
    /**
     * Holds the width of the screen.
     */
    uint8_t _width;

    /**
     * Holds the height of the screen.
     */
    uint8_t _height;

    /**
     * Holds the screen driver.
     */
    Adafruit_SSD1351 _lcd;

public:
    /**
     * Initializes a new instance of the Screen class.
     * @param sclkPin The clock pin.
     * @param mosiPin The data pin.
     * @param dcPin The DC select pin.
     * @param csPin The CS select pin.
     * @param rstPin The reset pin.
     * @param width The width of the screen.
     * @param height The height of the screen.
     */
    explicit Screen
    (
        uint8_t sclkPin,
        uint8_t mosiPin,
        uint8_t dcPin,
        uint8_t csPin,
        uint8_t rstPin,
        uint8_t width,
        uint8_t height
    ) noexcept;

    /**
     * Gets the drawing surface of the screen.
     * @return The graphics zone.
     */
    Adafruit_GFX& getSurface() noexcept;

    /**
     * Initializes the hardware.
     * @param frequency The clock frequency of the SPI bus. Defaults to a system-optimized value.
     */
    void initialize(uint32_t frequency = 0);

    /**
     * Clears the screen.
     */
    void clear();
};

#endif //DISTILLERY_CONTROLLER_SCREEN_H
