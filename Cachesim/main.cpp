#include <iostream>
#include <fstream>
#include "cachesim.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

  if (argc != 5) {
    std::cout << "Incorrect number of command line arguments." << '\n';
    std::cout << "Command line should be in the following format:" << '\n';
    std::cout << "filename.txt intTotalCacheSizeInKilobytes intCacheBlockSizeInBytes intNumOfWays" << '\n';
    return 0;
  }

  ifstream myReadFile;
  myReadFile.open(argv[1]);
  int cacheSize = atoi(argv[2]) * 1024;
  int blockSize = atoi(argv[3]);
  int numWays  = atoi(argv[4]);


  CacheSim cachesim = CacheSim(cacheSize, blockSize, numWays);
  cachesim.runSim(myReadFile);

  myReadFile.close();
  return 0;
}
