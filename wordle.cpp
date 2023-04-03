#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

void genstrings(const std::string& in, std::string base, std::string floating, size_t free_slots, std::set<std::string>& combinations, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> combinations;

    size_t free_slots = 0;
    for(size_t i = 0; i < in.size(); i++) if(in[i] == '-') free_slots++;

    genstrings(in, "", floating, free_slots, combinations, dict);

    return combinations;
}

void genstrings(const std::string& in, std::string base, std::string floating, size_t free_slots, std::set<std::string>& combinations,
                const std::set<std::string>& dict)
{
    // index of next character to be modified
    size_t index = base.size();
    // base case: base completed
    if(index == in.size())
    {
        //only insert if valid word
        if(dict.find(base) != dict.end()) combinations.insert(base);
        return;
    }

    // case: index is fixed
    if(in[index] != '-')
    {
        genstrings(in, base + in[index], floating, free_slots, combinations, dict);
        return;
    }

    // case: more free slots than floating characters. thus any letter 
    // can be here, including floating characters. if a floating character 
    // is added however, remove it from floating in the recursive step.

    if(floating.size() < free_slots)
    {
        for(size_t i = 0; i < 26; i++)
        {
            char c = 'a' + i;
            size_t floating_pos = floating.find(c);
            if(floating_pos == std::string::npos) // no need to update floating
            {
                genstrings(in, base + c, floating, free_slots - 1, combinations, dict);
            }
            else
            {
                string new_floating = floating.substr(0, floating_pos) + floating.substr(floating_pos+1, floating.size());
                genstrings(in, base + c, new_floating, free_slots - 1, combinations, dict);
            }
        }
        return;
    }

    // otherwise, must add floating characters
    for(size_t i = 0; i < floating.size(); i++)
    {
        string new_floating = floating.substr(0, i) + floating.substr(i+1, floating.size());
        genstrings(in, base + floating[i], new_floating, free_slots - 1, combinations, dict);
    }
}