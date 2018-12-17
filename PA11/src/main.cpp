#include <iostream>

#include "engine.h"
/**
 * main.cpp
 *
 */
/**
 * main
 * the main method
 * @params int argc the number of arguments
 * @argv the arguments
 */
int main(int argc, char **argv)
{
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Bee", 1000, 700);
gluPerspective(0, 1000 / 700, 1.0, 1000);
  if(!engine->Initialize())
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
