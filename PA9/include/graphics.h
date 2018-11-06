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
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();
void keys(unsigned int);

  private:
unsigned int a;
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_AmbientProduct, m_DiffuseProduct, m_SpecularProduct;
    GLint m_ModelView;
    GLint m_Projection;
    GLint m_LightPosition;
    GLint m_Shininess;
    

    Object *m_cube;
    Object *m_table;
    Object *m_sphere;
    Object *m_cylinder;
};

#endif /* GRAPHICS_H */
