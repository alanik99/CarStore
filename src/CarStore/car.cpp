#include "car.h"

std::ostream & operator<<(std::ostream & os, const Car & car)
{
    return os << "[ id: " << car.id
              << ";  color: " << car.color
              << ";  price: " << car.price
              << ";  velocity: " << car.velocity << " ]";
}
