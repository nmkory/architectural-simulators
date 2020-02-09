#include "branchprediction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>


BranchHistoryTable::BranchHistoryTable() {
  predictions = new predictor[256];
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
