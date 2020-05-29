#include <iostream>
#include <map>
#include "Utils.h"
#include "SectionCollection.h"
#include "ClusterAlg.h"

#define SECTION_SIZE 100 
#define NGRAM_SIZE 3
#define MIN_CLUSTER 10
#define SIM_THRESHOLD 0.7


int main()
{
    vector<string> files_path = { "input/sc.fasta", "input/sars.fasta", "input/Mers.fasta" };
    map<string, vector<Boundary>> clusters_result;
    vector<Boundary> result;

    for (const string& file : files_path)
    {
        /* Build sections collection for current file */
        SectionCollection sections(file, SECTION_SIZE, NGRAM_SIZE);
        sections.BuildCollection();

        /* Perform clustering operation on current file */
        ClusterAlg alg(sections, MIN_CLUSTER, SIM_THRESHOLD);
        alg.PerformClustering();

        /* Get vector result and save it into map files */
        result = alg.GetClustersResult();
        clusters_result[file] = result;
    }
}
