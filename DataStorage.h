//
// Created by Krzysztof on 27.05.2024.
//

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class DataStorage {
protected:
    static DataStorage* instance;
    DataStorage();
public:
    vector<vector<double>> ro;
    vector<double> t;
    vector<double> e_dot;
    bool save;
    static DataStorage* getInstance();
};

#endif //DATASTORAGE_H
