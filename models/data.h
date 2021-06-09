//
// Created by hussein on 08/06/2021.
//

#ifndef UNTITLED_DATA_H
#define UNTITLED_DATA_H

#include <iostream>
#include <ctime>

using namespace std;

struct Data {
    string name;
    double amount = 0;
    time_t date{};
};

istream& operator>>(istream& is, Data& data)
{
    is >> data.name;
    is >> data.amount;
    is >> data.date;

    return is;
}

ostream& operator<<(ostream& os, const Data& data)
{
    os << "\n" << data.name << " " << data.amount << " " << data.date;

    return os;
}

#endif //UNTITLED_DATA_H
