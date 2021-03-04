#include <iostream>

#include "big_integer.hpp"



int main(){
    NBigInt::bint_t a, b;
    char action;
    while( std::cin >> a >> b >> action ){
        if ( action == '+' ){
            std::cout << a + b << '\n';
        }else if ( action == '-' ){
            if (a < b){
                std::cout << "Error\n";
            } else {
                std::cout << a - b << '\n';
            }
        }
    }

    return 0;

}