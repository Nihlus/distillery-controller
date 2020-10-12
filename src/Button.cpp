//
//  Button.cpp.c
//
//  Author:
//       Jarl Gullberg <jarl.gullberg@gmail.com>
//
//  Copyright (c) 2020 Jarl Gullberg
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "Button.h"

#include <Arduino.h>

Button::Button(uint8_t pin, bool isPullUp, bool useInternalPullUp) noexcept :
    _buttonPin(pin),
    _isPullUp(isPullUp),
    _useInternalPullUp(useInternalPullUp)
{
    if (_useInternalPullUp)
    {
        _isPullUp = true;
    }
}

bool Button::isPressed() const
{
    auto value = digitalRead(_buttonPin);

    return _isPullUp
        ? value == 0
        : value == 1;
}

void Button::initialize() const noexcept
{
    auto mode = _useInternalPullUp
                ? INPUT_PULLUP
                : INPUT;

    pinMode(_buttonPin, mode);
}
