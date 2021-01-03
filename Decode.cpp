/*Author: Bhavana Laxmi R\n"
  Program 4: Decode TA: Hasti Sharifi JUL 28, 2019
  
*/

#include<iostream>
#include<string>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<vector>
#include<fstream>
#include<algorithm>
#include<bits/stdc++.h>
//#include"Decode.hpp"

using namespace std;
//--------------------------------------------------------------
//variales for part 1
string arr;
string array;
string transposed;
string reversed;
string cipher;
string userInput;
string keyword;
string repeatedKeyword;
string direction[1];
int length;
int keywordLength;
int transpositionVal;
char reverseSentence;


//--------------------------------------------------------------
//variables for part 2
string decodeUserInput;
string possibleDecodeKeywords;
string decodeKeyword;
string DecodeWords;
string decodeArray;
string repeatedDecodeKeyword;
string wordsArray[21876]; 
int numberOfKeywords;
vector<int> matchesForKeywords(numberOfKeywords);
//----------------------------------------------------------------
//variables for part 3
vector<string> storyWords;



//----------------------------------------------------------------
//PART 1 to encode the user input
//this section is going to find the key word in the daction and gonna choose th best possible word

bool contains(string dict){ 
    
    ifstream file;
    file.open("dictionary.txt");  
    string myWord;

    int index = 0;
    while(file >> myWord){
        wordsArray[index] = myWord; 
        index++;
    }
    //cout<<myWord;
    
    for(int i=0;i<21876;i++)
        {
            if( dict.compare(wordsArray[i]) == 0 ){     
                return true;
            }
        }
    file.close();
    return false;

}
//----------------------------------------------------------------
// this section is gonna take the test to be encoded and keyword to proceed to further step
void cipherText(string str,string arr)  
{
    int length = str.length(); 
    string cipher_text;
    cout<<"Enter a keyword for Vigenere encryption: ";
    cin>>keyword;
    cout<<"Keyword is: "<<keyword<<endl;
    int keywordLength = keyword.length();
    cout<<endl<<"Keyword, plainText and ciphertext are: "<<endl;
    
    for(int i=0;i< length;i++){
        repeatedKeyword[i] = keyword[((i)%(keywordLength))]; //reapeat the keyword till the length of the encode sentence 
            cout<<repeatedKeyword[i];
    }
    cout<<endl;
    cout<<arr<<endl;
    for (int i = 0; i <length; i++)
        {
        if(isalpha(str[i])){
            str[i] = toupper(str[i]);
            repeatedKeyword[i] = toupper(repeatedKeyword[i]);
            int x = (str[i] + repeatedKeyword[i]) %26; //  converting it to vigenere cipher
            x += 'a';
         cout<<char(x); 
        }
        else{
            cout<<" ";
        }
    }
    cout<<endl;
 
}


//---------------------------------------------------------------
//this sector of checks for capital letters and small letters and transposes respectively
void transposition(string array, int transpositionVal) // transposing the given text by the 
{
    for (int i=0;i<array.length();i++)
    {
        if(isalpha(array[i]))
        {
            if(islower(array[i]) && (int(array[i])+transpositionVal > int('z'))) // to check if the ascii value is exceeding z and making it a
            {
                int difference  = int(array[i]) + transpositionVal - int('z');
                array[i] = ('a' + (difference -1));
            }
            else if(isupper(array[i]) && (int(array[i])+transpositionVal > int('Z')) ) // to check if the ascii value is exceeding Z and making it A
            {
                int difference  = int(array[i]) + transpositionVal - int('Z');
                array[i] = ('A' + (difference -1));
            }
            else        
            {array[i] = array[i]+transpositionVal;}
        }
       cipher += array[i]; // adding all the words to cipher 
    }
}
//----------------------------------------------------------------
// this section of the code reverses the give text to be encoded word by word
void reverse(string arr, int p)
{
 vector<string> Words;
    string word;
    stringstream iss(arr);
        while (iss >> word){
        reverse(word.begin(), word.end());  // breaking a string into each word
          Words.push_back(word);  
        }
    for (int i = 0; i < Words.size(); i++) {
            array = Words[i];
        transposition(array,p); // calling fuction to transpose by taking each reversed word from words
        cipher+=" ";

        }
    
    cipherText(cipher,arr);
}
//----------------------------------------------------------------
// this section of the code keeps the word as it is and breaks the string into one one word to proceed to the next step
void forward(string arr, int p)
{
 vector<string> Words;
    string word;
    stringstream iss(arr);
        while (iss >> word)
        {
          Words.push_back(word);  // breaking a string into each word
        }
    for (int i = 0; i < Words.size(); i++) 
    {    
        array = Words[i];
        transposition(array,p);  // calling fuction to transpose by taking each reversed word from words
        cipher+=" ";

    }   
     cipherText(cipher,arr);
}

//-------------------------------------------------------------------
//this section of the code takes basic inputs of the user about direction, transposition value to procless above functions
void encodeText()
{
    
    
    cout << "Enter the text to be encoded:";
    cin.ignore();
    getline(cin,arr);
    char userInput[arr.length()];
    strcpy(userInput,arr.c_str());
    length = arr.length();
    cout<<"Enter direction (Forward or Reverse): ";
    cin>>direction[0];
    cout<<"Enter transposition value (0..25): ";
    cin>>transpositionVal;
    
    if(direction[0] == "reverse"){
        reverse(userInput, transpositionVal);  // checking user input and calling the function
    }
    else
    {
        forward(userInput,transpositionVal);
    } 
}
//PART-2 to decode the text
//-------------------------------------------------------------------
// this section of code is written to check the best match 
// But still working on it as it doesn't seem to be working
int maxValue(int array[], int size)
{
    int max = -20;
     for( int i=0; i<size; i++)
     {
        if ( array [i] > array[max] )
            max = i;
     }
    return max;
}
//-----------------------------------------------------------------------
// this section of the code is written to the work of transportation and looking to the dictionary to find the keyword with which the text was encoded
void Transposer(string transpose, string decodeKey, string direction){
   int stop_value;
   bool decoded = false;
    string str,word;
    vector<int> matchCount(storyWords.size());
    for(int i=0;i<26;i++)
    {
        int match = 0;
        int count = 0;
        
        int matchesForTransposeValues[26];
        str = transpose;
        for(int k=0;k<transpose.length();k++) 
        {
            if(isalpha(str[k])) // transposed the letters 26 times to check for the keyword
            {
                if( (int(transpose[k]) + i) > int('z')) // checks if the transpose is exceeding 'z' it is gonna bring is to 'a'
                {
                  int difference  = int(transpose[k]) + i - int('z');
                  str[k] = ('a' + (difference -1));
                }
                else
                {
                 str[k] += i;
                }
            }
        }
        
        stringstream iss(str);   //
        while (iss >> word){
            count++;
            if(contains(word))
            {match++; }
        }
        matchesForTransposeValues[i] = match;
        if(match == count &&(match!=0)&&(count!=0)) // checking for the decrypted text by checking all the words exist in the dictionary
        {
            cout <<"Dictionary hits: " <<match<<endl;
            cout <<"Decoded string is: " <<str <<endl;
            cout<<"\n"<<"Decrypted text is:\n"<<str;
               break;
        }
        if(match > 0)
        {
             cout <<"New best case: "<<" Dictionary hits: " <<match<<"  "<<"Keyword: "<<decodeKey;
             cout <<" Transposition: "<<i;
             cout << " Direction: "<< direction <<endl;
             cout <<"A possible text is : " << str <<endl<<endl;
        
    
    }
}
}
//--------------------------------------------------------------------------
// reverses and transposes to check for the dictionary word
void decodeReverse(string arr,string decodeKey){

    vector<string> reversedWords;
    string word;
    stringstream iss(arr);
    while (iss >> word)
    {
        reverse(word.begin(), word.end());
          reversedWords.push_back(word);
    }
    string reversed;
    for(int j=0;j<reversedWords.size();j++)
    {
        reversed+=reversedWords[j];
        reversed+=" ";
    }
        Transposer(reversed,decodeKey,"Reverse");
}



//--------------------------------------------------------------------------
// it decodes the cipherText
void decodeInput(string cipher_text,string decodeKey){
    
    string decodedChars;
    string repeatedDecodeKeyword;
    string orig_text;
    
    for(int i=0;i< cipher_text.length();i++)
    {
        repeatedDecodeKeyword[i] = decodeKey[((i)+decodeKey.length()) % (decodeKey.length())];
    }
    
    for (int i = 0 ; i < cipher_text.length(); i++)
    
    {
        if(isalpha(cipher_text[i]))
        {
            cipher_text[i] = toupper(cipher_text[i]);
            repeatedDecodeKeyword[i] = toupper(repeatedDecodeKeyword[i]);
            int x = (cipher_text[i] - repeatedDecodeKeyword[i] + 26) %26;
            x += 'a';
            decodedChars+=x;
        }
         else
         {
             decodedChars+= " ";
         } 
    }
    
    Transposer(decodedChars,decodeKey,"Forward");
    decodeReverse(decodedChars,decodeKey); 
}
//------------------------------------------------------------------
//it takes the ba
void decodeText(){

    string word;   
    numberOfKeywords = 0;
    string decodeWord;
    cout<<"Enter the cipherText to be decoded: ";
    cin.ignore();
    getline(cin,decodeUserInput);
    cout<<"Enter the Vigenere keywords to be tried:";
    getline(cin,possibleDecodeKeywords);
 
    char Words[word.length()];
    stringstream iss(possibleDecodeKeywords);
        while (iss >> word){
            numberOfKeywords++;
            strcpy(Words,word.c_str()); 
            decodeInput(decodeUserInput,Words);
            cout<<endl;
        }  
}
// PART-3
//--------------------------------------------------------------------

void decodeCipher(){
    
    fstream file("TheSecretAgentByJosephConrad.txt");
    string word;
    


    int index = 0;
    char chars[19] = {'.','\'',';',':',' ','_','-','*','"','#','[',']','&','?','@','(',')',',','/'};
    
    while(file >> word){
        transform(word.begin(),word.end(),word.begin(),::tolower);
        for(int i=0;i<18;i++)
        {
        word.erase(std::remove(word.begin(), word.end(), chars[i]), word.end());
        }
        storyWords.push_back(word);
    }
    
    for(int i=0;i<storyWords.size()-1;i++)
    {
            for(int j=i+1;j<storyWords.size();j++)
            {
                if(storyWords.at(j) == storyWords.at(i) )
                {storyWords.erase(storyWords.begin()+j);}
            }
    }
    
    ofstream f;
    f.open("analysis.txt");
    for(int i=0;i<storyWords.size();i++)
    {
        f << storyWords.at(i);
        f << "\n" ;
    }
    f.close();
    
    string cipher = "iqhn oh xalm ejg jyoq nbgnrv kmbqj ztnzzv";
    cout<<"ciphertext is :"<<"IQHN OH XALM EJG JYOQ NBGNRV KMBQJ ZTNZZV"<<endl;
    cout<<"String of possible keywords taken from file: analysis.txt"<<endl;
}

//--------------------------------------------------------------------

void readKeyword(){
    
    fstream keyword("analysis.txt");
    string dictKeyword;
    sort(storyWords.begin(),storyWords.end());
}
//--------------------------------------------------------------------

int main(){
int userChoice;

    cout<<"Author: Bhavana Laxmi R\n"
        <<"Program 4: Decode TA: Hasti Sharifi JUL 28, 2019\n"
        <<"Choose from the following options:\n"
        <<"1. Encode some text\n"
        <<"2. Decode using user-entered values\n"
        <<"3. Decode the ciphertext given with the assignment \n4. Exit program\n"
        <<"Your choice:";
    cin>>userChoice;
    
    if(userChoice == 1){
        encodeText();
       
        }
    else if(userChoice == 2){
        decodeText();
    }
    else if(userChoice == 3){
        decodeCipher();
    }
    else if(userChoice == 4){
        exit (0);
    }

    return 0;
}