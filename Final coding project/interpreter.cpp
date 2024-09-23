#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <utility>


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


int countChars(string str, char target){
  int count = 0;
  for(char term : str){
    if(term == target){
      count++;
    }
  }
  return count;
}

vector<string> listifyFile(ifstream& file){
  char ch;  // Create a char var, which is used to output the text file car by char to check for newlines and ;
  vector<string> lines;  // create a list(vector/array) to store all of the functions and individual lines
  string currentLine;  // create a string to store the current line that the loop is on, to add to the lines list(vector/array)

  bool previouslyNewLine = false;  // var to help remove tabs

  while (file.get(ch)) {  // Use a while loop together with the getline() function to read the file line by line
    if (ch == '\n' || ch == ';') {  // excude new lines
      // If newline or semicolon is encountered, save the current line
      if (!currentLine.empty()) {
          lines.push_back(currentLine);  // pushes the current line to the back end (last spot (append)) of the lines list
          currentLine.clear();
          previouslyNewLine = true;
      }
    }
    else {
      if (previouslyNewLine && (ch == ' ' || ch == '\t')){}  // if there's been a new line, without any actual characters besides spaces/tabs, that means these spaces are tabs 
      else{
        currentLine += ch;  // Accumulate characters for the current line
        previouslyNewLine = false;  // make sure the spaces aren't counted as tabs (runs every time a character sets, TRY TO FIX)
      }
    }
  }

  vector<vector<string>> execs;

  for (int i; i < lines.size(); i++){
    vector<string> instruct;
    if (lines[i][0] == '`'){

    }
  }

  return lines;
}

void printList(vector<string> list){
  cout << "["; for(const auto& term : list){cout << term << ", "; } cout << "]";
}

void printIList(vector<int> list){
  cout << "["; for(const auto& term : list){cout << term << ", "; } cout << "]";
}

void printStrPair(pair<string, string> inPair){
  cout << '[' << inPair.first << ", " << inPair.second << ']';
}

void printGoof1(pair<string, pair<string, string>> inPair){  // kinda temp but idk
  cout << '[' << inPair.first << ", ";
  printStrPair(inPair.second); cout << ']';
}

void printStrStack(unordered_map<string, pair<string, string>> list){
  cout << "["; for(const auto& term : list){printGoof1(term); cout << ", "; } cout << "]";
}

pair<vector<int>, vector<string>> findStrings(string line){
  int nOfQuotes = countChars(line, '\"');  // sets nOfQuotes to the count of quotes in the select string
  vector<int> pos;  // positions of quotation marks in the string
  vector<string> strings;  // the strings (areas between quotation marks) using the positions as found in pos

  // error handling
  if (nOfQuotes == 0) {
    return pair<vector<int>, vector<string>> {{1}, {"Error: No Quotes, Null # of Quotes"}};
  }
  if (nOfQuotes % 2 != 0) {
    return pair<vector<int>, vector<string>> {{1}, {"Error: No closing quotes, Null # of Quotes"}};
  }

  // find positions of quotation marks
  int minPos = 0;
  while (minPos < line.length()){
    int newestPos = line.find('\"', minPos);  // finds the position of the next quote. [string].find can take 2 params in this case, the thing to find and the position at which to start (which is absurdly helpful, I had like an extra 10 lines cuz I didn't know what the second param was for)
    if (newestPos == string::npos) {  //npos means impossible string index, in this case meaning no new quotes found
      break;  // no more quotes found
    }
    
    pos.push_back(newestPos);  // append the newest found position to the list of positions
    minPos = newestPos + 1;  // move to the character after the quote
  }

  // assign the terms of strings to the stuff in-between 2 quotes as found in the vector<int> pos section above
  for (int i = 0; i < nOfQuotes / 2; i++){
    strings.push_back(line.substr(pos[i * 2] + 1, pos[(i * 2) + 1] - pos[i * 2] - 1));  // extract string between the quotes (first arg of substr is position, second is len)
  }

  pair<vector<int>, vector<string>> fin;

  fin.first = pos;
  fin.second = strings;

  return fin;
}

string validVarChars = "abcdefghijklmnopqrstuvwxyz_1234567890§ABCDEFGHIJKLMNOPQRSTUVWXYZœ∑´®†¨ˆøπåß∂ƒ©˙∆˚¬æ«`Ωç√∫˜µ™£¢º€‹›ﬁﬂ‡ŒˇÁØ∏ÅÍÎÏÓÔÒÚÆ»Ç◊ıÂ";

string findFunc(string line){
  string func;
  for(char ch : line){
    if(countChars(validVarChars, ch) == 0){
      break;
    }
    func += ch;
    if (ch == '`'){break;}
  }
  return func;
}


//##################   CODING LANGUAGE FUNCTIONS   ####################//

unordered_map<string, pair<string, string>> stack;  // FIGURE OUT SOMETHING BETTER THAN STORING EVERYTHING AS STRINGS

void PRINT(string toPrint){
  cout << toPrint;
}

string READ(){ // maybe add printing in the read function like python
  string readIn;
  cin >> readIn;
  return readIn;
}

void PUSH(string datatype, string name, string val){
  stack.insert(make_pair(name, make_pair(datatype, val)));
}

//#####################################################################//

int main (){

  string fileName; cout << "What file to run?: "; cin >> fileName;  // helloworld.el2
  ifstream el2File(fileName);  // Read from the text file

  vector<string> instructions = listifyFile(el2File);
  
  /*
  printList(instructions);
  cout << "\n\n\n";
  cout << instructions[0] << endl;
  printList(findStrings(instructions[0]));
  */

  for(string line : instructions){
    string func = findFunc(line);
    cout << func << endl;
    vector<string> args;
    if (func == "`" || func == "print"){
      args[0] = findStrings(line).first[0];
      PRINT(args[0]);  //.......................................................ADD INPUT FOR STRINGS FROM FILE
    } else {
      if (func == "~" || func ==  "read"){
        READ();  //................................................................................MAYBE LET IT PRINT FROM THE READ FUNCTION LIKE IN PYTHON
      } else {
        if (func == "str" || func ==  "string"){
          cout << "str push" << endl;
          PUSH("str", "line", "read");  //.......................................................ADD INPUT FOR NAME AND VAL
        } else {
          if (func == "int" || func ==  "intager"){
            cout << "int push" << endl;
            PUSH("int", "loop", "read");  //.......................................................ADD INPUT FOR NAME AND VAL
          } else {
            if (func == "if"){
              
            }  else {
              cout << "some function I havn't cared to add yet" << endl;
            }
          }
        }
      }
    }
  }

  cout << "\n\n";
  printStrStack(stack);
  cout << "\n\n";

  // Close the file
  el2File.close();
  cout << '\n';
}