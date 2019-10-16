/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 3: Syntax Checker
main is the driver for Syntax Checker.
*/

#include "GenStack.cpp" //Including GenStack.cpp instead of .h to resolve template linking errors while keeping them in separate files
#include <iostream>
#include <fstream>
#include <limits> //For maxstreamsize to ignore

char getCharFromUser();

int main (int argc, char** argv) {
    if(argc < 2) {
        std::cout << "Please pass filename as a command argument" << std::endl;
        exit(1);
    }
    std::string filename = argv[1];

    char response = 'y';
    do {
        std::ifstream is(filename);
        if(is.fail()) {
            std::cout << "Could not open '" << filename << "'.  Aborting." << std::endl;
            exit(1);
        }
        std::string line;
        int lineNum = 0;
        GenStack<char> delimiterStack(10);
        while(!is.eof()) {
            ++lineNum;  //Keeping track of the line number for debug purposes
            std::getline(is, line);
            for(int i = 0; i < line.length(); ++i) {
                char currentChar = line[i];
                //Single-line comment checking; break if you found both //'s
                if(currentChar == '/' && i < line.length()-1 && line[i+1] == '/') { //Using short circuit evaluation of i < line.length()-1 to prevent seg fault if / is at end of line
                    break;
                }
                
                //Multi-line comment checking
                if(currentChar == '/' && i < line.length()-1 && line[i+1] == '*') { //Using short circuit evaluation of i < line.length()-1 to prevent seg fault if / is at end of line
                    delimiterStack.push('/');
                    continue;
                }
                
                if(!delimiterStack.isEmpty() && delimiterStack.peek() == '/') { //Using short circuit evaluation of isEmpty to prevent error from peek
                    if(currentChar == '*') { //Looking for the comment close
                        if(i < line.length()-1 && line[i+1] == '/') {
                            delimiterStack.pop();
                        }
                    }
                    continue; //Regardless of whether or not the end of comment is found, should return to top of loop
                }

                //Account for escaped out characters
                if(!delimiterStack.isEmpty() && delimiterStack.peek() == '\\') {
                    delimiterStack.pop();
                    //If there's an escape character within a string/character literal, ignore whatever character comes next in terms of delimiter parsing.
                    if(!delimiterStack.isEmpty() && (delimiterStack.peek() == '"' || delimiterStack.peek() == '\'')) {
                        continue;
                    }
                }

                //If a \ isn't escaped out, push it to the stack to account for whatever escaped character came up
                if(currentChar == '\\') {
                    delimiterStack.push('\\');
                    continue;
                }

                //String/char literals using ' and "
                if((currentChar == '\'' || currentChar == '"')) {
                    if(!delimiterStack.isEmpty() && delimiterStack.peek() == currentChar) {
                        delimiterStack.pop();
                        continue;
                    } else if (!delimiterStack.isEmpty() && ((delimiterStack.peek() == '\'' && currentChar == '"') || (delimiterStack.peek() == '"' && currentChar == '\''))) {
                        //String/char literals cannot be nested inside other string/char literals
                        continue;
                    } else {
                        delimiterStack.push(currentChar);
                        continue;
                    }
                }
                if(!delimiterStack.isEmpty() && (delimiterStack.peek() == '\'' || delimiterStack.peek() == '"')) { //If you're in a char/string literal, disregard delimiters found
                    continue;
                }

                //Push opening delimiters
                if(currentChar == '{' || currentChar == '(' || currentChar == '[') {
                    delimiterStack.push(currentChar);
                }

                
                //Pop closing delimiters
                if(currentChar == '}' || currentChar == ')' || currentChar == ']') {
                    if(delimiterStack.isEmpty()) {
                        std::cout << "ERROR: Line " << lineNum << ": found " << currentChar << " but never found opening delimiter " << std::endl;
                        exit(1);
                    }
                    char poppedChar = delimiterStack.pop();
                    if(poppedChar == '{') {
                        if(currentChar != '}') {
                            std::cout << "ERROR: Line " << lineNum << ": Expected } but found " << currentChar << std::endl;
                            exit(1);
                        }
                    } else if(poppedChar == '(') {
                        if(currentChar != ')') {
                            std::cout << "ERROR: Line " << lineNum << ": Expected ) but found " << currentChar << std::endl;
                            exit(1);
                        }
                    } else if (poppedChar == '[') {
                        if(currentChar != ']') {
                            std::cout << "ERROR: Line " << lineNum << ": Expected ] but found " << currentChar << std::endl;
                            exit(1);
                        }
                    }
                }
            }
        }
        is.close();  
        if(delimiterStack.isEmpty()) {
            std::cout << "No errors found.  File is good!" << std::endl;

            std::cout << "Would you like to examine another file? (y/n) ";
            response = getCharFromUser();
            if(response == 'y') {
                std::cout << "What is the name of the file you would like to examine? ";
                std::getline(std::cin, filename);
            }
        } else {
            std::cout << "Reached end of file, missing";
            while(!delimiterStack.isEmpty()) {
                char missingChar;
                switch(delimiterStack.pop()) {
                    case '[':
                        missingChar = ']';
                        break;
                    case '(':
                        missingChar = ')';
                        break;
                    case '{':
                        missingChar = '}';
                        break;
                    case '\'':
                        missingChar = '\'';
                        break;
                    case '"':
                        missingChar = '"';
                        break;
                    default:
                        missingChar = '?';
                }
                std::cout << " " << missingChar;
            }
            std::cout << std::endl;
            exit(1);
        }
    } while (response =='y');
    return 0;
}


/*
    Handles char input from users
    Returns char value user typed in
*/
char getCharFromUser() { //Accounting for bad input and clearing the buffer, Function taken from interterm c++ assignments
    char input;
    std::cin >> input;
    std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
    return input;
}