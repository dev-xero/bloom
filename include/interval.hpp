#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "common.hpp"

class Interval {
  public:
    double min_, max_;

    // for an empty interval min > max, which is mathematically
    // impossible
    Interval() : min_(+infinity), max_(-infinity) {}
    Interval(double min, double max) : min_(min), max_(max) {}

    double Size() const;
    double Clamp(double x) const;
    bool Contains(double x) const;
    bool Surrounds(double x) const;

    static const Interval empty, universe;
};

#endif
