# PA10: Pinball

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

The cmakelists.txt file includes imagemagick so imagemagick may need to be installed.
I used: sudo apt-get install libbullet-dev
to install bullet.

### Ubuntu/Linux

It works on the ECC ubuntu machine since they already have it downloaded.
```bash
sudo apt-get install libmagick++-dev

sudo apt-get install libassimp-dev assimp-utilsev
    
sudo apt-get install libglew-dev libglm-dev libsdl2-dev sudo apt-get install libbullet-dev bullet-dev
```
This project uses Assimp

### Mac OSX
Installation of brew is suggested to easily install the libs. Ensure that the latest version of the Developer Tools is installed.
```bash
brew install glew glm sdl2 
brew install assimp
brew install imagemagick 
brew install bullet
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
./Pinball
```


### Makefile Instructions 
Please use cmake

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Pinball
```
# How to load an object
Place object files in the objects folder. They should be download when the repository is cloned.

## Keyboard Controls
Hold space bar- plunger launcher

‘Z’ key - operates the left paddle

‘M’ key - operates the right paddle

Camera controls- Use Numpad Keys

‘4’ and ‘6’ - camera to move left and right

‘1’ and ‘2’ - camera to move up and down

‘8’ and ‘5’ - camera to move closer and farther

‘N’ key- per fragment shader

‘B’ key- per vertex shader

‘P’ key- spotlight

‘L’ key- normal light

‘A’ and ‘S’ keys- ambient light adjustment

‘1’ and ‘2’ keys- specular light adjustment

‘3’ and ‘4’ keys- specular light of the ball adjustment

‘5’ and ‘6’ keys- spotlight intensity

‘7’ and ‘8’ keys- radius of spotlight adjustment

# Extra Credit


Plunger intensity changes via holding down the spacebar

Spotlight radius and intensity can be changed with keyboard inputs.



### Group Members
Andrew Flangas

Christina Symon

Lucas Calabrese
