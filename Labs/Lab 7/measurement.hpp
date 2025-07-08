/*
Header file for measurements of ingredients.
Very simple so we define just a struct to represent the content.
Thus, there is no need for an implementation file.
*/
#ifndef _MEASUREMENT_HPP_
#define _MEASUREMENT_HPP_

#include <string>

struct Measurement {
    float quantity;
    std::string unit;
};

#endif