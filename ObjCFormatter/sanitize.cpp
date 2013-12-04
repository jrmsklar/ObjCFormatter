//
//  sanitize.cpp
//  ObjCFormatter
//
//  Created by Josh Sklar on 12/3/13.
//  Copyright (c) 2013 Josh Sklar. All rights reserved.
//

/*
 sanitize.cpp parses an Objective-C implementation file, and moves 
 every `{` at the end of a method declaration, private interface,
 or implementation line, to the next line.
 
 eg 1. it will transform a line like:
 `- (void)someMethod {`
 
 to lines like:
 `- (void)someMethod
 {
 `
 
 eg 2. it will transform a line like
 `@interface SomeClass <SomeDelegateProtocol> {`
 
 to lines like:
 `@interface SomeClass <SomeDelegateProtocol>
 {
 `
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

static const char kInstanceMethodCharacter = '-';
static const char kClassMethodCharacter = '+';
static const char kStartBracketCharacter = '{';
static const char kAtCharacter = '@';

static const string kImplmentationString = "@implementation";
static const string kInterfaceString = "@interface";

bool lineIsMethodDeclaration(const string & s);
bool lineIsInterfaceDeclaration(const string & s);
bool lineIsImplementationDeclaration(const string & s);

char getFirstCharOfLine(const string & s);
char getLastCharOfLine(const string & s);

string removeSpaces(const string & s);

int main(int argc, const char * argv[])
{
    string outpulFileName;
    
    if (argc == 2) {
        cout << "Attempting to open file: " << argv[1] << "\n";
    }
    else if (argc == 3) {
        cout << "Attempting to open file: " << argv[1] << " and write to output file " << argv[2] << "\n";
    }
    else {
        cerr << "Expected either 2 or 3 arguments on the command line, got " << argc << ".\n"
        "\tInstructions: Specify second argument as the full path to the input .m file.\n"
        "\tOptional: Specify a third argument as the full path for the ouput file. Otherwise, will overwrite the input file.\n"
        "Please specify the entire path of the .m file as the second argument.\n";
        return -1;
    }
    
    string fileName = argv[1];
    ifstream is;
    is.open(fileName.c_str());
    if (!is) {
        cout << "Couldn't open file.\nProgram will now quit.\n";
        return -1;
    }
    string s;
    string methodDeclarations = "";
    
    bool hasPassedImplementation = false;
    
    while (getline(is, s).good()) {
        char firstChar = getFirstCharOfLine(s);

        
        /* used the pragma marks for comments to groups of methods */
        if (lineIsInterfaceDeclaration(s)) {
            // determine if it's either an interface or implementation
            // if it is, sanitize the line
        }
        else if (lineIsImplementationDeclaration(s)) {
            
        }
        else if (lineIsMethodDeclaration(s)) {
            
        }
        else {
            
        }
        
        /* if the line starts with a -/+, get the method stub */
        if (firstChar == kInstanceMethodSign || firstChar == kClassMethodSign) {
            if (!hasPassedImplementation) {
                saveString(headerSectionLines, s);
            }
            else {
                
                string sanitizedMethodName = sanitizeMethodName(s);
                
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
    
    is.close();
    of.close();
    
    /* write results to file */
    is.open(tempFileName.c_str());
    /* if only 2 command line arguments were specified, copy temporary file into original file */
    if (argc == 2) {
        of.open(fileName.c_str());
        if (!of) {
            cerr << "Error opening output file: " << argv[2] << "\nProgram will now quit.\n";
            return -2;
        }
    }
    else {
        of.open(argv[2]);
        if (!of) {
            cerr << "Error opening output file: " << argv[2] << "\nProgram will now quit.\n";
            return -3;
        }
    }
    
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

bool lineIsMethodDeclaration(const string & s)
{
    char firstChar = getFirstCharOfLine(s);
    
    if (firstChar == kClassMethodCharacter ||
        firstChar == kInstanceMethodCharacter)
        return true;
    else
        return false;
}

bool lineIsInterfaceDeclaration(const string & s)
{
    size_t found = s.find(kInterfaceString);
    
    return found != std::string::npos;
}

bool lineIsImplementationDeclaration(const string & s)
{
    size_t found = s.find(kImplmentationString);
    
    return found != std::string::npos;
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

char getLastCharOfLine(const string & s)
{
    return ' ';
}


string removeSpaces(const string & s)
{
    string temp = "";
    for(int i = 0; i < s.length(); i++)
        if (!isspace(s[i]))
            temp += s[i];
    return temp;
}
