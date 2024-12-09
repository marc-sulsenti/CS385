 /*******************************************************************************
     * Name        : shortestpaths.cpp
     * Author      : Marc Sulsenti
     * Version     : 1.0
     * Date        : 12/6/2023 
     * Description : Implentation of Floyd's algorithm in order to solve shortest path
     * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. 
     ******************************************************************************/

    using namespace std;

    #include <iostream>
    #include <iomanip>
    #include <fstream>
    #include <limits>
    #include <string>
    #include <algorithm>
    #include <cmath> 


    // Global variables
    //Matricies
    long long int** shortest_path_matrix;
    long long int** graph_weights;
    long long int** path_matrix;

    int node_count;

    //Utilizing long long to go higher than 2^32, other than that we can't represent the high integers that we see 
    //in scenarios such as test case 17

    //numeric_limits<long long>::max()
    //will represent the largest possible integer for this data type (theoretically infinity is anything equal to or larger )
    long long int infinity = numeric_limits<long long>::max();



    // Check if a string is a number
    bool isDigitString(const string& str) {
    //itterate through all of the stirng, and check if it is a digit
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

    // Implementation of Floyd's algorithm
    void runFloydAlgorithm() {

        //initialize a matrix to reperesent our shortest paths
        shortest_path_matrix = new long long*[node_count];
        for (int i = 0; i < node_count; i++) {
            shortest_path_matrix[i] = new long long[node_count];
        }

        for (int i = 0; i < node_count; i++) {
            for (int j = 0; j < node_count; j++) {
                if (graph_weights[i][j] == 0 && i != j) {
                    shortest_path_matrix[i][j] = infinity;
                } else {
                    shortest_path_matrix[i][j] = graph_weights[i][j];
                }
            }
        }
        
        path_matrix = new long long*[node_count];
        for (int i = 0; i < node_count; i++) {
            path_matrix[i] = new  long long[node_count];
            fill_n(path_matrix[i], node_count, infinity);
        }

        for (int k = 0; k < node_count; k++) {
            for (int i = 0; i < node_count; i++) { 
                for (int j = 0; j < node_count; j++) {
                    // Check for overflow when adding distances or it will break
                    if (shortest_path_matrix[i][k] < infinity && shortest_path_matrix[k][j] < infinity &&
                        shortest_path_matrix[i][k] + shortest_path_matrix[k][j] < shortest_path_matrix[i][j]) {
                        shortest_path_matrix[i][j] = shortest_path_matrix[i][k] + shortest_path_matrix[k][j];
                        path_matrix[i][j] = k;
                    } 
                }
            }
        }
    }


    // Display a matrix as a table
    void printMatrix(long long** const mat, const string &heading, int dimension, const bool letters = false) {
    cout << heading << endl; 
    long highest_value = 0;
    for (int row = 0; row < dimension; row++) { 
        for (int col = 0; col < dimension; col++) { 
            long value = mat[row][col]; 
            if (value < infinity && value > highest_value) { 
                highest_value = value; 
            } 
        } 
    } 

    int width;
    if (letters) {
        width = 1;
    } else {
        width = log10(max(static_cast<long>(dimension), highest_value)) + 1;
    }
    cout << ' '; 

    for (int col = 0; col < dimension; col++) { 
        cout << setw(width + 1) << static_cast<char>('A' + col); 
    } 

    cout << endl; 
    for (int row = 0; row < dimension; row++) { 
        cout << static_cast<char>('A' + row); 
        for (int col = 0; col < dimension; col++) { 
            cout << " " << setw(width); 
            if (mat[row][col] == infinity) { 
                cout << "-"; 
            } else if (letters) { 
                cout << static_cast<char>('A' + mat[row][col]); 
            } else { 
                cout << mat[row][col]; 
            } 
        } 
        cout << endl; 
    } 

    cout << endl; 
}


    // Find the path from one node to another ie A -> 
    string getPath(int start, int end) {
        string route;
        if(path_matrix[start][end] == infinity) {
            route = char(start + 'A');
            if(start != end) {
                route += " -> ";
            } return route;
        } else {
            return getPath(start, path_matrix[start][end]) + getPath(path_matrix[start][end], end);
        }
    }

    // Display the shortest paths
    void showPaths() {
    for (int source = 0; source < node_count; source++) {
        for (int destination = 0; destination < node_count; destination++) {
            char sourceChar = static_cast<char>('A' + source);
            char destChar = static_cast<char>('A' + destination);
            cout << sourceChar << " -> " << destChar << ", distance: ";

            string distance;
            if (shortest_path_matrix[source][destination] == infinity) {
                distance = "infinity";
            } else {
                distance = to_string(shortest_path_matrix[source][destination]);
            }
            cout << distance << ", path: ";


            string finalPath = getPath(source, destination);
            if (source != destination) {
                if (shortest_path_matrix[source][destination] != infinity) {
                    finalPath += destChar;
                } else {
                    finalPath = "none";
                }
            }
            cout << finalPath << endl;
        }
    }
}

    // Delete all matrices to free memory
    void matrixDelete(long long **&matrix){
        for(int i=0; i< node_count; i++){
            delete[] matrix[i];
        }
        delete[] matrix;

        //cleanup
    }




    //--------------------FILE PROCESSING HELPERS -------------------------------

void populateWeights(int line){
    for (int i = 0; i < node_count; i++) {
     graph_weights[i] = new long long[node_count];
            }
    for(int i = 0; i < node_count; i++) {
        for(int j = 0; j < node_count; j++) {
            if(i == j) {
                graph_weights[i][j] = 0;
            } else {
             graph_weights[i][j] = infinity;
                            }
                        }
                    }
}
bool isValidNode(int node, int line_number, const string& node_label) {
    if (node_label.length() > 1 || node > node_count - 1 || node < 0) {
        cerr << "Error: Vertex '" << node_label << "' on line " << line_number << " is invalid." << endl;
        return false;
    }
    return true;
}

bool processWeight(const string& weight_str, long int& weight, int line_number) {
    if (weight_str.empty() || !isDigitString(weight_str) || stoi(weight_str) <= 0) {
        cerr << "Error: Invalid edge weight '" << weight_str << "' on line " << line_number << "." << endl;
        return false;
    }
    weight = stoi(weight_str);
    return true;
}



bool processEdgeData(const string& line, int line_number) {
    if (line.empty()) {
        cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
        return false;
    }

    auto first_space_pos = line.find(" ");
    if (first_space_pos == string::npos) {
        cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
        return false;
    }

    string start_vertex = line.substr(0, first_space_pos);
    int start_node = (start_vertex.empty() || start_vertex.length() > 1) ? -1 : start_vertex[0] - 'A';

    auto second_space_pos = line.find(" ", first_space_pos + 1);
    string end_vertex = line.substr(first_space_pos + 1, second_space_pos - (first_space_pos + 1));
    int end_node = (end_vertex.empty() || end_vertex.length() > 1) ? -1 : end_vertex[0] - 'A';

    string weight_str = (second_space_pos == string::npos) ? "" : line.substr(second_space_pos + 1);
    long int edge_weight;

    if (start_node < 0 || start_node >= node_count) {
        cerr << "Error: Starting vertex '" << start_vertex << "' on line " << line_number << " is not among valid values A-" << char('A' + node_count - 1) << "." << endl;
        return false;
    }

    if (end_node < 0 || end_node >= node_count) {
        cerr << "Error: Ending vertex '" << end_vertex << "' on line " << line_number << " is not among valid values A-" << char('A' + node_count - 1) << "." << endl;
        return false;
    }

    // Check if weight string is empty, indicating missing weight data
    if (weight_str.empty()) {
        cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
        return false;
    }

    if (!processWeight(weight_str, edge_weight, line_number)) {
        return false;
    }

    graph_weights[start_node][end_node] = edge_weight;
    return true;
}




bool processInputFile(ifstream& file_input, const char *argv[]) {
    istringstream iss;
    string line;
    int line_number = 1;

    try {
        while (getline(file_input, line)) {
            iss.clear();
            iss.str(line);

            if (line_number == 1) {
                if (!(iss >> node_count) || node_count < 1 || node_count > 26) {
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                    return false;
                }
                node_count = stoi(line);
                graph_weights = new long long*[node_count];
                populateWeights(node_count);
            } else {
                if (!processEdgeData(line, line_number)) return false;
            }
            line_number++;
        }
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return false;
    }

    return true;
}


//  RUN HELPER


void run(){


    //This method runs all of the proper methods in order for this assignment, after file is processed
    // Display the initial weight matrix
        printMatrix(graph_weights, "Distance matrix:", node_count, false);
    // Run the Floyd algorithm
        runFloydAlgorithm();
    // Display the resulting shortest paths and intermediate matrices
        printMatrix(shortest_path_matrix, "Path lengths:", node_count, false);
        printMatrix(path_matrix, "Intermediate vertices:", node_count, true);
    // Show the paths
        showPaths();
    // Free allocated memory for memleak
        matrixDelete(graph_weights), matrixDelete(shortest_path_matrix),matrixDelete(path_matrix);
        
}


// -----------MAIN



    int main(int argc, const char *argv[]) {
        // Ensure the correct number of command line arguments are provided.
        if (argc != 2) {
            cerr << "Usage: " << argv[0] << " <filename>" << endl;
            return 1;
        }
     // Create an ifstream object for file reading.
        ifstream file_input(argv[1]);
        // Check if the file exists and can be opened.
        if (!file_input) {
            cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
            return 1;
        }
          // Read and process input file
    if (!processInputFile(file_input,argv)) {
        return 1;
    }
    file_input.close(); // Close the file after leaving the processing method
    //Once the file is sucessfully processed, we can move onto running the algorithim


        //runs all methods for the assignment
        //stored in one function for clarity
        run();

        //Close file and return from program
        return 0;
        //end

    }