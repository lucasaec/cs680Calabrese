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

    
    Magick::Image* image1;
    Magick::Blob m_blob1;
    GLuint texture1;

//GL_TEXTURE_2D target;
    GLenum target;


  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB[2];
    GLuint IB[2];

    float angle;
};

#endif /* OBJECT_H */
