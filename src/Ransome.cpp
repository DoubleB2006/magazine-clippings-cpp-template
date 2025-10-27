#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>   // isspace, tolower
using namespace std;

bool canCreateNote(const string& note, const vector<string>& articles) {
    unordered_map<char, int> supply;

    auto norm = [](unsigned char c) -> int {
        if (isspace(c)) return -1;   // ignore whitespace entirely
        return tolower(c);           // case-insensitive
    };

    // 1) Build supply from all articles
    for (const string& art : articles) {
        for (unsigned char c : art) {
            int k = norm(c);
            if (k != -1) supply[(char)k]++;  // count everything except whitespace
        }
    }

    // 2) Consume supply to build the note
    for (unsigned char c : note) {
        int k = norm(c);
        if (k == -1) continue;               // skip whitespace in the target note
        auto it = supply.find((char)k);
        if (it == supply.end() || it->second == 0) return false;
        it->second--;
    }

    return true;
}

int main() {
    cout << canCreateNote("a", {"a"}) << "\n";                                                // true
    cout << canCreateNote("a", {"ab"}) << "\n";                                               // true
    cout << canCreateNote("a", {"a", "b"}) << "\n";                                           // true
    cout << canCreateNote("abc", {"a", "b", "c"}) << "\n";                                    // true
    cout << canCreateNote("The bird is red!", {"I write a lot.", "To and fro.", "Here be deadly dragons!"}) << "\n"; // true
    cout << canCreateNote("a", {"b"}) << "\n";                                                // false
    cout << canCreateNote("a", {"bc"}) << "\n";                                               // false
    cout << canCreateNote("a", {"b", "c"}) << "\n";                                           // false
    cout << canCreateNote("abc", {"a", "b", "d"}) << "\n";                                    // false
    cout << canCreateNote("The bird is red!", {"I write a lot.", "To and fro."}) << "\n";    // false
    cout << canCreateNote("The bird is red!", {"I write a lot.", "To and fro.", "Here be deadly dragons"}) << "\n"; // false
    return 0; 
}