//
//  Program.cpp
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

#include <Arduino.h>

#include "Program.h"
#include "configuration/Hardware.h"
#include "configuration/Settings.h"
#include "images/images.h"

using namespace distillery;

distillery::Program::Program() noexcept :
    _button1(hardware::BUTTON_1_PIN),
    _button2(hardware::BUTTON_2_PIN),
    _button3(hardware::BUTTON_3_PIN),
    _button4(hardware::BUTTON_4_PIN),
    _ntc1(hardware::THERMISTOR_1_PIN),
    _ntc2(hardware::THERMISTOR_2_PIN),
    _servo(),
    _screen
    (
        hardware::LCD_DATA_PIN,
        hardware::LCD_CLOCK_PIN,
        hardware::LCD_I2C_ADDRESS,
        hardware::LCD_WIDTH,
        hardware::LCD_HEIGHT
    )
{
}

#define LED_GREEN 6
#define LED_RED 7
#define LED_YELLOW 8

void Program::setup()
{
    _button1.initialize();
    _button2.initialize();
    _button3.initialize();
    _button4.initialize();

    _ntc1.initialize();
    _ntc2.initialize();

    //pinMode(hardware::POTENTIOMETER_PIN, INPUT);
    pinMode(hardware::SERVO_PIN, OUTPUT);

    _servo.attach
    (
        hardware::SERVO_PIN,
        hardware::SERVO_MIN_PULSE_WIDTH,
        hardware::SERVO_MAX_PULSE_WIDTH
    );

    // Start the servo at the default angle.
    _servo.write(0);

    _screen.initialize();

    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
}

void Program::loop()
{
    _screen.clear();
    auto& blue = _screen.getBlueZone();
    auto& yellow = _screen.getYellowZone();

    auto servoAngle = _servo.read();
    bool wasButtonPressed[4] = { };
    if (_button1.isPressed())
    {
        servoAngle = settings::BUTTON_1_ANGLE;
        wasButtonPressed[0] = true;

        digitalWrite(LED_RED, HIGH);
    }
    else
    {
        digitalWrite(LED_RED, LOW);
    }

    if (_button2.isPressed())
    {
        servoAngle = settings::BUTTON_2_ANGLE;
        wasButtonPressed[1] = true;
    }

    if (_button3.isPressed())
    {
        servoAngle = settings::BUTTON_3_ANGLE;
        wasButtonPressed[2] = true;
    }

    if (_button4.isPressed())
    {
        servoAngle = settings::BUTTON_4_ANGLE;
        wasButtonPressed[3] = true;
    }

    for (auto i = 0; i < 4; ++i)
    {
        auto circleX = i * 12 + 28;
        auto circleY = 40;

        blue.drawCircle(circleX, circleY, 5, WHITE);
        if (wasButtonPressed[i])
        {
            blue.fillCircle(circleX, circleY, 4, WHITE);
        }
    }

    _servo.write((int32_t)servoAngle);

    _ntc1.resampleTemperature();
    _ntc2.resampleTemperature();

    // set servo
    _servo.write((int32_t)servoAngle);

    // draw the screen
    yellow.setCursor(0, 0);
    yellow.setTextColor(WHITE);

    yellow.print("Angle ");
    yellow.print("Ntc1 ");
    yellow.print("Ntc2 ");
    yellow.setCursor(8, 9);
    yellow.print((uint8_t)servoAngle);
    yellow.setCursor(37, 9);
    yellow.print((_ntc1.getCurrentTemperature()), 1);
    yellow.setCursor(67, 9);
    yellow.print((_ntc2.getCurrentTemperature()), 1);

    images::draw_packed_image
    (
        blue,
        blue.width() - images::STILL_WIDTH - 8,
        blue.height() - images::STILL_HEIGHT - 8,
        images::STILL_WIDTH,
        images::STILL_HEIGHT,
        &images::still[0]
    );

    _screen.display();
}
