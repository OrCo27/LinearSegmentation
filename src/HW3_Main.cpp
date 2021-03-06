﻿#include <iostream>
#include <map>
#include "Utils.h"
#include "SectionCollection.h"
#include "ClusterAlg.h"

#define SECTION_SIZE 100
#define NGRAM_SIZE 3
#define MIN_CLUSTER 10
#define SIM_THRESHOLD 0.7

void WriteSummaryFileHeader(ofstream& ofile, vector<string> files_path)
{
    ofile << "Summary Of All Viruses In The Following Order: (";
    for (int i = 0; i < files_path.size(); i++)
    {
        string file_name = Utils::GetFileName(files_path[i]);
        ofile << file_name;

        if (i != files_path.size() - 1)
            ofile << ", ";
    }
    ofile << ")" << endl;
}

int main()
{
    vector<string> files_path = { "input/sc.fasta", "input/sars.fasta", "input/Mers.fasta" };
    string output_file = "output/summary.txt";
    ofstream ofile;
    
    ofile.open(output_file);

    /* Write to summary file the names as header */
    WriteSummaryFileHeader(ofile, files_path);

    /* Pass on each file an perform clustering algorithm */
    for (const string& file : files_path)
    {
        /* Build sections collection for current file */
        SectionCollection sections(file, SECTION_SIZE, NGRAM_SIZE);
        sections.BuildCollection();

        /* Perform clustering operation on current file */
        ClusterAlg alg(sections, MIN_CLUSTER, SIM_THRESHOLD);
        alg.PerformClustering();

        /* Save result to file */
        alg.SaveResultToFile();
        alg.AddToSummaryResultFile(ofile);
    }

    ofile.close();
}
