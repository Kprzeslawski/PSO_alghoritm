//
// Created by Krzysztof on 25.05.2024.
//

#include "testFunctions.h"

#include <stdexcept>

double testFunctions::fun1(double *x, int count) {
    if(count < 2)throw std::runtime_error("Invalid args count");
    return ((x[0] - 5) * (x[0] - 1) + 12) * ((x[1] - 2) * (x[1] - 3) + 4);

}
