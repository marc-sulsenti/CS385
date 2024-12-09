/*******************************************************************************
* Name : sieve.cpp
* Author : Marc Sulsenti
* Date : 9/18/2022
* Description : Sieve of Eratosthenes
* Pledge : I pledge my honor that I have abided by the Stevens Honor System
******************************************************************************/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector> // Include the vector library for storing prime numbers

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);
    ~PrimesSieve() {
        delete[] is_prime_;
    }
    void display_primes() const;

private:
    // Instance variables
    bool* const is_prime_;
    //limit represents the limit of primes found
    const int limit_;
    int num_primes_, max_prime_;
    vector<int> primes_; // Store prime numbers in a vector

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
    is_prime_{new bool[limit + 1]}, limit_{limit}, num_primes_{0}, max_prime_{2} {
    sieve();
}

void PrimesSieve::display_primes() const {
    //TODO
    //This method displays the number of primes that were found, and displays the user input primes upto
    //This method also is respondible for displaying all the prime numbers found, while keeping proper format (80 char per line)
    cout << "\nNumber of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width +1);
    int primes_in_row = 0;
    
    if( size(primes_)==1){
        cout << primes_[0] <<endl;
        return;
    }

    if(limit_ < 100){
        //Proper print out of the number of primes up to is less than 100
        //This is also the for if the max prime value is less than 3 digits
        for(int i : primes_){
            if( i == max_prime_){
                cout<< i<<  endl;
                return;
        }
        else{
            cout << i << " ";
        }
        }
        return;
    }

    for (int i : primes_) {
        //Main print out method
        if( i == max_prime_){
            cout<< i<<  endl;
            return;
        }
        if(primes_in_row+1 >= primes_per_row){
            cout << setw(max_prime_width) << i << endl;
            primes_in_row =0;
        }

        else{
        cout << setw(max_prime_width) << i << " ";
        primes_in_row++;
        }

        if (primes_in_row >= primes_per_row) {
            cout << endl;
            primes_in_row = 0;
        }
    }

    //cout << endl;
}

void PrimesSieve::sieve() {
    //This method is the sieve algorithim for finding all needed prime numbers
    for (int i = 2; i <= limit_; ++i) {
        is_prime_[i] = true;
    }

    for (int i = 2; i <= sqrt(limit_); ++i) {
        if (is_prime_[i]) {
            for (int j = i * i; j <= limit_; j += i) {
                is_prime_[j] = false;
            }
        }
    }

    // Store prime numbers in the primes vector
    for (int i = 2; i <= limit_; ++i) {
        if (is_prime_[i]) {
            primes_.push_back(i);
            num_primes_++; //update number of primes found
            max_prime_ = i; // Update the max (largest) prime found so far
        }
    }
}

int PrimesSieve::num_digits(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}


//MAIN STARTS HERE
int main() {
    cout << "**************************** " << "Sieve of Eratosthenes" <<
        " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    istringstream iss(limit_str);

    if (!(iss >> limit)) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve sieve(limit);
    sieve.display_primes();

    return 0;
}

//END
