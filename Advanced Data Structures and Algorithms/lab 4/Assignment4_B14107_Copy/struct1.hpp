#ifndef INFO_H
#define INFO_H

#include "vector.hpp"
#include<stdlib.h>
#include<string.h>
#include<cstring>

using namespace std;
using namespace abc;

namespace abc{

	typedef struct hash21
	{
		vector<string> key;
		vector<string> value;
		int probe;
		int capacity;
	} hash1;
}
#endif
