#include "stats.h"
#include <numeric>   // For std::accumulate
#include <algorithm> // For std::min_element

// The actual implementations go here!
double mean(const Vector<double>& v) {
    if (v.size() == 0) return 0.0;
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double min_val(const Vector<double>& v) {
	return *std::min_element(v.begin(), v.end());
}

double max_val(const Vector<double>& v){
	return *std::max_element(v.begin(), v.end());
}

double variance(const Vector<double>& V){
	//double mean = mean(V);
	auto sum = std::inner_product(V.begin(), V.end(), V.begin(), 0.0); 
	return ( sum / V.size() ) - (mean(V) * mean(V));
}
