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


// Add prototypes of helper functions here

std::set<std::string> wordleHelper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    int blanks
);
std::set<std::string> setUnion(std::set<std::string>& s1, std::set<std::string>& s2);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    int blanks = 0;
    for(int i = 0 ; i < in.length(); i++){
        if(in[i] == '-'){
            blanks++;
        }
    }
    return wordleHelper(in, floating, dict, blanks);
}

// Define any helper functions here

std::set<std::string> wordleHelper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    int blanks
)
{
    std::set<std::string> words;
    if(blanks == 0){
        if(dict.find(in) != dict.end()){
            words.insert(in);
        }
    }
    else{
        for(int i = 0; i < in.length(); i++){
            if(in[i] == '-'){
                if(floating.length() < blanks){
                    for(char letter = 'a'; letter <= 'z'; letter++){
                        std::string next = in;
                        next[i] = letter;
                        //std::cout << letter << std::endl;
                        std::set<std::string> word = wordleHelper(next, floating, dict, blanks - 1);
                        words = setUnion(words, word);
                    }
                }
                for(int j = 0; j < floating.length(); j++){
                    std::string next = in;
                    next[i] = floating[j];
                    std::string nFloating = floating.substr(0, j) + floating.substr(j+1, floating.length());
                    std::set<std::string> word = wordleHelper(next, nFloating, dict, blanks - 1);
                    words = setUnion(words, word);
                }
                break;
            }
        }
    }
    return words;
}


std::set<std::string> setUnion(std::set<std::string>& s1, std::set<std::string>& s2)
{
    std::set<std::string> Union;;
    typename std::set<std::string>::iterator it;
    for(it = s1.begin(); it != s1.end(); it++){
        Union.insert(*it);
    }
    for(it = s2.begin(); it != s2.end(); it++){
        Union.insert(*it);
    }
    return Union;
}