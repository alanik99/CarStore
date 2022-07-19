#pragma once

#include "car.h"

#include <memory>

class Customer
{
    std::shared_ptr<Car> car;

public:
    Customer() : car(nullptr) {}

    void setCar( const std::shared_ptr<Car> & car )  { this->car = car; }

    Car * getCar() const  { return car.get(); }
};
