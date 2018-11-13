#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include <btBulletDynamicsCommon.h>
#include <Magick++.h>
class Object
{
  public:
    Object();
    Object(std::string, float, float, float, float, int, std::string);
    ~Object();
    void Update(unsigned int dt);
    void Render();
    std::vector<Object*> children;
    int level;
    float scale1;
    Object* parent;
    glm::mat4 GetModel();
    glm::mat4 model;
    btVector3 triArray[3];
    btTriangleMesh *objTriMesh;
    btCollisionShape *shape;
    btRigidBody *rigidBody;
    int physics;

    Magick::Image* image;
    Magick::Blob m_blob;
    GLuint texture;

  private:
    
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
GLuint normal;

    float angle;
};

#endif /* OBJECT_H */
