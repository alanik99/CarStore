#include "program.h"
#include "algorithms.h"

#include <iostream>
#include <vector>

Program::Program()
{

}

void Program::exec()
{
    generateCatalog();
    execLoop();
}

void Program::generateCatalog()
{
    std::vector<char> carColors = { 'r', 'g', 'b', 'y', 's' };

    int catalogSize = gen.genRandInt(7, 10);

    for (int id = 0; id < catalogSize; ++id)
        catalog[id] = std::make_shared<Car>( Car{id,
                                                 carColors.at( gen.genRandInt(0, carColors.size()-1) ),
                                                 gen.genRandFloat(1.0, 3.0),
                                                 gen.genRandFloat(100.0, 400.0)} );
}

void Program::execLoop()
{
    bool isProgramActive = true;

    while ( isProgramActive )
    {
        std::cout << "\n\n�������� �������� (0 ��� ������ help): ";
        int action;
        processInput( action, std::string(" ������� �����: ") );

        switch ( action )
        {
        case 0:
        {
            printHelp();
            break;
        }
        case 1:
        {
            printCatalog( catalog );
            break;
        }
        case 2:
        {
            handleFilter();
            break;
        }
        case 3:
        {
            printCustomersAuto();
            break;
        }
        case 4:
        {
            buyAuto();
            break;
        }
        case 5:
        {
            isProgramActive = false;
            break;
        }
        default:
        {
            std::cout << "\n������! ������� ����� �� 0 �� 5";
            break;
        }
        }
    }
}

void Program::printHelp()
{
    std::cout << "\n"
                 "1 - ���������� ������ ����\n"

                 "2 - ���������� ��������������� ������ ����\n"

                 "3 - ���������� ����� ����������� ������� ����������\n"

                 "4 - ������ ������������ ���������� �� ID\n"

                 "5 - ����� �� ���������\n";
}

void Program::printCatalog(const std::map<int, std::shared_ptr<Car> > & catalog)
{
    std::cout << "\n������ ����:\n";
    for (const auto & elem : catalog)
        std::cout << *elem.second << '\n';
}

void Program::handleFilter()
{
    std::cout << "\n\n�������� ������ (0 - �������, 1 - �����): ";
    bool isNew;
    processInput( isNew, std::string(" ������� 0 ��� 1: ") );

    if ( isNew )
        setNewFilter();

    printCatalog( filteredCatalog );
}

void Program::setNewFilter()
{
    filteredCatalog = catalog;

    std::cout << "\n\n�������� ��������� ��� ���������� "
                 "(0 - ���������� ��������, 1 - ����������� �� ���������):\n";
    handleColor();
    handlePrice();
    handleVelocity();
}

void Program::handleColor()
{
    std::cout << "\n\n\t>���� (0 - ����������, 1 - �����������): ";
    bool isEnabled;
    processInput( isEnabled, std::string(" ������� 0 ��� 1: ") );
    if ( isEnabled )
    {
        std::cout << "\n\t\t��������� �����:\n"
                     "\t\tr - red;\n"
                     "\t\tg - green\n"
                     "\t\tb - blue\n"
                     "\t\ty - yellow\n"
                     "\t\ts - silver\n";
        std::cout << "\n\t\t������� �����: ";
        char color;
        processInput( color, std::string(" ������� �����: ") );

        erase_if( filteredCatalog, [=](auto const & pair)
        {
            return pair.second->color != color;
        });
    }
}

void Program::handlePrice()
{
    std::cout << "\n\n\t>������������ ���� (0 - ����������, 1 - �����������): ";
    bool isEnabled;
    processInput( isEnabled, std::string(" ������� 0 ��� 1: ") );
    if ( isEnabled )
    {
        std::cout << "\n\t\t������� ������������ ����: ";
        float maxPrice;
        processInput( maxPrice, std::string(" ������� �����: ") );

        erase_if( filteredCatalog, [=](auto const & pair)
        {
            return pair.second->price > maxPrice;
        });
    }
}

void Program::handleVelocity()
{
    std::cout << "\n\n\t>����������� �������� (0 - ����������, 1 - �����������): ";
    bool isEnabled;
    processInput( isEnabled, std::string(" ������� 0 ��� 1: ") );
    if ( isEnabled )
    {
        std::cout << "\n\t\t������� ����������� ��������: ";
        float minVelocity;
        processInput( minVelocity, std::string(" ������� �����: ") );

        erase_if( filteredCatalog, [=](auto const & pair)
        {
            return pair.second->velocity < minVelocity;
        });
    }
}

void Program::printCustomersAuto()
{
    customer.getCar() ?
                std::cout << "\n���� ����������: " << *customer.getCar() << '\n'
                : std::cout << "\n� ���������� ��� ����\n";
}

void Program::buyAuto()
{
    std::cout << "\n������� ID ����������: ";
    int id;
    processInput( id, std::string(" ������� �����: ") );

    auto iter = catalog.find( id );
    if ( iter != catalog.end() )
    {
        customer.setCar( iter->second );

        catalog.erase( iter );

        iter = filteredCatalog.find( id );
        if ( iter != filteredCatalog.end() )
            filteredCatalog.erase( iter );
    }
    else
        std::cout << "\n\n������! ���� � ����� ID �����������";
}
