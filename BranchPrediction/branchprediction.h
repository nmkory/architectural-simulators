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
public:
  uint8_t* predictions;
  BranchHistoryTable();

};



class BranchHistory {
public:
  BranchHistoryTable *table;
  int globalHistory = 0;
  bool twoBit;
  float count = 0;
  float miss = 0;
  BranchHistory(int m, int n);
  float makePrediction(ifstream &myReadFile);
};
