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
btRigidBody* table4;
btTransform table4Frame;
Object::Object() {}

/**
 *
 *
 */
Object:: Object(std::string objname, float scale, float posx, float posy, float posz ,int type, std::string textName)
{
    physics = type;
    scale1 = scale;
    objTriMesh = new btTriangleMesh();
    
    Assimp::Importer importer;
    std::string input;
    input = "../objects/"+objname ;
   
    const aiScene *scene = importer.ReadFile(input, aiProcess_Triangulate);
    image = new Magick::Image("../objects/" + textName);
    image->write(&m_blob, "RGBA");

    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

    glm::vec3 norm;
    angle = 0.0f;

    float q,w,e;
    
    
    
    float x,y,z;
    float a,b,c;
aiMesh *mesh = scene->mMeshes[0];
    for(int i = 0; i < mesh->mNumVertices; i++) {
        x = mesh->mVertices[i].x;
        y = mesh->mVertices[i].y;
        z = mesh->mVertices[i].z;
   
         if(mesh->HasTextureCoords(0) ) {   
	      const aiVector3D& texcoords = (mesh->mTextureCoords[0][i]);
	      q = texcoords.x;
	      w = texcoords.y;

	     // std::cout << q << '\n';
	  }

        if(mesh->HasNormals()) {
            a = mesh->mNormals[i].x;
            b = mesh->mNormals[i].y;
            c = mesh->mNormals[i].z;
        }
        Vertex vzq = { glm::vec3(x,y,z), glm::vec2(q,w), glm::vec3(a,b,c) };
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
    }
    
    if(type == 0) {
        shape = new btBvhTriangleMeshShape(objTriMesh, true); 
    }

    angle = 0.0f;
    
/*Motion state stuff*/
    if(type == 0) {
        btDefaultMotionState *shapeMotionState = NULL; 
        shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(posx, posy, posz))); 
        btScalar mass(0);
        btVector3 inertia(0, 0, 0); 
        shape->calculateLocalInertia(mass, inertia);
        btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
        rigidBody = new btRigidBody(shapeRigidBodyCI);
        table4 = rigidBody;
        
        worldStuff->dynamicsWorld->addRigidBody(rigidBody);
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    }
    if(type == 3 ) { //flipper
        btDefaultMotionState *shapeMotionState = NULL; 
        btCollisionShape* shape=new btBoxShape(btVector3(3.2,1.3,.25));
        btVector3 inertia(0,0,0);
        shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, 1.5, -14))); 
        btScalar mass(1);
        shape->calculateLocalInertia(mass, inertia);
        btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
        rigidBody = new btRigidBody(shapeRigidBodyCI);


        btTransform frame =  btTransform::getIdentity();
        frame.setOrigin(btVector3(0,10,0));
        btGeneric6DofConstraint* constraint = new btGeneric6DofConstraint(*rigidBody, frame,true);
	//constraint->
        constraint->setAngularLowerLimit(btVector3(0, -.6, 0));
        constraint->setAngularUpperLimit(btVector3(0, M_PI/2.5, 0));
        worldStuff->dynamicsWorld->addRigidBody(rigidBody);
        worldStuff->dynamicsWorld->addConstraint(constraint);
    }
    if(type == 11 ) { //flipper
        btDefaultMotionState *shapeMotionState = NULL; 
        btCollisionShape* shape=new btBoxShape(btVector3(3.2,1.3,.25));
        btVector3 inertia(0,0,0);
        shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(7, 1.5, -14))); 
        btScalar mass(1);
        shape->calculateLocalInertia(mass, inertia);
        btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
        rigidBody = new btRigidBody(shapeRigidBodyCI);


        btTransform frame =  btTransform::getIdentity();
        frame.setOrigin(btVector3(0,10,0));
        btGeneric6DofConstraint* constraint = new btGeneric6DofConstraint(*rigidBody, frame,true);
	//constraint->
        constraint->setAngularLowerLimit(btVector3(0, -.6, 0));
        constraint->setAngularUpperLimit(btVector3(0, M_PI/2.5, 0));
        worldStuff->dynamicsWorld->addRigidBody(rigidBody);
        worldStuff->dynamicsWorld->addConstraint(constraint);
    }
    if(type == 2) {
        btDefaultMotionState *shapeMotionState = NULL; 
        btCollisionShape* shape=new btBoxShape(btVector3(1,1,1));
        btVector3 inertia(0,0,0);
        shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0,1,1))); 
        btScalar mass(1);
        shape->calculateLocalInertia(mass, inertia);
        btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
        rigidBody = new btRigidBody(shapeRigidBodyCI);
       rigidBody->setRestitution(1.0);
        worldStuff->dynamicsWorld->addRigidBody(rigidBody);
    }//setRestitution(5.0)
    if(type == 8) { //bumper
        btDefaultMotionState *shapeMotionState = NULL; 
        btCollisionShape* shape=new btCylinderShape(btVector3(.5,2,1));
        btVector3 inertia(0,0,0);
        shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(posx, posy, posz))); 
        btScalar mass(0);
        shape->calculateLocalInertia(mass, inertia);
        btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
        rigidBody = new btRigidBody(shapeRigidBodyCI);
        rigidBody->setRestitution(1.4);
        worldStuff->dynamicsWorld->addRigidBody(rigidBody);
    }
    if(type == 4) {
        btDefaultMotionState *shapeMotionState = NULL; 
        btCollisionShape* shape = new btSphereShape((btScalar).4f);
        btVector3 inertia(0,0,0);
        shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(posx, posy, posz))); 
        btScalar mass(.6);
        shape->calculateLocalInertia(mass, inertia);
        btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
        rigidBody = new btRigidBody(shapeRigidBodyCI);
        rigidBody->setRestitution(1);
        worldStuff->dynamicsWorld->addRigidBody(rigidBody);
    }
    rigidBody->setActivationState(DISABLE_DEACTIVATION); 
    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW); 
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}
 

void Object::Update(unsigned int dt) { 
  btTransform trans;
  btScalar m[16]; 
  trans.setIdentity();

  worldStuff->dynamicsWorld->stepSimulation((float)dt/(float)1000, 10); 
  rigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m); 
  
  model = glm::make_mat4(m);  
}

glm::mat4 Object::GetModel() {
  return model;
}


/*
 
    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &normal);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normal);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
*/

void Object::Render()
{
    
    
   

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,normal));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texture));

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

