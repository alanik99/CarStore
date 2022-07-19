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
        std::cout << "\n\nВыберите действие (0 для вызова help): ";
        int action;
        processInput( action, std::string(" Введите цифру: ") );

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
            std::cout << "\nОшибка! Введите цифру от 0 до 5";
            break;
        }
        }
    }
}

void Program::printHelp()
{
    std::cout << "\n"
                 "1 - Отобразить список авто\n"

                 "2 - Отобразить отфильтрованный список авто\n"

                 "3 - Отобразить каким автомобилем владеет покупатель\n"

                 "4 - Купить определенный автомобиль по ID\n"

                 "5 - Выйти из программы\n";
}

void Program::printCatalog(const std::map<int, std::shared_ptr<Car> > & catalog)
{
    std::cout << "\nСписок авто:\n";
    for (const auto & elem : catalog)
        std::cout << *elem.second << '\n';
}

void Program::handleFilter()
{
    std::cout << "\n\nВыберите фильтр (0 - текущий, 1 - новый): ";
    bool isNew;
    processInput( isNew, std::string(" Введите 0 или 1: ") );

    if ( isNew )
        setNewFilter();

    printCatalog( filteredCatalog );
}

void Program::setNewFilter()
{
    filteredCatalog = catalog;

    std::cout << "\n\nВыберите параметры для фильтрации "
                 "(0 - пропустить параметр, 1 - фильтровать по параметру):\n";
    handleColor();
    handlePrice();
    handleVelocity();
}

void Program::handleColor()
{
    std::cout << "\n\n\t>Цвет (0 - пропустить, 1 - фильтровать): ";
    bool isEnabled;
    processInput( isEnabled, std::string(" Введите 0 или 1: ") );
    if ( isEnabled )
    {
        std::cout << "\n\t\tДоступные цвета:\n"
                     "\t\tr - red;\n"
                     "\t\tg - green\n"
                     "\t\tb - blue\n"
                     "\t\ty - yellow\n"
                     "\t\ts - silver\n";
        std::cout << "\n\t\tВведите букву: ";
        char color;
        processInput( color, std::string(" Введите букву: ") );

        erase_if( filteredCatalog, [=](auto const & pair)
        {
            return pair.second->color != color;
        });
    }
}

void Program::handlePrice()
{
    std::cout << "\n\n\t>Максимальная цена (0 - пропустить, 1 - фильтровать): ";
    bool isEnabled;
    processInput( isEnabled, std::string(" Введите 0 или 1: ") );
    if ( isEnabled )
    {
        std::cout << "\n\t\tВведите максимальную цену: ";
        float maxPrice;
        processInput( maxPrice, std::string(" Введите число: ") );

        erase_if( filteredCatalog, [=](auto const & pair)
        {
            return pair.second->price > maxPrice;
        });
    }
}

void Program::handleVelocity()
{
    std::cout << "\n\n\t>Минимальная скорость (0 - пропустить, 1 - фильтровать): ";
    bool isEnabled;
    processInput( isEnabled, std::string(" Введите 0 или 1: ") );
    if ( isEnabled )
    {
        std::cout << "\n\t\tВведите минимальную скорость: ";
        float minVelocity;
        processInput( minVelocity, std::string(" Введите число: ") );

        erase_if( filteredCatalog, [=](auto const & pair)
        {
            return pair.second->velocity < minVelocity;
        });
    }
}

void Program::printCustomersAuto()
{
    customer.getCar() ?
                std::cout << "\nАвто покупателя: " << *customer.getCar() << '\n'
                : std::cout << "\nУ покупателя нет авто\n";
}

void Program::buyAuto()
{
    std::cout << "\nВведите ID автомобиля: ";
    int id;
    processInput( id, std::string(" Введите число: ") );

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
        std::cout << "\n\nОшибка! Авто с таким ID отсутствует";
}
