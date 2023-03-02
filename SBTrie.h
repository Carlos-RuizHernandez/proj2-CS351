
#ifndef _MY_SB_TRIE_H
#define _MY_SB_TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include "Trie.h"


class SBTrie: public Trie {

  // the main reason for inheriting the Trie class is that the words() method in Tries
  // is quite inefficient for the use of the Spelling Bee game.
  //
  // This allows us to customize a better method to get the desired words by "adding an
  // addtional method" on the the Trie class at the cost of using inheritance.

  protected:
    // private/protected stuff goes here!
    //  - protected allows this class to be inherited
    //    and adapted to the problem at hand (if needed)
    //   typedefs
    //   data members
    //   definition of trie node structure
    //   private helper functions
    //   etc.

    // central letter for spelling bee game
    char central;
    // string of allowed letters
    string allowedLetters;
    // trie to store words that the user has found
    Trie* foundWords;
    // trie to store all valid words
    Trie* dictionary;
    // keeps track of user's score
    int score;
    // Pangram found status
    bool pangramFound;
    // Bingo found status
    bool bingoFound;
    // keeps track of current bingo state
    string bingo;

    //
    // findValidWords()
    // builds a vector of all words in the dictionary that are valid words for the spelling bee problem in ascending order
    //
    //
    void findValidWords(TrieNode* node, char str[], int level, vector<string>*& words, char centralLetter, string letters) const{

      // if leaf is found, add end of string character to string and push_back to word vector
      if (node->isLeaf) {
        string word = str;
        // word needs to be at least 4 letters, check that string index is at least 4. Also make sure string contains central letter
        if (level > 3 && word.find(centralLetter) != std::string::npos) {
          str[level] = '\0';
          words->push_back(str);
        }
      }

      // look for any paths from current node
      for (int i = 0; i < LETTERS; i++) {

        // if path is found, add letter to string and recursively call buildWordVector
        if (node->children[i]) {

          char character = i + 'a';

          // check if letter is valid
          if (letters.find(character) != std::string::npos || character == centralLetter) {
            str[level] = i + 'a';
            // recursive call takes the next letter in the path, the current string, the next index of the string, and the vector of words to return
            findValidWords(node->children[i], str, level + 1, words, centralLetter, letters);
          }
        }
      }
    }

  public:
    /**
    * constructor and destructor
    */
    SBTrie()   {

      // your constructor code here!
      foundWords = new Trie;
      dictionary = new Trie;
      score = 0;
      pangramFound = false;
      bingoFound = false;
      bingo = "";
    }
    ~SBTrie(){
      // your destructor code here.
    }

    //
    // getLetters
    // gets central and valid letters
    //
    void getLetters(char& centralLetter, string& letters) {
      centralLetter = central;
      letters = allowedLetters;
    }

    //
    // printLetters
    // displays central and allowed letters
    //
    void printLetters() {
      cout << "Central Letter: " << central << endl;
      cout << "6 Other Letters: " << allowedLetters[0] << "," << allowedLetters[1] << "," << allowedLetters[2] << "," << allowedLetters[3] << "," << allowedLetters[4] << "," << allowedLetters[5] << endl;
    }

    //
    // resetState
    // resets the state of the game
    //
    void resetState() {
      score = 0;
      foundWords->clear();
      pangramFound = false;
      bingoFound = false;
    }

    //
    // setRules()
    // sets the central letter and the allowedLetters for the game
    //
    void setRules(char centralLetter, string letters) {
      central = centralLetter;
      allowedLetters = letters;
    }

    //
    // newDictionary() 
    // clears current dictionary and makes a new one from a given filename
    //
    void newDictionary(string filename) {
      dictionary->clear();
      dictionary->getFromFile(filename);
    }

    //
    // updateDictionary() 
    // clears current dictionary and makes a new one from a given filename
    //
    void updateDictionary(string filename) {
      dictionary->getFromFile(filename);
    }

    //
    // searchDictionary()
    // searches for given word in dictionary data member
    //
    bool searchDictionary(string word) {
      return dictionary->search(word);
    }

    //
    // searchFoundWords()
    // searches for given word in foundWords data member
    //
    bool searchFoundWords(string word) {
      return foundWords->search(word);
    }

    //
    // wordFound()
    // inserts a word into found words, adds points scored, and return both points scored and overall points
    //
    void wordFound(string word, int& pointsScored, int& overallScore, bool& foundPangram, bool& scoredBingo) {
      // add word to found words trie
      foundWords->insert(word);
      // check if word is a Pangram
      bool pangramCheck = false;
      vector<char> letters;

      for (auto c : word) {
        // check if letter has been encountered before
        if (find(letters.begin(), letters.end(), c) == letters.end()) {
          letters.push_back(c);
        }
      }
      // check if vector contains all 7 letters
      if (letters.size() == 7) {
        pangramCheck = true;
      }

      // calculate score
      if (word.length() == 4) {
        score += 1;
        pointsScored = 1;
      } else if (pangramCheck) {
        score += word.length() + 7;
        pointsScored = word.length() + 7;
        foundPangram = true;
      } else {
        score += word.length();
        pointsScored = word.length();
      }

      overallScore = score;

      // check if word has been found with first letter
      if (bingo.find(word[0]) == std::string::npos) {
        bingo += word[0];
      }

      // check if bingo was scored this round
      if (!bingoFound) {
        if (bingo.length() == 7) {
          scoredBingo = true;
        }
      } 
    }

    //
    // displayInfo
    // displays info for command 6
    //
    void displayInfo() {
      int wordsFound = foundWords->wordCount();

      string message = to_string(wordsFound);

      if (wordsFound == 1) {
        message += " word found, total ";
      } else {
        message += " words found, total ";
      }

      if (score == 1) {
        message += to_string(score) + " point";
      } else {
        message += to_string(score) + " points";
      }

      if (pangramFound) {
        message += ", Pangram found";
      }

      if (pangramFound) {
        message += ", Bingo scored";
      }

      cout << message << endl;

    }

    /*
     * function: sbWords
     * description:  build a vector of all words in the dictionary that
     *   are valid words for the spelling bee problem and return that
     *   vector.  The words are to be in sorted ascending order.
     *   The words included must have a length of 4 or greater, 
     *                      must contain the central letter, and 
     *                      may contain the allowed letters 
     *
     * parameter: char centralLetter - the letter that MUST be contained in the words
     *            string letters - the other letters that are allowed to be in words
     *
     * return:  a pointer to a vector of strings
     *
     */
    std::vector<string>* sbWords(char cetralLetter, string letters) const{
      vector<string>* words = new vector<string>;
      char str[100];
      int level = 0;
      findValidWords(dictionary->getRoot(), str, level, words, cetralLetter, letters);
      return words;
    }


    


};

#endif
