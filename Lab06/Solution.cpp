#include "WordFreq.h"
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

void parseWords(vector<string>& words, string line) {
    string word; // Create temp word variable
    for (int i = 0; i < line.size(); i++) {
        if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')) { // Take the words if they're in the alphabet
            word.push_back(tolower(line[i])); // Push back the letter to the temp word variable
        }
        else if (!word.empty()) { // If it's end of the word and it's not empty
            if(word.size()>2) // If it's size greater than 2
                words.push_back(word); // Push the word to words vector
            word.clear(); // Clear temp word variable
        }
    }
    if (!word.empty()) { // Push last word to words vector
        if (word.size() > 2)
            words.push_back(word);
    }
}

bool compareWordFreq(const WordFreq& a, const WordFreq& b) {
    return a.freq > b.freq; // Compare frequency of 2 word
}
///-----------------------------------------------------------------
/// Process the given text file and return the most frequent "k" words
///
vector<WordFreq> GetMostFrequentKWords(string filename, int k) {
	vector<WordFreq> result;
	// Fill this in
    ifstream file(filename);
    string line;
    vector<string> words;
    while (getline(file, line)) { // Read the file
        parseWords(words, line); // Parse the words
    }
    file.close(); // Close file
    map<string, int> freqMap; // Create map
    for (const auto& word : words) { // Iterate through each word in the words vector
        if (freqMap.count(word) > 0) { // Check if the word is already in the frequency map
            freqMap[word]++;  // If yes, increment its frequency
        }
        else
            freqMap.insert(pair<string, int>(word, 1)); // If not, insert the word into the frequency map with a count of 1
    }
    // Convert the map to a vector of WordFreq
    vector<WordFreq> wordFreqVector;

    for (const auto& entry : freqMap) {
        wordFreqVector.push_back(WordFreq(entry.first)); // Push the word and its frequency
        wordFreqVector.back().freq = entry.second;
    }

    // Sort the vector in descending order based on frequency
    sort(wordFreqVector.begin(), wordFreqVector.end(), compareWordFreq);

    // Take the top k elements to the result vector
    result.assign(wordFreqVector.begin(), wordFreqVector.begin() + min(k, static_cast<int>(wordFreqVector.size())));
	return result;
} //end-GetMostFrequentKWords