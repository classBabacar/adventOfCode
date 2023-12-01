#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<string> DisassembleFileLinesAndStore(vector<string> &fileLines);
vector<string> ReadAndStoreFile(string fileName);
string GetDigitsInString(string fileLine);
string ConvertDigit(string digit);
int GetCalibrationValue(vector<string> &digitStrings);

int main() {
  vector<string> fileLines = ReadAndStoreFile("input.txt");
  vector<string> digitStrings = DisassembleFileLinesAndStore(fileLines);
  int calibrationValue = GetCalibrationValue(digitStrings);

  cout << "Your Calibration Value is: " << calibrationValue << endl;
}

vector<string> ReadAndStoreFile(string fileName) {
  string line;
  ifstream file(fileName);
  vector<string> fileLines;

  if (file.is_open()) {
    while (getline(file, line)) {
      fileLines.push_back(line);
    }
    file.close();
  }

  return fileLines;
}

vector<string> DisassembleFileLinesAndStore(vector<string> &fileLines) {
  string digitString;
  vector<string> digitStrings;
  vector<pair<string, int>> digitAndPosition;

  for (string line : fileLines) {
    digitString = GetDigitsInString(line);
    digitStrings.push_back(digitString);
  }

  return digitStrings;
}

string GetDigitsInString(string fileLine) {
  vector<pair<string, int>> digitAndPositions;
  vector<string> availableDigits = {
      "1",   "2",   "3",     "4",    "5",    "6",   "7",     "8",     "9",
      "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

  for (string digitToSearch : availableDigits) {
    size_t pos = fileLine.find(digitToSearch);

    while (pos != std::string::npos) {
      // Add digit and position to the vector
      digitAndPositions.push_back(make_pair(ConvertDigit(digitToSearch), pos));

      // Get the next occurrence from the current position
      pos = fileLine.find(digitToSearch, pos + digitToSearch.size());
    }
  }

  // sorting the second position of the part since order matters
  sort(digitAndPositions.begin(), digitAndPositions.end(),
       [](auto &left, auto &right) { return left.second < right.second; });

  string digitString = "";

  // create a string of all the digits we have seen
  for (auto x : digitAndPositions) {
    digitString += x.first;
  }

  return digitString;
}

string ConvertDigit(string digit) {
  map<string, string> converter = {
      {"one", "1"},   {"two", "2"},   {"three", "3"},
      {"four", "4"},  {"five", "5"},  {"six", "6"},
      {"seven", "7"}, {"eight", "8"}, {"nine", "9"}};

  if (converter.find(digit) != converter.end()) {
    return converter[digit];
  }

  return digit;
}

int GetCalibrationValue(vector<string> &digitStrings) {
  int calibrationValue = 0;
  string twoDigitString = "";

  for (string digitString : digitStrings) {
    twoDigitString = digitString[0];
    twoDigitString += digitString[digitString.size() - 1];
    calibrationValue += stoi(twoDigitString);
  }

  return calibrationValue;
}
