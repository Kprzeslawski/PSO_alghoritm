//
// Created by Krzysztof on 26.05.2024.
//
#include "PSO.h"

#include <random>

PSO::PSO() = default;

D * PSO::optimize(
    D fun(double*, int),
    D **constraints,
    int count,
    int particle_number,
    D inertia,
    D cop,
    D sios,
    D rsv
    ) {

    auto * best_solution = new D[count];
    for (int i = 0; i < count; ++i)
        best_solution[i] = (constraints[i][0] + constraints[i][1]) * .5;

    auto solution_value = fun(best_solution, count);

    //generate particle
    for(int i = 0; i < particle_number; i++) {
        //init its random cords
        auto * particle_position = new D[count];
        auto * best_particle_position = new D[count];
        auto * particle_velocity = new D[count];

        for(int i2 = 0; i2 < count; i2++) {
            particle_position[i2] = RN(constraints[i]);
            particle_velocity[i2] = RN(constraints[i]) * rsv;
            best_particle_position[i2] = particle_position[i2];
        }
        auto best_value = fun(best_particle_position, count);

        while (true) {
            for(int i3 = 0; i3 < count; i3++) {
                particle_velocity[i3] =
                    inertia * particle_velocity[i3] +
                    RN() * cop * (best_particle_position[i] - particle_position[i]) +
                    RN() * sios * (best_particle_position[i] - particle_position[i]);
                particle_position[i3] += particle_velocity[i3];

                if(particle_position[i3] < constraints[i3][0])particle_position[i3] = constraints[i3][0];
                else if(particle_position[i3] > constraints[i3][1])particle_position[i3] = constraints[i3][1];
            }


        }
    }
    return best_solution;
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