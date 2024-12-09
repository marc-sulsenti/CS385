    /*******************************************************************************
     * Name        : inversioncounter.cpp
     * Author      : Marc Sulsenti
     * Version     : 1.0
     * Date        : 10/28/2023
     * Description : Counts the number of inversions in an array.
     * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
     ******************************************************************************/
    #include <iostream>
    #include <algorithm>
    #include <sstream>
    #include <vector>
    #include <cstdio>
    #include <cctype>
    #include <cstring>

    using namespace std;

    // Function prototype.
    static long mergesort(int array[], int scratch[], int low, int high);

    /**
     * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
     */

    long count_inversions_slow(int array[], int length) {
        // TODO

        //Counting inversions utilziing two nested for loops
        //Start at the rear of the array, because the array should be sorted. If the array is sorted working backwards will allow us to easily count ivnersions
        long count = 0;
        for( int i = length -1; i >=0; i--){
            for(int j = 0; j < i; j++){
                if(array[j]>array[i]){
                    count++;
                }
            }
        }
        return count;
    }

    /**
     * Counts the number of inversions in an array in Theta(n lg n) time.
     */
    long count_inversions_fast(int array[], int length) {
        // TODO
        // Hint: Use mergesort!
        long count = 0;     //set inversion counter to 0
        int * sorted = new int[length];//creating a new array that will be the sorted version of what is being entered
        count = mergesort(array,sorted,0,length-1); //establishes the recursive call for mergesort
        delete [] sorted; //delete for memory purposes
        return count; // return the number of inversions

    }

    static long merge_sort_recursive(int array[], int scratch[], int low, int high) {
    if (low >= high) {
        return 0;  // Base case: no inversions in a single-element array
    }

    int middle = low + (high - low) / 2; //finding the middle value of the array 

    long count = 0; //set inversion counter to 0
    count += merge_sort_recursive(array, scratch, low, middle); //recursive call of merge_sort_recursive
    count += merge_sort_recursive(array, scratch, middle + 1, high); //recursive call of merge_sort_recursive

    // Merge the two sorted subarrays and count inversions
    int left = low; //low is equal to the left most value in the array
    int right = middle + 1;  //finding the middle value of the array
    int sc = low;  // Scratch array index

    while (left <= middle && right <= high) {
        if (array[left] <= array[right]) {
            scratch[sc++] = array[left++];
        } else {
            scratch[sc++] = array[right++];
            count += middle - left + 1;  // Count inversions
        }
    }

    // Copy any remaining elements from the left subarray
    while (left <= middle) {
        scratch[sc++] = array[left++];
    }

    // Copy any remaining elements from the right subarray
    while (right <= high) {
        scratch[sc++] = array[right++];
    }

    // Copy merged result back to the original array
    for (int i = low; i <= high; i++) {
        array[i] = scratch[i];
    }

    return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    if (low >= high) {
        return 0;  // Base case: no inversions in a single-element array
    }

    int middle = low + (high - low) / 2; //finding the middle value of the array
    long count = 0;

    //The main recursive operations within a mergesort algorithim

    count += mergesort(array, scratch, low, middle);
    count += mergesort(array, scratch, middle + 1, high);
    count += merge_sort_recursive(array, scratch, low, high);

    return count;
}

    int main(int argc, char *argv[]) {
        // TODO: parse command-line argument

        long count;

        //initialize our final result varaible of the count of inversions

        int slow_flag = 0; //flag for if we are utilzing slow mode or not
        
        if(argc == 2){
            string decision = argv[1];
            //If the slow argument is included within the command line arguments, then run the slow inversion counter
            if(decision.compare("slow") == 0){
                //flag that remembers if we using slow or fast sort (1 for slow, 0 for fast)
                slow_flag = 1;
            }
            else{
                cerr << "Error: Unrecognized option '" << decision << "'."<<endl;
                return 1;
            }
        }
        if(argc>2){
            cerr << "Usage: ./inversioncounter [slow]"<<endl;
            return 1;
        }
        

        cout << "Enter sequence of integers, each followed by a space: " << flush;

        istringstream iss;
        int value, index = 0;
        vector<int> values;
        string str;
        str.reserve(11);
        char c;
        while (true) {
            c = getchar();
            const bool eoln = c == '\r' || c == '\n';
            if (isspace(c) || eoln) {
                if (str.length() > 0) {
                    iss.str(str);
                    if (iss >> value) {
                        values.push_back(value);
                    } else {
                        cerr << "Error: Non-integer value '" << str
                            << "' received at index " << index << "." << endl;
                        return 1;
                    }
                    iss.clear();
                    ++index;
                }
                if (eoln) {
                    break;
                }
                str.clear();
            } else {
                str += c;
            }
        }

        // TODO: produce output
        int check = values.size();
        //Check for an input of 0 integers
        if(check==0){
            cerr << "Error: Sequence of integers not received." << endl;
            return 0;
        }
        
        //if slow was entered, run the slow inversion counter
        if(slow_flag==1){
            count = count_inversions_slow(&values[0],values.size());
        }
        //else, run the fast inversion counter (merge sort)
        else{
            count = count_inversions_fast(&values[0],values.size());
        }

        //output number of inversions based on wether or not slow or fast was used
        if(slow_flag == 1){
        cout << "Number of inversions (slow): " << count <<endl;
        }
        else{
            cout << "Number of inversions (fast): " << count <<endl;
        }

        return 0;
    }
