//
//  GraphicsZone.h
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

#ifndef DISTILLERY_CONTROLLER_GRAPHICSZONE_H
#define DISTILLERY_CONTROLLER_GRAPHICSZONE_H

#include <Adafruit_GFX.h>

/**
 * Represents a distinct zone of a graphics context.
 */
class GraphicsZone : public Adafruit_GFX
{
    /**
     * Holds the inner graphics context.
     */
    Adafruit_GFX& _inner;

    /**
     * Holds the X offset of the zone inside the inner context.
     */
    uint8_t _xOffset;

    /**
     * Holds the Y offset of the zone inside the inner context.
     */
    uint8_t _yOffset;

public:
    /**
     * Initializes a new instance of the GraphicsZone class.
     * @param inner The inner graphics context.
     * @param xOffset The X offset.
     * @param yOffset The Y offset.
     * @param width The width of the zone.
     * @param height The height of the zone.
     */
    explicit GraphicsZone
    (
        Adafruit_GFX& inner,
        uint8_t xOffset,
        uint8_t yOffset,
        uint8_t width,
        uint8_t height
    ) noexcept;

    /*
     * Adafruit_GFX implementation
     */

    void drawPixel(int16_t x, int16_t y, uint16_t color) override;
};

#endif //DISTILLERY_CONTROLLER_GRAPHICSZONE_H
