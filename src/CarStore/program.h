#pragma once

#include "randnumgenerator.h"
#include "car.h"
#include "customer.h"

#include <map>
#include <memory>

class Program
{
public:
    Program();
    void exec();

private:
    void generateCatalog();
    void execLoop();

    void printHelp();

    void printCatalog( const std::map<int, std::shared_ptr<Car>> & catalog );

    void handleFilter();
    void setNewFilter();
    void handleColor();
    void handlePrice();
    void handleVelocity();

    void printCustomersAuto();

    void buyAuto();

    RandNumGenerator gen;
    std::map<int, std::shared_ptr<Car>> catalog;
    std::map<int, std::shared_ptr<Car>> filteredCatalog;
    Customer customer;
};

