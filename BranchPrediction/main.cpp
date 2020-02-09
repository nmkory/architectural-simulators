#include <iostream>
#include <fstream>
#include "branchprediction.h"
// #include <stdlib.h>
// #include <stdio.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

  ifstream myReadFile;
  myReadFile.open(argv[1]);
  string pc;  //program counter
  string tont;  //taken or not taken
  while((myReadFile >> pc).good()) {
      myReadFile >> tont;
      cout << pc << tont << endl;
  };
  myReadFile.close();
  return 0;
}
