//
// Created by Krzysztof on 26.05.2024.
//

#include "PSO.h"


D * PSO::optimize(D fun(D *, int), D **constraints, int count) {

    auto * solution = new D[count];
    for (int i = 0; i < count; ++i)
        solution[i] = (constraints[i][0] + constraints[i][1]) * .5;

    auto solution_value = fun(solution, count);


    //TODO
    return solution;
}
