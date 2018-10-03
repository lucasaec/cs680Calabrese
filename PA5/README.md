# PA5: Loading Objects with Assimp

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev
```
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


### Makefile Instructions 
The makefile works as expected and must be updated with new files added in. ./Tutorial without command line arguments will not load any objects. Please see below in this Readme file to know how to use the command line arguments and load objects.

```bash
mkdir build
cd build
cp ../makefile .
make
./Tutorial
```

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial
```
# How to load an object
Place object files in the objects folder. Place material files in the objects folder. They should be download when the repository is cloned.
See "Text Input" to know what to do next.

## Text Input
Run the code like this:
Example:
```./Tutorial```

The program will then ask you to give it a file name. Enter the file name of the object you want to load. For example:

Please enter a file name

```box2.obj```

The program will then ask you to enter 0 or 1. If you want a random color enter 1. If you want one of the object's material colors enter 0.

Would you like the input to be random? Enter 1 for yes 0 for no

```1 ```



# Extra Credit
To load materials place materials in the objects folder. 
After following the build instructions run the code like this:
Example:
```./Tutorial```

You will be prompted for the file name. In the terminal, Type dragon.obj or box2.obj and press enter to enter a file name.

Example:

Please enter a file name

```box2.obj```


The program will then ask you to enter 0 or 1. If you want a random color enter 1. If you want one of the object's material colors enter 0. Enter 0 and then press enter in the terminal to load the object's material.

Would you like the input to be random? Enter 1 for yes 0 for no

```0 ```

### Group Members
Andrew Flangas

Christina Symon

Lucas Calabrese
