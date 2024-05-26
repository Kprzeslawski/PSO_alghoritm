//
// Created by Krzysztof on 26.05.2024.
//
#ifndef PSO_H
#define PSO_H

#ifndef D
#define D double
#endif

class PSO {
public:

    /**
     * @return Returns optimal solution (minimum)
     *
     * @param fun Optimized function
     * @param constraints Constraints of optimized function - first dim is for variable second for its min and max
     * @param count Count of variables
     */
    static D* optimize(
        D fun(D *, int),
        D **constraints,
        int count
    );
};

#endif //PSO_H