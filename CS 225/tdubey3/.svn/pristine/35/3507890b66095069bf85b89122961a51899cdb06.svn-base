/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::sort;
using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    ifstream words(filename);
    string temp;
    if(words.is_open()) {
        while(getline(words, temp)) {
            string key = temp;
            sort(key.begin(), key.end());
            dict[key].push_back(temp);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    vector<string>::const_iterator iterate;
    for(iterate=words.begin(); iterate<words.end(); iterate++) {
        string key = *iterate;
        sort(key.begin(), key.end());
        dict[key].push_back(*iterate);
    }
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    string temp = word;
    sort(temp.begin(), temp.end());
    auto lookup = dict.find(temp);
    if( lookup != dict.end()) {
        return lookup->second;
    } else {
        return vector<string> ();
    }
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
//    vector<vector <string>> temp;
//    for(auto iter=dict.begin(); iter!=dict.end(); iter++) {
//        if(iter->second.size()>1) {
//            temp.push_back(iter->second);
//        }
//    }
//    if(temp.empty()) {
//        return vector< vector < string > >();
//    } else {
//        return vector < vector <string>>();
//    }
    vector<vector<string>> ret;
        for(auto & key : dict){
            if(key.second.size() > 1){
                ret.push_back(key.second);
            }
        }
    return ret;
}


