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
#include <Adafruit_SSD1306.h>
#include <graphics/GraphicsZone.h>

/**
 * Represents an abstraction of an LCD screen.
 */
class Screen
{
    /**
     * Holds the data pin of the LCD screen.
     */
    uint8_t _dataPin;

    /**
     * Holds the clock pin of the LCD screen.
     */
    uint8_t _clockPin;

    /**
     * Holds the I²C address of the screen.
     */
    uint8_t _i2cAddress;

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
    Adafruit_SSD1306 _lcd;

    /**
     * Holds the graphics context for the yellow part of the screen.
     */
    GraphicsZone _yellowZone;

    /**
     * Holds the graphics context for the blue part of the screen.
     */
    GraphicsZone _blueZone;

public:
    /**
     * Initializes a new instance of the Screen class.
     * @param dataPin The data pin.
     * @param clockPin The clock pin.
     * @param i2cAddress The I²C address.
     * @param width The width of the screen.
     * @param height The height of the screen.
     */
    explicit Screen(uint8_t dataPin, uint8_t clockPin, uint8_t i2cAddress, uint8_t width, uint8_t height) noexcept;

    /**
     * Gets a graphics context that wraps the yellow part of the screen.
     * @return The graphics context.
     */
    GraphicsZone& getYellowZone() noexcept;

    /**
     * Gets a graphics context that wraps the blue part of the screen.
     * @return The graphics context.
     */
    GraphicsZone& getBlueZone() noexcept;

    /**
     * Initializes the hardware.
     */
    void initialize();

    /**
     * Clears the screen.
     */
    void clear();

    /**
     * Displays the drawn content between the last display call and now.
     */
    void display();
};

#endif //DISTILLERY_CONTROLLER_SCREEN_H
