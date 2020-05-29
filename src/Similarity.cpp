#include "Similarity.h"

Similarity::Similarity(const SectionCollection& _sections) : sections(_sections)
{
}

double Similarity::GetStoredScore(int first_index, int second_index)
{
    return sim_scores[first_index][second_index];
}

void Similarity::SaveScore(int first_index, int second_index, double score)
{
    sim_scores[first_index][second_index] = score;
}

double Similarity::CalcSimilarScore(int first_index, int second_index)
{
    vector<int> b1, b2;
    double sim_score;
    int volume_mul, scalar_mul = 0;
    int b1_volume = 0, b2_volume = 0;

    // Try to get a stored score
    sim_score = GetStoredScore(first_index, second_index);
    if (sim_score != 0)
    {
        return sim_score;
    }

    b1 = sections.GetSection(first_index);
    b2 = sections.GetSection(second_index);
    
    for (int i = 0; i < b1.size(); i++)
    {
        scalar_mul += b1[i] * b2[i];
        b1_volume += b1[i] * b1[i];
        b2_volume += b2[i] * b2[i];
    }

    volume_mul = b1_volume * b2_volume;

    sim_score = scalar_mul / sqrt(volume_mul);

    /* Save similarity score between both indexes for next usage */
    SaveScore(first_index, second_index, sim_score);

    return sim_score;
}