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
  int pc;  //program counter
  string tont;  //taken or not taken
  int prediction;
  while((myReadFile >> hex >> pc).good()) {
      count++;
      myReadFile >> tont;
      pc = (pc & 0xFF);

      prediction = table[globalHistory].predictions[pc];
      if ((prediction == 0 && tont == "T") || (prediction == 1 && tont == "N")) {
        miss++;
        if (tont == "N")
          table[globalHistory].predictions[pc] = 0;
        else
          table[globalHistory].predictions[pc] = 1;
      }
  };
  std::cout << (miss / count)*100 << "%" << '\n';
  return (miss / count)*100;
}
