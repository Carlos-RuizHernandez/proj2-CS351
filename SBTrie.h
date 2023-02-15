
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
    

  public:
    /**
    * constructor and destructor
    */
    SBTrie()   {

      // your constructor code here!
    }
    ~SBTrie(){
      // your destructor code here.
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
      
      return nullptr;
    }


    


};

#endif
