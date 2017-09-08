/**
 * @file
 * @brief Calculator for saturated properties for steam systems
 *
 * This contains the inputs for calculating saturated properties for steam systems
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include <unordered_map>
#include <string>

#ifndef AMO_TOOLS_SUITE_SATURATEDPROPERTIES_H
#define AMO_TOOLS_SUITE_SATURATEDPROPERTIES_H

/**
 * Saturated temperature class
 * Used to calculate the saturated temperature given the saturated pressure.
 */
class SaturatedTemperature {
public:
    /**
     *
     * Constructor for the saturated temperature calculator
     *
     * @param saturatedPressure double, saturated pressure in MPa
     *
     * @return nothing
     *
     * */
    explicit SaturatedTemperature(double saturatedPressure)
            : saturatedPressure_(saturatedPressure) {}
    /**
     * Calculates the saturated temperature
     *
     * @return double, saturated temperature in Kelvin
     */
    double calculate() const;

private:
    const double saturatedPressure_;
};


/**
 * Saturated pressure class
 * Used to calculate the saturated pressure given the saturated temperature.
 */
class SaturatedPressure {
public:
    /**
     * Constructor for the saturated pressure calculator
     *
     * @param saturatedTemperature double, saturated temperature in Kelvin
     *
     * @return nothing
     *
     * */
    explicit SaturatedPressure(double saturatedTemperature) : saturatedTemperature_(saturatedTemperature) {}

    /**
     * Calculates the saturated pressure
     *
     * @return double, saturated pressure in MPa
     */
    double calculate() const;

private:
    const double saturatedTemperature_;
};



/**
 * Saturated properties class
 * Used to calculate the properties of a saturated substance.
 */
class SaturatedProperties {
public:
    /**
     *
     * Constructor for the saturated properties calculator
     *
     * @param saturatedPressure double, saturated pressure in MPa
     * @param saturatedTemperature double, saturated temperature in Kelvin
     *
     * @return nothing
     *
     * */
    SaturatedProperties(double saturatedPressure, double saturatedTemperature)
            : saturatedPressure_(saturatedPressure),
              saturatedTemperature_(saturatedTemperature) {}

    std::unordered_map<std::string, double> calculate();

private:
    const double saturatedPressure_, saturatedTemperature_;
};


#endif //AMO_TOOLS_SUITE_SATURATEDPROPERTIES_H
