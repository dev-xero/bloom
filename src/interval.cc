#include "interval.hpp"
#include "common.hpp"

double interval::size() const { return max - min; }
double interval::clamp(double x) const {
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}
bool interval::contains(double x) const { return min <= x && x <= max; }
bool interval::surrounds(double x) const { return min < x && x < max; }

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
