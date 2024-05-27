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
    static D R;
    //stal
    static D b;
    static D d;
    static D u;
    static D Q;
    static D p0;

public:
    testFunctions() = default;

    static D fun1(D* x, int count);
    static D ff_solve(D* x, int count);

    static D* CalcUsingEuler(D* a, D e_dot, D t_kel);
    static D* CalcUsingEuler(D beg_ro, D beg_t, D end_t, int steps, D* a, D e_dot, D t_kel);
};



#endif //TESTFUNCTIONS_H
