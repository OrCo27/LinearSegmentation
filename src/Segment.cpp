#include "Segment.h"

Segment::Segment(Similarity *_sim) : sim(_sim)
{
    SetSegment(0, 0);
}

Segment& Segment::operator=(const Segment& other) {
    start_index = other.start_index;
    end_index = other.end_index;
    pairs_sim_sum = other.pairs_sim_sum;
    pairs_cnt = other.pairs_cnt;
    return *this;
}

int Segment::GetEndIndex()
{
    return end_index;
}

int Segment::GetStartIndex()
{
    return start_index;
}

void Segment::SetSegment(int start_index, int end_index)
{
    this->start_index = start_index;
    this->end_index = end_index;
    ResetScore();
}

void Segment::ResetScore()
{
    pairs_sim_sum = 0;
    pairs_cnt = 0;
}

void Segment::CalcInternalScore()
{
    for (int i = start_index; i < end_index; i++)
    {
        for (int j = i + 1; j < end_index; j++)
        {
            double sim_score = sim->CalcSimilarScore(i, j);
            pairs_sim_sum += sim_score;
            pairs_cnt++;
        }
    }
}

void Segment::ExpandSegment()
{
    // calc and add sim pairs only for the new one in left segment
    for (int j = start_index; j < end_index; j++)
    {
        pairs_sim_sum += sim->CalcSimilarScore(j, end_index);
        pairs_cnt++;
    }

    // expanding first segment
    end_index++;
}

void Segment::ShiftRightSegment()
{
    // calc and diff the sum pairs for new one in right segment
    for (int j = start_index + 1; j < end_index; j++)
    {
        pairs_sim_sum -= sim->CalcSimilarScore(start_index, j);
        pairs_sim_sum += sim->CalcSimilarScore(j, end_index);
    }

    // shifting right the second segment
    start_index++;
    end_index++;
}

double Segment::GetInternalScore() 
{
    return pairs_sim_sum / pairs_cnt;
}
