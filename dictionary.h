/**************************************************************************
Heriberto Bernal
CS211
October 27, 2015
Dr. Ahmad Hadaegh

This program will create a dictionary. The dictionary has 26 files such as A.txt, B.txt, etc.
A function called Process Transaction File will add a word, delete a word, search for a word,
print a file, spell checking, and insert words into the dictionary.
**************************************************************************/
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Dictionary
{
 private:
  const int maxWordsInDict;
  const int maxWordsPerFile;
  int totalWordsInDict;
  int numOfWordsInFile[26];
  static bool failure;
  static bool success;  
 public:
  Dictionary();
  Dictionary(int dictMaxWords, int fileMaxWords);
  bool AddAWord(string word);
  bool InsertWord(string word);
  bool DeleteAWord(string word);
  bool SearchForWord(string word);
  bool PrintAFileInDict(string fileName);
  bool SpellChecking(string fileName);
  bool InsertWordsIntoDict(string fileName);
  void ProcessTransactionFile();
};

