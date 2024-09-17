#include <iostream>
using namespace std;  // this allows me to remove the std:: before the iostream functions like cout or string

string helloworld = " Hello World! ";

void breakL(int lines = 1){
    for(int i = 0; i < lines; i++){
        cout << "\n";
    }
}

void coutInvestigation(){
    cout << "mmm me likie pizza" << helloworld << "what else do i write lol" << endl;  //std=standard, cout=character out, <<=output or left shift(in operators), endl=endline, works like \n
        cout << "line1\n"; // the backslash works like endl
        cout << "line2";  // without \n or endl, the lines merge
        cout << "line3";
}

void cinInvestigation(){
    // To read an entire line, you use the getline command.
    cout << "Please enter your full name: ";
    
    // Create a string variable and read in from the user
    string fullName;
    getline(cin, fullName);
    
    // You can stream multiple items to the output, like concatenating
    cout << "Hello " << fullName << "!" << endl;
    // endl tells C++ to move to a new line
    cout << "It is nice to meet you!" << endl;
    //###############################################################################
    cout << "Please enter your first name: ";
    string name;
    cin >> name;
    
    cout << "Hello " << name << "!" << endl;
    cout << "It is nice to meet you!" << endl;
}

int main(){
    coutInvestigation();
    breakL(3);
    cinInvestigation();
    return 0;
}