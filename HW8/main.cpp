/**
 * Jhan paul Mackey
 * CS2413-001
 * Apr. 20, 2024
 * HW8 - Unordered Map, Assignment Submissions
 * 
 * Creating an algorithm to generate a table containing the names of students alongside 
 * the amount of missing assignments from them, using two text files as input data.
 * 
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

/**
 * Populates and returns a list of names of students; will fill the list by the given order of the 
 * names from the text file containing the students' names.
 * 
 * Time Complexity: O(n), where n is the number of lines/names of students in the given text file.
 * 
 * @param studentStream - Input file stream referencing to the text file containing the students' names.
*/
vector<string> populateNames(ifstream& studentStream)
{
    vector<string> names;
    string line;
    while (getline(studentStream, line))
        names.push_back(line);

    return names;
}

/**
 * Populates and returns a table mapping each student's name to a list of assignment they submitted.
 * There is no maintained order of such keys/names.
 * 
 * Time Complexity: O(n*m), where n is the number of lines/total submitted assignments and m is the 
 * total number of assignments able to be submitted which is, at most, m.
 * 
 * (In the case of 9 total assignments, for instance, TC = O(n), since 9 is constant)
 * 
 * @param assignStream - Input file stream referencing to the text file containing the submitted assignments.
 * @param names - List of names of students to be mapped to submitted assignments.
*/
unordered_map<string, vector<int> > populateAssignments(ifstream& assignStream, vector<string>& names)
{
    vector<int> knownAssigns;
    unordered_map<string, vector<int> > map;
    string line; 
    while (getline(assignStream, line)) // Read each submission line
    {
        string name = line.substr(0, line.find('_')); // "John_..." Get string from first char to, but excluding, '_'

        // Retrieve number at the end of the submission line and converting into an int
        size_t last_index = line.find_last_not_of("0123456789");
        string result = line.substr(last_index + 1);
        int assignNum = stoi(result);

        // Assign student's list of submissions to temporary list
        knownAssigns = map[name];

        // If assignNum does not appear in student's submission list (a new submission)
        // (prevents duplicated submissions)
        if (find(knownAssigns.begin(), knownAssigns.end(), assignNum) == knownAssigns.end())
        {
            // Update and assign temporary list back to original student submission list in map
            knownAssigns.push_back(assignNum);
            map[name] = knownAssigns;
        }

    }

    // Traverse list of students' names; those who have not submitted an assignment will have an 
    // empty submission list
    for(string i : names)
    {
        if (map.find(i) == map.end())
            map[i] = vector<int>();
    }

    return map;
}

/**
 * Organizes and outputs the table mapping each student's name to their amount of missing assignments.
 * Order is maintained from the text file containing the students' names.
 * 
 * Time complexity: O(n*m), where n is the number of students' names and m is the number of submitted assignments
 * of which is at most a total of m submitted assignments.
 * 
 * (In the case of 9 total assignments, for instance, TC = O(n), since 9 is constant)
 * 
 * @param names - List of students' names from a given text file. Order is maintained.
 * @param map - Table/map of students' names to their amount of submitted assignments. Order is not maintained.
*/
void printData(const vector<string>& names, unordered_map<string, vector<int> >& map)
{
    cout << "NAME" << setw(33) << "MISSING ASSIGNMENTS\n" << endl; // Header line
    for (string str : names) // Traverse through students' names instead of the map to maintain order
    {
        int missing = 9;
        for (const int num : map[str]) // Count the amount of submitted assignments and subtracting from total
        {
            missing--;
        }
        
        cout << str << setw(18 - str.length()) << missing << endl; // Format output
    }
    
}



int main()
{
    vector<string> studentNames; // Storage for all student names
    unordered_map<string, vector<int> > studentToAssigns; // Table that maps each student to the amount of submitted assignments
    
    string studentFile, assignmentFile;
    ifstream studentStream, assignStream;

    // Input appropriate name text file (will loop until a valid file is found)
    while (true)
    {
        cout << "Enter students file: ";
        cin >> studentFile;
        cout << endl;

        studentStream.open(studentFile);
        if (!studentStream.fail())
            break;
    }
    studentNames = populateNames(studentStream);

    // Input the appropriate assignment text file (will loop until a valid file is found)
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
    studentToAssigns = populateAssignments(assignStream, studentNames);

    // Print table of data between students and missing assignments
    printData(studentNames, studentToAssigns);

    return 0;
}