#include "Vector.h"
#include "stats.h"
#include <cassert>
#include <cmath>
#include <iostream>


// Helper to compare floating point numbers
bool approx_equal(double a, double b, double epsilon = 0.0001) {
    return std::abs(a - b) < epsilon;
}

int main(){
	Vector<int> original(3);
	original[0] = 10;
	original[1] = 20;
	original[2] = 30;

	Vector<int> copy = original;
	copy[0] = 999;

	std::cout << original << std::endl;
	std::cout << copy << std::endl;



	Vector<int> a(3);
	a[0] = 1; a[1] = 2; a[2] = 3;

	Vector<int> b = a;        // copy constructor
	b[0] = 99;
	std::cout << a << "\n";   // must print [1,2,3] — not [99,2,3]

	Vector<int> c(3);
	c = a;                    // copy assignment
	c[1] = 77;
	std::cout << a << "\n";   // must still print [1,2,3]

	a = a;                    // self-assignment — must not crash
	std::cout << a << "\n";   // must print [1,2,3]
	
	Vector<int> v(5);
	Vector<int> cel(5);
	v.fill(6); 
	cel.fill(7);
	std::cout <<"filled with 6" << v << std::endl;
	Vector<int> zero_vec = Vector<int>::zeros(5);
	std::cout << "Zeros: " << zero_vec << std::endl;
	Vector<int> one_vec = Vector<int>::ones(5);
	std::cout << "Ones: " << one_vec << std::endl;
	Vector<int> vec_add = Vector<int>::ones(5);
	Vector<int> result = v * 2;
	std::cout << result << std::endl;
	int scalar = v.dot(cel); 
	std::cout << "Dot product :" << v << " . " << cel << ": "<< scalar <<  std::endl ;
	//std::cout << scalar << std::endl;
	
	
	std::cout << "=== Running Phase 5 Tests (Norms & Utilities) ===" << std::endl;

    	// 1. Setup a test vector with mixed positive and negative numbers
    	// v = [3, -4, 0]
    	Vector<int> v2(3);
    	v2[0] = 3;
    	v2[1] = -4;
    	v2[2] = 0;
    	std::cout << "Test Vector v2: " << v2 << std::endl;

    	// 2. Test L1 Norm (Sum of absolute values: |3| + |-4| + |0| = 7)
    	int l1 = v2.l1_norm();
    	std::cout << "L1 Norm (Expected: 7): " << l1 << std::endl;
    	assert(l1 == 7);
	// 3. Test L2 Norm (Euclidean distance: sqrt(3^2 + (-4)^2 + 0^2) = sqrt(25) = 5.0)
	double l2 = v2.l2_norm();
    	std::cout << "L2 Norm (Expected: 5.0): " << l2 << std::endl;
    	assert(approx_equal(l2, 5.0));
	
	// 4. Test L-Infinity Norm (Max absolute value: max(|3|, |-4|, |0|) = 4)
    	int linf = v2.linf_norm();
    	std::cout << "L-infinity Norm (Expected: 4): " << linf << std::endl;
    	assert(linf == 4);

    	// 5. Test Normalize (Should return [3/5, -4/5, 0/5] -> [0.6, -0.8, 0.0])
    	Vector<double> unit_v = v2.normalize();
    	std::cout << "Normalized unit_v: " << unit_v << std::endl;
    	assert(approx_equal(unit_v[0], 0.6));
    	assert(approx_equal(unit_v[1], -0.8));
    	assert(approx_equal(unit_v[2], 0.0));

    	// Verify the length of the normalized vector is exactly 1.0
    	std::cout << "Length of unit_v (Expected: 1.0): " << unit_v.l2_norm() << std::endl;
    	assert(approx_equal(unit_v.l2_norm(), 1.0));

    	// 6. Edge Case: Test Zero Vector Protection
    	Vector<double> zero_v = Vector<double>::zeros(3);
    	std::cout << "\nTesting Zero Vector: " << zero_v << std::endl;
    
    	try {
        	std::cout << "Attempting to normalize zero vector..." << std::endl;
        	Vector<double> broken = zero_v.normalize();
        	std::cout << "❌ FAILED: Should have thrown an exception for zero vector!" << std::endl;
    	} catch (const std::runtime_error& e) {
        	std::cout << "✅ PASSED: Caught expected exception: " << e.what() << std::endl;
    	} catch (const std::invalid_argument& e) {
        	std::cout << "✅ PASSED: Caught expected exception: " << e.what() << std::endl;
    	}

    	std::cout << "\n=== All Phase 5 Tests Passed Successfully! ===" << std::endl;
	std::cout << "=== Phase 6: Move Semantics Tests ===\n";

    	// 1. Move constructor
    	Vector<int> move_vec(3);
    	move_vec[0] = 1; move_vec[1] = 2; move_vec[2] = 3;
    
    	Vector<int> moved_vec = std::move(move_vec);         // move constructor
    	std::cout << "Moved-into moved_vec: " << moved_vec << "\n";   // [1,2,3]
    	assert(moved_vec[0] == 1 && moved_vec[1] == 2 && moved_vec[2] == 3);
    	assert(move_vec.size() == 0);                // a must be empty, not dangling
	
	
	
	// 2. Move assignment
	Vector<int> move_ass_vec(3);
    	move_ass_vec[0] = 7; move_ass_vec[1] = 8; move_ass_vec[2] = 9;

    	Vector<int> moved_ass_vec(1);
	moved_ass_vec= std::move(move_ass_vec);// move assignment — moved_ass_vec had existing memory
    	std::cout << "Moved-into moved_ass_vec: " << moved_ass_vec << "\n";   // [7,8,9]
    	assert(moved_ass_vec[0] == 7 && moved_ass_vec[1] == 8 && moved_ass_vec[2] == 9);
    	assert(move_ass_vec.size() == 0);                // must be empty

    	// 3. Move from a temporary (most common real-world case)
    	Vector<int> e = Vector<int>::ones(4); // temporary → move constructor
    	std::cout << "From temporary: " << e << "\n"; // [1,1,1,1]

    	// 4. Valgrind will catch double-free if move left other in bad state
    	std::cout << "\n=== All Phase 6 Tests Passed ===\n";
	
	//5. Testing Iterator
	for (auto x : moved_ass_vec) std::cout << x << " , ";
	
	const Vector<int> const_vec = moved_ass_vec;
	for (auto x : const_vec) std::cout << x << " ";  // must compile — uses const begin()/end()
	std::cout << "\n";	
		

	//STATS TEST DRIVE CODE

	

	Vector<double> data(5);
	data[0] = 2.0; data[1] = 4.0; data[2] = 4.0; data[3] = 4.0; data[4] = 5.5;

	std::cout << "Data: " << data << std::endl;
	std::cout << "Mean: " << mean(data) << " (Expected: 3.9)" << std::endl;
	std::cout << "Min: " << min_val(data) << " (Expected: 2.0)" << std::endl;
	std::cout << "Max: " << max_val(data) << " (Expected: 5.5)" << std::endl;

	// Variance calculation: 
	std::cout << "Variance: " << variance(data) << std::endl;	

    	return 0; 
}
