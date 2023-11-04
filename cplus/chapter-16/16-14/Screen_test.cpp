#include <iostream>
#include "Screen.h"
int main() {
    Screen<3, 3> screen('x');
    screen.display(std::cout);
    std::cout<<std::endl;
    screen.set(2, 2, 'o');
    screen.display(std::cout);
    std::cout<<std::endl;
    return 0;
}
