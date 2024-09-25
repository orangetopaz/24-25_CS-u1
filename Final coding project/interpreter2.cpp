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
typedef vector<vector<string>> listoflists_t;  // this just makes it so I don't have to type out that whole thing every time

string validChars = "abcdefghijklmnopqrstuvwxyz_1234567890§ABCDEFGHIJKLMNOPQRSTUVWXYZœ∑´®†¨ˆøπåß∂ƒ©˙∆˚¬æ«Ωç√∫˜µ™£¢º€‹›ﬁﬂ‡ŒˇÁØ∏ÅÍÎÏÓÔÒÚÆ»Ç◊ıÂ";

vector<string> funcList = {"`", "print", "~", "read", "loop", "int", "str", "flt", "bool", "intager", "float", "floating_point", "floating_point_number", "string", "boolean", "if", "elif", "else"};

void resetFile(ifstream& file){
  file.clear();  // only modifies the flags and errors, in this case, removing the endoffile flag, allowing for another loop through
  file.seekg(0, file.beg);  // sets the internal file pointer to the beginning
}

void printFile(ifstream& file){
  string printed;
  while(getline(file, printed)){
    cout << printed << endl;
  }
  resetFile(file);
}

int countFileChars(ifstream& file){
  file.seekg(0, file.end);  // seek to end of file
  int size = file.tellg();

  resetFile(file);  // reset file pointer to the beginning of the file
  return size;
}

char getNthFileChar(ifstream& file, int n){
  char ch;
  char returner;
  int i = 0;
  while(file.get(ch)){
    returner = ch;
    i++;
    if(i == n){break;}
  }
  return returner;
}


bool inList(vector<string> list, string term){
  if(std::any_of(list.begin(), list.end(), [term](string q) {return term == q;})){  // another lambda function, kinda know how they work but no really, original for this one: https://stackoverflow.com/a/60131309
    return true;
  }
  else{
    return false;
  }
}

vector<string> subVector(vector<string> original, int spos, int epos){
  return vector<string> (original.begin() + spos, original.begin() + epos);
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

vector<string> fileGetTokens(ifstream& file){  // I probably spent about 1/3 of my entire coding time on this, just getting it to work, isn't anything good but it does finaly (mostly probobly) work
  char ch;
  char Pch = '\0'; //  previos character
  vector<string> tokens;  // create a list(vector/array) to store all of the functions and individual tokens
  string currentToken;  // create a string to store the current file that the loop is on, to add to the tokens list(vector/array)

  bool previouslyNewLine = false;  // var to help remove tabs
  bool inString = false;

  while (file.get(ch)){  // checks char by char the file

    if(Pch == '\\'){ // maualy get rid of backslashes after they're delt with (lazy, i know, but i don't have the mental capacity to go through this mess of a function right now)
      currentToken.pop_back();
    }

    if(!(previouslyNewLine && (ch == ' ' || ch == '\t'))){
      if(inString){
        currentToken += ch;
        previouslyNewLine = false;
      } else if(validChars.find(ch) != string::npos){
        currentToken += ch;
      } else if(validChars.find(ch) == string::npos && ch != ' '){
        if(!currentToken.empty() && !(inString)){
          tokens.push_back(currentToken);
          currentToken.clear();
        }
        currentToken += ch;
      }
      previouslyNewLine = false;
    } 
    if(validChars.find(ch) == string::npos){  // if ch isn't part of the valid chars string
      if(ch == '\"' && !inString && Pch != '\\'){
        inString = true;
      } else if(ch == '\"' && inString && Pch != '\\'){
        inString = false;
      }
      if(!currentToken.empty() && !(inString)){
        tokens.push_back(currentToken);
        currentToken.clear();
      }
      if(!inString){previouslyNewLine = true;}
    }
    Pch = ch;
  }

  // Check if there's still something in currentToken after the loop. this lets the last file go onto the list even if there isn't a \n or ; at the end of the file
  if(!currentToken.empty()){
    tokens.push_back(currentToken);
  }

  resetFile(file);
  return tokens;
}

listoflists_t tokensToLines(vector<string> tokens){
  vector<string> currentLine;
  listoflists_t returner;
  for(string token : tokens){
    if(token == "\n" || token == ";"){
      returner.push_back(currentLine);
      currentLine.clear();
    }
    else{
      currentLine.push_back(token);
    }
  }

  if(!currentLine.empty()){
    returner.push_back(currentLine);
  }

  return returner;
}

void printListOfLists(listoflists_t listoflist){
  cout << "["; for(const auto& list : listoflist){printList(list); cout << ", ";} cout << "]";
}


//#############  Invisible Functional Functions  ##############

//string extractPrint(vector<string> tokens){}  // get a string from all the functions at the back of a print statement

//#############  Visible Functional Functions  ##############

void PRINT(int mode, string printed){
  if(mode == 0){
    cout << printed;
  }
  if(mode == 1){
    cout << "Error: " << printed;
  }
}

//###########################################################


int main(){
  cout << "What file do you want to run? Full relative path to interpreter: "; string quarkFile; cin >> quarkFile; ifstream file(quarkFile);
  VariableStack stack;

  vector<string> tokens = fileGetTokens(file);
  listoflists_t linedTokens = tokensToLines(tokens);

  //printFile(file); cout << "\n\n\n";
  //printList(tokens); cout << "\n\n\n";
  //printListOfLists(linedTokens); cout << "\n\n\n";

  string token;
  string Ptoken;
  string Ntoken;
  vector<string> line;
  string Lfunc;  // line function
  for(int i=0; i<linedTokens.size(); i++){  // the reason for using the int interation instead of looping though the list is so i can more easily check the upcomeing and previous tokens
    for(int j=0; j<linedTokens[i].size(); j++){
      token = linedTokens[i][j];  // what you think im gonna type this out every time? I probably would but i was smarter this time
      Ptoken = linedTokens[i][j-1];
      Ntoken = linedTokens[i][j+1];
      line = linedTokens[i];
      Lfunc = linedTokens[i][0];

      if(inList(funcList, token)){
        if(token == "`" || token == "print"){
          if(line.size() == 2 || line.size() == 4){  // as long as its either printing a string or error

            if(Ntoken[0] == '\"' && line.size() == 2){
              PRINT(0, Ntoken.substr(1, Ntoken.length()-2));
            }
            else if(Ntoken == "."){
              if(linedTokens[i][j+2] == "error"){
                PRINT(1, linedTokens[i][j+3].substr(1, linedTokens[i][j+3].length()-2));
              } 
              else{cout << "Sorry! Unsupourted function" << endl;}

            }
            else{cout << "Sorry! Unsupourted." << endl;}
          }
          else{cout << "Sorry! Unsupourted function" << endl;}
        }

        if(token == "~" || token == "read"){

        }

        if(token == "int" || token == "intager"){

        }

        if(token == "flt" || token == "float" || token == "floating_point" || token == "floating_point_number"){

        }
        
        if(token == "str" || token == "string"){

        }

        if(token == "bool" || token == "boolean"){

        }

        if(token == "loop"){

        }

        if(token == "if"){
          
        }

        if(token == "elif"){
          
        }

        if(token == "else"){
          
        }
      }
    }
  }

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

  cout << "\n\n\n";
  file.close();
  return 0;
}