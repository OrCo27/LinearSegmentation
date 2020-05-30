#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
#include "Similarity.h"
using namespace std;

class Segment
{
private:
	Similarity *sim;
	int start_index;
	int end_index;
	/* Sum of similarity scores of each pairs on current segment */
	double pairs_sim_sum;
	/* Count of all pairs in current segment */
	int pairs_cnt;
	void ResetScore();

public:
	Segment(Similarity *sim);
	Segment& operator=(const Segment& other);
	void SetSegment(int start_index, int end_index);
	int GetStartIndex();
	int GetEndIndex();
	void CalcInternalScore();
	void ExpandSegment();
	void ShiftRightSegment();
	double GetInternalScore();
};

#endif