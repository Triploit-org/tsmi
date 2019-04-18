all:
	if [ ! -d bin/ ]; then mkdir bin/; fi
	g++ -static -static-libstdc++ -static-libgcc -w main.cpp -o bin/tsmi

windows:
	i686-w64-mingw32-g++ -static -static-libstdc++ -static-libgcc -w main.cpp -o bin/tsmiw.exe

linux:
	g++ -static -static-libstdc++ -static-libgcc -w main.cpp -o bin/tsmil
