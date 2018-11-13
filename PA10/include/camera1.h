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
    glm::mat4 view;
  private:
    glm::mat4 projection;
    
};

#endif /* CAMERA_H */
