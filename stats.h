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
double percentile(const Vector<double>& v, double p);

Vector<double> z_score_normalise(const Vector<double>& v);

std::vector<int> histogram(const Vector<double>& v, int bins);

void print_summary(const Vector<double>& v);

#endif
