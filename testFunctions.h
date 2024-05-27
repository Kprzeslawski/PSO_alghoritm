//
// Created by Krzysztof on 25.05.2024.
//

#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#ifndef D
#define D double
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class testFunctions {
    //stałe
    D R = 8.314462;
    //stal
    D b = 0.25e-9;
    D d = 30;
    D u = 43500;
    D Q = 312000;
    D p0 = 1e4;

public:
    static D fun1(D* x, int count);
    static D ff_solve(D* x, int count);

    D* CalcUsingEuler(D* a, D e_dot, D t_kel);
    D* CalcUsingEuler(D beg_ro, D beg_t, D end_t, int steps, D* a, D e_dot, D t_kel);
};



#endif //TESTFUNCTIONS_H
