#include "branchprediction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

BranchHistoryTable::BranchHistoryTable() {
  predictions = new uint8_t[256];
  memset(predictions, 0, sizeof(predictions));
}


BranchHistory::BranchHistory(int m, int n) {
  if (m == 1)
    twoBit = false;
  else
    twoBit = true;
  if (n == 0)
    table = new BranchHistoryTable[1];
  else
    table = new BranchHistoryTable[64];
}

float BranchHistory::makePrediction(ifstream &myReadFile) {
  string pc;  //program counter
  string tont;  //taken or not taken
  while((myReadFile >> pc).good()) {
      myReadFile >> tont;
      cout << pc << tont << endl;
  };
  return 0;
}
