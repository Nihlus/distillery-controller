//
//  Button.h
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

#ifndef DISTILLERY_CONTROLLER_BUTTON_H
#define DISTILLERY_CONTROLLER_BUTTON_H

#include <stdint.h>
#include <Debounce.h>

/**
 * Represents a button.
 */
class Button
{
    /**
     * Holds the button pin.
     */
    uint8_t _buttonPin;

    /**
     * Holds a value indicating whether the button is connected to a pull-up resistor.
     */
    bool _isPullUp;

    /**
     * Holds the debounced button wrapper.
     */
    Debounce _debouncedButton;

    /**
     * Holds a value indicating whether the internal pull-up resistor should be used.
     */
    bool _useInternalPullUp;

    /**
     * Holds a value indicating whether the button is a one-shot button (that is, if isPressed should only return true
     * once, even if the button is held.).
     */
    bool _isOneShot;

    /**
     * Holds a value indicating whether the button was pressed the last time it was checked.
     */
    bool _wasPressedLastCheck = false;

public:
    /**
     * Initializes a new instance of the Button class.
     * @param pin The pin the button is connected to.
     * @param isOneShot Whether the button is a one-shot button.
     * @param isPullUp Whether the button is connected to a pull-up resistor.
     * @param useInternalPullUp Whether the internal pull-up resistor should be used.
     */
    explicit Button(uint8_t pin, bool isOneShot = false, bool isPullUp = true, bool useInternalPullUp = true) noexcept;

    /**
     * Initializes the hardware for this button.
     */
    void initialize() const noexcept;

    /**
     * Determines whether the button is currently pressed.
     * @return true if the button is pressed, otherwise, false.
     */
    bool isPressed();
};

#endif //DISTILLERY_CONTROLLER_BUTTON_H
