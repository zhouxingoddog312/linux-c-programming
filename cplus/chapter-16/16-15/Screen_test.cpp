#include <iostream>
#include "Screen.h"
int main() {
    Screen<3, 3> screen('x');
    std::cout<<screen;
    std::cout<<std::endl;
    screen.set(2, 2, 'o');
    std::cout<<screen;
    std::cout<<std::endl;
    std::cin>>screen;
    std::cout<<screen;
    std::cout<<std::endl;
    return 0;
}
