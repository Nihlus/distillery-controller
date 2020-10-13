//
//  main.cpp
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
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Screen.h>

#include "images/still.h"
#include "Hardware.h"
#include "Settings.h"
#include "Button.h"

#define lengthof(a) sizeof(a) / sizeof(a[0])

Button buttons[] =
{
    Button(hardware::BUTTON_1_PIN),
    Button(hardware::BUTTON_2_PIN),
    Button(hardware::BUTTON_3_PIN),
    Button(hardware::BUTTON_4_PIN)
};

uint8_t buttonAngles[] =
{
    settings::BUTTON_1_ANGLE,
    settings::BUTTON_2_ANGLE,
    settings::BUTTON_3_ANGLE,
    settings::BUTTON_4_ANGLE,
};

uint8_t servoAngle = 0;

Servo servo;
Screen screen = Screen
(
    hardware::LCD_DATA_PIN,
    hardware::LCD_CLOCK_PIN,
    hardware::LCD_I2C_ADDRESS,
    hardware::LCD_WIDTH,
    hardware::LCD_HEIGHT
);

void draw_packed_image(uint8_t xOffset, uint8_t yOffset)
{
    auto& blue = screen.getBlueZone();

    for (auto y = 0; y < images::STILL_HEIGHT; ++y)
    {
        for (auto x = 0; x < images::STILL_WIDTH; ++x)
        {
            auto bitOffset = (y * images::STILL_WIDTH) + x;

            auto byteIndex = (int)floor(bitOffset / 8.0);
            auto bitIndex = bitOffset % 8;

            auto currentValue = pgm_read_byte(&images::still[byteIndex]);

            if ((currentValue & (1 << bitIndex)) == 0)
            {
                continue;
            }

            blue.drawPixel(x + xOffset, y + yOffset, WHITE);
        }
    }
}

void setup()
{
    for (auto& button : buttons)
    {
        button.initialize();
    }

    pinMode(hardware::POTENTIOMETER_PIN, INPUT);
    pinMode(hardware::SERVO_PIN, OUTPUT);

    servo.attach
    (
        hardware::SERVO_PIN,
        hardware::SERVO_MIN_PULSE_WIDTH,
        hardware::SERVO_MAX_PULSE_WIDTH
    );

    // Start at 0 degrees
    servo.write(servoAngle);

    screen.initialize();
}

void loop()
{
    screen.clear();
    auto& blue = screen.getBlueZone();
    auto& yellow = screen.getYellowZone();

    for (auto i = 0; i < lengthof(buttons); ++i)
    {
        auto& button = buttons[i];

        auto circleX = i * 12 + 8;
        auto circleY = 12;

        blue.drawCircle(circleX, circleY, 4, WHITE);

        if (button.isPressed())
        {
            blue.fillCircle(circleX, circleY, 2, WHITE);
            servoAngle = buttonAngles[i];
        }
    }
    servo.write(servoAngle);

    //

    yellow.setCursor(0, 0);
    yellow.setTextColor(WHITE);
    yellow.print("Angle: ");
    yellow.print(servoAngle);

    draw_packed_image
    (
        blue.width() - images::STILL_WIDTH - 8,
        blue.height() - images::STILL_HEIGHT - 8
    );

    screen.display();
}