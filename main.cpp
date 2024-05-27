#include <iostream>

#include "PSO.h"
#include "testFunctions.h"

int main() {
    double arr[] = {3.,2.};

    auto **f_con = new double*[] {
        new double[]{0., 10.},
        new double[]{0., 10.}
    };
    std::cout << "Random value from constraints: "<< PSO::RN(f_con[0]) << std::endl;

    auto alg = PSO();

    std::cout << "F(0,0): "<< testFunctions::fun1(arr,2) << std::endl;
    std::cout << "F - optimal: "
        << testFunctions::fun1(alg.optimize(testFunctions::fun1,f_con,2,1000,0.8,0.1,0.1),2)
        << std::endl;
    return 0;
}
