#include <iostream>
#include <queue>
#include <random>
#include "Polinom.h"
#include "tlist.h"

#pragma once

class BasePolinomStorage {
public:
    virtual ~BasePolinomStorage() = default;
    virtual int add() { return 0; };   // Добавить полином
    virtual Polinom find() { return Polinom(); };  // Найти полином
    virtual int remove() { return 0; };
};
