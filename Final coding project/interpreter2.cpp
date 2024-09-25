#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <variant>
#include <string>
#include <stdexcept>

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
  using std::variant;
} using namespace files_and_print;


//######################################  STACK CREATION AND MANAGMENT  ################################################

//      ------------  SIMPLIFIED VERSION WITH JUST INTS  ------------

/*
struct Variable {  // kinda creates my own type of variable, like a std::pair{string x, int y}
    string name;
    int value;
    // could add layer marker here, but html style makes it easier to understand
};

class Stack {
private:
    vector<Variable> stack;  // you won't be able to access the stack directly in the script

public:
    // Push a variable onto the stack
  void push(const string& name, int value) {
    stack.push_back({name, value});
  }

  // Push a scope marker to represent entering a new scope
  void enterScope() {  // creates a marker for the exit scop function to stop deleting once at it
    stack.push_back({"<scope>", 0});  // Scope marker
  }  // I could use levels as a property of the varible, individual scopes determined by where in the stack it is, but this is like html, with the only drawback of taking up a little more space and meaning you can't use the variable name "<scope>"

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
  int getValue(const std::string& name) const {
    // Iterate over the stack from top to bottom (reverse)
    for (auto it = stack.rbegin(); it != stack.rend(); ++it) {  // this basicaly loops over the stack from the end to beginning, finding the most recently added var under that name, to avoid duplicates in different scope. .rend(reverse end) = one term before the beginning of the list, while .rbegin(reverse begin) is the last term of the list
      if (it->name == name) {  // since "it" is a pointer (reverse iterator, but same difference) you have to refrence the original ("it" isn't the original, it just points to it) using -> instead of .
        return it->value;  // Return the most recent variable value
      }
    }
    // If variable not found, throw an exception or return a default error value
    //throw std::runtime_error("Variable not found!");
    cout << "Variable not found!";
  }
};
*/

//      ------------  FULL VERSION WITH MORE DATATYPES  ------------

struct StackVariable {  // kinda creates my own type of variable, like a std::pair{string x, int y}
  string name;
  variant<std::monostate, int, float, std::string> value;  // Supports int, float, and string. allows it to vary between different ones, and managed seperately
};

class VariableStack {
private:
  vector<StackVariable> stack;
  
public:
  // Push a variable with int value
  void push(const string& name, int value){
    stack.push_back({name, value});
  }
  
  // Push a variable with float value
  void push(const string& name, float value){
    stack.push_back({name, value});
  }
  
  // Push a variable with string value
  void push(const string& name, const string& value){
    stack.push_back({name, value});
  }
  
  void pop(){
    if (!stack.empty()) {
      stack.pop_back();
    }
  }

  // Push a scope marker to represent entering a new scope
  void enterScope(){  // creates a marker for the exit scop function to stop deleting once at it
    stack.push_back({"<scope>", 0});  // Scope marker
  }  // I could use levels as a property of the varible, individual scopes determined by where in the stack it is, but this is like html, with the only drawback of taking up a little more space and meaning you can't use the variable name "<scope>"

  // Pop all variables until the scope marker is reached
  void exitScope(){
      while (!stack.empty()) {  // keeps popping vars as long as there are vars to be popped
          if (stack.back().name == "<scope>") {  // if a marker is found ...
              stack.pop_back();  // ... Remove the scope marker, and
              break;  // ... stop poping vars
          }
          stack.pop_back();  // Remove variable if no marker is found
      }
  }

  // Retrieve the value of a variable
  variant<std::monostate, int, float, std::string> getValue(const string& name) const{
    // Iterate over the stack from top to bottom (reverse)
    for (auto it = stack.rbegin(); it != stack.rend(); ++it){  // this basicaly loops over the stack from the end to beginning, finding the most recently added var under that name, to avoid duplicates in different scope. .rend(reverse end) = one term before the beginning of the list, while .rbegin(reverse begin) is the last term of the list
      if (it->name == name){  // since "it" is a pointer (reverse iterator, but same difference) you have to refrence the original ("it" isn't the original, it just points to it) using -> instead of .
        return it->value;  // Return the most recent variable value
      }
    }
    // If variable not found, throw an exception or return a default error value
    //throw std::runtime_error("Variable not found!");
    cout << "Variable not found!";
    return std::monostate();
  }
};

//#######################################################################################################################

typedef variant<int, float, string, bool, double> anyVar_t;
typedef vector<vector<string>> listolists_t;  // this just makes it so I don't have to type out that whole thing every time

string validChars = "abcdefghijklmnopqrstuvwxyz_1234567890§ABCDEFGHIJKLMNOPQRSTUVWXYZœ∑´®†¨ˆøπåß∂ƒ©˙∆˚¬æ«`Ωç√∫˜µ™£¢º€‹›ﬁﬂ‡ŒˇÁØ∏ÅÍÎÏÓÔÒÚÆ»Ç◊ıÂ";

void resetFile(ifstream& file){
  file.clear();  // only modifies the flags and errors, in this case, removing the endoffile flag, allowing for another loop through
  file.seekg(0, std::ios::beg);  // sets the internal file pointer to the beginning
}

void printFile(ifstream& file){
  string printed;
  while(getline(file, printed)){
    cout << printed << endl;
  }
  resetFile(file);
}


string getTypeName(const anyVar_t& var) {  // THIS FUNCTION IS GENERATED BY CHAT GPT, I ONLY UNDERSTAND HOW SOME OF IT WORKS. DO NOT GRADE THIS.
  return visit([](auto&& arg) -> string {  // lambda function? whatever that means?
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, int>) {
      return "int";
    } else if constexpr (std::is_same_v<T, float>) {
      return "float";
    } else if constexpr (std::is_same_v<T, string>) {
      return "string";
    } else if constexpr (std::is_same_v<T, bool>){
      return "bool";
    } else if constexpr (std::is_same_v<T, double>){
      return "double";
    }
    return "unknown";  // Fallback
  }, var);
}

void printAny(anyVar_t toPrint){
  if(getTypeName(toPrint) == "int"){
    cout << std::get<int>(toPrint);
  }
  if(getTypeName(toPrint) == "float"){
    cout << std::get<float>(toPrint);
  }
  if(getTypeName(toPrint) == "string"){
    cout << std::get<string>(toPrint);
  }
  if(getTypeName(toPrint) == "bool"){
    cout << std::get<bool>(toPrint);
  }
  if(getTypeName(toPrint) == "double"){
    cout << std::get<double>(toPrint);
  }
}

void printList(vector<string> list){
  cout << "["; for(const auto& term : list){cout << term << ", "; } cout << "]";
}

vector<string> fileGetTokens(ifstream& file){
  char ch;
  vector<string> tokens;  // create a list(vector/array) to store all of the functions and individual tokens
  string currentToken;  // create a string to store the current file that the loop is on, to add to the tokens list(vector/array)

  bool previouslyNewLine = false;  // var to help remove tabs
  bool inString = false;

  while (file.get(ch)){  // checks char by char the file
    if(validChars.find(ch) == string::npos){  // if ch isn't part of the valid chars string
      if(ch == '\"' && !inString){
        inString = true;
      } else if(ch == '\"' && inString){
        inString = false;
      }
      if(!currentToken.empty()){
        tokens.push_back(currentToken);
        currentToken.clear();
      }
      previouslyNewLine = true;
    }
    if(!(previouslyNewLine && (ch == ' ' || ch == '\t'))){
      currentToken += ch;
      previouslyNewLine = false;
    }
  }

  // Check if there's still something in currentToken after the loop. this lets the last file go onto the list even if there isn't a \n or ; at the end of the file
  if(!currentToken.empty()){
    tokens.push_back(currentToken);
  }
  resetFile(file);
  return tokens;
}

vector<string> combineStringsInTokens(vector<string> tokens){
  bool inString = false;
  string currentString;
  vector<string> combined;
  for(string token : tokens){
    if(token[0] == '\"' && !inString){
      currentString += token;
      inString = true;
    } else if(token[0] == '\"' && inString){
      combined.push_back(currentString);
      currentString.clear();
      inString = false;
    } else if(inString){
      currentString += token;
      currentString += ' ';
    } else if(!inString){
      combined.push_back(token);
    }
  }
  return combined;
}

int main(){
  ifstream file("tests/test.q");
  VariableStack stack;

  printFile(file); cout << "\n\n\n";

  printList(combineStringsInTokens(fileGetTokens(file)));

/* Stack Tests
  //testing stack
  VariableStack stack;

  // Push variables with different types
  stack.push("x", 10);              // int
  stack.push("y", 3.14f);           // float
  stack.push("z", std::string("hi")); // string

  try {
    // Retrieve values
    auto x = stack.getValue("x");
    auto y = stack.getValue("y");
    auto z = stack.getValue("z");

    // Access values based on type using std::get
    cout << "x = " << std::get<int>(x) << endl;
    cout << "y = " << std::get<float>(y) << endl;
    cout << "z = " << std::get<string>(z) << endl;

  }  
  */
/* printAny Tests
  anyVar_t x;
  x = 3.5;
  printAny(x); */

  file.close();
  return 0;
}