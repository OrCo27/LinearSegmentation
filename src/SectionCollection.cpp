#include "SectionCollection.h"

SectionCollection::SectionCollection(const string& file_name, int section_size, int ngram_size)
{
	this->file_name = file_name;
    this->ngram_size = ngram_size;
    this->section_size = section_size;
}

void SectionCollection::BuildVocabulary(const string& input_text, size_t input_size)
{
    int word_index = 0;

    // Pass over each n-gram in text and add to vocabulary
    for (int i = 0; i <= input_size - ngram_size; i++)
    {
        string ngram_word = input_text.substr(i, ngram_size);

        // Current word not exists yet on vocabulary
        if (vocab_map.find(ngram_word) == vocab_map.end())
        {
            // Add current word to vocabulary
            vocab_map.insert(pair<string, int>(ngram_word, word_index));
            word_index++;
        }
    }
}

void SectionCollection::BuildSections(const string& input_text, size_t input_size)
{
    string ngram_word;
    int start_section, vocab_index, i;

    // Pass over each section in text and build ngram vector 
    for (start_section = 0; start_section <= input_size - section_size; start_section += section_size)
    {
        // Initialize a new ngram vector for current section
        vector<int> section_vector(vocab_map.size());

        // Pass over each ngram on current section
        for (i = start_section; i <= start_section + section_size - ngram_size; i++)
        {
            ngram_word = input_text.substr(i, ngram_size);
            vocab_index = vocab_map[ngram_word];
            section_vector[vocab_index]++;
        }

        // Save ngram vectors
        sections_vectors.push_back(section_vector);
    }
}

string SectionCollection::GetFilePath()
{
    return file_name;
}

size_t SectionCollection::GetTotalSections()
{
    return sections_vectors.size();
}

vector<int> SectionCollection::GetSection(int index)
{
    return sections_vectors[index];
}

void SectionCollection::BuildCollection()
{
    // Read input text and calculate fixed size
    string input_text = Utils::GetFileString(file_name, true);

    /* Cut the end of input for alignment to section size defined */
    size_t input_size = input_text.size() - (input_text.size() % section_size);

    /* Build vocabulary map of input text */
    BuildVocabulary(input_text, input_size);

    /* Build all sections in input text */
    BuildSections(input_text, input_size);
}