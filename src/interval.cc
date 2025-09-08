#include "interval.h"
#include "common.h"

double interval::size() const { return max - min; }
bool interval::contains(double x) const { return min <= x && x <= max; }
bool interval::surrounds(double x) const { return min < x && x < max; }

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
