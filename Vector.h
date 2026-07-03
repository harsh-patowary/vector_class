#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
//using namespace std;

template<typename T>
class Vector;

template<typename U>
std::ostream& operator<<(std::ostream&, const Vector<U>& v);


template <typename T>
class Vector{
private:
	T* m_data; //Pointer to heap array
	std::size_t m_size; //Number of elements currently stored
	//int* dimension;
	
	//size_t m_capacity; //Total Capacity allocated
public:
	explicit Vector(std::size_t n);

	~Vector();

	Vector(const Vector& other);
	Vector<T>& operator=(const Vector& other);
	Vector<T> operator+(const Vector& other) const;
	Vector<T> operator-(const Vector& other) const;
	Vector<T> operator*(const T& scalar) const;
	T dot(const Vector<T>& other) const;
	T& operator[](std::size_t i);
	const T& operator[](std::size_t i) const;
	template<typename U>
	friend std::ostream& operator<<(std::ostream& os, const Vector<U>&);
	std::size_t size() const;
	void fill(T value);
	static Vector<T> zeros(std::size_t n);
	static Vector<T> ones(std::size_t n);
	T l1_norm() const;
	double l2_norm() const;
	T linf_norm() const;
	Vector<double> normalize() const;
	Vector(Vector&& other) noexcept;
	Vector<T>& operator=(Vector&& other) noexcept;
};

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept : m_data(other.m_data), m_size(other.m_size){
	other.m_size = 0;
	other.m_data = nullptr;
	
}
template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
	if (this == &other) return *this;
	delete[] m_data;
	m_data = other.m_data;
	m_size = other.m_size;
	other.m_size = 0;
	other.m_data = nullptr;
	return *this;
}


template<typename T>
T Vector<T>::l1_norm() const{
	T acc{};
	for(std::size_t i = 0; i < m_size; i++){
		acc += std::abs(m_data[i]);	
	}
	return acc;
}
template<typename T>
double Vector<T>::l2_norm() const{
	double sumSq = 0.0;
	for (std::size_t i = 0; i < m_size; i++){
		sumSq += static_cast<double>(m_data[i]) * static_cast<double>(m_data[i]);
	}
	return std::sqrt(sumSq);
}
template<typename T>
T Vector<T>::linf_norm() const{
	//T[] arr[m_size]{};
	T max_val = m_data[0];
	for(std::size_t i = 0; i < m_size; ++i){
		max_val = std::max(max_val, std::abs(m_data[i]));
	}

	return max_val;
}
template<typename T>
Vector<double> Vector<T>::normalize() const {
	
	double magnitude = l2_norm();
	if (magnitude == 0)  {throw std::runtime_error("cannot Normalize a Zero Vector");}
	Vector<double> normed_vec(m_size);
	
	for (std::size_t i = 0; i < m_size; ++i){
		normed_vec[i] = (static_cast<double>(m_data[i]) / magnitude);
	}
	return normed_vec;
}

template<typename T>
Vector<T>::Vector(std::size_t n)
    : m_data(new T[n]{}),  // {} zero-initialises every element
      m_size(n)
{
    // The body is empty because the initialiser list did the work.
    // new double[n]{} is equivalent to: allocate n doubles, set all to 0.0
    //
    // What's on the heap right now:
    //   data_ ──► [ 0.0 | 0.0 | 0.0 | ... | 0.0 ]  (n elements)
}
template<typename T>
Vector<T>::Vector(const Vector<T>& other) : m_data(new T[other.m_size]{}), m_size(other.m_size){ 
	//m_size = other.m_size; 
	//m_data = new T[m_size]{}; 
	for(std::size_t i = 0; i < other.m_size; i++){ 
		m_data[i] = other.m_data[i]; 
	} 
}
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other){
	if (this == &other) return *this;
	delete[] m_data;
	m_size = other.m_size;
	m_data = new T[m_size];
	for(std::size_t i = 0; i < other.m_size; i++){ 
		m_data[i] = other.m_data[i]; 
	}
	return *this;
}
template<typename T>
Vector<T> Vector<T>::operator+(const Vector& other) const {
	if (m_size == other.m_size) {
		Vector<T> results(other.m_size);
		for(std::size_t i = 0; i < m_size; ++i){
			results[i] = m_data[i] + other[i];
		}
		return results;
	} else throw std::invalid_argument("Vector sizes must match for addiction");
}
template<typename T>
Vector<T> Vector<T>::operator-(const Vector& other) const {
	if (m_size == other.m_size) {
		Vector<T> results(other.m_size);
		for(std::size_t i = 0; i < m_size; ++i){
			results[i] = m_data[i] - other[i];
		}
		return results;
	} else throw std::invalid_argument("Vector sizes must match for addiction");
}
template<typename T>
Vector<T> Vector<T>::operator*(const T& scalar) const {
	Vector<T> results(m_size);
	for(std::size_t i = 0; i < m_size; ++i){
		results[i] = m_data[i] * scalar;
	}
	return results;
}



template<typename T>
Vector<T>::~Vector(){
	delete[] m_data;
	m_data = nullptr;
}

template<typename T>
std::size_t Vector<T>::size() const {
	return m_size;
}
template<typename T>
T Vector<T>::dot(const Vector<T>& other) const{
	T scalar{};
	if (m_size == other.m_size){
		for (std::size_t i=0;i<m_size;++i){
			scalar += m_data[i] * other.m_data[i];
		}
		return scalar;
	} else throw std::invalid_argument("The vector dimensions are invalid for dot product");
}


template<typename T>
T& Vector<T>::operator[](std::size_t i){
	if (i >= m_size) throw std::out_of_range("Vector index out of range");
	return m_data[i];
}
template<typename T>
const T& Vector<T>::operator[](std::size_t i) const {
	if (i >= m_size) throw std::out_of_range("Vector index out of range");
	return m_data[i];
}


template<typename U>
std::ostream& operator<<(std::ostream& os, const Vector<U>& v) {
	os << "[";
	for (std::size_t i = 0; i < v.m_size; ++i) {
		os << v.m_data[i];
		if (i + 1 <v.m_size) os << ",";
	}
	os << "]";
	return os;
}

template<typename T>
void Vector<T>::fill(T value){
	for(std::size_t i = 0; i < m_size; ++i){
		m_data[i] = value;
	}
}

template<typename T>
Vector<T> Vector<T>::zeros(std::size_t n){
	Vector<T> v(n);
	return v;
}
template<typename T>
Vector<T> Vector<T>::ones(std::size_t n){
	Vector<T> v(n);
	v.fill(1);
	return v;
}
