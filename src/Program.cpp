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


// 1351


// Screen dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128 // Change this to 96 for 1.27" OLED.

// You can use any (4 or) 5 pins 
#define SCLK_PIN 13
#define MOSI_PIN 11
#define DC_PIN   9
#define CS_PIN   10
#define RST_PIN  8

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

// Option 1: use any pins but a little slower
//Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  

// Option 2: must use the hardware SPI pins 
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be 
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);



// 1351





#include <Arduino.h>

#include "Program.h"
#include "configuration/Hardware.h"
#include "configuration/Settings.h"
#include "images/images.h"

using namespace distillery;

distillery::Program::Program() noexcept :
    _button1(hardware::BUTTON_1_PIN),
//    _button2(hardware::BUTTON_2_PIN, true),
    _button2(hardware::BUTTON_2_PIN),
    _button3(hardware::BUTTON_3_PIN),
    _button4(hardware::BUTTON_4_PIN, true),
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

    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);

    _servo.attach
    (
        hardware::SERVO_PIN,
        hardware::SERVO_MIN_PULSE_WIDTH,
        hardware::SERVO_MAX_PULSE_WIDTH
    );

    // Start the servo at the close angle.
    _servo.write(settings::CLOSE_ANGLE);

    _screen.initialize();

    // eriks lekstuga
    digitalWrite(LED_YELLOW, HIGH);
    
     tft.begin();    

//  tft.fillRect(0, 0, 128, 128, BLACK);
    tft.fillScreen(BLACK);
}

void Program::loop()
{
//  tft.clearDisplay();    
    _screen.clear();
//    tft.fillScreen(BLACK);    
    auto& blue = _screen.getBlueZone();
    auto& yellow = _screen.getYellowZone();

    _ntc1.resampleTemperature();
    _ntc2.resampleTemperature();

    float ntc1temp = floor(_ntc1.getCurrentTemperature() * 10 + 0.5) / 10 ;
    float ntc2temp = floor(_ntc2.getCurrentTemperature() * 10 + 0.5) / 10 - 4;
    //float ntc1temp = _ntc1.getCurrentTemperature();
    //double f2 = floor(f1 * 100 + 0.5) / 100.0;
    
    auto servoAngle = _servo.read();
    bool wasButtonPressed[4] = { };
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
        servoAngle = servoAngle +2;
        wasButtonPressed[1] = true;
    }

    if (_button3.isPressed())
    {
        servoAngle = servoAngle -2;
        wasButtonPressed[2] = true;
    }

    if (_button4.isPressed())
    {
        _shouldCheckColumnTemperature = true;
        //_isColumnHot = false;
        _columnBreakTemp = (ntc1temp + 0.2);
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_YELLOW, LOW);
        digitalWrite(LED_GREEN, HIGH);

        wasButtonPressed[3] = true;
    }

    
    if (_shouldCheckColumnTemperature && ntc1temp > _columnBreakTemp) 
    {
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
        _savetemp = ntc2temp;
        _saveangle = servoAngle;
        servoAngle = (settings::CLOSE_ANGLE);

        _shouldCheckColumnTemperature = false;                
    
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



    // set servo
    _servo.write((int32_t)servoAngle);

    // draw the screen
    //yellow.setCursor(0, 0);
    //yellow.setTextColor(WHITE);

//    tft.print("Angle ");
    

/*    tft.fillScreen(BLACK);
    tft.setCursor(0, 5);
    tft.setTextColor(RED);  
    tft.setTextSize(1);
    tft.println("Hello World!");
    tft.setTextColor(YELLOW);
    tft.setTextSize(2);
    tft.println("Hello World!");
    tft.setTextColor(BLUE);
    tft.setTextSize(3);
    tft.print(1234.567);
*/

/*
    yellow.print("Ntc1 ");
    yellow.print("Ntc2 ");
    yellow.setCursor(8, 9);
    yellow.print((uint8_t)servoAngle);
    yellow.setCursor(37, 9);
    yellow.print((ntc1temp), 1);
    yellow.setCursor(67, 9);
    yellow.print((ntc2temp), 1);
    yellow.print(" ");
    yellow.print(_columnBreakTemp, 1);
    
    blue.setCursor(0, 9);
    blue.setTextColor(WHITE);

    blue.println(_saveangle);
    blue.println((_savetemp), 1);
    //blue.print(ntc1temp);
    
*/  

    tft.fillRect(37, 7, 50, 17, RED);
    tft.setTextSize(2);    
    tft.setTextColor(GREEN);    
    
    tft.setCursor(37, 9);
    tft.print((ntc1temp), 1);
//    tft.print("Ntc1 ");
//    tft.setTextColor(YELLOW);    
//    tft.print("Ntc2 ");
//    tft.setCursor(8, 9);
//    tft.print((uint8_t)servoAngle);
//    tft.setCursor(67, 9);
//    tft.print((ntc2temp), 1);
//    tft.print(" ");
//    tft.print(_columnBreakTemp, 1);
    
//    tft.setCursor(0, 9);
//    tft.setTextColor(WHITE);

//    tft.println(_saveangle);
//    tft.println((_savetemp), 1); 
   //blue.print(ntc1temp);

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
