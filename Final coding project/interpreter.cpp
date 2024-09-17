#include <iostream>
#include <fstream>


namespace files_and_print{
    using std::cout;
    using std::cin;
    using std::endl;
    using std::string;
    using std::to_string;
    using std::ofstream;
    using std::ifstream;
}
using namespace files_and_print;

int main () {

  string file; cout << "What file to run?: "; cin >> file;

  // Create a text string, which is used to output the text file
  string myText;

  // Read from the text file
  ifstream el2File(file);
  char ch;

  // Use a while loop together with the getline() function to read the file line by line
  while (el2File.get(ch)) {
    // Output the text from the file
    cout << ch;
  }
  // Close the file
  el2File.close();
}
