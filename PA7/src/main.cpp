#include <iostream>

#include "engine.h"

int main(int argc, char **argv)
{
 // IMGUI_CHECKVERSION();
  //ImGui::CreateContext();
  //ImGui::StyleColorsDark();


    


  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Solar System", 1000, 800);
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
//  ImGui::DestroyContext();
  return 0;
}
