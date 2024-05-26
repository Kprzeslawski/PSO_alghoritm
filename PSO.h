//
// Created by Krzysztof on 26.05.2024.
//
#ifndef PSO_H
#define PSO_H

#ifndef D
#define D double
#endif

class PSO {

    /**
     * @return Returns optimal solution (minimum)
     *
     * @param fun Optimized function
     * @param constraints Constraints of optimized function
     * @param count Count of variables
     */
    static D* optimize(
        D* fun(D* ,int),
        D** constraints,
        int count
    );
};

#endif //PSO_H