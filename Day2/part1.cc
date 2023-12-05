#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

using namespace std;

vector<string> ReadAndStoreFile(string fileName);
vector<string> Tokenizer(string stringToTokenize, string delimeter);
vector<string> CleanUpVector(vector<string> colorNumArray);
bool ConvertColorAndNumToMap(vector<string> colorNumArray);
string lLtrim(const string &s);
string Rtrim(const string &s);
string Trim(const string &s);

int main() {
  vector<string> games = ReadAndStoreFile("input.txt");
  vector<string> bags;
  vector<string> colorAndNums;
  int gameId = 1;
  int result = 0;
  bool isValidSet;

  for (string game : games) {
    isValidSet = true;

    bags = Tokenizer(game, ";");
    for (string set : bags) {
      colorAndNums = Tokenizer(set, " ");
      colorAndNums = CleanUpVector(colorAndNums);

      if (!ConvertColorAndNumToMap(colorAndNums)) {
        isValidSet = false;
      }
    }

    if (isValidSet) {
      result += gameId;
    }

    // precautionary cleanup :)
    colorAndNums.clear();
    bags.clear();
    gameId++;
  }

  cout << "Sum of Valid ID games: " << result << endl;
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
  replace(stringToTokenize.begin(), stringToTokenize.end(), ',', ' ');

  while ((pos = stringToTokenize.find(delimeter)) != string::npos) {
    token = stringToTokenize.substr(0, pos);
    tokens.push_back(Trim(token));
    stringToTokenize.erase(0, pos + delimeter.length());
  }

  tokens.push_back(Trim(stringToTokenize));
  return tokens;
}

bool ConvertColorAndNumToMap(vector<string> colorAndNums) {
  map<string, string> map;
  string number;
  string color;

  for (int i = 0; i < colorAndNums.size(); i += 2) {
    number = colorAndNums[i];
    color = colorAndNums[i + 1];
    map[color] = number;
  }

  if (map.find("blue") != map.end() && stoi(map["blue"]) > 14) {
    return false;
  }

  if (map.find("red") != map.end() && stoi(map["red"]) > 12) {
    return false;
  }

  if (map.find("green") != map.end() && stoi(map["green"]) > 13) {
    return false;
  }

  return true;
}

vector<string> CleanUpVector(vector<string> colorNumArray) {
  // Removing any empty string or empty space elements, the array should have an
  // even amount of elements
  for (auto i = colorNumArray.begin(); i != colorNumArray.end(); ++i) {
    if (*i == "" || *i == " ") {
      colorNumArray.erase(i);
      i--;
    }
  }

  return colorNumArray;
}

string Ltrim(const string &s) {
  return regex_replace(s, regex("^\\s+"), string(""));
}

string Rtrim(const string &s) {
  return regex_replace(s, regex("\\s+$"), string(""));
}

string Trim(const string &s) { return Ltrim(Rtrim(s)); }