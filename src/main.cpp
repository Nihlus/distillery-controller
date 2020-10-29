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
#include "Thermistor.h"


#define lengthof(a) sizeof(a) / sizeof(a[0])

#define LED_GREEN 6
#define LED_RED 7
#define LED_YELLOW 8

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

bool wasButtonPressed[] =
{
    false,
    false,
    false,
    false
};

uint8_t servoAngle = settings::BUTTON_1_ANGLE;

Servo servo;
Screen screen = Screen
(
    hardware::LCD_DATA_PIN,
    hardware::LCD_CLOCK_PIN,
    hardware::LCD_I2C_ADDRESS,
    hardware::LCD_WIDTH,
    hardware::LCD_HEIGHT
);

Thermistor ntc1 = Thermistor(hardware::THERMISTOR_1_PIN);
Thermistor ntc2 = Thermistor(hardware::THERMISTOR_2_PIN);

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

    ntc1.initialize();
    ntc2.initialize();

    //pinMode(hardware::POTENTIOMETER_PIN, INPUT);
    pinMode(hardware::SERVO_PIN, OUTPUT);

    servo.attach
    (
        hardware::SERVO_PIN,
        hardware::SERVO_MIN_PULSE_WIDTH,
        hardware::SERVO_MAX_PULSE_WIDTH
    );

    // Start button 1
    servo.write((int32_t)servoAngle);

    screen.initialize();

    //Ntc 3.3v med ref
    // analogReference(EXTERNAL);

    //led
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
}

void loop()
{
    screen.clear();
    auto& blue = screen.getBlueZone();
    auto& yellow = screen.getYellowZone();

    for (auto i = 0u; i < lengthof(buttons); ++i)
    {
        auto& button = buttons[i];

        auto circleX = i * 12 + 28;
        auto circleY = 40;

        blue.drawCircle(circleX, circleY, 5, WHITE);

        if (button.isPressed())
        {
            blue.fillCircle(circleX, circleY, 4, WHITE);

            if (wasButtonPressed[i])
            {
                continue;
            }

            switch (i)
            {
                case 0:
                case 3:
                {
                    servoAngle = buttonAngles[i];
                    break;
                }
                case 1:
                {
                    servoAngle += buttonAngles[i];
                    servoAngle = servoAngle > hardware::SERVO_MAX_ANGLE ? hardware::SERVO_MAX_ANGLE : servoAngle;

                    break;
                }
                case 2:
                {
                    servoAngle -= buttonAngles[i];
                    servoAngle = servoAngle < hardware::SERVO_MIN_ANGLE ? hardware::SERVO_MIN_ANGLE : servoAngle;

                    break;
                }
                default:
                {
                    break;
                }
            }

            wasButtonPressed[i] = true;
        }
        else
        {
            if (!wasButtonPressed[i])
            {
                continue;
            }

            wasButtonPressed[i] = false;
        }
    }

    servo.write((int32_t)servoAngle);

    //Ntc1
    ntc1.resampleTemperature();
    ntc2.resampleTemperature();

    //  led
    if (buttons[0].isPressed())
    {
        digitalWrite(LED_RED, HIGH);
    }
    else
    {
        digitalWrite(LED_RED, LOW);
    }

    // set servo

    servo.write((int32_t)servoAngle);


    // draw the screen

    yellow.setCursor(0, 0);
    yellow.setTextColor(WHITE);
    //yellow.setTextSize(0,0);

    //blue.setCursor(0, 20);
    //blue.setTextColor(WHITE);

    yellow.print("Angle ");
    yellow.print("Ntc1 ");
    yellow.print("Ntc2 ");
    yellow.setCursor(8, 9);
    yellow.print((uint8_t)servoAngle);
    yellow.setCursor(37, 9);
    yellow.print((ntc1.getCurrentTemperature()), 1);
    yellow.setCursor(67, 9);
    yellow.print((ntc2.getCurrentTemperature()), 1);

    draw_packed_image(blue.width() - images::STILL_WIDTH - 8, blue.height() - images::STILL_HEIGHT - 8);

    screen.display();
}
