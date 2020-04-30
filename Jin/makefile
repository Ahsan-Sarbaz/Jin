all: ./build/jin
 
./build/jin: pch.h.gch $(patsubst %.cpp, ./build/obj/%.o, $(wildcard *.cpp))
	g++ -g ./build/obj/*.o -o ./build/jin imgui.a -lGL -lGLEW -lglfw
	
pch.h.gch: pch.h
	g++ -x c++-header -c $< -o $@ -I/home/sarbaz/dev/imgui -I/home/sarbaz/dev/stb

./build/obj/%.o: %.cpp
	g++ -g -c $< -o $@ -I/home/sarbaz/dev/imgui -I/home/sarbaz/dev/stb
	
clean:
	rm -f ./build/jin ./build/obj/*.o
	
run:
	MESA_GL_VERSION_OVERRIDE=4.3 ./build/jin
