#include <iostream>
#include "Vector.h"
#include <string>
#include <chrono>
#include <iomanip>
using std::cout;
using std::endl;
using std::string;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::fixed;

#include <vector>;
using std::vector;

const unsigned int sz = 100000000;  // 100000, 1000000, 10000000, 100000000
const unsigned int loops = 1;

int main() {
	double allTime = 0;
	int reallocations = 0;
	for (int x = 0; x < loops; x++) {
		vector<int> v1;
		auto start = high_resolution_clock::now();
		for (int i = 1; i <= sz; ++i) {
			v1.push_back(i);
			if (v1.size() == v1.capacity()) { reallocations++; }
		}
		auto end = high_resolution_clock::now();
		auto time = duration<double>(end - start);
		allTime += time.count();
	}
	cout << "Vector " << sz << " element fill time: " << fixed << allTime / loops << "s. " << reallocations << " reallocations" << endl;
	
	allTime = 0;
	reallocations = 0;
	for (int x = 0; x < loops; x++) {
		Vec<int> v2;
		auto start = high_resolution_clock::now();
		for (int i = 1; i <= sz; ++i) {
			v2.push_back(i);
			if (v2.size() == v2.capacity()) { reallocations++; }
		}
		auto end = high_resolution_clock::now();
		auto time = duration<double>(end - start);
		allTime += time.count();
	}
	cout << "Vec " << sz << " element fill time: " << fixed << allTime / loops <<  "s. " << reallocations << " reallocations" << endl;
}