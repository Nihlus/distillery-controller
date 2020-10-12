//
//  Hardware..h
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

#ifndef DISTILLERY_CONTROLLER_HARDWARE_H
#define DISTILLERY_CONTROLLER_HARDWARE_H

#include <stdint.h>

namespace hardware
{
    /**
     * Defines the pin for the first button.
     */
    constexpr uint8_t BUTTON_1_PIN = 0;

    /**
     * Defines the pin for the second button.
     */
    constexpr uint8_t BUTTON_2_PIN = 1;

    /**
     * Defines the pin for the third button.
     */
    constexpr uint8_t BUTTON_3_PIN = 2;

    /**
     * Defines the pin for the fourth button.
     */
    constexpr uint8_t BUTTON_4_PIN = 3;

    /**
     * Defines the pin for the potentiometer.
     */
    constexpr uint8_t POTENTIOMETER_PIN = 4;

    /**
     * Defines the pin for the servo.
     */
    constexpr uint8_t SERVO_PIN = 5;

    /**
     * Defines the pin for the LCD data.
     */
    constexpr uint8_t LCD_DATA_PIN = A4;

    /**
     * Defines the pin for the LCD clock.
     */
    constexpr uint8_t LCD_CLOCK_PIN = A5;
}

#endif //DISTILLERY_CONTROLLER_HARDWARE_H
