#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;
int main()
{
    vector<string> studentNames;
    vector<int> knownAssigns;
    unordered_map<string, vector<int> > studentToAssigns;
    string studentFile, assignmentFile;

    ifstream studentStream, assignStream;
    while (true)
    {
        cout << "Enter students file: ";
        cin >> studentFile;
        cout << endl;

        studentStream.open(studentFile);
        if (!studentStream.fail())
            break;
    }

    string line;
    while (getline(studentStream, line))
    {
        string name = line;
        studentNames.push_back(name);
    }
    studentStream.close();

//--------------------------------------------------------------------------------------------------------------------

    while (true)
    {
        cout << "Enter assignments file: ";
        cin >> assignmentFile;
        cout << endl;

        assignStream.open(assignmentFile);
        if (!assignStream.fail())
        {
            break;
        }
    }
    
    string otherLine;
    while (getline(assignStream, otherLine))
    {
        string name = otherLine.substr(0, otherLine.find('_'));

        size_t last_index = otherLine.find_last_not_of("0123456789");
        string result = otherLine.substr(last_index + 1);
        int assignNum = stoi(result);

        knownAssigns = studentToAssigns[name];
        if (find(knownAssigns.begin(), knownAssigns.end(), assignNum) == knownAssigns.end())
        {
            knownAssigns.push_back(assignNum);
            studentToAssigns[name] = knownAssigns;
        }
    }
    assignStream.close();

//--------------------------------------------------------------------------------------------------------------------
    
    cout << "NAME" << setw(33) << "MISSING ASSIGNMENTS\n" << endl;
    for (auto iter = studentToAssigns.begin(); iter != studentToAssigns.end(); iter++)
    {
        int missing = 9;
        for (int i = 0; i < iter->second.size(); i++)
        {
            missing--;
        }
        cout << iter->first << right;
        cout << setw(18-(iter->first.length())) << missing << endl;
        
    }

    return 0;
}