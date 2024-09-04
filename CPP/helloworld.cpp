#include <iostream>

void sPrint(std::string out){  // for some reason a str var don's exist, so i need to use whatever tf std:string is in the same way as like int or float or bool
    std::cout << out <<std::endl;
}

int main(){
    sPrint("mmm me likie pizza");  //std=standard, cout=character out, <<=output or left shift(in operators), endl=endline
    return 0;
}