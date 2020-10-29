//
//  images.cpp
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

#include "images/images.h"
#include <Adafruit_SSD1306.h>

using namespace images;

void images::draw_packed_image
(
    Adafruit_GFX& gfx,
    uint8_t xOffset,
    uint8_t yOffset,
    uint8_t width,
    uint8_t height,
    const uint8_t* data
) noexcept
{
    for (auto y = 0; y < height; ++y)
    {
        for (auto x = 0; x < width; ++x)
        {
            auto bitOffset = (y * width) + x;

            auto byteIndex = (int)floor(bitOffset / 8.0);
            auto bitIndex = bitOffset % 8;

            auto addressOffset = data + byteIndex;
            auto currentValue = pgm_read_byte(addressOffset);

            if ((currentValue & (1 << bitIndex)) == 0)
            {
                continue;
            }

            gfx.drawPixel(x + xOffset, y + yOffset, WHITE);
        }
    }
}