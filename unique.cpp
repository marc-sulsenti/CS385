
/*******************************************************************************
* Name : unique.cpp
* Author : Marc Sulsenti
* Date : 9/24/2023
* Description : Determining uniqueness of chars with int as bit vector.
* Pledge : I pledge my honor that I have abided by the Stevens Honor System
* 
* 
******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream> 

using namespace std;
bool is_all_lowercase(const string &s) {
// TODO: returns true if all characters in string are lowercase
// letters in the English alphabet; false otherwise.


for (size_t i = 0; i < s.length(); ++i) {
        char ch = s[i];

        if (ch < 'a' || ch > 'z') {
            //Any ASCII values < 'a' and > 'z' means that the character is not lowercase
           cout << "Error: String must contain only lowercase letters." << endl;
            return false;
        }
}

return true;
}




bool all_unique_letters(const string &s) {
// TODO: returns true if all letters in string are unique, that is
// no duplicates are found; false otherwise.
// You MUST use only single unsigned integers and work with bitwise
// and bitshifting operators only. Using any other kind of solution
// will automatically result in a grade of ZERO for the whole assignment.

//logically, if any string exceeds 26 characters then it MUST have repeating characters
if(s.size() > 27){
    return false;
}


//unsigned integers
unsigned int vector = 0;
unsigned int setter;

//itteration through the string
//utilziing bitwise operators to detect unqiue characters
for (size_t i = 0; i < s.length(); ++i) {
        setter = 1 << ('z' - s[i]);
        
        if((vector & setter) != 0){
        return false;
     }
     else{
        vector = vector | setter;
     }
    }
    

return true;
}


int main(int argc, char * const argv[]) {
// TODO: reads and parses command line arguments.
// Calls other functions to produce correct output.
istringstream iss;

//First Case and Second case  - No arguments or too many arguments
if (argc <= 1 || argc > 2) {
        std::cerr << "Usage: " << argv[0] << " <string>" << std::endl;
        return 1;
    }


//Cast any integer inputs to a string format to be checked in "is_all_lowercase" method
iss.str(argv[0]);

//All Other cases
//If there is an argument input then we go into this if statement
if(argc == 2){
    //First check if the string is all lowecase. This method will also make sure no numbers are in the string due to istringstream
    if(is_all_lowercase(argv[1])==false){
        return 0;
    }
    //If we pass then we can check the uniqueness of the string
    else{
        iss.clear(); //clears iss 
        //check uniqueness
        if( all_unique_letters(argv[1])== true){
            cout << "All letters are unique." << endl;
        }
        else{
            cout << "Duplicate letters found." << endl;
            
        }
        
    }
    
    
}

return 0;
}
