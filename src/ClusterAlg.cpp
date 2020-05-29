#include "ClusterAlg.h"

ClusterAlg::ClusterAlg(const SectionCollection& _sections, int min_cluster, double sim_threshold)
	: sections(_sections), sim(sections), left_seg(&sim), right_seg(&sim)
{	
    this->min_cluster = min_cluster;
    this->sim_threshold = sim_threshold;

    /* Set initial boundaries of each segment */
    left_seg.SetSegment(0, min_cluster);
    right_seg.SetSegment(min_cluster, 2 * min_cluster);
}

double ClusterAlg::CalcObjectiveFunction()
{
	double obj_func;
	obj_func = (left_seg.GetInternalScore() + right_seg.GetInternalScore()) / 2.0;
	return obj_func;
}

void ClusterAlg::RemoveSimilarBoundaries()
{
    int start_index = 0;
    int curr_boundary_index, next_boundary_index;
    double boundary_score;

    // final passing to remove boundaries with similar clusters 
    for (int i = 0; i < result.size() - 1; i++)
    {
        curr_boundary_index = result[i].index;
        next_boundary_index = result[i+1].index;

        // set segments boundaries
        left_seg.SetSegment(start_index, curr_boundary_index);
        right_seg.SetSegment(curr_boundary_index, next_boundary_index);

        // calc internal similarity score for each segment
        left_seg.CalcInternalScore();
        right_seg.CalcInternalScore();

        boundary_score = CalcObjectiveFunction();

        // inactive boundary that pass the threshold
        if (boundary_score > sim_threshold)
            result[i].DisableBoundary();

        start_index = curr_boundary_index;
    }

    // remove inactive boundaries from list
    result.erase(remove_if(result.begin(), result.end(), [](Boundary& x) { return !x.IsActive(); }), result.end());
}

void ClusterAlg::DivideFirstClustering()
{
    double potential_boundary_score, curr_boundary_score;
    bool has_improvment = false;
    Segment left_max(&sim), right_max(&sim);

    // calculate internal score only for left segment
    // right segment will update next
    left_seg.CalcInternalScore();

    // not reached to end
    while ((right_seg.GetEndIndex() + min_cluster) <= sections.GetTotalSections())
    {
        // calculate internal scores for right segment
        right_seg.CalcInternalScore();

        // calculate the boundary score as the sum of both segments
        potential_boundary_score = CalcObjectiveFunction();

        // reset max segments to current segments
        left_max = left_seg;
        right_max = right_seg;

        do
        {
            has_improvment = false;  // reset for searching next improvment
            int start_index = right_seg.GetStartIndex() + 1;
            int end_index = right_seg.GetEndIndex();

            // pass over missed boundaries on the second segment for finding better score
            for (int i = start_index; i < end_index; i++)
            {
                // expanding first segment
                left_seg.ExpandSegment();

                // shifting right the second segment
                right_seg.ShiftRightSegment();

                curr_boundary_score = CalcObjectiveFunction();

                // current boundary has better score
                if (curr_boundary_score > potential_boundary_score)
                {
                    // save max boundary score
                    potential_boundary_score = curr_boundary_score;

                    // save max segments
                    left_max = left_seg;
                    right_max = right_seg;

                    // remember that we improve objective function
                    has_improvment = true;
                }
            }

            // reset segments to max matching
            left_seg = left_max;
            right_seg = right_max;
        } while (has_improvment);

        // there is no improvment -> save this boundary
        result.push_back(Boundary(left_seg.GetEndIndex(), potential_boundary_score));

        // set the new pairs segments and update boundary to next min cluster
        left_seg = right_seg;
        right_seg.SetSegment(left_seg.GetEndIndex(), left_seg.GetEndIndex() + min_cluster);
    }
}

vector<Boundary> ClusterAlg::GetClustersResult()
{
    return result;
}

void ClusterAlg::PerformClustering()
{
    /* First clustering division */
    DivideFirstClustering();

    /* Last passing on division for removing similar segments */
    RemoveSimilarBoundaries();
}