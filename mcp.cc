#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, const char* argv[]) {
    
    if (argc < 5) {
        cerr << "Please use the format : mcp -s <source_file> -t <target_file> [-t <target_file2> ...]" << endl;
        exit(EXIT_FAILURE);
    }

    string sourceFile;
    vector<string> targetFiles;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-s") {
            if (i + 1 < argc) {
                sourceFile = argv[++i];
            } else {
                cerr << "Error: Missing source file after -s " << endl;
                exit(EXIT_FAILURE);
            }
        } 
        else if (arg == "-t") {
            if (i + 1 < argc) {
                targetFiles.push_back(argv[++i]);
            } else {
                cerr << "Error: Missing target file after -t " << endl;
                exit(EXIT_FAILURE);
            }
        } 
        else {
            cerr << "Error: Unknown argument '" << arg << endl;
            exit(EXIT_FAILURE);
        }
    }

    if (sourceFile.empty()) {
        cerr << "Error: No source file specified " << endl;
        exit(EXIT_FAILURE);
    }

    if (targetFiles.empty()) {
        cerr << "Error: No target files specified " << endl;
        exit(EXIT_FAILURE);
    }

    if (!fs::exists(sourceFile)) {
        cerr << "Error: Source file '" << sourceFile << "' does not exist " << endl;
        exit(EXIT_FAILURE);
    }

    unordered_set<string> seenTargets;
    for (const auto& t : targetFiles) {
        if (!seenTargets.insert(t).second) {
            cerr << "Error: Duplicate target file name '" << t <<  "'" << endl;
            exit(EXIT_FAILURE);
        }
    }

    for (const auto& t : targetFiles) {
        if (fs::exists(t)) {
            cerr << "Error: Target file '" << t << "' already exists " << endl;
            exit(EXIT_FAILURE);
        }
    }

    ifstream sourceStream(sourceFile, ios::binary);
    if (!sourceStream) {
        cerr << "Error: Could not open source file '" << sourceFile << "'" << endl;
        exit(EXIT_FAILURE);
    }

    for (const auto& target : targetFiles) {
        ofstream targetStream(target, ios::binary);
        if (!targetStream) {
            cerr << "Error: Could not open target file " << target << " for writing " << endl;
            exit(EXIT_FAILURE);
        }
        targetStream << sourceStream.rdbuf(); //copies the contents of the source file to the target file

        if (!targetStream) {
            cerr << "Error: Failed while writing to '" << target << endl;
            exit(EXIT_FAILURE);
        }

        sourceStream.clear();
        sourceStream.seekg(0, ios::beg); // Reset the source file cursor so it can be read again for the next target
    }
    cout << "Successfully copied from " << sourceFile << " to ";
    for (size_t i = 0; i < targetFiles.size(); ++i) {
        cout << targetFiles[i];
        if (i != targetFiles.size() - 1) cout << ", ";
    }
    cout << endl;

    return 0;
}


