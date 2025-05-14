#include <iostream>
#include <queue>
#include <random>
#include "Polinom.h"
#include "tlist.h"

#pragma once

class BasePolinomStorage {
public:
    virtual ~BasePolinomStorage() = default;
    virtual int add() { return 0; };   // �������� �������
    virtual Polinom find() { return Polinom(); };  // ����� �������
    virtual int remove() { return 0; };
};
