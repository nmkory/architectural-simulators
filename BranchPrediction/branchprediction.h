#include <string>


struct predictor {
 // two-bit unsigned field,
 uint8_t twobits : 2;
};


class BranchHistoryTable {

	public:
    BranchHistoryTable();
    predictor* predictions;
};



class BranchHistory {

	public:
    BranchHistory(int m, int n);
		BranchHistoryTable *table;
    int globalHistory = 0;
    bool twoBit;
};
