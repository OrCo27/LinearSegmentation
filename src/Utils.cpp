#include "Utils.h"

string Utils::GetFileString(const string& fileName, bool include_header)
{
    vector<string> file_lines = Utils::GetFileLines(fileName);
    string file_text;

    for (int i = 0; i < file_lines.size(); i++)
    {
        // skip on header
        if (i == 0 && include_header)
            continue;


        file_text.append(file_lines[i]);
    }

    return file_text;
}

vector<string> Utils::GetFileLines(const string& fileName)
{
    vector<string> lines;
    // Open the File
    ifstream in(fileName.c_str());
    // Check if object is valid
    if (!in)
    {
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return lines;
    }

    string str;
    // Read the next line from File untill it reaches the end.
    while (getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0)
            lines.push_back(str);
    }
    //Close The File
    in.close();
    return lines;
}

string Utils::GetFileName(const string& filePath)
{
    size_t firstindex = filePath.find_first_of("/");
    size_t lastindex = filePath.find_last_of(".");
    return filePath.substr(firstindex + 1, lastindex - firstindex - 1);
}

bool Utils::FileIsExists(const string& fileName)
{
    ifstream infile(fileName);
    return infile.good();
}