#ifndef CLUSTERALG_H
#define CLUSTERALG_H

#include "SectionCollection.h"
#include "Similarity.h"
#include "Segment.h"
#include "Boundary.h"
#include <unordered_map>
#include <algorithm>

#define EPS 0.01

using namespace std;

class ClusterAlg
{
private:
	SectionCollection sections;
	Similarity sim;
	Segment left_seg;
	Segment right_seg;
	vector<Boundary> boundaries_res;
	int min_cluster;
	double sim_threshold;
	double CalcObjectiveFunction();
	void RemoveSimilarBoundaries();
	void DivideFirstClustering();
	void CalcSimThreshold();

public:
	ClusterAlg(const SectionCollection& sections, int min_cluster, double sim_threshold);
	void PerformClustering();
	void SaveResultToFile();
	void AddToSummaryResultFile(ofstream& ofile);
	vector<Boundary> GetClustersResult();
};

#endif