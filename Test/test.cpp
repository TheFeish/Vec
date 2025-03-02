#include "pch.h"
#include "../Vector/Vector.h"
#include <vector>
using std::vector;
using std::move;

template<class T>
void isEq(vector<T> vector, Vec<T> vec, bool testCapacity) {
	EXPECT_EQ(vector.size(), vec.size());
	if (testCapacity) { EXPECT_EQ(vector.capacity(), vec.capacity()); }
	if (vector.size() == vec.size()) {
		for (int i = 0; i < vec.size(); i++) {
			EXPECT_EQ(vector[i], vec[i]);
		}
	}
}

TEST(VectorConstrutorTesting, DefaultConstructor) {
	vector<int> vector;
	Vec<int> vec;
	isEq(vector, vec, false);
}

TEST(VectorConstrutorTesting, FillConstructor) {
	vector<int> vector(10, 14);
	Vec<int> vec(10, 14);
	isEq(vector, vec, false);
}

TEST(VectorConstrutorTesting, RangeConstructor) {
	vector<int> init(10, 14);
	vector<int> vector(init.begin(), init.end());
	Vec<int> vec(init.begin(), init.end());
	isEq(vector, vec, false);
}

TEST(VectorConstrutorTesting, CopyConstructor) {
	vector<int> vector1(10, 14);
	vector<int> vector2(vector1);

	Vec<int> vec1(10, 14);
	Vec<int> vec2(vec1);

	EXPECT_EQ(vec1 == vec2, true);
	isEq(vector2, vec2, false);
}

TEST(VectorConstrutorTesting, MoveConstructor) {
	vector<int> vector1(10, 14);
	vector<int> vector2(move(vector1));

	Vec<int> vec1(10, 14);
	Vec<int> vec2(move(vec1));

	isEq(vector1, vec1, true);
	isEq(vector2, vec2, false);
}

TEST(VectorDestructorTesting, DefaultDestructor) {
	vector<int> vector(10, 14);
	Vec<int> vec(10, 14);
	vector.~vector();
	vec.~Vec();
	isEq(vector, vec, true);
}

TEST(VectorAssignmentTesting, CopyAssignment) {
	vector<int> vector1(10, 14);
	vector<int> vector2 = vector1;

	Vec<int> vec1(10, 14);
	Vec<int> vec2 = vec1;

	EXPECT_EQ(vec1 == vec2, true);
	isEq(vector2, vec2, false);
}

TEST(VectorAssignmentTesting, MoveAssignment) {
	vector<int> vector1(10, 14);
	vector<int> vector2 = move(vector1);

	Vec<int> vec1(10, 14);
	Vec<int> vec2 = move(vec1);

	isEq(vector1, vec1, true);
	isEq(vector2, vec2, false);
}

TEST(VectorIteratorTesting, BeginIterator) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(*vector.begin(), *vec.begin());
	EXPECT_EQ(*(vector.begin() + 1), *(vec.begin() + 1));
}

TEST(VectorIteratorTesting, CbeginIterator) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(*vector.cbegin(), *vec.cbegin());
	EXPECT_EQ(*(vector.cbegin() + 1), *(vec.cbegin() + 1));
}

TEST(VectorIteratorTesting, EndIterator) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(*(vector.end() - 1), *(vec.end() - 1));
	EXPECT_EQ(*(vector.end() - 2), *(vec.end() - 2));
}

TEST(VectorIteratorTesting, CendIterator) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(*(vector.cend() - 1), *(vec.cend() - 1));
	EXPECT_EQ(*(vector.cend() - 2), *(vec.cend() - 2));
}

TEST(VectorIteratorTesting, RbeginIterator) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(*vector.rbegin(), *vec.rbegin());
	EXPECT_EQ(*(vector.rbegin() + 1), *(vec.rbegin() + 1));
}

TEST(VectorIteratorTesting, CrbeginIterator) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(*vector.crbegin(), *vec.crbegin());
	EXPECT_EQ(*(vector.crbegin() + 1), *(vec.crbegin() + 1));
}

TEST(VectorIteratorTesting, RendIterator) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(*(vector.rend() - 1), *(vec.rend() - 1));
	EXPECT_EQ(*(vector.rend() - 2), *(vec.rend() - 2));
}

TEST(VectorIteratorTesting, CrendIterator) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(*(vector.crend() - 1), *(vec.crend() - 1));
	EXPECT_EQ(*(vector.crend() - 2), *(vec.crend() - 2));
}

TEST(VectorCapacityTesting, SizeAndResizeFunction) {
	vector<int> vector(10, 14);
	Vec<int> vec(10, 14);

	vector.resize(5, 15);
	vec.resize(5, 15);
	isEq(vector, vec, false);
	EXPECT_EQ(vector.size(), vec.size());

	vector.resize(15, 15);
	vec.resize(15, 15);
	isEq(vector, vec, false);
	EXPECT_EQ(vector.size(), vec.size());
}

TEST(VectorCapacityTesting, CapacityAndReserveFunction) {
	vector<int> vector(10, 14);
	Vec<int> vec(10, 14);

	vector.reserve(5);
	vec.reserve(5);
	isEq(vector, vec, true);
	EXPECT_EQ(vector.capacity(), vec.capacity());

	vector.reserve(15);
	vec.reserve(15);
	isEq(vector, vec, true);
	EXPECT_EQ(vector.capacity(), vec.capacity());
}
TEST(VectorCapacityTesting, EmptyFunction) {
	vector<int> vector1;
	Vec<int> vec1;
	vector<int> vector2(10, 14);
	Vec<int> vec2(10, 14);

	EXPECT_EQ(vector1.empty(), vec1.empty());
	EXPECT_EQ(vector2.empty(), vec2.empty());
}

TEST(VectorCapacityTesting, Shrink_to_fitFunction) {
	vector<int> vector(10, 14);
	Vec<int> vec(10, 14);

	vector.reserve(15);
	vec.reserve(15);

	vector.shrink_to_fit();
	vec.shrink_to_fit();

	EXPECT_EQ(vector.capacity(), vec.capacity());
}

TEST(VectorElementAccessTesting, ElementAccessOperator) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(vector[5], vec[5]);

	vector[5] = 0;
	vec[5] = 0;
	isEq(vector, vec, false);
}

TEST(VectorElementAccessTesting, AtFunction) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(vector.at(5), vec.at(5));
}

TEST(VectorElementAccessTesting, FrontFunction) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(vector.front(), vec.front());
}

TEST(VectorElementAccessTesting, BackFunction) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	EXPECT_EQ(vector.back(), vec.back());
}

TEST(VectorElementAccessTesting, DataFunction) {
	vector<int> vector;
	Vec<int> vec;
	for (int i = 0; i < 15; i++) {
		vector.push_back(i);
		vec.push_back(i);
	}

	int* vectorData = vector.data();
	int* vecData = vector.data();

	for (int i = 0; i < vec.size(); i++) {
		EXPECT_EQ(vectorData[i], vecData[i]);
	}
}

TEST(VectorModifierTesting, AssignFunction) {
	vector<int> init(10, 14);
	vector<int> vector;
	Vec<int> vec;

	vector.assign(init.begin(), init.end());
	vec.assign(init.begin(), init.end());

	isEq(vector, vec, false);

	vector.assign(15, 9);
	vec.assign(15, 9);

	isEq(vector, vec, false);
}

TEST(VectorModifierTesting, Push_backFunction) {
	vector<int> vector(10, 14);
	Vec<int> vec(10, 14);

	vector.push_back(15);
	vec.push_back(15);

	isEq(vector, vec, false);
}

TEST(VectorModifierTesting, Pop_backFunction) {
	vector<int> vector(10, 14);
	Vec<int> vec(10, 14);

	vector.pop_back();
	vec.pop_back();

	isEq(vector, vec, false);
}

TEST(VectorModifierTesting, InsertFunction) {
	vector<int> rangeTest(10, 9);

	vector<int> initVector(10, 14);
	Vec<int> initVec(10, 14);

	vector<int> vector = initVector;
	Vec<int> vec = initVec;
	vector.insert(vector.begin() + 5, 15);
	vec.insert(vec.begin() + 5, 15);
	isEq(vector, vec, false);

	vector = initVector;
	vec = initVec;
	vector.insert(vector.begin() + 5, 5, 9);
	vec.insert(vec.begin() + 5, 5, 9);
	isEq(vector, vec, false);

	vector = initVector;
	vec = initVec;
	vector.insert(vector.begin() + 5, rangeTest.begin(), rangeTest.end());
	vec.insert(vec.begin() + 5, rangeTest.begin(), rangeTest.end());
	isEq(vector, vec, false);
}

TEST(VectorModifierTesting, EraseFunction) {
	vector<int> initVector(10, 14);
	Vec<int> initVec(10, 14);

	vector<int> vector = initVector;
	Vec<int> vec = initVec;
	vector.erase(vector.begin() + 5);
	vec.erase(vec.begin() + 5);
	isEq(vector, vec, false);

	vector = initVector;
	vec = initVec;
	vector.erase(vector.begin() + 3, vector.begin() + 7);
	vec.erase(vec.begin() + 3, vec.begin() + 7);
	isEq(vector, vec, false);
}

TEST(VectorModifierTesting, SwapFunction) {

	vector<int> vector1(10, 14);
	Vec<int> vec1(10, 14);
	vector<int> vector2(14, 10);
	Vec<int> vec2(14, 10);

	vector1.swap(vector2);
	vec1.swap(vec2);

	isEq(vector1, vec1, false);
	isEq(vector2, vec2, false);
}

TEST(VectorModifierTesting, ClearFunction) {
	vector<int> vector(10, 14);
	Vec<int> vec(10, 14);

	vector.clear();
	vec.clear();

	isEq(vector, vec, false);
}

TEST(VectorRelationalOperatorsTesting, EqualityOperator) {
	vector<int> vector1;
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector<int> vectorLess(vector1);
	vectorLess[1] = 1;
	vector<int> vectorGreater(vector1);
	vectorGreater[1] = 3;
	vector<int> vectorEqual(vector1);
	Vec<int> vec1(vector1.begin(), vector1.end());
	Vec<int> vecLess(vectorLess.begin(), vectorLess.end());
	Vec<int> vecGreater(vectorGreater.begin(), vectorGreater.end());
	Vec<int> vecEqual(vectorEqual.begin(), vectorEqual.end());

	EXPECT_EQ(vector1 == vectorLess, vec1 == vecLess);
	EXPECT_EQ(vector1 == vectorGreater, vec1 == vecGreater);
	EXPECT_EQ(vector1 == vectorEqual, vec1 == vecEqual);
}

TEST(VectorRelationalOperatorsTesting, UnequalityOperator) {
	vector<int> vector1;
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector<int> vectorLess(vector1);
	vectorLess[1] = 1;
	vector<int> vectorGreater(vector1);
	vectorGreater[1] = 3;
	vector<int> vectorEqual(vector1);
	Vec<int> vec1(vector1.begin(), vector1.end());
	Vec<int> vecLess(vectorLess.begin(), vectorLess.end());
	Vec<int> vecGreater(vectorGreater.begin(), vectorGreater.end());
	Vec<int> vecEqual(vectorEqual.begin(), vectorEqual.end());

	EXPECT_EQ(vector1 != vectorLess, vec1 != vecLess);
	EXPECT_EQ(vector1 != vectorGreater, vec1 != vecGreater);
	EXPECT_EQ(vector1 != vectorEqual, vec1 != vecEqual);
}

TEST(VectorRelationalOperatorsTesting, LessOperator) {
	vector<int> vector1;
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector<int> vectorLess(vector1);
	vectorLess[1] = 1;
	vector<int> vectorGreater(vector1);
	vectorGreater[1] = 3;
	vector<int> vectorEqual(vector1);
	Vec<int> vec1(vector1.begin(), vector1.end());
	Vec<int> vecLess(vectorLess.begin(), vectorLess.end());
	Vec<int> vecGreater(vectorGreater.begin(), vectorGreater.end());
	Vec<int> vecEqual(vectorEqual.begin(), vectorEqual.end());

	EXPECT_EQ(vector1 < vectorLess, vec1 < vecLess);
	EXPECT_EQ(vector1 < vectorGreater, vec1 < vecGreater);
	EXPECT_EQ(vector1 < vectorEqual, vec1 < vecEqual);
}

TEST(VectorRelationalOperatorsTesting, GreaterOperator) {
	vector<int> vector1;
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector<int> vectorLess(vector1);
	vectorLess[1] = 1;
	vector<int> vectorGreater(vector1);
	vectorGreater[1] = 3;
	vector<int> vectorEqual(vector1);
	Vec<int> vec1(vector1.begin(), vector1.end());
	Vec<int> vecLess(vectorLess.begin(), vectorLess.end());
	Vec<int> vecGreater(vectorGreater.begin(), vectorGreater.end());
	Vec<int> vecEqual(vectorEqual.begin(), vectorEqual.end());

	EXPECT_EQ(vector1 > vectorLess, vec1 > vecLess);
	EXPECT_EQ(vector1 > vectorGreater, vec1 > vecGreater);
	EXPECT_EQ(vector1 > vectorEqual, vec1 > vecEqual);
}

TEST(VectorRelationalOperatorsTesting, LessOrEqualOperator) {
	vector<int> vector1;
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector<int> vectorLess(vector1);
	vectorLess[1] = 1;
	vector<int> vectorGreater(vector1);
	vectorGreater[1] = 3;
	vector<int> vectorEqual(vector1);
	Vec<int> vec1(vector1.begin(), vector1.end());
	Vec<int> vecLess(vectorLess.begin(), vectorLess.end());
	Vec<int> vecGreater(vectorGreater.begin(), vectorGreater.end());
	Vec<int> vecEqual(vectorEqual.begin(), vectorEqual.end());

	EXPECT_EQ(vector1 <= vectorLess, vec1 <= vecLess);
	EXPECT_EQ(vector1 <= vectorGreater, vec1 <= vecGreater);
	EXPECT_EQ(vector1 <= vectorEqual, vec1 <= vecEqual);
}

TEST(VectorRelationalOperatorsTesting, GreaterOrEqualOperator) {
	vector<int> vector1;
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector<int> vectorLess(vector1);
	vectorLess[1] = 1;
	vector<int> vectorGreater(vector1);
	vectorGreater[1] = 3;
	vector<int> vectorEqual(vector1);
	Vec<int> vec1(vector1.begin(), vector1.end());
	Vec<int> vecLess(vectorLess.begin(), vectorLess.end());
	Vec<int> vecGreater(vectorGreater.begin(), vectorGreater.end());
	Vec<int> vecEqual(vectorEqual.begin(), vectorEqual.end());

	EXPECT_EQ(vector1 >= vectorLess, vec1 >= vecLess);
	EXPECT_EQ(vector1 >= vectorGreater, vec1 >= vecGreater);
	EXPECT_EQ(vector1 >= vectorEqual, vec1 >= vecEqual);
}