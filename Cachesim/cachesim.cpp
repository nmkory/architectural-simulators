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
    for (auto it = sets[i]->cbegin(); it != sets[i]->cend(); it++)
    {
        std::cout << *it << " | ";
    }
    cout << "\n";

  }


  // for (int i = 0; i < numSets; i++) {
  //   for (Block val : sets[i])
	// 	  cout << val;
  // }
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
