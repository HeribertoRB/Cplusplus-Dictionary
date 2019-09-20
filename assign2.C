/**************************************************************************
Heriberto Bernal
CS211
October 27, 2015
Dr. Ahmad Hadaegh

This program will create a dictionary. The dictionary has 26 files such as A.txt, B.txt, etc.
A function called Process Transaction File will add a word, delete a word, search for a word,
print a file, spell checking, and insert words into the dictionary.
**************************************************************************/
#include "dictionary.h"
using namespace std;

int main()
{
  Dictionary DictForCS211;
  DictForCS211.ProcessTransactionFile();
  return 0;
}
