#include <iostream>
#include <windows.h>
#include "API-Hashmap.hpp"

using namespace API_Hashmap;
using PTR_MSGBOXA = int (WINAPI *)(HWND, LPCSTR, LPCSTR, UINT);

// EP
int main(int argc, char* argv[]) {
	
	// try
	Hashmap::Initialize(Library::USER32, "Hello World");
	if (Hashmap::If_Collision()) {
		
		std::cerr << "[WARNING] Collision Occured ! Change the salt please !!" << std::endl;
	} else {
		
		std::cout << "[TRACE] Nice, no collision from the chosen salt." << std::endl;
	}
	
	// do a hash on messageboxa, and query it
	uint64_t hash = Hashmap::Hash("MessageBoxA");
	void *ptr_func = (void *)Hashmap::Resolve_HashedAPI(Library::USER32, hash);
	std::cout << std::endl << "[DEBUG] The hash of MessageBoxA: " << hash << std::endl;
	std::cout << "[DEBUG] Resolved address of hashed MessageBoxA: " << ptr_func << std::endl;
	
	// try invoke it
	PTR_MSGBOXA func = (PTR_MSGBOXA)ptr_func;
	func(nullptr, "YOU CAN'T SEE ME IN IAT !!", "EVASION :)", MB_OK);

	// Exit gracefully
	std::cout << std::endl << "[TRACE] The program exit gracefully...." << std::endl;
	return 0;
}
