#include "branchprediction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;


BranchHistoryTable::BranchHistoryTable() {
  predictions = new uint8_t[256];
  //used = new uint8_t[256];  //question 4
  memset(predictions, 0, sizeof(predictions));
  //memset(predictions, 0, sizeof(used));  //question 4
}


LocalHistory::LocalHistory() {
  localBranchHistory = new uint8_t[16];
  localTable = new BranchHistoryTable[1];
}


bool LocalHistory::makePrediction(int pc, string tont) {
  int branch = pc & 0b1111;
  int index = localBranchHistory[branch];
  int prediction = localTable[0].predictions[index];
  bool localMiss = false;

  switch (prediction) {
    case 0 :  //strong not taken
      if (tont == "T") {
        localMiss = true;
        localTable[0].predictions[index] = 1;
      }
      break;
    case 1 :  //weak not taken
      if (tont == "T") {
        localMiss = true;
        localTable[0].predictions[index] = 3;
      }
      else
        localTable[0].predictions[index] = 0;
      break;
    case 2 :  //weak taken
      if (tont == "T")
        localTable[0].predictions[index] = 3;
      else {
        localMiss = true;
        localTable[0].predictions[index] = 0;
      }
      break;
    case 3 :  //strong taken
      if (tont == "N") {
        localMiss = true;
        localTable[0].predictions[index] = 2;
      }
      break;
  }

  int newIndex = index;
  newIndex = (newIndex >> 1);
  if (tont == "T") {
    newIndex = newIndex | 0b100000;
  }
  localBranchHistory[branch] = newIndex;

  return localMiss;
}


BranchHistory::BranchHistory(int m, int n) {
  if (m == 0) {
    numTables = 1;
    table = new BranchHistoryTable[numTables];
  }
  else  {
    numTables = 64;
    table = new BranchHistoryTable[numTables];
  }
  if (n == 1)
    twoBit = false;
  else
    twoBit = true;

  localHistory = new LocalHistory();
}


float BranchHistory::makePrediction(ifstream &myReadFile) {
  int pc;  //program counter
  string tont;  //taken or not taken
  int prediction;
  bool globalMiss;
  while((myReadFile >> hex >> pc).good()) {
      count++;
      myReadFile >> tont;
      pc = (pc & 0xFF);
      globalMiss = false;  //reset globalMiss

      prediction = table[globalHistory].predictions[pc];
      /*  //question 4
      if (table[globalHistory].used[pc] == 0) {
        table[globalHistory].used[pc]++;
        numUsed++;
        }
      */  //question 4
      if (twoBit == false) {
        if ((prediction == 0 && tont == "T") || (prediction == 1 && tont == "N")) {
          globalMiss = true;
          if (tont == "N")
            table[globalHistory].predictions[pc] = 0;
          else
            table[globalHistory].predictions[pc] = 1;
        }
      }

      else {
        switch (prediction) {
          case 0 :  //strong not taken
            if (tont == "T") {
              globalMiss = true;
              table[globalHistory].predictions[pc] = 1;
            }
            break;
          case 1 :  //weak not taken
            if (tont == "T") {
              globalMiss = true;
              table[globalHistory].predictions[pc] = 3;
            }
            else
              table[globalHistory].predictions[pc] = 0;
            break;
          case 2 :  //weak taken
            if (tont == "T")
              table[globalHistory].predictions[pc] = 3;
            else {
              globalMiss = true;
              table[globalHistory].predictions[pc] = 0;
            }
            break;
          case 3 :  //strong taken
            if (tont == "N") {
              globalMiss = true;
              table[globalHistory].predictions[pc] = 2;
            }
            break;
        }
      }

      if (numTables != 1) {
        globalHistory = (globalHistory >> 1);
        if (tont == "T") {
          globalHistory = globalHistory | 0b100000;
        }
      }

      bool localMiss = localHistory->makePrediction(pc, tont);


      if (globalMiss) {
        miss++;
      }




  }  //end of while loop
  std::cout << (miss / count)*100 << "%" << '\n';
  // std::cout << "Num used:" << numUsed << '\n';  //question 4
  return (miss / count)*100;
}
