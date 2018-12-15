# PA11: Open Project

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

Installation of these programs are required to run this project on the operating systems:  GLEW, GLM,  SDL2, ASSIMP, Bullet, SDL2_mixer, and ImageMagick

I used: sudo apt-get install libbullet-dev
to install bullet.

### Ubuntu/Linux
It works on the ECC ubuntu machine since they already have it downloaded.
```bash
sudo apt-get install libmagick++-dev
sudo apt-get install libassimp-dev assimp-utilsev
sudo apt-get install libglew-dev libglm-dev libsdl2-dev
sudo apt-get install libbullet-dev bullet-dev 
sudo apt-get intall libsdl2-mixer-dev

```
## Building and Running
To build this project there are two options. One is to use CMake which makes including new libraries easier, and handles new files added automatically to the src and include directory. CMake is a small new learning curve but makes things easier in the future.
The second option is to use the provided Makefile which is used as usual.

Running the make in a separate directory will allow easy cleanup of the build data, and an easy way to prevent unnecessary data to be added to the git repository.  

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary. Later use with CMake and Shader files will be require the copy of a directory where those files are stored (ex. shaders). To do this in the 

```
mkdir build
cd build
cmake ..
make
./Bee
```

### Makefile Instructions 
Please use cmake

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial
```

## Keyboard Controls
Camera controls- Use Numpad Keys

‘4’ and ‘6’ - camera to move left and right

‘1’ and ‘2’ - camera to move up and down

‘8’ and ‘5’ - camera to move closer and farther

Keyboard Keys Below

‘N’ key- per fragment shader

‘B’ key- per vertex shader

‘A’ key - add ambient light

‘S’ key - remove ambient light

‘2’ key - increase bee light radius 

‘1’ key - decrease bee light radius

‘3’ key - increase specular

‘4’ key - decrease specular


## Mouse Input
Cursor to change the position of the net

Left button to rotate the net left

Right button to rotate the net right

# Extra Credit


### Group Members
Andrew Flangas

Christina Symon

Lucas Calabrese 
