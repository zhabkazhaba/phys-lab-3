//
// Created by zhabkazhaba on 2/29/24.
//

#ifndef PHYS_LAB_1_UTILITYFUNCS_HPP
#define PHYS_LAB_1_UTILITYFUNCS_HPP


namespace util {

    inline float convertMillimetersToMeters(float mm) {
        return mm * 0.001f;
    }

    inline float convertMetersToMillimeters(float m) {
        return m * 1000.0f;
    }

    inline float convertMillimetersToCentimeters(float mm) {
        return mm * 0.1f;
    }

    inline float convertGramsToKilograms(float g) {
        return g * 0.001f;
    }

    inline float convertKilogramsToGrams(float kg) {
        return kg * 1000.0f;
    }
}

#endif //PHYS_LAB_1_UTILITYFUNCS_HPP
