#pragma once

class Boundary
{
private:
    bool active;

public:
    int index;
    double score;

    Boundary(int index, double score);
    void DisableBoundary();
    bool IsActive();
};