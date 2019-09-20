/**************************************************************************
Heriberto Bernal
CS211
October 27, 2015
Dr. Ahmad Hadaegh

This program will create a dictionary. The dictionary has 26 files such as A.txt, B.txt, etc. 
A function called Process Transaction File will add a word, delete a word, search for a word, 
print a file, spell checking, and insert words into the dictionary.
**************************************************************************/
#include<fstream>
#include "dictionary.h"
using namespace std;

const int LETTERS = 25;

bool Dictionary::failure = false;
bool Dictionary::success = true;

//This function will set a dictionary to default
//*******************************************************
Dictionary::Dictionary(): maxWordsInDict(10000), maxWordsPerFile(100)
{
  totalWordsInDict = 0;
  for(int i=0; i < LETTERS; i++)
    numOfWordsInFile[i] = 0;
}
//*******************************************************

//This function will set a dictionary with the following information
//******************************************************
Dictionary::Dictionary(int dictMaxWords, int fileMaxWords): maxWordsInDict(dictMaxWords), maxWordsPerFile(fileMaxWords)
{
  totalWordsInDict = 0;
  for(int i=0; i < LETTERS; i++)
    numOfWordsInFile[i] = 0;
}
//******************************************************

//This function will add a word to the dictionary by checking if it is possible to add it and then
//this function will call the InsertWord function to add the word to the dictionary
//*******************************************************************
bool Dictionary::AddAWord(string word)
{
  if(totalWordsInDict >= maxWordsInDict)
    return failure;

  char ch = word[0];
  ch = toupper(ch);
  int index = ch - 'A';

  if(numOfWordsInFile[index] >= maxWordsPerFile)
    return failure;

  bool found = SearchForWord(word);
  if(found == failure)
    {
      InsertWord(word);
      return success;
    }
  else
    {
    return failure;
    }
}
//**********************************************************************

//This function will search if a word exist in the dictionary
//*************************************************************
bool Dictionary::SearchForWord(string word)
{
  char ch = word[0];
  ch = toupper(ch);
  
  ifstream fin;
  string filename = "#.txt";
  string newWord;

  filename[0] = ch;

 fin.open(filename.data());

 if(!fin)
   return failure;

 else
   {
     while(fin >> newWord)
       {
	 if(word == newWord)
	   return success;
       }
     return failure;
   }
}
//***********************************************************

//This function will open a certain file and then add a word to the file
//************************************************************
bool Dictionary::InsertWord(string word)
{
  char ch = word[0];
  ch = toupper(ch);
  string fileName = "#.txt";
  fileName[0] = ch;
  int index = ch - 'A';
  ofstream fout;
  fout.open(fileName.data(), ios::app);
  fout << word << endl;
  numOfWordsInFile[index]++;
  totalWordsInDict++;
  fout.close();
  return success;
}
//******************************************************************

//This function will print a certain file to the screen
//*************************************************************
bool Dictionary::PrintAFileInDict(string fileName)
{
  vector<string> w;
  string word;

  ifstream fin;
  fin.open(fileName.data());

  if(!fin)
    return failure;

  else
    {
      while(fin >> word)
	{
	  w.push_back(word);
	}
      fin.close();

      cout << "*************** PrintF " << fileName << " ****************" << endl;
      for(int i=0; i < w.size(); i++)
	{
	  for(int e=0; e < 5; e++)
	    {
	      cout << w[i] << " ";
	      i++;
	    }
	  cout << endl;
	}
      cout << endl;
    }
}
//************************************************************

//This function will open a file and will try to add all the words to the dictionary
//*************************************************************
bool Dictionary::InsertWordsIntoDict(string fileName)
{
  string word;
  ifstream fin;
  fin.open(fileName.data());

  if(!fin)
    return failure;
  else
    {
      cout << "***************** InsertF " << fileName << " ******************" << endl;
      while(fin >> word)
	{ 
	  AddAWord(word) ;
	}
      cout << endl;
      return success;
    }
  fin.close();
}
//****************************************************************

//This function will open a file and then delete a word on the file
//*****************************************************************
bool Dictionary::DeleteAWord(string word)
{
  char ch = word[0];
  ch = toupper(ch);
  string wd;
  vector<string> v;
  int index = ch - 'A';

  ifstream fin;
  string filename = "#.txt";

  filename[0] = ch;

  fin.open(filename.data());

  if(!fin)
    return failure;

  else
    {
      if(failure == SearchForWord(word))
	 return failure;     
      else
        {
           while(fin >> wd)
             {
	       if(wd != word)
		 v.push_back(wd);
	     }
	   fin.close();

	   totalWordsInDict--;
	   numOfWordsInFile[index]--;
	   
	   ofstream fout;
	   fout.open(filename.data());

	   for(int e=0; e < v.size(); e++)
	     {
	       fout << v[e] << endl;
	     }
	   fout.close();

	   return success;
        }
    }
}
//**********************************************************************

//This function will open a file and check if the word exist in the dictionary. 
//If the word does not exist, this function will print the word to the screen.
//***********************************************************************
bool Dictionary::SpellChecking(string fileName)
{
  ifstream fin;
  vector<string> v;
  string word;

  fin.open(fileName.data());

  if(!fin)
    return failure;
  else
    {
      cout << "************ Spellcheking " << fileName << " ************" << endl;
      while(fin >> word)
	{
	  if(failure == SearchForWord(word))
	    cout << word << " does not exist" << endl;
	}
      cout << endl;
      return success;
    }
}
//*************************************************************************

//This function will open a file and call a function depending what the file say.
//***************************************************************************
void Dictionary::ProcessTransactionFile()
{
  ifstream fin;
  string word;
  string name;

  cout << "Enter a transaction name: ";
  cin >> name;

  fin.open(name.data());

  while(fin)
	{
	  fin >> word;
	  if(word == "AddW")
	    {
	      fin >> word;
	      cout << "************ AddW  " << word << " **************" << endl;
	      AddAWord(word);
	      cout << word << " has been added" << endl;
	      cout << endl;
	    }
	  else if(word == "DeleteW")
	    {
	      fin >> word;
	      cout << "************ DeleteW " << word << " **************" << endl;
	      DeleteAWord(word);
	      cout << word << " has been deleted" << endl;
	      cout << endl;
	    }
	  else if(word == "SearchW")
	    {
	      fin >> word;
	       cout << "************ SearchW " << word << " ***************" << endl;
	      if(success == SearchForWord(word))
		{
		  cout << word << " was found" << endl;
		}
	      else
		{
		  cout << word << " was not found" << endl;
		}
	      cout << endl;
	    }
	  else if(word == "PrintF")
	    {
	      fin >> word;
	      PrintAFileInDict(word);
	    }
	  else if(word == "SpellCheck")
	    {
	      fin >> word;
	      SpellChecking(word);
	    }
	  else if(word == "InsertF")
	    {
	      fin >> word;
	      InsertWordsIntoDict(word);
	    }
	}
}
//***************************************************************************

//This function will change a letter to upper case
//****************************************************************
string toupper(string wd)
{
  for(int i=0; i < wd.size(); i++)
    {
      if(wd[i] >= 'a' && wd[i] <= 'z')
	wd[i] = wd[i] - 32;
    }
  return wd;
}
//************************************************************
