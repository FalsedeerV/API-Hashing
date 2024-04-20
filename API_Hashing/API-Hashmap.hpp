// This is a Singleton class for handling the hashtable and parsing &  creation for API-Hashing 
// Map: [Function Hash] => Function Address

#ifndef API_HASHING
#define API_HASHING

#include <vector>
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <windows.h>

namespace API_Hashmap {
	
	// ----------------- ENUM CLASS ---------------
	
	// For choosing the dll to interact with
	enum class Library : int {
		
		KERNEL32 = 1 << 0,
		USER32 = 1 << 1,
		GDI32 = 1 << 2,
		ADVAPI32 = 1 << 3,
		SHELL32 = 1 << 4,
		COMCTL32 = 1 << 5,
		COMDLG32 = 1 << 6,
		MSVCRT = 1 << 7,
		WS2_32 = 1 << 8,
		NTDLL = 1 << 9,
		ALL = 1 << 10
	};
	
	// since enum class is type-safe, so we need manual operator overloading
	inline Library operator|(Library lib1, Library lib2) {
		return static_cast<Library>(static_cast<int>(lib1) | static_cast<int>(lib2));
	}
	
	inline Library operator&(Library lib1, Library lib2) {
		return static_cast<Library>(static_cast<int>(lib1) & static_cast<int>(lib2));
	}
	
	// -------------- HASHMAP CLASS ----------------
	
	// macro auto invoke
	#define INVOKE_API(func_ptr, ...) func_ptr(__VA_ARGS__)
	
	// some typedef to make your life easier
	using Map = std::unordered_map<uint64_t, void*>;
	using Table = std::unordered_map<Library, Map>;
	
	// Main class for interacting with
	class Hashmap {
	
	private:
		// private constructor
		Hashmap();
	
		// member
		inline static bool Is_Cleaned = false;
		inline static bool Is_Init = false;
		inline static bool Collision = false;
		inline static std::string Salt;
		inline static Library DLL_Libs;
		inline static Table HashTable;
		inline static std::vector<HMODULE> list_hdlrs;
	
		// method
		void Create_HashTable(void);	
		std::optional<Map> Create_HashMap(std::string DLL_Name);
		Map Compute_HashChunk(const std::vector<std::string>& name_chunk, const std::vector<void *>& addr_chunk);
	
	public:
		// declare to remain singleton
		Hashmap(const Hashmap& instance) = delete;
		void operator=(const Hashmap& instance) = delete;
		
		// public destructor
		~Hashmap();
		
		// method
		static void Initialize(const Library libs, const std::string& salt);
		static FARPROC Resolve_HashedAPI(Library module, uint64_t hash);
		static Hashmap& Get_Instance(void);
		static bool If_Collision(void);
		static uint64_t Hash(std::string api_name);
		static void Debug(std::string dll_name);
		static void Cleanup(void);
	};
}

#endif