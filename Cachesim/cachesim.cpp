#include "cachesim.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;


Cache::Cache(int ways, int numSets) {
  this->sets = new list <Block> *[numSets];
  for (int i = 0; i < numSets; i++) {
    sets[i] = new list <Block>(ways);
    for (auto it = sets[i]->cbegin(); it != sets[i]->cend(); it++) {
        cout << *it << " | ";
    }
    cout << "\n";
  }
};


void Cache::search(int setNum, int tagNum) {
  Block recentlyUsed;
  recentlyUsed.valid = 1;
  recentlyUsed.tag = tagNum;

  for (auto it = sets[setNum]->cbegin(); it != sets[setNum]->cend(); it++) {
      if ((*it).tag == tagNum) {
        hits++;
        sets[setNum]->emplace_front(recentlyUsed);
        sets[setNum]->erase(it);
        return;
      }
  }

  misses++;
  sets[setNum]->pop_back();
  sets[setNum]->emplace_front(recentlyUsed);
  return;
};


CacheSim::CacheSim(int cacheSize, int blockSize, int numWays) {
  this->cacheSize = cacheSize;
  blockSizeInBytes = blockSize;
  cacheSizeInBlocks = (cacheSize / blockSize);
  switch (numWays) {
    case 0:
      //fully	associative
      ways = cacheSizeInBlocks;
      sets = 1;
      break;
    case 1:
      //direct
      ways = 1;
      sets = cacheSize / blockSizeInBytes;
      break;
    default:
      //set	associative
      ways = numWays;
      sets = cacheSize / (blockSizeInBytes * ways);
  }
  numIndexBits = log2(sets);
  numOffsetBits = log2(blockSizeInBytes);
  numTagBits = 32 - numIndexBits - numOffsetBits;
  cache = new Cache(ways, sets);
}




void CacheSim::runSim(ifstream &myReadFile) {
  string ins;  //instruction
  int insOffset;  //instruction offset
  unsigned long long memAddr; //memory address
  int setNum;
  int tagNum;
  int setMask = 0;

  for (int i = 0; i < numIndexBits; i++) {
    setMask <<= 1;
    setMask |= 1;
  }

  std::cout << setMask << '\n';

  while((myReadFile >> ins).good()) {
      myReadFile >> insOffset;
      myReadFile >> hex >> memAddr;
      memAddr += insOffset;
      memAddr = (memAddr & 0xFFFFFFFF);
      tagNum = memAddr >> (numIndexBits + numOffsetBits);
      setNum = (memAddr >> numOffsetBits) & setMask;
      cache->search(setNum, tagNum);

  }
  std::cout << "hits:" << cache->hits << '\n';
  std::cout << "misses:" << cache->misses << '\n';
}
