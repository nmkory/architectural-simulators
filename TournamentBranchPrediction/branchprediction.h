#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


class BranchHistoryTable {
public:
  uint8_t* predictions;
  BranchHistoryTable();
  //uint8_t* used; //question 4

};


class LocalHistory {
public:
  uint8_t* localBranchHistory;
  BranchHistoryTable *localTable;
  bool makePrediction(int pc, string tont);
  LocalHistory();
};


class BranchHistory {
public:
  BranchHistoryTable *table;
  LocalHistory *localHistory;
  uint8_t tournPicker = 0;
  int globalHistory = 0;
  bool twoBit;
  float count = 0;
  float miss = 0;
  //int numUsed = 0;  //question 4
  int numTables;
  BranchHistory(int m, int n);
  void updatePicker(bool globalMiss, bool localMiss);
  float makePrediction(ifstream &myReadFile);
};
