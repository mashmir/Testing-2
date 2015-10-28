
//
//  main.cpp
//  Redundancy Dectector
//
//  Created by Mohsin Ashfaq on 10/18/15.
//  Copyright © 2015 Mashmir. All rights reserved.
//

#include <iostream>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//#define INPUT_FILE_NAME "example3.txt"// "sampledocument.txt"
void updateVars(int &lettersCount, int &wordsCount, int &sWordLetters, int &lWordLetters, string &word);
void updateSuffixTreeForWord(string word);
bool is_file_exist(const char *fileName);


class Node
{
  public:
  char ch;
  int count;
  unordered_map<char, Node*> children;
  Node(char c):ch(c){}
};

Node* root;
int noOfTimesApp = 0;

void updateVars(int &lettersCount, int &wordsCount, int &sWordLetters, int &lWordLetters, string &word)
{
  // Helper method for maintaining counts for
  // "Number of letters in the shortest word"
  // "Number of letters in the longest word"
  // "Average number of letters"
  // &
  // For updating suffix tree for every word.
  
  if (lettersCount>0)
  {
    wordsCount++;
    
    if (wordsCount == 1)
    {
      sWordLetters = lettersCount;
      lWordLetters = lettersCount;
    }
    else
    {
      if (lettersCount < sWordLetters)
        sWordLetters = lettersCount;
      
      if (lettersCount > lWordLetters)
        lWordLetters = lettersCount;
    }
  }
  
  lettersCount = 0;
  updateSuffixTreeForWord(word); // Update Suffix Tree for every word
  word = "";
  
  return;
}

void insertInSuffixTree(Node* root, string str, string originalSuffix, int level=0)
{
  if(str.empty()) return;
  
  Node* child;
  if(root->children.count(str[0]) == 0)
  {
    child = new Node(str[0]);
    child->count++;
    root->children[str[0]] = child;
  }
  else
  {
    child = root->children[str[0]];
    child->count++;
  }
  
  insertInSuffixTree(child, str.substr(1), originalSuffix, level+1);
}

void updateSuffixTreeForWord(string word)
{
  if(!root)
    root = new  Node('@');
  
  //insert all substring in suffix tree
  for(int i=0; i<word.size(); i++){
    string s = word.substr(i);
    insertInSuffixTree(root, s, s);
  }
}

void dedectRedundancyForString(Node* node , string strToMatch , int ind)
{
  char ch = strToMatch[ind];
  if(node->children.count(ch) != 0)
  {
    Node* child = node->children[ch];
    //cout << " [" << child->ch << "] " << child->count  << endl;
    noOfTimesApp = child->count;
    
    ind++;
    ch = strToMatch[ind];
    
    if(child->children.count(ch) == 0 && ind < strToMatch.length())
    {
      noOfTimesApp = 0;
      return;
    }
    
    dedectRedundancyForString(child , strToMatch , ind);
  }
}

void takeInputToSearchWord()
{
  string input;
  cout << "input word :";
  cin>>input;
  
  dedectRedundancyForString(root , input , 0);
  
  cout << "Number of times '"<<input<<"' appears: "<< noOfTimesApp << endl;
  cout <<"\ninput search term: ";
  input = "";
  cin>>input;

  while (input.compare("letsquit") != 0)
  {
    cout <<"input search term: ";
    cin>>input;
  }
}

void foo(int *p)
{
  printf("%d 2==== \n", *p);
}

void foo1(float *p)
{
  printf("%f\n", *p);
}

void foo3(int **const p)
{
  int j = 11;
  *p = &j;
  printf("%d --", **p);
}

void pointers()
{
  // http://www.cplusplus.com/doc/tutorial/pointers/
  
  // & = address of operator
  // * = dereference operator (value pointed by)
  // [] = offset operator are dereferencing operator
  // a[5] = 0; // a[offset of 5] = 0.
  // *(a+5) = pointed to by (a+5) = 0.
  
  int j = 10, *p = &j;
  printf("%d 1==== \n", *p);
  foo(p++);
  printf("%d 3==== \n", *p);
  
  {
    int i = 10;
    int *p = &i;
    foo3(&p);
    printf("%d ==", *p);
    printf("%d ==", *p);
  }
  
  int i = 10;
  int *ptr = &i; // ptr point to address of "i".
  
  printf("The value pointed to by ptr is: %d \n",*ptr);
  printf("The ptr value is: %p which is address of i:%p \n\n",ptr,&i);
  
  int firstValue, secondValue;
  int *myPointer;
  
  myPointer = &firstValue;
  *myPointer = 10;
  myPointer = &secondValue;
  *myPointer = 20;
  
  cout << "firstvalue is " << firstValue << '\n';
  cout << "secondvalue is " << secondValue << '\n'<< '\n';
  
  firstValue = 5;
  secondValue = 15;
  int *p1, *p2;
  
  p1 = &firstValue;
  p2 = &secondValue;
  *p1 = 10;
  *p2 = *p1;
  p1 = p2;
  *p1 =20;
  
  cout << "firstvalue is " << firstValue << '\n';
  cout << "secondvalue is " << secondValue << '\n';
  
  // Pointers and Arrays
  
  int numbers[5];
  myPointer = numbers;  *myPointer = 10;
  myPointer++;          *myPointer = 20;
  myPointer = &numbers[2]; *myPointer = 30;
  myPointer = numbers +3;  *myPointer = 40;
  myPointer = numbers;     *(myPointer+4) = 50;
  
  for (int i = 0; i < 5; i++)
  {
    cout<< numbers[i]<<", ";
  }
  cout<< endl;
  
  myPointer = numbers;
  int val = *myPointer++; // same as *(myPointer++) : increment pointer, and dereference unincremented address
  cout<< val <<"\n";
  
  myPointer = numbers;
  val = *++myPointer; // same as *(++myPointer) : increment pointer, and dereference incremented address
  cout<< val <<"\n";
  
  myPointer = numbers;
  val = (*myPointer)++; // derefernce pointer and post increment value its point to
  cout<< val <<"\n";
  
  myPointer = numbers;
  val = ++*myPointer; // same as ++(*myPointer): dereference pointer, and increment the value it points to
  cout<< val <<"\n";
  
  myPointer = numbers;
  int *myPointer2 = numbers;
  *myPointer++ = *myPointer2++;
  cout<< *myPointer << *myPointer2;
}

int* abc()
{
  int a = 10;
  return &a;
}

int main(int argc, const char * argv[])
{
  /* Input File Path like I've done on Mac OS
    
   /Users/mohsinashfaq/Desktop/example.txt
   
   */
 
  pointers();
  
  string path = "";
  cout << "File Path: ";
  cin>>path;
  ifstream myfile(path);//INPUT_FILE_NAME
  
  if(myfile.peek() == ifstream::traits_type::eof())
  {
    cout<<"Invalid/ Empty File!"<<endl;
    return 0;
  }
  
  if (myfile.good() && myfile.is_open())
  {
    //int array_size = 1024;           // define the size of character array
    //char * a = new char[array_size]; // allocating an array of 1kb
    
    int ch;// N = 0;
    int wordsCount = 0, sWordLetters = 0, lWordLetters = 0, noOfNewLines = 0;
    int lettersCount = 0; // per word alphabetic count
    int alphaCount = 0;   // Total alphabetic counts
    double alphaAvg = 0.0;
    string word = "";
    
    while ((ch = myfile.get()) != EOF)
    {
      if (isspace(ch))
      {
       // a[N++] = ' ';
        if (ch == '\n')
          noOfNewLines ++;
        
        updateVars(lettersCount,wordsCount,sWordLetters,lWordLetters,word);
      }
      else if (isprint(ch))
      {
       // a[N++] = ch;
        
        if (isalpha(ch)) // To avoid . | , etc
        {
          lettersCount ++;
          alphaCount ++;
          
          word+=ch;
        }
      }
    }
    myfile.close();
    updateVars(lettersCount,wordsCount,sWordLetters,lWordLetters,word);
    
    if (wordsCount > 0)
      alphaAvg = (double)alphaCount / wordsCount;
    
    cout << "===Document Summary===" << endl;
    cout << "Total Word Count: "<< wordsCount << endl;
    cout << "Number of letters in the shortest word: "<< sWordLetters << endl;
    cout << "Number of letters in the longest word: " << lWordLetters << endl;
    cout << "Average number of letters: " << alphaAvg << endl;
    cout << "Number of newline characters: "<< noOfNewLines << endl << endl;
    
    takeInputToSearchWord();
  }
  else
    cout << "Unable to open file \n";
  
  return 0;
}

