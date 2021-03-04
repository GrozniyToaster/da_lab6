#include <iostream>

#include "big_integer.hpp"



int main(){
    NBigInt::bint_t a, b;
    char action;
    while( std::cin >> a >> b >> action ){
        if ( action == '+' ){
            std::cout << a + b << '\n';
        }else if ( action == '-' ){
            //std::cout << a - b << '\n';
        }
    }

}