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
bool CheckValidAdjacency(int left, int right, int up, int down, int upleft,
                         int upright, int downleft, int downright);

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
      if (engines[row][col] == '*') {
        // Left
        int left = ScanForStringNumber(engines, row, col - 1);

        // Right
        int right = ScanForStringNumber(engines, row, col + 1);

        // Up
        int up = ScanForStringNumber(engines, row - 1, col);

        // Down
        int down = ScanForStringNumber(engines, row + 1, col);

        // Up Left
        int upleft = ScanForStringNumber(engines, row - 1, col - 1);

        // Up Right
        int upright = ScanForStringNumber(engines, row - 1, col + 1);

        // Down Left
        int downleft = ScanForStringNumber(engines, row + 1, col - 1);

        // Down Right
        int downright = ScanForStringNumber(engines, row + 1, col + 1);

        if (CheckValidAdjacency(left, right, up, down, upleft, upright,
                                downleft, downright)) {
          int gearRatio = 1;
          gearRatio *= (left != 0) ? left : 1;
          gearRatio *= (right != 0) ? right : 1;
          gearRatio *= (up != 0) ? up : 1;
          gearRatio *= (down != 0) ? down : 1;
          gearRatio *= (upleft != 0) ? upleft : 1;
          gearRatio *= (upright != 0) ? upright : 1;
          gearRatio *= (downleft != 0) ? downleft : 1;
          gearRatio *= (downright != 0) ? downright : 1;

          result += gearRatio;
        }
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

  // Basically finding the start and end range of the string
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

bool CheckValidAdjacency(int left, int right, int up, int down, int upleft,
                         int upright, int downleft, int downright) {
  int count = 0;

  count += (left > 0) ? 1 : 0;
  count += (right > 0) ? 1 : 0;
  count += (up > 0) ? 1 : 0;
  count += (down > 0) ? 1 : 0;
  count += (upleft > 0) ? 1 : 0;
  count += (upright > 0) ? 1 : 0;
  count += (downleft > 0) ? 1 : 0;
  count += (downright > 0) ? 1 : 0;

  if (count == 2) {
    return true;
  }

  return false;
}