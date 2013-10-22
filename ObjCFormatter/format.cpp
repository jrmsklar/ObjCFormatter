//
//  main.cpp
//  ObjCFormatter
//
//  Created by Josh Sklar on 7/11/13.
//  Copyright (c) 2013 Josh Sklar. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

static const char kInstanceMethodSign = '-';
static const char kClassMethodSign = '+';
static const char kPoundSign = '#';

char getFirstCharOfLine(const string & s);

/*
 returns whether the line 's' is a pragma mark line or not 
 */
bool isPragmaMark(const string & s);

/*
 returns whether the line 's' contains '@implementation'
 */
bool isImplementationLine(const string & s);

/*
 returns the comment from a pragma mark line.
 ie. s = "#pragma mark - Facebook delegate methods"
     would return "Facebook delegate methods"
 Also works for prama marks such as: "#pragma mark Facebook delegate methods"
                                 or: " #prama mark - Facebook delegate methods"
                                 or: " #prama mark Facebook delegate methdos"
 */
string getPragmaMarkComment(const string & s);

// returns '/* <comment< */'
string formatPragmaMarkComment(const string & s);

bool isInHeader(const vector<string> & v, const string & s);

/*
 removes any white space from s, and inserts it into v
 */
void saveString(vector<string> & v, const string & s);

string removeSpaces(const string & s);

int main(int argc, const char * argv[])
{
    if (argc != 2) {
        printf("Expected either 2 or arguments on the command line, got %i.\n"
               "Please specify the entire path of the .m file as the second argument.\n", argc);
        return -1;
    }

    return 0;
    string fileName = argv[1];
    ifstream is;
    is.open(fileName.c_str());
    if (!is) {
        cout << "Couldn't open file.\nProgram will not quit.\n";
        return -1;
    }
    string s;
    string methodDeclarations = "";
    
    bool hasPassedImplementation = false;
    
    /* vector of what is in the header, to check that if a method declaration is
        already there, not to add it */
    vector<string> headerSectionLines;
    
    while (getline(is, s).good()) {
        char firstChar = getFirstCharOfLine(s);
        
        if (isImplementationLine(s))
            hasPassedImplementation = true;

        /* used the pragma marks for comments to groups of methods */
        if (firstChar == kPoundSign) {
            if (isPragmaMark(s)) {
                string comment = getPragmaMarkComment(s);
                methodDeclarations += formatPragmaMarkComment(comment);
            }
        }
        
        /* if the line starts with a -/+, get the method stub */
        if (firstChar == kInstanceMethodSign || firstChar == kClassMethodSign) {
            if (!hasPassedImplementation) {
                saveString(headerSectionLines, s);
            }
            else {
                
                string newMethodDeclaration = s + ";\n";
                
                /* check to make sure it's not already in the header section */
                if (!isInHeader(headerSectionLines, newMethodDeclaration))
                    methodDeclarations += newMethodDeclaration;
            }
        }
    }
    
    cout << "Result:\n\n";
    
    cout << methodDeclarations << endl;
    
    // insert this after the @interface line
    
    ofstream of;
    string tempFileName = fileName + ".tmp";
    of.open(tempFileName.c_str());
    is.close();
    is.open(fileName.c_str());
    
    while (getline(is, s).good()) {
        of << s << endl;
        
        /* line containing '>' will be the @interface line. Or, it will be
         the end of a multiple-line @implementation line. Either way, insert the 
         declarations after that line */
        if (s.find("@interface") != string::npos)
            of << endl << methodDeclarations;
    }
    
    /* copy temporary file into original file */
    is.close();
    of.close();
    
    is.open(tempFileName.c_str());
    of.open(fileName.c_str());
    
    while (getline(is, s).good())
        of << s << endl;

    
    if(remove(tempFileName.c_str()) != 0 )
        cout << "Error deleting temporary file\n";
    else
        cout << "Temporary ile successfully deleted\n";
    
    is.close();
    of.close();

    return 0;
}

char getFirstCharOfLine(const string & s)
{
    if (!isspace(s[0]))
        return s[0];
    int i = 0;
    while (i < s.length() && isspace(s[i]))
        i++;
    return s[i];
}

bool isPragmaMark(const string & s)
{
    string temp = s;
    std::transform(temp.begin(), temp.end(),temp.begin(), ::tolower);
    
    if (temp.find("pragma mark") != string::npos)
        return true;
    
    return false;
}

bool isImplementationLine(const string & s)
{
    if (s.find("@implementation") != string::npos)
        return true;
    return false;
}

string getPragmaMarkComment(const string & s)
{
    /* first determine if s contains a '-' */
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == kInstanceMethodSign) {
            i++;
            string result = "";
            
            /* advance till no white space */
            while (i < s.length()) {
                if (isspace(s[i]))
                    i++;
                else
                    break;
            }
            
            for (; i < s.length(); i++)
                result += s[i];

            return result;
        }
    }
    
    /* otherwise it doesn't contain a '-', and only a space(s) between the 
     'pragma mark' and the comment */
    unsigned long pos = s.find("pragma mark"); // position of "pragma mark" in str
    
    /* advance till no white spaces */
    int lengthOfPragmaMark = 11;
    int i = (int)pos + lengthOfPragmaMark;
    while (i < s.length()) {
        if (isspace(s[i]))
            i++;
        else
            break;
    }
    
    string result = "";
    
    for (; i < s.length(); i++)
        result += s[i];
    
    return result;
}

string formatPragmaMarkComment(const string & s)
{
    return "\n/* " + s + " */\n";
}

bool isInHeader(const vector<string> & v, const string & s)
{
    string temp = removeSpaces(s);
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == temp)
            return true;
    }

    return false;
}

void saveString(vector<string> & v, const string & s)
{
    string temp = removeSpaces(s);
    
    v.push_back(temp);
}

string removeSpaces(const string & s)
{
    string temp = "";
    for(int i = 0; i < s.length(); i++)
        if (!isspace(s[i]))
            temp += s[i];
    return temp;
}