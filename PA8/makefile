# Check for OS Type
UNAME_S := $(shell uname -s)

# Linux
ifeq ($(UNAME_S), Linux)
	CC=g++
	LIBS=-lSDL2 -lGLEW -lGL -lassimp -I/usr/include/bullet -lBulletDynamics -lBulletSoftBody -lBulletCollision –lLinearMath
# Mac
else
	CC=clang++
	LIBS=-lSDL2 -framework OpenGL -framework Cocoa -lGLEW -stdlib=libc++ -lassimp
endif

# Paths, use this to set Include directories, or library directories; uncomment in all: if used
#PATHI=-I/usr/local/include/ 
#PATHL=-L/usr/local/lib/

#Compiler Flags
CXXFLAGS=-g -Wall -std=c++0x

# .o Compilation
O_FILES=main.o camera.o engine.o graphics.o object.o shader.o window.o shaderLoader.o

# Point to includes of local directories
INDLUDES=-I../include


all: $(O_FILES)
	$(CC) $(CXXFLAGS) -o Tutorial $(O_FILES) $(LIBS) #$(PATHI) $(PATHL)

main.o: ../src/main.cpp
	$(CC) $(CXXFLAGS) -c ../src/main.cpp -o main.o $(INDLUDES)

camera.o: ../src/camera.cpp
	$(CC) $(CXXFLAGS) -c ../src/camera.cpp -o camera.o $(INDLUDES)

engine.o: ../src/engine.cpp
	$(CC) $(CXXFLAGS) -c ../src/engine.cpp -o engine.o $(INDLUDES)

graphics.o: ../src/graphics.cpp
	$(CC) $(CXXFLAGS) -c ../src/graphics.cpp -o graphics.o $(INDLUDES)

object.o: ../src/object.cpp
	$(CC) $(CXXFLAGS) -c ../src/object.cpp -o object.o $(INDLUDES)

shader.o: ../src/shader.cpp
	$(CC) $(CXXFLAGS) -c ../src/shader.cpp -o shader.o $(INDLUDES)

window.o: ../src/window.cpp
	$(CC) $(CXXFLAGS) -c ../src/window.cpp -o window.o $(INDLUDES)

shaderLoader.o: ../src/shaderLoader.cpp
	$(CC) $(CXXFLAGS) -c ../src/shaderLoader.cpp -o shaderLoader.o $(INDLUDES)

clean:
	-@if rm *.o Tutorial 2>/dev/null || true; then echo "Main Removed"; else echo "No Main"; fi
