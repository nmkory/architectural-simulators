#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>

using namespace std;


class Block {
public:
  short valid = 0;
  int tag = 0;
  friend ostream& operator<<(ostream& os, const Block& blk) {
      os << "Block: " << blk.valid << " - Tag: " << blk.tag;
      return os;
  };
};


class Cache {
public:
  int hits = 0;
  int misses = 0;
  list <Block> **sets;
  Cache(int ways, int sets);
  void search(int setNum, int tagNum);
};


class CacheSim {
public:
  int cacheSize;
  int ways;
  int blockSizeInBytes;
  int sets;
  int cacheSizeInBlocks;
  int numTagBits;
  int numIndexBits;
  int numOffsetBits;
  Cache *cache;
  CacheSim(int cacheSize, int blockSize, int numWays);
  void runSim(ifstream &myReadFile);
};
