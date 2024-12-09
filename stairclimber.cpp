
/*******************************************************************************
* Name : stairclimber.cpp
* Author : Marc Sulsenti
* Date : October 7th 2023
* Description : Lists the number of ways to climb n stairs.
* Pledge : I pledge my honor that I have abided by the Stevens Honor System
******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

int numDigits(int number)
{
	//This method is a helper function to the "display_ways" method.
	//This method takes an integer and returns the number of digits in said integer.
	//This method acomplishes this by looking at how many places are in the integer (dividing by 10)
	//This is useful for setting up the width for displaying the vectors later on in the code

    int digits = 0;
    if (number < 0) digits = 1; 
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}


vector< vector<int> > get_ways(int num_stairs) {
// TODO: Return a vector of vectors of ints representing
// the different combinations of ways to climb num_stairs
// stairs, moving up either 1, 2, or 3 stairs at a time.

//our vector of vectors we will utilize and then return
//This method follows a similar code to the stairclimber.py seen in class, but translated to cpp
vector< vector<int> > ways;

if(num_stairs <= 0 ){
    //return empty vectory;
    vector<int> m;
    //adding an empty vector m to the vector of vectors "ways"
    ways.push_back(m);
}
else{
    
//for-loop that sets up our vectors within the vector
for (int i = 1; i < 4; ++i) {
	//itterating less than four, because as per the rules the program can only climb 3 stairs at a time.
	//result represents the one vector of one way which will then be appended to the final vector of vectors "ways"
        if (num_stairs >= i) {

            vector<vector<int>> result = get_ways(num_stairs - i);
            for (size_t j = 0; j < result.size(); j++) {

                result[j].insert(result[j].begin(), i);
            }
            ways.insert(ways.end(), result.begin(), result.end());
        }
}
}
return ways;
}


void display_ways(const vector< vector<int> > &ways) {
	/*This method is responsible for displaying  all the possible ways that input number of stairs can be climbed 
	Outputs the correct format as needed in the testing script.
	*/

    int stairs = 0;

    for(size_t i= 0; i < ways[0].size();i++){
        stairs = stairs + ways[0][i];
    }


for(size_t i = 0; i < ways.size(); i++){
	//Displaying the vectors utilizing a setwidth from the number of digits in an integer.
	//Itterating through a vector of vectors (ways) to print out each of the ways of ways
    cout << setw(numDigits(ways.size())) << i+1 << ". [";


    for(size_t j = 0; j< ways[i].size();j++){
        if(j == ways[i].size() - 1){
            cout << ways[i][j];
        }
        else{
            cout << ways[i][j] << ", ";
} }
    cout << "]" << endl;
}


}






int main(int argc, char * const argv[]) {
	//Main method for stairclimber.cpp
	int n;
	stringstream iss;
	if (argc != 2)// too many or too few args, we only need 1 argument total for this program (how many steps)
	{
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}

	iss.str(argv[1]);

	if (!(iss >> n))//arg is not an int (arg must be a positive integer)
	{
		cerr << "Error: Number of stairs must be a positive integer.";
		return 1;
	}

	if(n<0)//arg is not positive (arg must be a positive integer)
	{
		cerr << "Error: Number of stairs must be a positive integer.";
		return 1;
	}

    //Displaying back to user as per the instructions
	vector< vector< int > > steps = get_ways(n);

	cout << steps.size() << " way";

	if (steps.size() != 1)//if plural
		cout << "s";

	cout << " to climb " << n << " stair";

	if (steps.size() != 1)//if plural
			cout << "s";
	cout << "."<< endl;

	display_ways(steps);

	return 1;
}
