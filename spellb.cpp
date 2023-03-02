
#include "SBTrie.h"
#include "Trie.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::cin;
using std::string;

void getNewDictionary(SBTrie *sbt, string filename){
  sbt->newDictionary(filename);
}

void updateDictionary(SBTrie *sbt, string filename){
  sbt->updateDictionary(filename);
}

void setupLetters(SBTrie *sbt, string letters){
  // check if input was 7 letters long
  if (letters.length() != 7) {
    cout << "Invalid letter set" << endl;
    return;
  }

  char centralLetter;
  string allowedLetters = "";
  // check for first valid letter --- will be assigned as central letter
  bool firstValidLetter = true;

  for (int i = 0; i < letters.length(); i++) {
    // check if character at index is in the alphabet
    if (isalpha(letters[i])) { 
      // check whether its in the allowedLetters string or the central letter
      if (firstValidLetter) {
        centralLetter = tolower(letters[i]);
        firstValidLetter = false;
      } else {
        allowedLetters += tolower(letters[i]);
      }
      sbt->setRules(centralLetter, allowedLetters);
    }
  }

  // reset state of the game
  sbt->resetState();

}

void showLetters(SBTrie *sbt){
  sbt->printLetters();
}

void attemptWord(SBTrie *sbt, string letters){
  char centralLetter;
  string allowedLetters;

  sbt->getLetters(centralLetter, allowedLetters);
  std::transform(letters.begin(), letters.end(), letters.begin(), ::tolower);

  // check if word is too short or is missing central letter
  if (letters.length() < 4) {
    cout << "word is too short" << endl;
    return;
  } else if (letters.find(centralLetter) == std::string::npos) {
    cout << "word is missing central letter" << endl;
    return;
  }

  // check for any invalid letters
  for (auto c: letters) {
    if (allowedLetters.find(c) == std::string::npos && c != centralLetter) {
      cout << "word contains invalid letter" << endl;
      return;
    }
  }

  // check if word is in the dictionary
  if (!sbt->searchDictionary(letters)) {
    cout << "word is not in the dictionary" << endl;
    return;
  }

  // check if word has already been found
  if (sbt->searchFoundWords(letters)) {
    cout << "word has already been found" << endl;
    return;
  }

  int overallScore;
  int pointsScored;
  bool foundPangram = false;
  bool scoredBingo = false;

  sbt->wordFound(letters, pointsScored, overallScore, foundPangram, scoredBingo);

  string message = "found " + letters + " " + to_string(pointsScored) + " ";

  if (pointsScored == 1) {
    message += "point, total " + to_string(overallScore);
  } else {
    message += "points, total " + to_string(overallScore);
  }

  if (overallScore == 1) {
    message += " point";
  } else {
    message += " points";
  }

  if (foundPangram) {
    message += ", Pangram found";
  } 

  if (scoredBingo) {
    message += ", Bingo scored";
  }

  cout << message << endl;

}

void showFoundWords(SBTrie *sbt){
  sbt->displayInfo();
}

void showAllWords(SBTrie *sbt){
  char central;
  string allowed;
  sbt->getLetters(central, allowed);
  vector<string> *sbWords = sbt->sbWords(central, allowed);

  for (auto word : *sbWords) {
    // check if word is a Pangram
    if (word.length() == 7) {
      cout << word << setw(20 - word.length()) << word.length() << " Pangram" << endl;
    } else {
      cout << word << setw(20 - word.length()) << word.length() << endl;
    }
    
  }
}

void displayCommands(){
  cout << "\nCommands are given by digits 1 through 9\n\n";
  cout << "  1 <filename> - read in a new dictionary from a file\n";
  cout << "  2 <filename> - update the existing dictionary with words from a file\n";
  cout << "  3 <7letters> - enter a new central letter and 6 other letters\n";
  cout << "  4            - display current central letter and other letters\n";
  cout << "  5 <word>     - enter a potential word\n";
  cout << "  6            - display found words and other stats\n";
  cout << "  7            - list all possible Spelling Bee words from the dictionary\n";
  cout << "  8            - display this list of commands\n";
  cout << "  9            - quit the program\n\n";

}

int main(int argc, char** argv){
  SBTrie *sbt = new SBTrie;

  cout << "Welcome to Spelling Bee Game\n";

  displayCommands();
  
  bool done = false;
  string line;
  string input;

  do {
    cout << "cmd> ";

    // read a complete line
    std::getline(std::cin, line);

    // now create a "stringstream" on the line just read
    std::stringstream ss(line);

    // clear input from any previous value
    input = "";

    // get command character
    char command;
    ss >> command;
    //cout << "Debug command:" << command << "***\n";
    
    if(command == '1'){
        ss >> input;
        //cout << std::setw(17) << input << " " << std::right << std::setw(2) << input.length() << std::left << endl;
        //cout << "Debug 1:" << input << "***\n";
        getNewDictionary(sbt, input);
    }

    if(command == '2'){
        ss >> input;
        //cout << "Debug 2:" << input << "***\n";
        updateDictionary(sbt, input);
    }
        
    if(command == '3'){
        ss >> input;
        cout << "Debug 3:" << input << "***\n";
        setupLetters(sbt, input);
    }

    if(command == '4'){
        showLetters(sbt);
    }

    if(command == '5'){
        ss >> input;
        //cout << "Debug 5:" << input << "***\n";
        attemptWord(sbt, input);
    }

    if(command == '6'){
        showFoundWords(sbt);
    }

    if(command == '7'){
        showAllWords(sbt);
    }

    if(command == '8' || command == '?'){
        displayCommands();
    }

    if(command == '9' || command == 'q'){
        done=true;
    }

  } while(!done && !cin.eof());

  delete sbt;
  return 0;
}
