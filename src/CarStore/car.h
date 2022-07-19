#pragma once

#include <iostream>

struct Car
{
    int   id;
    char  color;
    float price;
    float velocity;
};

std::ostream & operator<<(std::ostream & os, const Car & car);
