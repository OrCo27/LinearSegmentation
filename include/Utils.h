#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>

using namespace std;

class Utils
{
private:
    Utils();

public:
    /* Get all content of the file into string */
    static string GetFileString(const string& fileName, bool include_header);
    /* Get content of file into lines save on vector of strings */
    static vector<string> GetFileLines(const string& fileName);
    /* Check if map file is already exists */
    static bool FileIsExists(const string& fileName);
};

#endif