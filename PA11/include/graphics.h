#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <btBulletDynamicsCommon.h>
#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera1.h"
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
    bool Render();
    void Fire(float force);
void keys(unsigned int);
std::string response;
float x;
float camera;
float cam;
float cam1;
    Object *glassT;
    Object *glassL;
    Object *glassR;
    Object *glassF;
  private:
unsigned int a;
float amb,spec_tab,spec_cube,spotlight_strength,spot_rad;
    std::string ErrorString(GLenum error);

    Camera1 *m_camera;
   // Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    Object *m_cube;
    Object *m_table;
    Object *m_sphere;
    Object *m_cylinder;
    Object *l_flipper;
    Object *launcher;

    
};

#endif /* GRAPHICS_H */