#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// struct predictor {
//  // two-bit unsigned field,
//  uint8_t twobits : 2;
// };


class BranchHistoryTable {
  uint8_t* predictions;
public:
  BranchHistoryTable();

};



class BranchHistory {
  BranchHistoryTable *table;
  int globalHistory = 0;
  bool twoBit;
  float count = 0;
  float correct = 0;
public:
  BranchHistory(int m, int n);
  float makePrediction(ifstream &myReadFile);
};
