#include <iostream>

#include "testFunctions.h"

int main() {
    double arr[] = {3.,2.};
    std::cout << "F(0,0): "<< testFunctions::fun1(arr,2) << std::endl;
    return 0;
}
