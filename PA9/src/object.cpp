#include "object.h"
#include <assimp/Importer.hpp> //includes the importer, which is used to read our obj file
#include <assimp/scene.h> //includes the aiScene object
#include <assimp/postprocess.h> //includes the postprocessing variables for the importer
#include <assimp/color4.h> //includes the aiColor4 object, which is used to handle the colors from the mesh objects
#include <assimp/material.h> 
#include <stdlib.h> 
#include <btBulletDynamicsCommon.h>
#include "BulletUp.h"
extern BulletUp* worldStuff;

Object::Object()
{  
unsigned int random = 0;
Assimp::Importer importer;
std::string input;
input = "../objects/table.obj" ;
//std::cout << "Would you like the colors to be random? Enter 1 for yes 0 for no" << '\n';
//std::cin >> random;
random = 1;

float a,b,c;

const aiScene *scene = importer.ReadFile(input, aiProcess_Triangulate);//aiProcessPreset_TargetRealtime_Fast has the configs you'll need

aiMesh *mesh = scene->mMeshes[0];


aiMaterial* mat = scene->mMaterials[1];
aiColor4D color (0.f,0.f,0.f,0.f);
aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&color);

angle = 0.0f;
float q,w,e;
q= color.r;
w= color.g;
e= color.b;
float x,y,z;
for(int i = 0; i < mesh->mNumVertices; i++) {
              x = mesh->mVertices[i].x;
              y = mesh->mVertices[i].y;
              z = mesh->mVertices[i].z;
    
if(mesh->HasNormals())
{
a = mesh->mNormals[i].x;
b = mesh->mNormals[i].y;
c = mesh->mNormals[i].z;
//norm = glm::vec3(normal.x,normal.y,normal.z);


}

   Vertex vzq = {glm::vec3(x,y,z),glm::vec3(q,w,e),glm::vec3(a,b,c)};
   Vertices.push_back(vzq);
}


for(int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    unsigned int* mIndices = face.mIndices;
    Indices.push_back(mIndices[0]);
    Indices.push_back(mIndices[1]);
    Indices.push_back(mIndices[2]);
}


for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
    aiString mtlName =  scene->mMeshes[i]->mName;
}


  angle = 0.0f;


}
/**
 *
 *
 */
Object:: Object(std::string objname, float scale, float posx, float posy, float posz ,int type)
{
    physics = type;
    scale1 = scale;
    objTriMesh = new btTriangleMesh();
    unsigned int random = 0;
    Assimp::Importer importer;
    std::string input;
    input = "../objects/"+objname ;
    random = 1;



    const aiScene *scene = importer.ReadFile(input, aiProcess_Triangulate);//aiProcessPreset_TargetRealtime_Fast has the configs you'll need

    aiMesh *mesh = scene->mMeshes[0];


    aiMaterial* mat = scene->mMaterials[1];
    aiColor4D color (0.f,0.f,0.f,0.f);
    aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&color);
    glm::vec3 norm;
    angle = 0.0f;
    float q,w,e;
    q= color.r;
    w= color.g;
    e= color.b;
    float x,y,z;
float a,b,c;

    for(int i = 0; i < mesh->mNumVertices; i++) {
        x = mesh->mVertices[i].x;
        y = mesh->mVertices[i].y;
        z = mesh->mVertices[i].z;
   
if(mesh->HasNormals())
{
a = mesh->mNormals[i].x;
b = mesh->mNormals[i].y;
c = mesh->mNormals[i].z;
//norm = glm::vec3(normal.x,normal.y,normal.z);


}

       
        Vertex vzq = { glm::vec3(x,y,z), glm::vec3(q,w,e), glm::vec3(a,b,c) };
        Vertices.push_back(vzq);
    }


    for(int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        
        unsigned int* mIndices = face.mIndices;
        Indices.push_back(mIndices[0]);
        Indices.push_back(mIndices[1]);
        Indices.push_back(mIndices[2]);
        if(type == 0) {
        aiVector3D position = mesh->mVertices[face.mIndices[0]]; 
        triArray[0] = btVector3(position.x, position.y, position.z);

        position = mesh->mVertices[face.mIndices[1]]; 
        triArray[1] = btVector3(position.x, position.y, position.z);

        position = mesh->mVertices[face.mIndices[2]]; 
        triArray[2] = btVector3(position.x, position.y, position.z);

        objTriMesh->addTriangle(triArray[0], triArray[1], triArray[2]);
        }
       // std::cout << triArray[i][0] << '\n';
        //float a = mesh->mVertices[face.mIndices[0]][0];
        //std::cout << a << '\n';
  
    }
 
    if(type == 0) {
    shape = new btBvhTriangleMeshShape(objTriMesh, true); 
    }

    angle = 0.0f;


    /** Model stuff that gets overwritten anyways**/
    model = glm::mat4(1.0f);
    model = glm::translate(glm::vec3(posx, posy+5, posz) );
    model = glm::scale(model, glm::vec3(1.0*scale1,1.0*scale1,1.0*scale1) );

/*Motion state stuff*/
if(type == 0) {
    btDefaultMotionState *shapeMotionState = NULL; 
  shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0))); 
  btScalar mass(0);
  
  btVector3 inertia(0, 0, 0); 
  shape->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
  rigidBody = new btRigidBody(shapeRigidBodyCI);
  worldStuff->dynamicsWorld->addRigidBody(rigidBody);
rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
}
if(type == 3 ) {
  btDefaultMotionState *shapeMotionState = NULL; 
btCollisionShape* shape=new btBoxShape(btVector3(.4,.4,.4));
btVector3 inertia(0,0,0);
shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0))); 
btScalar mass(1);
shape->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
  rigidBody = new btRigidBody(shapeRigidBodyCI);
  worldStuff->dynamicsWorld->addRigidBody(rigidBody);
}
if(type == 2) {
btDefaultMotionState *shapeMotionState = NULL; 
btCollisionShape* shape=new btCylinderShape(btVector3(.5,2,1));
btVector3 inertia(0,0,0);
shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0))); 
btScalar mass(0);
shape->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
  rigidBody = new btRigidBody(shapeRigidBodyCI);
  worldStuff->dynamicsWorld->addRigidBody(rigidBody);
}
if(type == 4) {
  btDefaultMotionState *shapeMotionState = NULL; 
btCollisionShape* shape = new btSphereShape((btScalar).4f);
btVector3 inertia(0,0,0);
shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 4))); 
btScalar mass(1);
shape->calculateLocalInertia(mass, inertia);
  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
  rigidBody = new btRigidBody(shapeRigidBodyCI);
  worldStuff->dynamicsWorld->addRigidBody(rigidBody);


}
rigidBody->setActivationState(DISABLE_DEACTIVATION);
  
}
Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}
 

void Object::Update(unsigned int dt)
{

 
  if(physics == 2 || physics == 3 || physics == 4 || physics == 0) {
  
  btTransform trans;
  btScalar m[16]; 
  trans.setIdentity();
 

  worldStuff->dynamicsWorld->stepSimulation((float)dt/(float)1000, 10); 

 
  

 rigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m); 
  
  model = glm::make_mat4(m);

  }
  
}

glm::mat4 Object::GetModel()
{
  return model;
}




void Object::Render()
{

    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
    
     glGenBuffers(1, &normal);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normal);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,normal));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

