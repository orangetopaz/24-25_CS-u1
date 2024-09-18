#include <iostream>
#include <vector>
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
}
using namespace files_and_print;

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
  return lines;
}

int main () {

  string fileName; cout << "What file to run?: "; cin >> fileName;  // helloworld.el2
  ifstream el2File(fileName);  // Read from the text file

  vector<string> instructions = listifyFile(el2File);

  cout << "["; for(const auto& line : instructions){cout << line << ", "; } cout << "]";

  // Close the file
  el2File.close();
  cout << '\n';
}