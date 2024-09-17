#include <iostream>
#include <vector>

/* Typedef has mostly been replaced with "using" keyword, which works better with templates

*/


//typedef std::vector<std::pair<std::string, int> > pairlist_t;  // creates a vector/tuple of a string and an int I think, and renames that long definition into just pairlist_t
// common convention is that you should end a typdef variable type with _t

// simpler example:
//typedef std::string text_t;
//typedef int number_t;

// using the 'using' keyword
using text_t = std::string;
using number_t = int;


int main(){
    //std::vector<std::pair<std::string, int>> pairlist;  // instead of this, use this:
    //pairlist_t pairlist; // This is a variable declaration, using the "new" variable type "pairlist_t"
    text_t first_name = "bray";
    number_t age = 15;

    std::cout << "\n\n\n" << first_name << age << "\n\n\n";


    return 0;
}