#include "stats.h"
#include <iomanip>
#include <iostream> 
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

// Uses the "linear interpolation between closest ranks" method (type 7 in R).
// This matches NumPy's default: numpy.percentile(data, p, interpolation='linear')
// P75 of [2,4,4,4,5,5,7,9] returns 5.5, not 6.0.
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

Vector<double> z_score_normalise(const Vector<double>& v){
	//thinking...... mf
	if (v.size() == 0 ) return Vector<double>::zeros(0);
	double sd = stddev(v);
	double m = mean(v);
	if (sd == 0.0){
		throw std::runtime_error("Cannot Z-score normalise a vector with zero standard deviation");
	}
	Vector<double> result(v.size());
	std::transform(
		v.begin(),
		v.end(),
		result.begin(),
		[m, sd](double x){
			return (x - m)/ sd;
	});

	return result;
	
}

std::vector<int> histogram(const Vector<double>& v, int bins){
	if (v.size() == 0 || bins <= 0) return std::vector<int>();
	double lo = min_val(v);
	double hi = max_val(v);
	double bin_width = (hi - lo) / bins;
	std::vector<int> result(bins, 0);
	if (hi == lo){
		result[0] = v.size();
		return result;
	}

	for (double x : v){
		int bin_idx = static_cast<int>((x - lo) / bin_width);

		if (bin_idx >= bins){
      			bin_idx = bins - 1;
		}
		result[bin_idx]++;
	}
	return result;
}

void print_summary(const Vector<double>& v){
	//string bc = "█";
	// 1. Gather all statistical data points
	//std::size_t n = v.size();
	double m     = mean(v);
	double sd    = stddev(v);
	double min_v = min_val(v);
	double max_v = max_val(v);
	double med   = median(v);
	double p25   = percentile(v, 0.25);
	double p75   = percentile(v, 0.75);
	// Set precision to 3 decimal places for floating points
	std::cout << std::fixed << std::setprecision(3);
	std::cout << std::left << std::setw(12) << "Mean"   << ": " << m     << "\n";
	std::cout << std::left << std::setw(12) << "Stddev" << ": " << sd    << "\n";
	std::cout << std::left << std::setw(12) << "Min"    << ": " << min_v << "\n";
	std::cout << std::left << std::setw(12) << "Max"    << ": " << max_v << "\n";
	std::cout << std::left << std::setw(12) << "Median" << ": " << med   << "\n";
	std::cout << std::left << std::setw(12) << "P25"    << ": " << p25   << "\n";
	std::cout << std::left << std::setw(12) << "P75"    << ": " << p75   << "\n";
	int num_bins = 4;
	std::vector<int> counts = histogram(v, num_bins);
	std::cout << "Histogram (" << num_bins << " bins):\n";
	double bin_width = (max_v - min_v) / num_bins;
	for (int i = 0; i < num_bins; ++i){
		double bin_start = min_v + i * bin_width;
        	double bin_end = bin_start + bin_width;
		std::cout << "[";
		std::cout << std::setw(5) << std::setprecision(1) << bin_start;
		std::cout << " - ";
		std::cout << std::setw(5) << std::setprecision(1) << bin_end;
		// Match standard notation: last bin closing bracket is inclusive ']'
		if (i == num_bins - 1) {
		    std::cout << "] | ";
		} else {
		    std::cout << ") | ";
		}

		// Build the visual block string. 
		// If using '█' gives your terminal encoding issues, swap it out for "#" or "*"!
		std::string bar(counts[i] * 2, '#'); 
		std::cout << std::left << std::setw(10) << bar << " | " << counts[i] << "\n";
	}
}
