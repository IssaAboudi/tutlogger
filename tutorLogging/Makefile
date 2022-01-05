tutlogger: main.o Files/files_linux.o Files/files_windows.o Files/files_all.o
	g++ *.o -o tutoring.sh

main.o: main.cpp DebugMode.hpp Files/files.hpp
	g++ -c main.cpp

Files/files_linux.o: Files/files_linux.cpp
	g++ -c Files/files_linux.cpp

Files/files_windows.o: Files/files_windows.cpp
	g++ -c Files/files_windows.cpp

Files/files_all.o: Files/files_all.cpp
	g++ -c Files/files_all.cpp
