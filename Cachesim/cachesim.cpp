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
    //print cache
    // for (auto it = sets[i]->cbegin(); it != sets[i]->cend(); it++) {
    //     cout << " | " << *it << " | ";
    // }
    // cout << "\n";
  }
};


void Cache::search(int setNum, int tagNum) {
  Block recentlyUsed;
  recentlyUsed.valid = 1;
  recentlyUsed.tag = tagNum;

  for (auto it = sets[setNum]->cbegin(); it != sets[setNum]->cend(); it++) {
      if ((*it).tag == tagNum) {
        hits++;
        sets[setNum]->erase(it);
        sets[setNum]->emplace_front(recentlyUsed);
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


int CacheSim::createSetMask(int numIndexBits) {
  int setMask = 0;
  for (int i = 0; i < numIndexBits; i++) {
    setMask <<= 1;
    setMask |= 1;
  }
  return setMask;
}


void CacheSim::runSim(ifstream &myReadFile) {
  string ins;  //instruction
  int insOffset;  //instruction offset
  unsigned long long memAddr; //memory address
  int setNum;
  int tagNum;
  float missRate;
  int setMask = createSetMask(numIndexBits);

  //cout << setMask << '\n';

  while((myReadFile >> ins).good()) {
      myReadFile >> insOffset;
      myReadFile >> hex >> memAddr;
      memAddr += insOffset;
      memAddr = (memAddr & 0xFFFFFFFF);
      tagNum = memAddr >> (numIndexBits + numOffsetBits);
      setNum = (memAddr >> numOffsetBits) & setMask;
      cache->search(setNum, tagNum);
  }

  missRate = (cache->misses) / (cache->misses + cache->hits);

  // std::cout << cache->misses << '\n';
  // std::cout << cache->hits << '\n';

  cout << fixed << setprecision(2);
  cout << "Miss rate: " << missRate << '\n';
  cout << "Hit rate: " << 1 - missRate << '\n';
  cout << "# of sets: " << sets << '\n';
  cout << "# of ways: " << ways << '\n';
  cout << "# of tag bits: " << numTagBits << '\n';
  cout << "# of index bits: " << numIndexBits << '\n';
  cout << "# of offset bits: " << numOffsetBits << '\n';
}
