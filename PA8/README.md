# PA5: Loading Objects with Assimp

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

The cmakelists.txt file includes imagemagick so imagemagick may need to be installed.
I used: sudo apt-get install libbullet-dev
to install bullet.

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
The building of the project is done using CMake, installation with apt-get or brew may be necessary. Later use with CMake and Shader files will be require the copy of a directory where those files are stored (ex. shaders). To do this in the 

`
mkdir build

cd build

cmake ..

make

./BulletTest`


### Makefile Instructions 
Please use cmake

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial
```
# How to load an object
Place object files in the objects folder. They should be download when the repository is cloned.
See "Text Input" to know what to do next.

## Text Input
Run the code like this:
Example:
```./BulletTest```

The program will then ask you to give it a file name in terminal (so you can test the extra credit with the bowl). Enter the file name of the object you want to load. 

Please only choose "table4.obj" or "bowl.obj". table4 is for testing the regular requirements of the assignment, while the bowl is for testing the extra credit

## Keyboard Controls
up arrow - pushes cube forward with a force

left arrow - pushes cube left with a force

right arrow -pushes cube right with a force

down arrow -pushes cube backwards with a force

spacebar -pushes cube up with a force (towards the sky)

# Extra Credit
We added used triangle meshes for collision shapes for the table and the bowl. You can test the triangle meshes with the bowl.
The program will prompt you for a file to load in the terminal. You can use table4.obj or bowl.obj. Please note that there is a hole at the bottom of the bowl, so you may need to add an upwards force to push the cube out.

### Group Members
Andrew Flangas

Christina Symon

Lucas Calabrese
