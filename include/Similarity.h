#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <unordered_map>
#include "SectionCollection.h"
using namespace std;

class Similarity
{
private:
	/* Two-dimensional key for pair indexes (i, j) and value as their score */
	unordered_map<int, unordered_map<int, double> > sim_scores;
	/* Section collection (const reference object) */
	SectionCollection sections;

	double GetStoredScore(int first_index, int second_index);
	void SaveScore(int first_index, int second_index, double score);

public:
	Similarity(const SectionCollection& sections);
	double CalcSimilarScore(int first_index, int second_index);
};

#endif