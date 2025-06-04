#include "fileWriteTest.h"

// returns the file location of the root directory of
// the project  as a path datatype which ensures
// compatibility accross mac, windows, and linux
// by ensuring folder paths are automatically defined
// between forward and backwards slash for mac and linux '/' and '\' for windows
fs::path findProjectRoot(const string &folderName)
{
    // grabs the path of the current directory (the build directory)
    fs::path path = fs::current_path();
    // iterate though the each folder until root folder folderName is found
    // if we have iterated to an empty path name we are far too gone and
    // folderName is probably wrong
    while (!path.empty() && path.filename() != folderName)
        path = path.parent_path();
    // returns the path to the root directory
    if (path.filename() == folderName)
        return path;
    else
        throw runtime_error("Project root '" + folderName + "' not found.");
}

// Clears the contents of the output file used for generating reports.
void clearOutputFile()
{
    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for clearing\n";
        return;
    }
    outFile.close();

    ifstream inFile(outputPath);
    if (inFile.peek() != ifstream::traits_type::eof())
        cerr << "Warning: File may not have been cleared properly\n";

    inFile.close();
}

// this file reads and writes to a file named
// "output.txt" within the project folder
// and writes it to consoleF
void testReadToWriteFile()
{
    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt"; //./src/output.txt
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }
    // outFile << "hello from /src/output.txt!" << "\n";
    outFile << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "test" << "\n"
            << "blah";
    outFile.close();
}

// prints whatever was written to output.txt to the terminal for debugging
void printOutputTxt()
{
    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ifstream outputFile(outputPath);
    if (!outputFile.is_open())
    {
        cerr << "Error: Could not open output.txt for reading\n";
        return;
    }

    cout << "\nCONTENTS OF OUTPUT.TXT:\n";
    cout << "=======================\n";
    string line;
    while (getline(outputFile, line))
    {
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        cout << line << '\n';
    }
    cout << "=======================\n";
    outputFile.close();
}