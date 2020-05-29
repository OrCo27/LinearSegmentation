#include "Boundary.h"

Boundary::Boundary(int index, double score)
{
    this->index = index;
    this->score = score;
    this->active = true;
}

void Boundary::DisableBoundary()
{
    this->active = false;
}

bool Boundary::IsActive()
{
    return active;
}