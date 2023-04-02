// main() program to test your schedule function.
// Feel free to modify though it will be easiest to
// simply pass in different command line arguments to test
// various cases of words and letters.
// This file will not be graded. 
#include <iostream>
#include <set>
#include <string>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2){
        cout << "Please provide an initial string (e.g. \"s---ng\")"
                " and optional string of floating characters." << endl;
        return 1;
    }
    const std::set<std::string>& dict = readDictWords("dict-eng.txt");    
    string in(argv[1]);
    string floatingChars;
    if(argc > 2){
        floatingChars = argv[2];
    }
    std::set<string> answers;
    answers = wordle(in, floatingChars, dict);
    for(auto s : answers){
        cout << s << endl;
    }
    return 0;
}