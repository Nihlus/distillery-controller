//
//  Thermistor.h
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

#ifndef DISTILLERY_CONTROLLER_THERMISTOR_H
#define DISTILLERY_CONTROLLER_THERMISTOR_H

#include <stdint.h>

/**
 * Represents a thermistor.
 */
class Thermistor
{
    /**
     * Holds the pin associated with the thermistor.
     */
    uint8_t _pin;

    /**
     * Holds the current measured and steinhart-corrected temperature.
     */
    double _currentTemp;

    /**
     * Holds the nominal resistance of the thermistor.
     */
    uint16_t _nominalResistance;

    /**
     * Holds the temperature of the thermistor at the nominal resistance. Typically, this is 25C.
     */
    uint16_t _nominalTemperature;

    /**
     * Holds the beta coefficient of the thermistor.
     */
    uint16_t _betaCoefficient;

    /**
     * Holds the resistance of the in-series resistor.
     */
    uint16_t _seriesResistance;

    /**
     * The minimum difference between the latest sample and the current temperature for the value to be updated.
     */
    double _temperatureTolerance;

public:
    /**
     * Initializes a new instance of the Thermistor class.
     * @param pin The thermistor pin.
     * @param nominalResistance The nominal resistance of the thermistor.
     * @param nominalTemperature The temperature of the thermistor at the nominal resistance.
     * @param betaCoefficient The beta coefficient of the thermistor.
     * @param seriesResistance The resistance of the in-series resistor.
     * @param temperatureTolerance The minimum difference between the latest sample and the current temperature for the
     * value to be updated.
     */
    explicit Thermistor
    (
        uint8_t pin,
        uint16_t nominalResistance = 10000,
        uint16_t nominalTemperature = 25,
        uint16_t betaCoefficient = 3950,
        uint16_t seriesResistance = 10000,
        double temperatureTolerance = 0.1
    ) noexcept;

    /**
     * Initializes the hardware associated with the thermistor.
     */
    void initialize() const noexcept;

    /**
     * Gets the current measured temperature.
     * @return The current temperature.
     */
    double getCurrentTemperature() const noexcept;

    /**
     * Sets the temperature tolerance.
     * @param temperatureTolerance The new temperature tolerance.
     */
    void setTemperatureTolerance(double temperatureTolerance);

    /**
     * Resamples the thermistor, updating the current measured temperature.
     * @param sampleCount The number of sampleCount to average.
     */
    void resampleTemperature(uint8_t sampleCount = 5) noexcept;
};

#endif //DISTILLERY_CONTROLLER_THERMISTOR_H
