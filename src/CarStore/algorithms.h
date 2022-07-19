#pragma once

#include <iostream>

template< class ContainerT, class PredicateT >
void erase_if(ContainerT & cont, PredicateT pred)  // similar template is available since C++20
{
    for ( auto it = cont.begin(); it != cont.end(); )
    {
        if ( pred(*it) )
            it = cont.erase(it);
        else
            ++it;
    }
}

template< class T >
void processInput( T & var, const std::string & errorStr )
{
    std::cin >> var;
    while ( std::cin.fail() )
    {
        std::cin.clear();
        std::cin.ignore(256, '\n');

        std::cerr << "\nÎøèáêà ââîäà!" << errorStr;
        std::cin >> var;
    }
}
