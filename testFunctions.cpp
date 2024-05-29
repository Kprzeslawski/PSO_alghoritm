//
// Created by Krzysztof on 25.05.2024.
//

#include "testFunctions.h"

#include <stdexcept>
#include <cmath>

#include "DataStorage.h"


//stałe
D testFunctions::R = 8.314462;
//stal
D testFunctions::b = 0.25e-9;
D testFunctions::d = 30.;
D testFunctions::u = 43500.;
D testFunctions::Q = 312000.;
D testFunctions::p0 = 1e4;

D testFunctions::fun1(D *x, int count) {
    if(count < 2)throw std::runtime_error("Invalid args count");
    return ((x[0] - 5) * (x[0] - 1) + 12) * ((x[1] - 2) * (x[1] - 3) + 4);

}

D testFunctions::ff_solve(D *x, int count) {
    if(count < 2)throw std::runtime_error("Invalid args count");
    D y = 0;
    auto ds = DataStorage::getInstance();
    D* res = nullptr;

    for (int i = 0; i < 9; i++) {
        // std::cout << "________________________ITER: "<< i << std::endl;
        // res = CalcUsingEuler(DT{ xt(0),xt(1),xt(2),
        // 	xt(3),xt(4),xt(5),xt(6),xt(7),xt(8),xt(9),
        // 	xt(10)}, ds.e_dot[i], ds.t[i] + 273.);
        //D args[] = { x[0],x[1],x[2],3e10*0.05317,1e3*123.12,0.452,x[3],0.409,0.,1e13*0.000042,x[4]};
        D args[] = {
            x[0],
            x[1],
            // 0.000119459,
            // 21961.6,
            1e3 * 83.349,
            3e10 * 0.05317,
            1e3 * 123.12,
            0.452,
            0.13751,
            0.409,
            // x[0],
            0.,
            // x[1],
            1e13 * 0.000042,
            // 1e8 * 2.42,
            0.07486};
        res = CalcUsingEuler(args, ds->e_dot[i], ds->t[i]);

        for (int i2 = 0; i2 < 500; i2++) {
            y += pow( 1. - ds->ro[i][i2]/res[i2],2.);
            // if (i2 < 1000) {
            //     D grad_res = (res[i2] - res[i2 + 1]) / res[i2];
            //     D grad_y = (ds->ro[i][i2] - ds->ro[i][i2 + 1]) / ds->ro[i][i2];
            //     y += pow(grad_res - grad_y,2.);
            // }
        }
        if (ds->save && i == 0) {
            std::cout << "SAVING... \n";
            std::ofstream plik("data_counted.txt");
            for (int i2 = 0; i2 < 1001; i2++) plik << res[i2] << std::endl;
            plik.close();
            std::cout << "OK\n";
        }
    }
    delete res;

    return y;
}

D* testFunctions::CalcUsingEuler(D* a, D e_dot, D t_kel) {
    return CalcUsingEuler(p0, 0., 1. / e_dot, 1000, a, e_dot, t_kel);
}

D* testFunctions::CalcUsingEuler(D beg_ro, D beg_t, D end_t, int steps, D* a, D e_dot, D t_kel){

    D h = (end_t - beg_t) / steps;
    D* ro_dt = new double[steps + 1];
    ro_dt[0] = beg_ro;

    D Z = e_dot * exp(Q / (R * t_kel));
    D p_cr = -a[8] + a[9] * pow(Z, a[7]);
    // D p_cr = 4.53e13;
    //  std::cout << "E: " << e_dot << std::endl;
    //  std::cout << "Z: " << Z << std::endl;
    // std::cout << "A10: " << a[7] << std::endl;
    //  std::cout << "Z^P: " << pow(Z, a[7]) << std::endl;
    //  std::cout << "A12: " << a[9] << std::endl;
    //  std::cout << "S A12: " << 1.84e13 / pow(Z, a[7])  << std::endl;
    //  std::cout << "S A12: " << 4.63e13 / pow(Z, a[7])  << std::endl;
    // std::cout << "RO_CR: " << p_cr << std::endl;//4.60
    D l = a[0] / pow(Z, a[10]);
    D a1 = 1. / (b * l);
    D a2 = a[1] * pow(e_dot, -a[6]) * exp(-a[2] / (R * t_kel));
    D tau = 1e6 * u * b * b / 2.;
    D a3 = a[3] * tau / d * exp(-a[4] / (R * t_kel));
    int t_cr_ind = 0;
    bool crit = true;

    for (int i = 1; i <= steps; i++) {
        ro_dt[i] = ro_dt[i - 1];
        if (crit) {
            ro_dt[i] += h * (a1 * e_dot - a2 * ro_dt[i - 1] * e_dot);
            if(ro_dt[i] >= p_cr) {
                t_cr_ind = i;
                crit = false;
            }
        }
        else {
            ro_dt[i] += h * (a1 * e_dot - a2 * ro_dt[i - 1] * e_dot
                - a3 * pow(ro_dt[i - 1], a[5]) * ro_dt[i - t_cr_ind]);
        }
    }
    return ro_dt;
}
