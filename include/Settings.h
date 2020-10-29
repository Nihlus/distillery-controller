//
//  Settings.h
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

#ifndef DISTILLERY_CONTROLLER_SETTINGS_H
#define DISTILLERY_CONTROLLER_SETTINGS_H

#include <stdint.h>

namespace settings
{
    /**
     * Defines the angle the first button should set the servo to.
     */
    constexpr uint8_t BUTTON_1_ANGLE = 10;

    /**
     * Defines the angle the second button should add to the current angle of the servo.
     */
    constexpr uint8_t BUTTON_2_ANGLE = 2;

    /**
     * Defines the angle the second button should remove from the current angle of the servo.
     */
    constexpr uint8_t BUTTON_3_ANGLE = 2;

    /**
     * Defines the angle the fourth button should set the servo to.
     */
    constexpr uint8_t BUTTON_4_ANGLE = 80;

    // Led colors
    constexpr uint8_t LED_GREEN = 6;
    constexpr uint8_t LED_RED = 7;
    constexpr uint8_t LED_YELLOW = 8;

}

#endif //DISTILLERY_CONTROLLER_SETTINGS_H
