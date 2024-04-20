#include <mutex>
#include <future>
#include <chrono>
#include <thread>
#include <iostream>
#include <optional>
#include <windows.h>
#include <stdexcept>
#include <unordered_map>
#include "FNV-1a.hpp"
#include "API-Hashmap.hpp"

namespace API_Hashmap
{	
	// private constructor, to control who can create instance
	Hashmap::Hashmap() {

		Create_HashTable();
	}
	
	// public destructor
	Hashmap::~Hashmap() {
		
		if (!Is_Cleaned) {
			
			// drop map content
			HashTable.clear();
			
			// free list of library's hmodule
			for (size_t i = 0; i < list_hdlrs.size(); i++) {
				
				FreeLibrary(list_hdlrs[i]);
			}
			
			// clean list
			list_hdlrs.clear();
		
			// mark as cleaned
			Is_Cleaned = true;
		}
	}
	
	// DESC: For initialization
	void Hashmap::Initialize(const Library libs, const std::string& salt) {
		
		DLL_Libs = libs;
		Salt = salt;
		Is_Init = true;
		return;
	}
	
	// DESC: The instance and initialize manager
	Hashmap& Hashmap::Get_Instance(void) {
		
		if (!Is_Init) {
		
			// throw exception since we must need something to create the hashmap
			throw std::runtime_error("Class must call function \"Initialize()\" before getting the instance of it !");
		}
		
		// if init, create a static instance for once only
		static Hashmap instance;
		return instance;
	}
	
	// DESC: The function to create mapping of all selected dll
	void Hashmap::Create_HashTable(void) {
		
		if ((DLL_Libs & Library::ALL) == Library::ALL) {
			
			std::cout << "[DEBUG] You selected All avalible library" << std::endl;
				
			auto kernel32_map = Create_HashMap("Kernel32.dll");
			auto user32_map = Create_HashMap("User32.dll");
			auto gdi32_map = Create_HashMap("Gdi32.dll");
			auto advapi32_map = Create_HashMap("Advapi32.dll");
			auto shell32_map = Create_HashMap("Shell32.dll");
			auto comctl32_map = Create_HashMap("Comctl32.dll");
			auto comdlg32_map = Create_HashMap("Comdlg32.dll");
			auto msvcrt_map = Create_HashMap("Msvcrt.dll");
			auto ws2_32_map = Create_HashMap("Ws2_32.dll");
			auto ntdll_map = Create_HashMap("Ntdll.dll");
			
			if (kernel32_map.has_value()) {
			
				HashTable[Library::KERNEL32] = kernel32_map.value();
			}
			if (user32_map.has_value()) {
				
				HashTable[Library::USER32] = user32_map.value();
			}
			if (gdi32_map.has_value()) {
				
				HashTable[Library::GDI32] = gdi32_map.value();
			}
			if (advapi32_map.has_value()) {
				
				HashTable[Library::ADVAPI32] = advapi32_map.value();
			}
			if (shell32_map.has_value()) {
				
				HashTable[Library::SHELL32] = shell32_map.value();
			}
			if (comctl32_map.has_value()) {
				
				HashTable[Library::COMCTL32] = comctl32_map.value();
			}
			if (comdlg32_map.has_value()) {
				
				HashTable[Library::COMDLG32] = comdlg32_map.value();
			}
			if (msvcrt_map.has_value()) {
				
				HashTable[Library::MSVCRT] = msvcrt_map.value();
			}
			if (ws2_32_map.has_value()) {
				
				HashTable[Library::WS2_32] = ws2_32_map.value();
			}
			if (ntdll_map.has_value()) {
				
				HashTable[Library::NTDLL] = ntdll_map.value();
			}
			
		} else {
			
			// If need Kernel32.dll hashmap
			if ((DLL_Libs & Library::KERNEL32) == Library::KERNEL32) {
				
				// debug
				std::cout << "[DEBUG] Selected Kernel32.dll" << std::endl;
				
				// create hashmap
				auto map = Create_HashMap("Kernel32.dll");
				if (map.has_value()) {
					HashTable[Library::KERNEL32] = map.value();	
				}
			}
			
			// If need User32.dll hashmap
			if ((DLL_Libs & Library::USER32) == Library::USER32) {
				
				// debug
				std::cout << "[DEBUG] Selected User32.dll" << std::endl;
				
				// create hashmap
				auto map = Create_HashMap("User32.dll");
				if (map.has_value()) {
					HashTable[Library::USER32] = map.value();	
				}
			}
			
			// If need Gdi32.dll hashmap
			if ((DLL_Libs & Library::GDI32) == Library::GDI32) {
				
				// debug
				std::cout << "[DEBUG] Selected Gdi32.dll" << std::endl;
				
				// create hashmap
				auto map = Create_HashMap("Gdi32.dll");
				if (map.has_value()) {
					HashTable[Library::GDI32] = map.value();	
				}
			}
			
			// If need Advapi32.dll hashmap
			if ((DLL_Libs & Library::ADVAPI32) == Library::ADVAPI32) {
				
				// debug
				std::cout << "[DEBUG] Selected Advapi32.dll" << std::endl;
				
				// create hashmap
				auto map = Create_HashMap("Advapi32.dll");
				if (map.has_value()) {
					HashTable[Library::ADVAPI32] = map.value();	
				}
			}
			
			// If need Shell32.dll hashmap
			if ((DLL_Libs & Library::SHELL32) == Library::SHELL32) {
				
				// debug
				std::cout << "[DEBUG] Selected Shell32.dll" << std::endl;
				
				// create hashmap
				auto map = Create_HashMap("Shell32.dll");
				if (map.has_value()) {
					HashTable[Library::SHELL32] = map.value();	
				}
			}
			
			// If need Comctl32.dll hashmap
			if ((DLL_Libs & Library::COMCTL32) == Library::COMCTL32) {
				
				// debug
				std::cout << "[DEBUG] Selected Comctl32.dll" << std::endl;
				
				// create hashmap
				auto map = Create_HashMap("Comctl32.dll");
				if (map.has_value()) {
					HashTable[Library::COMCTL32] = map.value();	
				}
			}
			
			// If need Comdlg.dll hashmap
			if ((DLL_Libs & Library::COMDLG32) == Library::COMDLG32) {
				
				// debug
				std::cout << "[DEBUG] Selected Comdlg32.dll" << std::endl;
				
				// create hashmap
				auto map = Create_HashMap("Comdlg32.dll");
				if (map.has_value()) {
					HashTable[Library::COMDLG32] = map.value();	
				}
			}
			
			// If need Msvcrt.dll hashmap
			if ((DLL_Libs & Library::MSVCRT) == Library::MSVCRT) {
				
				// debug
				std::cout << "[DEBUG] Selected Msvcrt.dll" << std::endl;
				
				// create hashmap
				auto map = Create_HashMap("Msvcrt.dll");
				if (map.has_value()) {
					HashTable[Library::MSVCRT] = map.value();	
				}
			}
			
			// If need Ws2_32.dll hashmap
			if ((DLL_Libs & Library::WS2_32) == Library::WS2_32) {
				
				// debug
				std::cout << "[DEBUG] Selected Ws2_32.dll" << std::endl;
				
				// create hashmap
				auto map = Create_HashMap("Ws2_32.dll");
				if (map.has_value()) {
					HashTable[Library::WS2_32] = map.value();	
				}
			}
			
			// If need Ntdll.dll hashmap
			if ((DLL_Libs & Library::NTDLL) == Library::NTDLL) {
				
				// debug
				std::cout << "[DEBUG] Selected Ntdll.dll" << std::endl;
				
				// create hashmap
				auto map = Create_HashMap("Ntdll.dll");
				if (map.has_value()) {
					HashTable[Library::NTDLL] = map.value();	
				}
			}
		}	
	}
	
	// DESC: Use single thread & parallelism to create a export function map of hash for a specific dll
	std::optional<Map> Hashmap::Create_HashMap(std::string dll_name) {
		Map localmap;
		HMODULE hdlr_dll;
		
		// timer start
		auto start = std::chrono::high_resolution_clock::now();
		
		// load the dll for parsing
		hdlr_dll = LoadLibrary(dll_name.c_str());
		
		// If succeed loading target DLL, start parsing
		if (!hdlr_dll) {
			
			std::cout << "Failed to load library: " << dll_name << std::endl;
			return std::nullopt;
		}
	
		// check if we got a valid dos header
		if (((IMAGE_DOS_HEADER*)hdlr_dll)->e_magic != IMAGE_DOS_SIGNATURE) {
        
        	// Error: Invalid DOS header
        	std::cout << "Invalid DOS Header" << std::endl;
        	return std::nullopt;
    	}
	
		// reach the image_nt_header by combining the base address (hmodule) and the e_lfanew
		IMAGE_NT_HEADERS *ptr_ntheader = (IMAGE_NT_HEADERS *)((BYTE*)hdlr_dll + ((IMAGE_DOS_HEADER *)hdlr_dll)->e_lfanew);
		
		// check if our extraced image nt header is valid
		if(ptr_ntheader->Signature != IMAGE_NT_SIGNATURE) {
    	
    		// Error: Invalid NT headers
    		std::cout << "Invalid NT Header" << std::endl;
    		return std::nullopt;
		}
		
		// reach the image_export_directory by addint the base address (hmodule) to the RVA of the export directory stored in image_directory_entry_export (optional header)
		IMAGE_EXPORT_DIRECTORY *ptr_exportdir = (IMAGE_EXPORT_DIRECTORY *)((BYTE *)hdlr_dll + ptr_ntheader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
		
		// Iterate throught the export functions
		std::cout << std::endl;
		std::cout << "[INFO] Detected " << ptr_exportdir->NumberOfNames << " number of names" << std::endl;
		std::cout << "[INFO] Detected " << ptr_exportdir->NumberOfFunctions << " number of functions" << std::endl;
		
		// locate the start of each array
		DWORD *ptr_name = (DWORD *)((BYTE *)hdlr_dll + ptr_exportdir->AddressOfNames);
		DWORD *ptr_address = (DWORD *)((BYTE *)hdlr_dll + ptr_exportdir->AddressOfFunctions);
		WORD *ptr_ordinal = (WORD *)((BYTE *)hdlr_dll + ptr_exportdir->AddressOfNameOrdinals);
		
		// for the function name, address storing in list for further parallel hashing in chunk for optimize
		/*std::vector<std::string> funcname_pool;
		std::vector<void *> funcaddr_pool;
		std::vector<std::future<Map>> future;*/
		
		// loop extracting the export table function
		for (int i = 0; i < ptr_exportdir->NumberOfNames; i++) {
			
			char *name = (char *)((BYTE *)hdlr_dll + ptr_name[i]);
			DWORD function_rva = ptr_address[ptr_ordinal[i]];
			void *ptr_function = (void *)(reinterpret_cast<uintptr_t>(hdlr_dll) + function_rva);
			
			
			// hash on the fly
			localmap[FNV::FNV_1a::Compute(name, Salt)] = ptr_function;
			
			/*// Add the current function name, address to vector for further hashing in paralell
			funcname_pool.push_back(name);
			funcaddr_pool.push_back (ptr_address);*/
		}
		
		/*// try to assign job to parallel thread workers for optimize
		size_t count_thread = std::thread::hardware_concurrency();
		size_t size_chunk = funcname_pool.size() / count_thread;
			
		// job assignment to thread workers
		for (size_t i = 0; i < count_thread; ++i) {
			
			auto name_begin = funcname_pool.begin() + i * size_chunk;
			auto name_end = (i == count_thread - 1) ? funcname_pool.end() : name_begin + size_chunk; 
			auto addr_begin = funcaddr_pool.begin() + i * size_chunk;
			auto addr_end = (i == count_thread - 1) ? funcaddr_pool.end() : addr_begin + size_chunk; 
			
			// push the task in vector, since the calling function is the same class member, so we'll need a lambda to do the magic
			future.push_back(std::async(std::launch::async, 
										[this](const std::vector<std::string>& names, const std::vector<void *>& addrs) {
   	 										return this->Compute_HashChunk(names, addrs);
										}, 
										std::vector<std::string>(name_begin, name_end),
										std::vector<void *>(addr_begin, addr_end)));
		}
		
		// receive the result from thread worker
		for (auto& result : future) {
			
			Map map_chunk = result.get();
			localmap.insert(map_chunk.begin(), map_chunk.end());
		}*/
		
		// check for collision
		if (localmap.size() != ptr_exportdir->NumberOfNames) {
			
			Collision = true;
		}
		
		// stop & show timer
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << std::endl << "Time Elapsed: " << duration.count() << " (microsecond)" << std::endl;
		std::cout << "--------------------------------------------------" << std::endl << std::endl;
		
		// cleanup
		list_hdlrs.push_back(hdlr_dll);
		return localmap;	
	}
	
	// DESC: Parallel hashing worker - Reserved for future usage if dataset gets bigger
	Map Hashmap::Compute_HashChunk(const std::vector<std::string>& name_chunk, const std::vector<void *>& addr_chunk) {
		Map localmap;

		for (size_t i = 0; i < name_chunk.size(); i++) {
		
			/*std::cout << "Func name: " << name_chunk[i] << std::endl;	
			std::cout << "Func hash: " << FNV::FNV_1a::Compute(name_chunk[i], Salt) << std::endl;
			std::cout << "Func address: " << addr_chunk[i] << std::endl << std::endl;*/
			
			// insert entry
			localmap[FNV::FNV_1a::Compute(name_chunk[i], Salt)] = addr_chunk[i];
		}
		
		return localmap;
	}
	
	// DESC: Resolve function from a hashed api
	FARPROC Hashmap::Resolve_HashedAPI(Library module, uint64_t hash) {
		
		// If the function is not initialized yet
		if (!Is_Init) {
			return nullptr;
		}
		
		// perform the search on the hashtable
		auto outer_iterator = HashTable.find(module);
		if (outer_iterator != HashTable.end()) {
			
			auto inner_iterator = (outer_iterator->second).find(hash);
			if (inner_iterator != (outer_iterator->second).end()) {
				
				return (FARPROC)inner_iterator->second;
				
			} else {
				
				return nullptr;
			}
			
		} else {
			
			return nullptr;
		}
	}
	
	// DESC: A helper to check for hash collision
	bool Hashmap::If_Collision(void) {
		
		// invoke get_instance to process the selected libs
		Hashmap& dummy = Get_Instance();
		return Collision;
	}
	
	// DESC: A rapid hashing function run by your salt
	uint64_t Hashmap::Hash(std::string api_name) {
		
		return FNV::FNV_1a::Compute(api_name, Salt);
	}
	
	// DESC: For Debug
	void Hashmap::Debug(std::string dll_name) {
		Map localmap;
		HMODULE hdlr_dll;
		
		// timer start
		auto start = std::chrono::high_resolution_clock::now();
		
		// load the dll for parsing
		hdlr_dll = LoadLibraryA(dll_name.c_str());
		
		// If succeed loading target DLL, start parsing
		if (!hdlr_dll) {
			
			std::cout << "Failed to load library: " << dll_name << std::endl;
			return;
		}
	
		// check if we got a valid dos header
		if (((IMAGE_DOS_HEADER*)hdlr_dll)->e_magic != IMAGE_DOS_SIGNATURE) {
        
        	// Error: Invalid DOS header
        	std::cout << "Invalid DOS Header" << std::endl;
        	return;
    	}
	
		// reach the image_nt_header by combining the base address (hmodule) and the e_lfanew
		IMAGE_NT_HEADERS64 *ptr_ntheader = (IMAGE_NT_HEADERS64 *)((BYTE*)hdlr_dll + ((IMAGE_DOS_HEADER *)hdlr_dll)->e_lfanew);
		
		// check if our extraced image nt header is valid
		if(ptr_ntheader->Signature != IMAGE_NT_SIGNATURE) {
    	
    		// Error: Invalid NT headers
    		std::cout << "Invalid NT Header" << std::endl;
    		return;
		}
		
		// reach the image_export_directory by addint the base address (hmodule) to the RVA of the export directory stored in image_directory_entry_export (optional header)
		IMAGE_EXPORT_DIRECTORY *ptr_exportdir = (IMAGE_EXPORT_DIRECTORY *)((BYTE *)hdlr_dll + ptr_ntheader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
		
		// Iterate throught the export functions
		std::cout << std::endl;
		std::cout << "[INFO] Detected " << ptr_exportdir->NumberOfNames << " number of names" << std::endl;
		std::cout << "[INFO] Detected " << ptr_exportdir->NumberOfFunctions << " number of functions" << std::endl << std::endl;
		
		// locate the start of each array
		DWORD *ptr_name = (DWORD *)((BYTE *)hdlr_dll + ptr_exportdir->AddressOfNames);
		DWORD *ptr_address = (DWORD *)((BYTE *)hdlr_dll + ptr_exportdir->AddressOfFunctions);
		WORD *ptr_ordinal = (WORD *)((BYTE *)hdlr_dll + ptr_exportdir->AddressOfNameOrdinals);
		
		// loop extracting the export table function
		for (int i = 0; i < ptr_exportdir->NumberOfNames; i++) {
			
			DWORD name_rva = ptr_name[i];
			char *name = (char *)((BYTE *)hdlr_dll + name_rva);
			DWORD function_rva = ptr_address[ptr_ordinal[i]];
			void *ptr_function = (void *)(reinterpret_cast<uintptr_t>(hdlr_dll) + function_rva);
			
			// hash on the fly
			std::cout << "Base Address: " << (void *)hdlr_dll << std::endl;
			std::cout << "Name: " << name << std::endl;
			std::cout << std::hex << "Name RVA: " << name_rva << std::endl;
			std::cout << std::hex << "Function RVA: " << function_rva << std::endl;
			std::cout << "Address: " << ptr_function << std::endl << std::endl;
		}
		
		
		// exit
		FreeLibrary(hdlr_dll);
		return;
	}
	
	// DESC: Manual free resource
	void Hashmap::Cleanup(void) {
		
		if (!Is_Cleaned) {
			
			// drop map content
			HashTable.clear();
			
			// free list of library's hmodule
			for (size_t i = 0; i < list_hdlrs.size(); i++) {
				
				FreeLibrary(list_hdlrs[i]);
			}
			
			// clean list
			list_hdlrs.clear();
			
			// mark as cleaned
			Is_Cleaned = true;
		}
	}
}