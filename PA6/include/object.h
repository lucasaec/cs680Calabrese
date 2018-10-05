#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include <Magick++.h>
class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt);
    void Render();

    glm::mat4 GetModel();
    Magick::Image* image;
    Magick::Blob m_blob;
    GLuint texture;
//GL_TEXTURE_2D target;
    GLenum target;


  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;
};

#endif /* OBJECT_H */
