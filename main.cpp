#include <iostream>

#include "PSO.h"
#include "testFunctions.h"

int main() {
    double arr[] = {3.,2.};

    auto **f_con = new double*[] {
        new double[]{0., 10.},
        new double[]{0., 10.}
    };

    std::cout << "F(0,0): "<< *testFunctions::fun1(arr,2) << std::endl;
    std::cout << "F - optimal: "<<
        *testFunctions::fun1(PSO::optimize(testFunctions::fun1,f_con,2),2)
        << std::endl;
    return 0;
}
