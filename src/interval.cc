#include "interval.hpp"
#include "common.hpp"

double Interval::Size() const { return max_ - min_; }

double Interval::Clamp(double x) const {
    if (x < min_)
        return min_;
    if (x > max_)
        return max_;
    return x;
}

bool Interval::Contains(double x) const { return min_ <= x && x <= max_; }

bool Interval::Surrounds(double x) const { return min_ < x && x < max_; }

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);
