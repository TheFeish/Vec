# Vec
### Alternative to c++ vector class.
# Tests
## unit tests
Tested to produce same results to vector class.
### range constructor
``` c++
TEST(VectorConstrutorTesting, RangeConstructor) {
	vector<int> init(10, 14);
	vector<int> vector(init.begin(), init.end());
	Vec<int> vec(init.begin(), init.end());
	isEq(vector, vec, false);
}
```
### copy assignment
``` c++
TEST(VectorAssignmentTesting, CopyAssignment) {
	vector<int> vector1(10, 14);
	vector<int> vector2 = vector1;

	Vec<int> vec1(10, 14);
	Vec<int> vec2 = vec1;

	EXPECT_EQ(vec1 == vec2, true);
	isEq(vector2, vec2, false);
}
```
### size and resize functions
``` c++
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
```
### insert function
``` c++
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
```
### equality operator
``` c++
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
```
## Write times
| Class/Entry number | 10000     | 100000    | 1000000   | 10000000  | 100000000 |
|--------------------|-----------|-----------|-----------|-----------|-----------|
| vector             | 0.000020s | 0.000190s | 0.004111s | 0.057612s | 0.518634s |
| Vec                | 0.000013s | 0.000118s | 0.002602s | 0.041893s | 0.308240s |

vector was reallocated 46 time in 100000000 entries test.
Vec was reallocated 27 time in 100000000 entries test.
## Other execution times
Times got from using vector and Vec containers in a program that reads, splits, sorts and writes container data using 10000 entries.
| function\class      | vector    | Vec       |
|---------------------|-----------|-----------|
| Execution time      | 0.709096s | 0.770304s |
| File read time      | 0.437634s | 0.490140s |
| Entry split time    | 0.016121s | 0.017096s |
| Entry sort time     | 0.067816s | 0.072152s |
| write to file1 time | 0.092978s | 0.096783s |
| write to file2 time | 0.094548s | 0.094133s |
