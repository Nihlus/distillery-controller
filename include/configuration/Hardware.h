//
//  Hardware..h
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

#ifndef DISTILLERY_CONTROLLER_HARDWARE_H
#define DISTILLERY_CONTROLLER_HARDWARE_H

#include <stdint.h>
#include <pins_arduino.h>

namespace hardware
{
    /**
     * Defines a pixel count.
     */
    typedef uint8_t pixels_t;

    /**
     * Defines a microsecond type.
     */
    typedef uint16_t microseconds_t;

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
    constexpr uint8_t POTENTIOMETER_PIN = A3;

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

    /**
     * Defines the I²C address of the LCD.
     */
    constexpr uint8_t LCD_I2C_ADDRESS = 0x3C;

    /**
     * Defines the height of the LCD screen.
     */
    constexpr pixels_t LCD_HEIGHT = 64;

    /**
     * Defines the height of the LCD screen.
     */
    constexpr pixels_t LCD_WIDTH = 128;

    /**
     * Defines the lower bound of the pulse width for the servo.
     */
    constexpr microseconds_t SERVO_MIN_PULSE_WIDTH = 750;

    /**
     * Defines the upper bound of the pulse width for the servo.
     */
    constexpr microseconds_t SERVO_MAX_PULSE_WIDTH = 2650;

    /**
     * Defines the minimum angle the servo can reach.
     */
    constexpr double SERVO_MIN_ANGLE = 0.0;

    /**
     * Defines the maximum angle the servo can reach.
     */
    constexpr double SERVO_MAX_ANGLE = 90.0;

    /**
     * Defines the delay between checks for debouncing.
     */
    constexpr uint8_t DEBOUNCE_DELAY = 25;

    /**
     * Defines the pin for thermistor 1.
     */
    constexpr uint8_t THERMISTOR_1_PIN = A0;

    /**
     * Defines the pin for thermistor 2.
     */
    constexpr uint8_t THERMISTOR_2_PIN = A1;
}

#endif //DISTILLERY_CONTROLLER_HARDWARE_H
