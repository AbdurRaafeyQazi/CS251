#include <vector>

using namespace std;

#ifdef COMPILED_FOR_GTEST
#define main original_main
#endif

double average(vector<int> v);
