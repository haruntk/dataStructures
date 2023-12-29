#include "WordFreq.h"
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

void parseWords(vector<string>& words, string line) {
    std::string word;
    for (int i = 0; i < line.size(); i++) {
        if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')) {
            word.push_back(tolower(line[i]));
        }
        else if (!word.empty()) {
            if(word.size()>2)
                words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        if (word.size() > 2)
            words.push_back(word);
    }
}

///-----------------------------------------------------------------
/// Process the given text file and return the most frequent "k" words
///
vector<WordFreq> GetMostFrequentKWords(string filename, int k) {
	vector<WordFreq> result;
	// Fill this in
    std::ifstream file(filename);
    std::string line;
    vector<string> words;
    while (getline(file, line)) {
        parseWords(words, line);
    }
    file.close();
    map<string, int> freqMap;
    for (const auto& word : words) {
        if (freqMap.count(word) > 0) {
            freqMap[word]++;
        }
        else
            freqMap.insert(pair<string, int>(word, 1));
    }
    map<string, int>::iterator itr;
    for (itr = freqMap.begin(); itr != freqMap.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second
            << '\n';
    }

	return result;
} //end-GetMostFrequentKWords