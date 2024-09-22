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

vector<string> findStrings(string line){
  int nOfQuotes = countChars(line, '\"');  // sets nOfQuotes to the count of quotes in the select string
  vector<int> pos;  // positions of quotation marks in the string
  vector<string> strings;  // the strings (areas between quotation marks) using the positions as found in pos

  // error handling
  if (nOfQuotes == 0){
    return vector<string> {"Error: No Quotes, Null # of Quotes"};
  }
  if (nOfQuotes % 2 != 0){
    return vector<string> {"Error: No closing quotes, Null # of Quotes"};
  }
  //if(nOfQuotes == 2){return vector<string> {"Valid"};}

  // find positions of quotation marks
  int minPos = -1;
  while(countChars(line.substr(minPos), '\"') != 0){  // loops through each " in the string, until there aren't any
    int newestPos = line.substr(minPos, line.length()).find('\"');  // finds the position of closest to beginning location of " along the string
    pos.push_back(newestPos);  // appends the newest found position to the list of positions
    minPos = newestPos + 1;  // sets the new starting position to search from to the newest one found +1
  }

  // assign the terms of strings to the stuff inbetween 2 quotes as found in the vector<int> pos section above
  for(int i=0; i < nOfQuotes/2; i++){
    strings.push_back(line.substr(pos[i*2]+1, pos[(i*2)+1]-1));  // appends a substr of the inputted string, from the first quote's pos +1 (first char in the string) and 2nd quote's pos -1(last char in the string), then changing 1st and second as needed
  }
  return strings;
}

void printList(vector<string> list){
  cout << "["; for(const auto& term : list){cout << term << ", "; } cout << "]";
}

int main () {

  string fileName; cout << "What file to run?: "; cin >> fileName;  // helloworld.el2
  ifstream el2File(fileName);  // Read from the text file

  vector<string> instructions = listifyFile(el2File);

  //cout << "["; for(const auto& line : instructions){cout << line << ", "; } cout << "]";
  printList(instructions);
  cout << "\n\n\n";
  cout << instructions[0];
  printList(findStrings(instructions[0]));

  // Close the file
  el2File.close();
  cout << '\n';
}