#include <iostream>

#include "DataStorage.h"
#include "PSO.h"
#include "testFunctions.h"

void test_1();
void solve();
void save();
void calculate_slope();
D* calculate_diff(int points,D h, D* center, D* right, D* left);

int main() {
    // test_1();
    // solve();
    // save();
    calculate_slope();
}

void calculate_slope() {
    auto dt = DataStorage::getInstance();
    auto opt_sol = new double[] {
      9.50753e-05,//A1
      17945.4,//A2
      1e3 * 83.349,//A3
      3e10 * 0.05317,//A4
      1e3 * 123.12,//A5
      0.452,//A8
      0.13751,//A9
      0.409,//A10
      0.,//A11
      1e13 * 0.000042, //A12
      0.07486 //A13
    };

    auto param_l = new double[] {
        1e-4,
        7000.,
        50e3,
        0.08*3e10,
        50e3,
        0.6,
        0.2,
        0.8,
        0.,
        0.00008e13,
        0.08
    };

    // variable 1
    int param_n = 3;
    D p = 0.05;
    int experiment = 7;
    auto res = testFunctions::CalcUsingEuler(opt_sol, dt->e_dot[experiment], dt->t[experiment]);
    opt_sol[param_n] -= param_l[param_n] * p;
    auto res_min = testFunctions::CalcUsingEuler(opt_sol, dt->e_dot[experiment], dt->t[experiment]);
    opt_sol[param_n] += 2*param_l[param_n] * p;
    auto res_max = testFunctions::CalcUsingEuler(opt_sol, dt->e_dot[experiment], dt->t[experiment]);

    auto forw = calculate_diff(1001,0.5e-05,res,res_max,nullptr);
    auto back = calculate_diff(1001,0.5e-05,res,nullptr,res_min);
    auto center = calculate_diff(1001,0.5e-05,res,res_max,res_min);

    std::ofstream plik("data_diff.txt");
        plik << "opt; opt-h; opt+h; grad; grad-h; grad+h"<< std::endl;
        for (int i2 = 0; i2 < 1001; i2++)
            plik
                << res[i2] << "; "
                << res_min[i2] << "; "
                << res_max[i2] << "; "
                << center[i2] << "; "
                << back[i2] << "; "
                << forw[i2] << "; "
                << std::endl;
        plik.close();

}

void save() {
    auto save = new double[]{9.50753e-05, 17945.4}; // 1.21 - 500
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
        new double[]{5e-5, 15e-5},//A1
        new double[]{7000., 22000.}, //A2
        // new double[]{1e3*50., 1e3*100.}, //A3
        // new double[]{3e10*.01, 3e10*.09}, //A4
        // new double[]{1e3*100., 1e3*150.}, //A5
        // new double[]{.2, .8}, //A8
        // new double[]{.05, .25}, //A9
        // new double[]{.1, .9}, //A10
        // new double[]{.01, .09} //A13
        // new double[]{50e3, 100e3},
        // new double[]{0.05, 0.25},
        // new double[]{0.01, 0.09}
        // new double[]{0.2, 0.6},//0.409, - A10
        // new double[]{1e8*.2, 1e10*2.}// 1e8 * 2.42, - A12
    };

    auto alg = PSO();

    auto t_0 = clock();
    auto sol_vect = alg.optimize(testFunctions::ff_solve,f_con,2,1000,100,0.9,0.001,0.002,0.001);
    std::cout << "T: " << clock() - t_0 << std::endl;

    dt->save = true;

    D res = testFunctions::ff_solve(sol_vect,2);
    std::cout << "F - optimal: "
        << res
        << " At: "
        << sol_vect[0] << ", "
        << sol_vect[1] << ", "
        << sol_vect[2] << ", "
        << sol_vect[3] << ", "
        << sol_vect[4] << ", "
        << sol_vect[5] << ", "
        << sol_vect[6] << ", "
        << sol_vect[7] << ", "
        << sol_vect[8] << ", "
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

D* calculate_diff(int points,D h, D* center, D* right, D* left) {
    D* dif = new double[points];

    if(right != nullptr && left != nullptr && center != nullptr) {
        for(int i = 0; i < points; i++) {
            dif[i] = (right[i] - left[i])/center[i]/2.;
        }
    }
    else if(right != nullptr && center != nullptr) {
        for(int i = 0; i < points; i++) {
            dif[i] = (right[i] - center[i])/center[i];
        }
    }
    else if(left != nullptr && center != nullptr) {
        for(int i = 0; i < points; i++) {
            dif[i] = (center[i] - left[i])/center[i];
        }
    }

    return dif;
}