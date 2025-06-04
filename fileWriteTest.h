#ifndef FILEWRITETEST_H
#define FILEWRITETEST_H

#include <filesystem>
#include <fstream>
#include <iostream>
using namespace std;
namespace fs = std::filesystem;

/*******************************************************************
 * fs::path findProjectRoot(const string& folderName = "Baseball_Project")
 *
 * Accessor; This method recursively searches upward from the current
 * working directory until it finds the specified folder name and returns
 * its path.
 *------------------------------------------------------------------
 * Parameter: folderName (const string&) - the target root folder to locate
 *------------------------------------------------------------------
 * Return: path to the root project directory
 *******************************************************************/
fs::path findProjectRoot(const string &folderName = "Baseball_Project");

/*******************************************************************
 * void clearOutputFile()
 *
 * Mutator; This method clears the contents of the output.txt file
 * located in the project's /src directory by truncating it.
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/
void clearOutputFile();

/*******************************************************************
 * void testReadToWriteFile()
 *
 * Mutator; This method demonstrates reading from a text file and writing
 * its contents to output.txt as a test utility.
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/
void testReadToWriteFile();

/*******************************************************************
 * void printOutputTxt()
 *
 * Accessor; This method reads and prints the contents of the
 * output.txt file to standard output.
 *------------------------------------------------------------------
 * Parameter: none
 *------------------------------------------------------------------
 * Return: none
 *******************************************************************/
void printOutputTxt();

#endif // FILEWRITETEST_H
