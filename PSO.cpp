//
// Created by Krzysztof on 26.05.2024.
//
#include "PSO.h"

#include <random>

PSO::PSO() = default;

D * PSO::optimize(D fun(D *, int), D **constraints, int count) {

    auto * solution = new D[count];
    for (int i = 0; i < count; ++i)
        solution[i] = (constraints[i][0] + constraints[i][1]) * .5;

    auto solution_value = fun(solution, count);

    //generate particle
    for(int i = 0; i < this->particle_number; i++) {
        //init its random cords
        auto * particle_position = new D[count];
        for(int i2 = 0; i2 < count; i2++)
            particle_position[i2] = RN(constraints[i]);

    }
    return solution;
}


D PSO::RN() {
    std::uniform_real_distribution<auto> unif(0,1);
    std::random_device r;
    std::default_random_engine re(r());
    return unif(re);
}

D PSO::RN(D * c) {
    std::uniform_real_distribution<auto> unif(c[0],c[1]);
    std::random_device r;
    std::default_random_engine re(r());
    return unif(re);
}

D PSO::RN(D a, D b) {
    std::uniform_real_distribution<auto> unif(a,b);
    std::random_device r;
    std::default_random_engine re(r());
    return unif(re);
}