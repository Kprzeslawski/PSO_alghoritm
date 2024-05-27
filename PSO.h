//
// Created by Krzysztof on 26.05.2024.
//
#ifndef PSO_H
#define PSO_H

#ifndef D
#define D double
#endif

class PSO {

    int particle_number = 1000;

public:
    //generators
    static D RN();
    static D RN(D *);
    static D RN(D ,D);


    PSO();

    /**
     * @return Returns optimal solution (minimum)
     *
     * @param fun Optimized function
     * @param constraints Constraints of optimized function - first dim is for variable second for its min and max
     * @param count Count of variables
     * @param particle_number Number of particles
     * @param particle_steps number of times new particle position is calculated
     * @param inertia Inertia of particle
     * @param cop Cognition of particle
     * @param sios Social influence of swarm
     * @param rsv Random initial velocity multiplayer based on constraints
     */
    D* optimize(
        D (*fun)(D *, int),
        D **constraints,
        int count,
        int particle_number,
        int particle_steps,
        D inertia,
        D cop,
        D sios,
        D rsv
    );


};

#endif //PSO_H