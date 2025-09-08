#ifndef INTERVAL_H
#define INTERVAL_H

#include "common.h"

class interval {
  public:
    double min, max;

    // for an empty interval min > max, which is mathematically
    // impossible
    interval() : min(+infinity), max(-infinity) {}
    interval(double min, double max) : min(min), max(max) {}

    double size() const;
    bool contains(double x) const;
    bool surrounds(double x) const;

    static const interval empty, universe;
};

#endif
