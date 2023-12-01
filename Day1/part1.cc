#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> DisassembleFileLinesAndStore(vector<string> &fileLines);
vector<string> ReadAndStoreFile(string fileName);
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

  for (string line : fileLines) {
    digitString = "";
    for (char character : line) {
      if (isdigit(character))
        digitString += character;
    }

    if (digitString != "") {
      digitStrings.push_back(digitString);
    }
  }

  return digitStrings;
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
