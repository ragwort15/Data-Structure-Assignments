#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

vector< vector<int> > readMatrix(string matrix_filename) {
    
    ifstream file(matrix_filename, ios::in);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << matrix_filename << endl;
        exit(EXIT_FAILURE);
    }
    // Read rows and cols
    int rows = 0, cols = 0;
    if (!(file >> rows)) {
        cerr << "Unable to read row from file: " << matrix_filename << endl;
        exit(EXIT_FAILURE);
    }
    if (!(file >> cols)) {
        cerr << "Unable to read column from file: " << matrix_filename << endl;
        exit(EXIT_FAILURE);
    }

    if(rows < 1 || cols < 1){
        cerr << "The number of rows or columns of a matrix need to be positive, please enter a positive value." << endl;
        exit(EXIT_FAILURE);
    }

    vector< vector<int> > matrix;
    for (int row = 0; row < rows; row++) {
        vector<int> rowVector(cols);
        for (int col = 0; col < cols; col++) {
            if(!(file >> rowVector[col])) {
                cerr << "Unable to read integer from file: " << matrix_filename << " at row=" << row << " col=" << col << endl;
                exit (EXIT_FAILURE);
            }
        }
        matrix.push_back(rowVector);
    }

    file.close();

    return matrix;
}

vector<int> readVector(string vector_filename) {
    vector<int> vec;
    ifstream file(vector_filename);
    if (!file.is_open()) {
        cerr << "unable to open file " << vector_filename << "\n";
        exit(EXIT_FAILURE);
    }

    int rows;
    //the ">>"(extraction operator) reads the next integer from the file stream 
    // it skips whitespace
    if(!(file >> rows)) {
        cerr << "Unable to read row from file: " << vector_filename << endl;
        exit(EXIT_FAILURE);
    }  
    if (rows < 1) {
        cerr << "The number of rows of the vector need to be positive, please enter a positive value." << endl;
        exit(EXIT_FAILURE);
    }

    int value;
    for (int i = 0; i < rows; i++) {
        if (!(file >> value)) {
            cerr << "Error: Unable to read integer from file: " << vector_filename << " for row=" << i << endl;
            exit(EXIT_FAILURE);
        }
        vec.push_back(value);
    }

    file.close();
    return vec;
}

vector<int> multipy(vector< vector<int> > matrix, vector<int> vec) {
    vector<int> outputVector(matrix.size());
    for (int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
            outputVector[i] += matrix[i][j] * vec[j];
        }
    }
    return outputVector;
}

void printVector(vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << endl;
    }
}

int inputFormatError() {
    cerr << "please use the format : ./matrixproduct -m <matrix_filename> -v <vector_filename>" << endl;
    return EXIT_FAILURE;
}

int main(int argc, char const *argv[]) {
    if (argc != 5){
        return inputFormatError();
    }
    string matrix_filename, vector_filename = argv[4];
    if (strcmp(argv[1], "-m") == 0) {
        matrix_filename = argv[2];
        if (strcmp(argv[3], "-v") == 0) {
            vector_filename = argv[4];
        } else {
            return inputFormatError();
        }
    } else if (strcmp(argv[1], "-v") ==0) {
        vector_filename = argv[2];
        if (strcmp(argv[3], "-m") == 0) {
            matrix_filename = argv[4];
        } else {
            return inputFormatError();
        }
    } else {
        return inputFormatError();
    }

    vector< vector<int> > matrix = readMatrix(matrix_filename);
    vector<int> vec = readVector(vector_filename);

    if (matrix[0].size() != vec.size()) {
        cerr << "Matrix dimension is: " << matrix.size() << "x" << matrix[0].size() << " but vector dimension is: " << vec.size() << "x1. Multiplication is not possible" << endl;
        return EXIT_FAILURE;
    }

    vector<int> output = multipy(matrix, vec);
    printVector(output);
    return EXIT_SUCCESS;
}
