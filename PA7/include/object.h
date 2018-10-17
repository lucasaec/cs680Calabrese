#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include <Magick++.h>
class Object
{
  public:
    Object();
    Object(float distance, float speed1, float speed21, signed int direction1, signed int direction21, unsigned int pause1, float double21,  float scale1, std::string objName,std::string textName);
    ~Object();
    void Update(unsigned int dt);
    void Render();
    void Reverse(int x);
    float distance;
    float speed;
    float speed2;
    std::vector<Object*> children; 
    Object* parent;
    int level;
    float sc;
    glm::mat4 GetModel();
    glm::mat4 model2;

    
    Magick::Image* image;
    Magick::Blob m_blob;
    GLuint texture;

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
 
    float angle;
    float angle2;
    signed int direction;
    signed int direction2;
    unsigned int pause;
    float double2;
   
    
};

#endif /* OBJECT_H */
