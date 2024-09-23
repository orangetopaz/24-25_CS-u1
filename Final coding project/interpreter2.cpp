#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <variant>

namespace files_and_print{
  using std::cout;
  using std::cin;
  using std::endl;
  using std::string;
  using std::to_string;
  using std::ofstream;
  using std::ifstream;
  using std::vector;
  using std::fstream;
  using std::unordered_map;
  using std::pair;
  using std::make_pair;
} using namespace files_and_print;


//######################################  STACK CREATION AND MANAGMENT  ################################################

//      ------------  SIMPLIFIED VERSION WITH JUST INTS  ------------

struct Variable {  // kinda creates my own type of variable, like a std::pair{string x, int y}
    string name;
    int value;
};

class VariableStack {
private:
    vector<Variable> stack;  // you won't be able to access the stack directly in the script

public:
    // Push a variable onto the stack
    void push(const string& name, int value) {
        stack.push_back({name, value});
    }

    // Push a scope marker to represent entering a new scope
    void enterScope() {  // creates a marker for the exit scop function to stop deleting once at
        stack.push_back({"<scope>", 0});  // Scope marker
    }

    // Pop all variables until the scope marker is reached
    void exitScope() {
        while (!stack.empty()) {  // keeps popping vars as long as there are vars to be popped
            if (stack.back().name == "<scope>") {  // if a marker is found ...
                stack.pop_back();  // ... Remove the scope marker, and
                break;  // ... stop poping vars
            }
            stack.pop_back();  // Remove variable if no marker is found
        }
    }

    // Retrieve the value of a variable
    bool getValue(const string& name, int& outValue) const {
        for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
            if (it->name == name) {
                outValue = it->value;
                return true;
            }
        }
        return false;  // Not found
    }
    
    void printValue(const string& name) const {
        int outValue;
        if (getValue(name, outValue)) {
            cout << name << " = " << outValue << endl;
        } else {
            cout << "Variable not found!" << endl;
        }
    }
};

//#######################################################################################################################

int main(){
    ifstream file("test.q");
    string printed;
    while(getline(file, printed)){
      cout << printed;
    }
}