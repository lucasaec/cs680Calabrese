#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <btBulletDynamicsCommon.h>
#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();
Shader *m_shader;
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();
void keys(unsigned int);
std::string response;
float x;
  private:
unsigned int a;
float amb,spec_tab,spec_cube,spec_cyl,spec_sphere;
    std::string ErrorString(GLenum error);

    Camera *m_camera;
   // Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    Object *m_cube;
    Object *m_table;
    Object *m_sphere;
    Object *m_cylinder;
};

#endif /* GRAPHICS_H */
