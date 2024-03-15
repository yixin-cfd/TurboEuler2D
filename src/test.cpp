#include <iostream>

#include "cfdVector.hpp"
using namespace std;

int main(int argc, char* argv[]){
    std::cout <<" Euler !" <<std::endl;

    /*------------------test ds.hpp------------------------*/

    auto vec1 = cfdVector<double>(3);
    std::cout << vec1 << std::endl;
    vec1[0] = 1.5;
    std::cout << vec1 << std::endl;
    vec1.setValue(std::vector<double>{1,2,3.0});
    std::cout << vec1 << std::endl;

    auto vec2 = vec1;
    auto res = dot(vec1, vec2);
    cout << res << endl;

    auto vec3 = -1*vec2;
    cout << vec3 << endl;
    vec3 = vec3*-1;
    cout << vec3 <<endl;
    auto vec4 = cross(vec1, vec2);
    cout << vec4<<endl;
    return 0;
}