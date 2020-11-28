//
//  Thermistor.cpp
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

#include <Arduino.h>

#include "abstractions/Thermistor.h"

Thermistor::Thermistor
(
    uint8_t pin,
    uint16_t nominalResistance,
    uint16_t nominalTemperature,
    uint16_t betaCoefficient,
    uint16_t seriesResistance,
    double temperatureTolerance
) noexcept :
    _pin(pin),
    _currentTemp(0),
    _nominalResistance(nominalResistance),
    _nominalTemperature(nominalTemperature),
    _betaCoefficient(betaCoefficient),
    _seriesResistance(seriesResistance),
    _temperatureTolerance(temperatureTolerance)
{
}

void Thermistor::initialize() const noexcept
{
    pinMode(_pin, INPUT);
}

double Thermistor::getCurrentTemperature() noexcept
{
    // average all the samples out
    double average = 0;
    for (auto i = 0; i < _samples.size(); ++i)
    {
        average += _samples[i];
    }

    average /= _samples.size();

    // convert the value to resistance
    average = 1023 / average - 1;
    average = _seriesResistance / average;

    double steinhart;
    steinhart = average / _nominalResistance;     // (R/Ro)
    steinhart = log(steinhart);                  // ln(R/Ro)
    steinhart /= _betaCoefficient;                   // 1/B * ln(R/Ro)
    steinhart += 1.0 / (_nominalTemperature + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart;                 // Invert
    steinhart -= 273.15;                         // convert absolute temp to C

    auto diff = abs(steinhart - _currentTemp);
    if (diff < _temperatureTolerance)
    {
        // Return the current value without updating it
        return _currentTemp;
    }

    // Update and return the new temperature
    _currentTemp = steinhart;
    return _currentTemp;
}

void Thermistor::setTemperatureTolerance(double temperatureTolerance)
{
    _temperatureTolerance = temperatureTolerance;
}

void Thermistor::pushSample() noexcept
{
    _samples.push(analogRead(_pin));
}

