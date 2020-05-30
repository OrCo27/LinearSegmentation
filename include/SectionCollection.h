#ifndef SECTIONS_H
#define SECTIONS_H

#include <string>
#include <unordered_map>
#include "Utils.h"
using namespace std;

class SectionCollection
{
private:
	string file_name;
	int ngram_size;
	int section_size;
	/* Vocabulary map contains ngram word as key, and index number as value */
	unordered_map<string, int> vocab_map;
	/* Sections vectors in input text, so each element is ngram vector */
	vector<vector<int>> sections_vectors;
	void BuildVocabulary(const string& input_text, size_t input_size);
	void BuildSections(const string& input_text, size_t input_size);

public:
	SectionCollection(const string& file_name, int section_size, int ngram_size);
	void BuildCollection();
	vector<int> GetSection(int index);
	size_t GetTotalSections();
	string GetFilePath();
};

#endif