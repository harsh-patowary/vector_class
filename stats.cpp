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
double stddev(const Vector<double>& v){
	return std::sqrt(variance(v));
}
double median(const Vector<double>& V){
	if (V.size() == 0) return 0.0;
	Vector<double> v = V;
	if (v.size() % 2 != 0) {
		std::nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
		return v[v.size()/2];
	} else {

		std::nth_element(v.begin(), v.begin() + v.size() / 2, v.end());	
		std::nth_element(v.begin(), (v.begin() + ((v.size() / 2)-1)), v.end());
		return (v[(v.size()/2) - 1] + v[(v.size()/2)]) / 2.0;
	}

}
double percentile(const Vector<double>& v, double p){
	if (v.size() == 0) return 0.0;
	if(p < 0.0 || p > 1.0) throw std::invalid_argument("Percentile p must be between 0.0 and 1.0");
	Vector<double> copy = v;
		
	std::sort(copy.begin(), copy.end());

	// Calculate virtual fractional index
	double virtual_idx = p * (copy.size() - 1);

	std::size_t lower_idx = static_cast<std::size_t>(std::floor(virtual_idx));
	std::size_t upper_idx = static_cast<std::size_t>(std::ceil(virtual_idx));

	// If it lands exactly on a whole index, return it directly
	if (lower_idx == upper_idx) {
	return copy[lower_idx];
	}

	// Otherwise, perform Linear Interpolation:
	double fraction = virtual_idx - lower_idx;
	return copy[lower_idx] + fraction * (copy[upper_idx] - copy[lower_idx]);
}

