#ifndef STATS_H
#define STATS_H

#include "Vector.h"
#include <vector>
#include <numeric>   // Crucial for accumulate and inner_product
#include <algorithm> // Crucial for min/max elements
#include <cmath>     // Crucial for sqrt

// 1. Mean (Average)
double mean(const Vector<double>& v);

double median(const Vector<double>& v);


// 2. Variance (Spread of data)
double variance(const Vector<double>& v);

// 3. Standard Deviation
double stddev(const Vector<double>& v);

// 4. Minimum Value
double min_val(const Vector<double>& v);

// 5. Maximum Value
double max_val(const Vector<double>& v);

// 6. Percentile
//
//
// Uses the "linear interpolation between closest ranks" method (type 7 in R).
// This matches NumPy's default: numpy.percentile(data, p, interpolation='linear')
// P75 of [2,4,4,4,5,5,7,9] returns 5.5, not 6.0.
double percentile(const Vector<double>& v, double p);

Vector<double> z_score_normalise(const Vector<double>& v);

std::vector<int> histogram(const Vector<double>& v, int bins);

void print_summary(const Vector<double>& v);

#endif
