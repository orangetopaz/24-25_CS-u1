#include <iostream>
#include <string>
#include <vector>

using namespace std;

string validChars = "abcdefghijklmnopqrstuvwxyz_1234567890§ABCDEFGHIJKLMNOPQRSTUVWXYZœ´®†¨ˆøπåß∂ƒ©˙∆˚¬æ«`Ωç˜µ™£¢º€‹›ﬁﬂ‡ŒˇÁØ∏ÅÍÎÏÓÔÒÚÆ»Ç◊ıÂ";

vector<string> getTokens(string line){
  vector<string> tokens;  // create a list(vector/array) to store all of the functions and individual tokens
  string currentToken;  // create a string to store the current line that the loop is on, to add to the tokens list(vector/array)

  bool previouslyNewLine = false;  // var to help remove tabs

  for (char ch : line){  // checks char by char the line
    if(validChars.find(ch) == string::npos){  // if ch isn't part of the valid chars string
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

  // Check if there's still something in currentToken after the loop. this lets the last line go onto the list even if there isn't a \n or ; at the end of the file
  if(!currentToken.empty()){
    tokens.push_back(currentToken);
  }
  return tokens;
}

void printList(vector<string> list){
  cout << "["; for(const auto& term : list){cout << term << "|"; } cout << "]";
}

int main(){
  string str1 = "45";
  string str2 = "3.14159";
  char str3[] = "31337 geek";
  string line = "int   xephyr  ,   yanis   ,  zachary \n  x    =   1; y   =   2; z   =  3";
 
  /* cout << std::stoi(str1) << endl;
  cout << stoi(str2) << endl;
  cout << stoi(str3) << endl;
  cout << stof(str2) << endl;
  cout << str3  << endl; */

  printList(getTokens(line));


  return 0;
}