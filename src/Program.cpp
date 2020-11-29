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
    //    _button2(hardware::BUTTON_2_PIN, true),
    _button2(hardware::BUTTON_2_PIN, true),
    _button3(hardware::BUTTON_3_PIN, true),
    _button4(hardware::BUTTON_4_PIN, true),
    _ntc1(hardware::THERMISTOR_1_PIN),
    _ntc2(hardware::THERMISTOR_2_PIN),
    _servo(),
    _screen
    (
        hardware::LCD_SCLK_PIN,
        hardware::LCD_MOSI_PIN,
        hardware::LCD_DC_PIN,
        hardware::LCD_CS_PIN,
        hardware::LCD_RST_PIN,
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

/*  //define led pins mode
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
*/
    _servo.attach(hardware::SERVO_PIN, hardware::SERVO_MIN_PULSE_WIDTH, hardware::SERVO_MAX_PULSE_WIDTH);

    // Start the servo at the close angle.
    _servo.write(settings::CLOSE_ANGLE);

    _screen.initialize();
    _screen.clear();

    // eriks lekstuga
    // digitalWrite(LED_YELLOW, HIGH);
    auto& surface = _screen.getSurface();    
    surface.println("Angle ");
    surface.println("Boiler ");
    surface.println(" ");
    surface.println("Angle ");
    surface.println("Boiler ");    
}

void Program::loop()
{
    //_screen.clear();
    auto& surface = _screen.getSurface();

    _ntc1.pushSample();
    _ntc2.pushSample();

    float ntc1temp = floor(_ntc1.getCurrentTemperature() * 10 + 0.5) / 10;
    float ntc2temp = floor(_ntc2.getCurrentTemperature() * 10 + 0.5) / 10 - 4;
    //float ntc1temp = _ntc1.getCurrentTemperature();
    //double f2 = floor(f1 * 100 + 0.5) / 100.0;

    auto servoAngle = _servo.read();
    bool wasButtonPressed[4] = {};
/*
    if (_button1.isPressed())
    {
        digitalWrite(LED_RED, HIGH);
        wasButtonPressed[0] = true;
    }
    else
    {
        digitalWrite(LED_RED, LOW);
    }
*/
    if (_button2.isPressed())
    {
        servoAngle = servoAngle + 2;
        wasButtonPressed[1] = true;
    }

    if (_button3.isPressed())
    {
        servoAngle = servoAngle = 0;
        wasButtonPressed[2] = true;
    }

    if (_button4.isPressed())
    {
        _shouldCheckColumnTemperature = true;
        //_isColumnHot = false;
        _columnBreakTemp = (ntc1temp + 0.2);
        
        wasButtonPressed[3] = true;
    }


    if (_shouldCheckColumnTemperature && ntc1temp > _columnBreakTemp)
    {
        _savetemp = ntc2temp;
        _saveangle = servoAngle;
        servoAngle = (settings::CLOSE_ANGLE);

        _shouldCheckColumnTemperature = false;

    }


    // set servo
    _servo.write((int32_t)servoAngle);

    // draw the screen

    int ssdx = 45; // x placement int
    int ssdy = 0; // y placement int   

    
    // draw values on upper screen
    
    surface.setTextSize(1);
    surface.setTextColor(colours::White,colours::Black);
    
    surface.setCursor(ssdx, ssdy);    
    
    if (servoAngle < 10)
    {
    surface.print(" ");
    }
    
    surface.print(servoAngle);
    
    surface.setCursor(ssdx, ssdy+8);    
    surface.print((ntc2temp), 1);

    surface.setCursor(ssdx, ssdy+24);    
    
    if (_saveangle < 10)
    {
    surface.print(" ");
    }
    
    surface.println(_saveangle);
     
    surface.setCursor(ssdx, ssdy+32);    
    surface.print((_savetemp), 1);
    

//  Draw a size 2 temp including black clear colum temp

    ssdx = 0; // x placement
    ssdy = 114; // y placement
    //surface.fillRect(ssdx, ssdy, 46, 14, colours::Black);
    surface.setTextSize(2);
    surface.setTextColor(colours::Green,colours::Black);
    surface.setCursor(ssdx, ssdy);

    surface.print((ntc1temp), 1);    // comlum

//  Draw a size 2 temp including black clear boiler temp

    ssdx = 64; // x placement
    ssdy = 114; // y placement
    //surface.fillRect(ssdx, ssdy, 46, 14, colours::Black);
    surface.setTextSize(2);
    surface.setTextColor(colours::Red,colours::Black);
    surface.setCursor(ssdx, ssdy);
    surface.print((_columnBreakTemp), 1);   //boiler

//  draw button circles

    for (auto i = 0; i < 4; ++i)
    {
        auto circleX = i * 12 + 40;
        auto circleY = 90;

        surface.drawCircle(circleX, circleY, 5, colours::White);
        if (wasButtonPressed[i])
        {
            surface.fillCircle(circleX, circleY, 4, colours::White);
        }
        else
        {        
            surface.fillCircle(circleX, circleY, 4, colours::Black);
        }
    }


/*
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
*/
}
