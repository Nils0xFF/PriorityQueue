#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Random.h"

using namespace std;

Random::Random(int r )
{
	max_range = r;
	fill_mask = 0;
	fill_bits = 0;
	/* determine no. of bits required */
	if (max_range > RAND_MAX) {
		int req_padding = (max_range / RAND_MAX);
		//cout << "Required padding is: " << req_padding << endl;
		int cur_padding = 1;
		while (cur_padding < req_padding) {
			cur_padding = cur_padding << 1;
			fill_mask = fill_mask << 1;
			fill_mask += 1;
			fill_bits++;
		}
	}
	//cout << "No. of fill bits is: " << fill_bits << endl;
	//cout << "Fill mask is: " << fill_mask << endl;
	//srand(clock());
	srand (12);
}

Random::~Random()
{
}

int Random::give()
{
	int value = rand();
	int sec_value = rand();

	for (int i = 1; i <= fill_bits; i++) {
		value = value << 1;
	}	
	value += (sec_value &&  fill_mask);
	return (value % max_range);
}