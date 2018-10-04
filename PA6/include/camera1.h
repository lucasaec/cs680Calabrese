#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera1
{
  public:
    Camera1();
    ~Camera1();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
  
  private:
    glm::mat4 projection;
    glm::mat4 view;
};

#endif /* CAMERA_H */

//credit to Rowan Gudmundsson for makefile
