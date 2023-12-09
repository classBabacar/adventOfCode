#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

using namespace std;

vector<string> ReadAndStoreFile(string fileName);
vector<string> Tokenizer(string stringToTokenize, string delimeter);
string lLtrim(const string &s);
string Rtrim(const string &s);
string Trim(const string &s);

int main() {
  vector<string> cards = ReadAndStoreFile("input.txt");
  vector<string> numbers;
  map<int, int> numbersMap;
  bool shouldAddWinningNumbers = true;
  int winningNumbersFound = 0;
  int result = 0;

  for (auto card : cards) {
    numbers = Tokenizer(card, " ");
    for (auto number : numbers) {
      number = Trim(number);

      if (number.empty())
        continue;

      if (number == "|") {
        shouldAddWinningNumbers = false;
      } else if (shouldAddWinningNumbers) {
        numbersMap[stoi(number)]++;
      } else {
        if (numbersMap[stoi(number)] > 0)
          winningNumbersFound++;
      }
    }

    result += pow(2, winningNumbersFound - 1);

    shouldAddWinningNumbers = true;
    winningNumbersFound = 0;
    numbersMap.clear();
  }

  cout << "Total Card Points: " << result << endl;
}

vector<string> ReadAndStoreFile(string fileName) {
  string line;
  ifstream file(fileName);
  vector<string> fileLines;

  if (file.is_open()) {
    while (getline(file, line)) {
      string key = ":";
      size_t found = line.rfind(key);
      if (found != string::npos) {
        line = line.substr(found + 2, line.size() - found - 1);
      }
      fileLines.push_back(Trim(line));
    }

    file.close();
  }

  return fileLines;
}

vector<string> Tokenizer(string stringToTokenize, string delimeter) {
  vector<string> tokens;
  size_t pos = 0;
  string token;

  while ((pos = stringToTokenize.find(delimeter)) != string::npos) {
    token = stringToTokenize.substr(0, pos);
    tokens.push_back(Trim(token));
    stringToTokenize.erase(0, pos + delimeter.length());
  }

  tokens.push_back(Trim(stringToTokenize));
  return tokens;
}

string Ltrim(const string &s) {
  return regex_replace(s, regex("^\\s+"), string(""));
}

string Rtrim(const string &s) {
  return regex_replace(s, regex("\\s+$"), string(""));
}

string Trim(const string &s) { return Ltrim(Rtrim(s)); }