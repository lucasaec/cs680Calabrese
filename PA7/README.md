# PA7 : SOLAR SYSTEM

## Group Members
Andrew Flangas

Christina Symon

Lucas Calabrese

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev
```

### Mac OSX
Installation of brew is suggested to easily install the libs. Ensure that the latest version of the Developer Tools is installed.
```bash
brew install glew glm sdl2
```

All dependencies for this project should be on the ECC computers.

## Building and Running
To build this project there are two options. One is to use CMake which makes including new libraries easier, and handles new files added automatically to the src and include directory. CMake is a small new learning curve but makes things easier in the future.
The second option is to use the provided Makefile which is used as usual.

Running the make in a separate directory will allow easy cleanup of the build data, and an easy way to prevent unnecessary data to be added to the git repository.  

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary. Later use with CMake and Shader files will be require the copy of a directory where those files are stored (ex. shaders). To do this in the ```add_custom_target``` function place 
```cmake
COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders/ ${CMAKE_CURRENT_BINARY_DIR}/shaders
```

```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```

### Menu Input
-The zoom in function allows you to zoom in on a planet.

-the zoom slider lets you zoom out when you are zoomed in on a planet. (it only works when you are click a planet to zoom in on in the menu)

-Affect all does nothing

-Disable clicks is to stop the planets from reversing when you click the menu

-Undo changes does nothing

-Reset view lets you reset to the default view. It undoes any zooming also.

-Scaled View Please don't press this.




### Keyboard Input
- a:          Reverse rotation of cube and it's orbit
- s:          Reverse the orbit of the cube
- d:          Reverse the rotation of the cube itself
- f:          Pause, Pressing a,s,d,f keys or Clicking left,right,or middle on the mouse unpauses the cube
- z: changes what you will affect when pressing a,s,d f, middle click, left click, and right click. Before pressing z you will be able your interactions will affect all moons and planets and pluto. If you press z, you will affect one of the moons or planet or pluto. You can press z any to interact with any of the moons. After you iterate through all of them, you will be able to affect all moons again, and be able to iterate through planets again.
- Arrow Up:   Zooms out the planet 
- Arrow down: Zooms in the planet (will move camera past the planet if you zoom too much)
- Right Arrow stops the zooming.

### Mouse Input
- Middle Click:         Reverse rotation of cube and it's orbit
- Left Click:           Reverse the orbit of the cube
- Right Click:          Reverse the rotation of the cube itself


### Extra Credit
Slider Menu for speed

Slider Menu for zoom in and out

Configuration file

## Note
It may take a while for everything to load when starting the program.

Disable Clicks on the menu disables the left and right clicks of the mouse that is used for reversing directions. You can still click on the menu when this is pressed.

The "Scaled View" and "Undo Changes" do not perform any functions or changes.

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial
```
