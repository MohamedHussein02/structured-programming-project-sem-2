//
// Created by hussein on 09/06/2021.
//

#ifndef UNTITLED_DATA_IO_UTILS_H
#define UNTITLED_DATA_IO_UTILS_H
#include "../models/data.h"
#include <vector>
#include <iterator>
#include <fstream>
#include <unistd.h>

vector<Data> readSaveFile(string &filePath) {
    vector<Data> vec;
    ifstream inputStream;

    inputStream.open(filePath);

    while(!inputStream.eof()) {
        Data element;
        inputStream >> element;

        vec.push_back(element);
    }

    return vec;
}

bool writeSaveFile(vector<Data> &vec, string &filePath) {

    if (vec.size() == 0) {
        return true;
    }

    ofstream outStream;

    outStream.open(filePath, ios::trunc);

    for (int i = 0; i <= vec.size() - 1; ++i) {
        outStream << vec[i];
    }

    outStream.close();

    return true;
}
#endif //UNTITLED_DATA_IO_UTILS_H
