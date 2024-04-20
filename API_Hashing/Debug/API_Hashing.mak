################################################################################
# [Aug.31.2023.17:27:00]                                                       #
#                                 API_Hashing                                  #
#                                                                              #
#                                             Saturday 20 April 2024, 18:14:17 #
################################################################################

##### GROUPS ###################################################################

FG00=\
	FNV-1a.o\
	API-Hashmap.o\
	Main.o


##### BUILD ####################################################################

ALL: $(FG00)
	g++ -mconsole -o API_Hashing.EXE $(FG00) -lstdc++ -lkernel32 -user32 -lgdi32 -lcomctl32 -lcomdlg32

API_Hashing.EXE: $(FG00)
	g++ -mconsole -o API_Hashing.EXE $(FG00) -lstdc++ -lkernel32 -user32 -lgdi32 -lcomctl32 -lcomdlg32


##### COMMANDS #################################################################

run:  API_Hashing.EXE
	API_Hashing.EXE

debug:  API_Hashing.EXE
	gdb API_Hashing.EXE

peview:  API_Hashing.EXE
	uetools -pe API_Hashing.EXE

makef: 
	uestudio API_Hashing.mak


##### COMPILE ##################################################################

FNV-1a.o: ..\FNV-1a.cpp
	g++ -c -I "C:\MinGW\Include" -ggdb -O0 -o FNV-1a.o ..\FNV-1a.cpp


API-Hashmap.o: ..\API-Hashmap.cpp
	g++ -c -I "C:\MinGW\Include" -ggdb -O0 -o API-Hashmap.o ..\API-Hashmap.cpp


Main.o: ..\Main.cpp
	g++ -c -I "C:\MinGW\Include" -ggdb -O0 -o Main.o ..\Main.cpp



##### CLEAN ####################################################################

CLEAN:
	-@erase "FNV-1a.o"
	-@erase "API-Hashmap.o"
	-@erase "Main.o"
	-@erase "API_Hashing.EXE"

