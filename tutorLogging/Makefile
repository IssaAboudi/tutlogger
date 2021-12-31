tutlogger: main.o Files/files_linux.o Files/files_windows.o
	g++ *.o -o tutoring.sh

main.o: main.cpp DebugMode.hpp
	g++ -c main.cpp

Files/files_linux.o: Files/files_linux.cpp
	g++ -c Files/files_linux.cpp

Files/files_windows.o: Files/files_windows.cpp
	g++ -c Files/files_windows.cpp

