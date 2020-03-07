#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>

using namespace std;


class Block {
  short valid = 0;
  int tag = 0;
  friend ostream& operator<<(ostream& os, const Block& blk) {
      os << "Block: " << blk.valid << " - Tag: " << blk.tag;
      return os;
  };
};



class Cache {
public:
  list <Block> **sets;
  Cache(int ways, int sets);
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
};
