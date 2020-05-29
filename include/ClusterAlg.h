#pragma once

#include "SectionCollection.h"
#include "Similarity.h"
#include "Segment.h"
#include "Boundary.h"
#include <unordered_map>
using namespace std;

class ClusterAlg
{
private:
	SectionCollection sections;
	Similarity sim;
	Segment left_seg;
	Segment right_seg;
	vector<Boundary> result;
	int min_cluster;
	double sim_threshold;
	double CalcObjectiveFunction();
	void RemoveSimilarBoundaries();
	void DivideFirstClustering();

public:
	ClusterAlg(const SectionCollection& sections, int min_cluster, double sim_threshold);
	void PerformClustering();
	vector<Boundary> GetClustersResult();
};