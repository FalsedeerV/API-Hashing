#include <iostream>
#include <string>
#include "FNV-1a.hpp"

namespace FNV {

	// contructor & destuctor
	FNV_1a::FNV_1a()
	{}
	
	FNV_1a::~FNV_1a()
	{}

	// DESC: The Fnv1 hash computing function
	uint64_t FNV_1a::Compute(const std::string &data, const std::string &salt) {
    	uint64_t hash{FNV_OFFSET_BASIS};
    	std::string combined_data{data + salt};

    	/* Since we combined the salt with the actual data,
    	   so now it will only need to perform the hashing for once, not needing to do it twice for data and salt, 
    	   and later combining it for return.
    	   
    	   And the design of combining the salt and data for hashing can effectivly add some collision resistence to it, 
    	   Consider a scenario where two different salt-data combinations produce the same intermediate hash after the salt is processed. 
    	   If those two combinations are then followed by the same data string, they will produce the same final hash. 
    	   However, if we combine the data with the salt and then do the hasing, 
    	   they will certain result in differ data. */
    	for (char c : combined_data) {
        	hash ^= c;
        	hash *= FNV_PRIME;
    	}

    	return hash;
	}
}