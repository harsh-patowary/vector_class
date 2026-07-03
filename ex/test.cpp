#include <iostream>
#include <memory>
using namespace std;


template <typename T> T dot(T* a, T* b, int n){
	T result{};
	for (int i=0;i<n;i++){
		result += a[i] * b[i];
	}
	return result;
}




class Person {
private:
	int *age;
public:
	string name;

	Person(string n, int a) {
		name = n;
		age = new int(a);
	}

    	Person(const Person& other) {
        	name = other.name;
		if(other.age != nullptr){
			age = new int(*(other.age));
		} else {
			age = nullptr;
		}
    	}

	~Person(){
		delete age;
	}
	int get_age() const {
		if(age != nullptr){
			return *age;
		}
		return 0;
	}

	friend ostream& operator<<(ostream& os, const Person& p) {
		os << "Name: " << p.name << ", Age: " << p.get_age();
		return os;
	}
};

class Number{
public:
	int *value;
	Number(int x) {
		value = new int(x);
	}
	~Number(){
		delete value;
	}
	Number(const Number& other){
		value = new int(*other.value);
	}
	
	Number operator+(Number n){
		return Number(*value + *n.value);
	}

	int getValue() const{
		return *value;
	}
	friend ostream& operator<<(ostream& os, const Number& n){
		os << n.getValue();
		return os;
	}
	
};

int main() {
	Person p1("Rick", 18);
	Person p2("John", 20);
	cout << p1 << endl;
	cout << p2 << endl;
	Number a(5);
	cout << a << endl;
	Number b(7);
	cout << b << endl;
	Number c = a + b;
	cout << c << endl;

	int n = 3;
    
    	// 1. Create float arrays and call dot()
    	float f1[] = {1.0f, 2.0f, 3.0f};
    	float f2[] = {4.0f, 5.0f, 6.9f};
    	// Call your function here and print the result
    	float result1 = dot(f1, f2, n);
	cout << "Dot Product (floats): " << result1 << endl;
    	// 2. Create double arrays and call dot()
    	double d1[] = {1.0, 2.0, 3.0};
    	double d2[] = {4.0, 5.0, 6.9};
    	// Call your function here and print the result
	double result2 = dot(d1, d2, n);
	cout << "Dot Product (double): " << result2 << endl;
	return 0;
}
