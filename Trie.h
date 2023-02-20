
#ifndef _MY_TRIE_H
#define _MY_TRIE_H
#define LETTERS 26
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Trie {

  protected:
    // private/protected stuff goes here!
    //  - protected allows this class to be inherited
    //    and adapted to the problem at hand (if needed)
    //   typedefs
    //   data members
    //   definition of trie node structure
    //   private helper functions
    //   etc.

    struct TrieNode {
      TrieNode* children[LETTERS];
      bool isLeaf;
    };
    int wordCount;
    TrieNode* root;
    
    TrieNode* newNode() {
      TrieNode* newNode = new TrieNode;
      newNode->isLeaf = false;
      for (int i = 0; i < LETTERS; i++) {
        newNode->children[i] = NULL;
      }
      return newNode;
    }

    void freeTrieNode(TrieNode* node) {
      // Free the trienode sequence
      for(int i = 0; i < LETTERS; i++) {
        if (node->children[i] != NULL) {
            freeTrieNode(node->children[i]);
        }
        else {
            continue;
        }
    }
    free(node);
    }
  public:
    /**
    * constructor and destructor
    */
    Trie()   {
      // your constructor code here!
      root = newNode();
      wordCount = 0;
    }
    ~Trie(){
      // your destructor code here.
      freeTrieNode(root);
    }

    /*
     * function: getFromFile
     * description:  extract all of the words from the file
     *   specified by the filename given in the parameter.
     *   Words are separated by whitespace characters and 
     *   must only contain letters.
     *
     * return:  indicates success/failure (file not readable...)
     */
    bool getFromFile(string filename){
      return false;
    }

    /*
     * function: insert 
     * description:  inserts the word given by the parameter
     *   into the trie data structure.
     *   
     *   fails if word already exists or contains non-letters
     *
     * return:  indicates success/failure
     */
    bool insert(string word){
      //
      // start with root
      //
      TrieNode* cur = root;
      int letter;

      for (auto c : word) {
        // get index of current letter
        letter = c - 'a';

        // if path does not exist, make new trie node at index
        if (!cur->children[letter]) {
          cur->children[letter] = newNode();
        }

        // go to next letter in path
        cur = cur->children[letter];
      }

      // if last letter is a leaf, word already exists, return false
      if (cur->isLeaf) {
        return false;
      } 
      
      // if word doesnt exist yet, mark final letter as a leaf and return true
      cur->isLeaf = true;
      wordCount++;
      return true;
    }

    /*
     * function: search 
     * description:  determines if the word given by the parameter
     *   is stored in the trie data structure.
     *   
     *   fails if word already does not exist
     *
     * return:  indicates success/failure
     */
    bool search(string word) const{

      // start with root
      TrieNode* cur = root;
      int letter;

      for (auto c : word) {
        // get index of current letter
        letter = c - 'a';

        // if path does not exist, word does not exist; return false
        if (!cur->children[letter]) {
          return false;
        }

        // go to next letter in path
        cur = cur->children[letter];
      }

      // if isLeaf --> TRUE 
      // if !isLeaf --> FALSE
      return cur->isLeaf;
    }

    /*
     * function: remove 
     * description:  removes the word given by the parameter
     *   from the trie data structure.  Only deallocate nodes
     *   in subtrees that do not contain any words.
     *   
     *   succeed if word exists and is properly removed
     *
     * return:  indicates success/failure
     */
    bool remove(string word){

      return false;
    }

    /*
     * function: clear
     * description:  remove all words from the trie and deallocate
     *   all nodes.
     *
     * return:  indicates success/failure
     */
    bool clear(){
      return false;
    }



    /*
     * function: wordCount
     * description:  return the number of words currently stored in the trie
     *
     * return:  an integer containing the number of words stored
     *
     * comment/note:  this should have an O(1) runtime.
     */
    int wordCount( ) const{
      return wordCount;
    }    


    /*
     * function: words
     * description:  build a vector of all words in the dictionary and return that
     *   vector.  The words are to be in sorted ascending order.
     *
     * return:  a pointer to a vector of strings
     *
     */
    std::vector<string>* words( ) const{
      
      return nullptr;
    }


    


};

#endif
