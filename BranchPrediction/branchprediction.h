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
  //uint8_t* used; //question 4

};



class BranchHistory {
public:
  BranchHistoryTable *table;
  int globalHistory = 0;
  bool twoBit;
  float count = 0;
  float miss = 0;
  //int numUsed = 0;  //question 4
  int numTables;
  BranchHistory(int m, int n);
  float makePrediction(ifstream &myReadFile);
};
