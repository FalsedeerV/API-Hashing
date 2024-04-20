/* I choose the FNV-1a for this project is because this algorithm have more collision resistence then DJB2, ROR13, 
   even though it is slightly slower do to the multiplication operation during hashing, however I think it's acceptable.
   and I deliberately avoid ROR13 is because of Metasploit implementing this for their shellcode, 
   which had gained lot of notice from AV vender. 
   
   Also, I used 64-bit version of FNV-1a for the implementation, 
   which have better collision resistence comparing to the 32 bit version. */

#ifndef FNV_ALGORITHM
#define FNV_ALGORITHM 

#include <cstdint>

namespace FNV {
	 
	 class FNV_1a {
	 
	 private:
	 	// Some data for initializing the FNV-1a Algorithm of 64 bit output
	 	static const uint64_t FNV_PRIME = 0x100000001B3;
	 	static const uint64_t FNV_OFFSET_BASIS = 0xCBF29CE484222325;
	 		 
	 public:
	 	FNV_1a();
	 	~FNV_1a();
	 	static uint64_t Compute(const std::string& data, const std::string& salt);
	 };
}

#endif