#include <iostream>

#include "cfdVector.hpp"

int main(int argc, char* argv[]){
    std::cout <<" Euler !" <<std::endl;

    /*------------------test ds.hpp------------------------*/

     auto vec = cfdVector<double>(3);
    std::cout << vec << std::endl;
    vec[0] = 1.5;
    std::cout << vec << std::endl;
    vec.setValue(std::vector<double>{1,2,3.0});
    std::cout << vec << std::endl;

    
    return 0;
}