#ifndef FILEWRITETEST_H
#define FILEWRITETEST_H
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace std;
namespace fs = std::filesystem;

fs::path findProjectRoot(const string &folderName = "Baseball_Project");
void clearOutputFile();
void testReadToWriteFile();
void printOutputTxt();

#endif // FILEWRITETEST_H
