#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> ReadAndStoreFile(string fileName);
vector<vector<char>> ConvertTo2DArray(vector<string> &fileContents);
int GetPartNumberSum(vector<vector<char>> &engines);
int ScanForStringNumber(vector<vector<char>> &engines, int row, int col);
int GetStringValue(vector<vector<char>> &engines, int row, int col);

int main() {
  vector<string> fileContents = ReadAndStoreFile("input.txt");
  vector<vector<char>> engines = ConvertTo2DArray(fileContents);
  int sum = GetPartNumberSum(engines);

  cout << "Part Number sum is: " << sum << endl;
}

vector<string> ReadAndStoreFile(string fileName) {
  string line;
  ifstream file(fileName);
  vector<string> fileLines;

  if (file.is_open()) {
    while (getline(file, line)) {

      // Necessary because string has\r in windows
      line.pop_back();
      fileLines.push_back(line);
    }
    file.close();
  }

  return fileLines;
}

vector<vector<char>> ConvertTo2DArray(vector<string> &fileContents) {
  vector<vector<char>> engines;

  for (auto x : fileContents) {
    vector<char> engine;
    for (auto y : x) {
      engine.push_back(y);
    }
    engines.push_back(engine);
  }

  return engines;
}

int GetPartNumberSum(vector<vector<char>> &engines) {
  int result = 0;

  for (int row = 0; row < engines.size(); ++row) {
    for (int col = 0; col < engines[row].size(); ++col) {
      if (ispunct(engines[row][col]) && engines[row][col] != '.') {

        // Left
        result += ScanForStringNumber(engines, row, col - 1);

        // Right
        result += ScanForStringNumber(engines, row, col + 1);

        // Up
        result += ScanForStringNumber(engines, row - 1, col);

        // Down
        result += ScanForStringNumber(engines, row + 1, col);

        // Up Left
        result += ScanForStringNumber(engines, row - 1, col - 1);

        // Up Right
        result += ScanForStringNumber(engines, row - 1, col + 1);

        // Down Left
        result += ScanForStringNumber(engines, row + 1, col - 1);

        // Down Right
        result += ScanForStringNumber(engines, row + 1, col + 1);
      }
    }
  }

  return result;
}

int ScanForStringNumber(vector<vector<char>> &engines, int row, int col) {
  // out of bounds
  if (col < 0 || row < 0 || col >= engines[0].size() || row >= engines.size()) {
    return 0;
  }

  if (engines[row][col] == '.') {
    return 0;
  }

  int stringVal = GetStringValue(engines, row, col);
  return stringVal;
}

int GetStringValue(vector<vector<char>> &engines, int row, int col) {
  int leftCol = col;
  int rightCol = col;

  // finding the start and end range of the string, adding them up and using
  // stoi
  while (leftCol - 1 >= 0 && isdigit(engines[row][leftCol - 1])) {
    leftCol--;
  }

  while (rightCol + 1 < engines.size() && isdigit(engines[row][rightCol + 1])) {
    rightCol++;
  }

  string stringNumber = "";
  for (int i = leftCol; i <= rightCol; ++i) {
    stringNumber += engines[row][i];
    engines[row][i] = '.';
  }

  if (stringNumber != "") {
    return stoi(stringNumber);
  }

  return 0;
}