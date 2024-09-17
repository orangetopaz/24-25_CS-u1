#include <iostream>

namespace printing{
    using std::cout;
    using std::endl;
    using std::string;
    using std::to_string;
}

void print(std::string input){
    using namespace printing;
    cout << input << endl;
}

int main(){
    using namespace printing;

    int x;  // Declaration
    int y = 6;
    x = 5;  // Behaves like a 5
    int sum = x+y;

    cout << x << "hello\n" << y << endl;
    cout << sum << endl;

    //int(ager) = whole number

    int age = 21;
    int year = 2024;
    float days = 7.5;

    print(to_string(days));

    //float(ing point decemal) = funky small less precice decimal number (4 bytes)
    //double = funky big more precise decimal number (8 bytes)
    //string = text
    //char(acter) = single character
    //





    
    cout << "\n\n\n";
    return 0;
}