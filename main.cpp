#include <iostream>

#include "DataStorage.h"
#include "PSO.h"
#include "testFunctions.h"

void test_1();
void solve();
void save();

int main() {
    // test_1();
    solve();
}
void save() {
    auto save = new double[]{0.00010227, 18096.1};
    auto dt = DataStorage::getInstance();

    dt->save = true;

    D res = testFunctions::ff_solve(save,2);
    std::cout << "F - optimal: "
        << res
        << " At: "
        << save[0] << ", "
        << save[1] << ", "
    << std::endl;
}
void solve() {

    auto dt = DataStorage::getInstance();
    auto **f_con = new double*[] {
        new double[]{5e-5, 15e-5},
        new double[]{7000., 22000.}
        // new double[]{50e3, 100e3},
        // new double[]{0.05, 0.25},
        // new double[]{0.01, 0.09}
    };

    auto alg = PSO();

    auto t_0 = clock();
    auto sol_vect = alg.optimize(testFunctions::ff_solve,f_con,2,10000,10,0.9,0.001,0.002,0.001);
    std::cout << "T: " << clock() - t_0 << std::endl;

    dt->save = true;

    D res = testFunctions::ff_solve(sol_vect,2);
    std::cout << "F - optimal: "
        << res
        << " At: "
        << sol_vect[0] << ", "
        << sol_vect[1] << ", "
    << std::endl;
}


void test_1() {
    auto **f_con = new double*[] {
        new double[]{0., 10.},
        new double[]{0., 10.}
    };

    auto alg = PSO();

    auto t_0 = clock();
    auto sol_vect = alg.optimize(testFunctions::fun1,f_con,2,100,100,0.8,0.1,0.1,0.1);
    std::cout << "T: " << clock() - t_0 << std::endl;

    std::cout << "F - optimal: "
        << testFunctions::fun1(sol_vect,2)
        << " At: " << sol_vect[0] << ", " << sol_vect[1] << std::endl;
}
