#include "ladder.h"

void error(string word1, string word2, string msg){
    cout << "Error: " << msg << " for words: " << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (str1 == str2)
        return true;
    int len1 = str1.length();
    int len2 = str2.length();

    if((abs(len1 - len2)) > d)
        return false;

    int i = 0, j = 0;
    bool foundDifference = false;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            // If we have already found a difference, return false.
            if (foundDifference) {
                return false;
            }
            foundDifference = true;
            // If the strings have the same length, we move to the next character in both.
            if (len1 == len2) {
                ++i;
                ++j;
            } else {
                // If one string is longer, we move to the next character in that string.
                if (len1 > len2) {
                    ++i;
                } else {
                    ++j;
                }
            }
        } else {
            // If the characters are the same, we move to the next character in both strings.
            ++i;
            ++j;
        }
    }
    if ((i < len1 || j < len2) && !foundDifference) {
        return true;
    }
    return foundDifference;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for (const auto& word : word_list){
            if (is_adjacent(last_word, word)){
                if (visited.find(word) == visited.end()){
                    visited.insert(word);

                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return vector<string>();
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    string word;
    while(file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.size() == 0)
        cout << "No word ladder found.\n";
    else{
    cout << "Word ladder found: ";
    for (auto word : ladder)
        cout << word << " ";
    cout << "\n";
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}