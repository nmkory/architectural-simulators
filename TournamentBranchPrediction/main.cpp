#include <iostream>
#include <fstream>
#include "branchprediction.h"
// #include <stdlib.h>
// #include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

  if (argc != 4) {
    std::cout << "Incorrect number of command line arguments." << '\n';
    std::cout << "Command line should be in the following format:" << '\n';
    std::cout << "filename.txt intM intN" << '\n';
    return 0;
  }

  if (!((*argv[2] == '0') || (*argv[2] == '6'))) {
    std::cout << "intM can only be 0 or 6" << '\n';
    return 0;
  }

  if (!((*argv[3] == '1') || (*argv[3] == '2'))) {
    std::cout << "intN can only be 1 or 2" << '\n';
    return 0;
  }

  ifstream myReadFile;
  myReadFile.open(argv[1]);
  int m = atoi(argv[2]);
  int n = atoi(argv[3]);

  BranchHistory branchsim = BranchHistory(m, n);
  float result = branchsim.makePrediction(myReadFile);

  myReadFile.close();
  return 0;
}
