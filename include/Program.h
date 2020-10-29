//
//  main.h
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

#ifndef DISTILLERY_CONTROLLER_PROGRAM_H
#define DISTILLERY_CONTROLLER_PROGRAM_H

#include <Servo.h>
#include "abstractions/Button.h"
#include "abstractions/Thermistor.h"
#include "abstractions/Screen.h"

namespace distillery
{
    class Program
    {
        /**
         * Holds the first button instance.
         */
        Button _button1;

        /**
         * Holds the second button instance.
         */
        Button _button2;

        /**
         * Holds the third button instance.
         */
        Button _button3;

        /**
         * Holds the fourth button instance.
         */
        Button _button4;

        /**
         * Holds the first thermistor instance.
         */
        Thermistor _ntc1;

        /**
         * Holds the second thermistor instance.
         */
        Thermistor _ntc2;

        /**
         * Holds the servo instance.
         */
        Servo _servo;

        /**
         * Holds the screen instance.
         */
        Screen _screen;

    public:
        /**
         * Initializes a new instance of the program.
         */
        explicit Program() noexcept;

        /**
         * Sets up hardware.
         */
        void setup() noexcept;

        /**
         * Represents one iteration of the program
         */
        void loop() noexcept;
    };
}

#endif //DISTILLERY_CONTROLLER_PROGRAM_H
