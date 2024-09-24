#include <iostream>
#include <vector>
#include <map>
#include <fstream>

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

vector<string> listifyFile(ifstream& file){
  char ch;  // Create a char var, which is used to check the text file car by char to check for newlines and ;
  vector<string> lines;  // create a list(vector/array) to store all of the functions and individual lines
  string currentLine;  // create a string to store the current line that the loop is on, to add to the lines list(vector/array)

  bool previouslyNewLine = false;  // var to help remove tabs

  while (file.get(ch)) {  // Use a while loop together with the getline() function to read the file line by line
    if(ch == '\n' || ch == ';'){
      if(!currentLine.empty()){
        lines.push_back(currentLine);
        currentLine.clear();
      }
      previouslyNewLine = true;
    }
    else if(!(previouslyNewLine && (ch == ' ' || ch == '\t'))){
      currentLine += ch;
      previouslyNewLine = false;
    }
  }

  // Check if there's still something in currentLine after the loop. this lets the last line go onto the list even if there isn't a \n or ; at the end of the file
  if(!currentLine.empty()){
    lines.push_back(currentLine);
  }

  resetFile(file);
  return lines;
}

int main(){
  ifstream file("tests/breakdowntest.q");

  printFile(file); cout << "\n\n\n";

  vector<string> lines = listifyFile(file);
  cout << "{"; for (string line : lines){cout << line << ", ";} cout << "}"; cout << endl;  // prints the list of the file term by term

  file.close();
  return 0;
}