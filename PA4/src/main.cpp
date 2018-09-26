#include <iostream>

#include "engine.h"

std::string *objs;
int length;
int main(int argc, char **argv)
{
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600);

  std::string a[argc];

  for(unsigned int i = 0; i < argc; i++) {
       std::string z = argv[i];
       a[i] = z;
  }
  objs = a;
  length = argc;
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
