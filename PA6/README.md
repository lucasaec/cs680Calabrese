# PA6: Loading Objects with Assimp

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev

```
This Project uses imagemagick
I followed this tutorial: (https://linuxconfig.org/how-to-install-imagemagick-7-on-ubuntu-18-04-linux)  to do this.
I also used: 
sudo apt-get install libmagick++-dev
It works on the ECC ubuntu machine since they already have it downloaded.

Also, the cmake file is the one that was posted on canvas
### Ubuntu/Linux

This project uses Assimp

### Ubuntu/Linux
```bash
 sudo apt-get install libassimp-dev assimp-utilsev
```

### Mac OSX
Installation of brew is suggested to easily install the libs. Ensure that the latest version of the Developer Tools is installed.
```bash
brew install assimp
```

## Building and Running
To build this project there are two options. One is to use CMake which makes including new libraries easier, and handles new files added automatically to the src and include directory. CMake is a small new learning curve but makes things easier in the future.
The second option is to use the provided Makefile which is used as usual.

Running the make in a separate directory will allow easy cleanup of the build data, and an easy way to prevent unnecessary data to be added to the git repository.  

### CMake Instructions
Please don't use cmake. please just use the makefile
```bash
mkdir build
cd build
cmake ..
make
./Buddha
```

### Makefile Instructions 
Please use cmake


## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Buddha
```
# How to load an object
Make sure that  the objects folder has the following files: buddha.obj, buddha.mtl, checker.jpg, and granite.jpg.
Then run the program

# Extra Credit
There was no extra credit for this assignment

### Group Members
Andrew Flangas

Christina Symon

Lucas Calabrese
