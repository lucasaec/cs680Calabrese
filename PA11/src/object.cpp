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
extern int mousex;
extern int mousey;
extern float rotationAmount;
btRigidBody* table4;
btTransform table4Frame;
Object::Object() {}

/**
 *
 *
 */
Object:: Object(std::string objname, float scale, float posx, float posy, float posz ,int type, std::string textName)
{
    beePoints = 0;
    beeIndex = 0;
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
        if(type == 0 || type == 99) {
            aiVector3D position = mesh->mVertices[face.mIndices[0]]; 
            triArray[0] = btVector3(position.x, position.y, position.z);
 
            position = mesh->mVertices[face.mIndices[1]]; 
            triArray[1] = btVector3(position.x, position.y, position.z);
            
            position = mesh->mVertices[face.mIndices[2]]; 
            triArray[2] = btVector3(position.x, position.y, position.z);
      
            objTriMesh->addTriangle(triArray[0], triArray[1], triArray[2]);
        }
    }
    
    if(type == 0 || type == 99) {
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
        rigidBody->setRestitution(0);
        rigidBody->setUserIndex(2);
        worldStuff->dynamicsWorld->addRigidBody(rigidBody);
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    }
    if(type == 99 ) { //All other Kinematic OBjects
        btDefaultMotionState *shapeMotionState = NULL; 
        shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(posx, posy, posz))); 
        btScalar mass(0);
        btVector3 inertia(0, 0, 0); 
        shape->calculateLocalInertia(mass, inertia);
        btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
        rigidBody = new btRigidBody(shapeRigidBodyCI);
        table4 = rigidBody;
        //rigidBody->setRestitution(1);
         rigidBody->setUserIndex(45);
        worldStuff->dynamicsWorld->addRigidBody(rigidBody);
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    }
    if(type == 2) {
        btDefaultMotionState *shapeMotionState = NULL; 
        btCollisionShape* shape=new btBoxShape(btVector3(1,1,1));
        btVector3 inertia(0,0,0);
        shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(posx,posy,posz))); 
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
        shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(posx, 0, posz))); 
        btScalar mass(0);
        shape->calculateLocalInertia(mass, inertia);
        btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
        rigidBody = new btRigidBody(shapeRigidBodyCI);
        rigidBody->setRestitution(1.4);
       // rigidBody->setUserIndex(2);
        worldStuff->dynamicsWorld->addRigidBody(rigidBody);
    }
    if(type == 4) {
        btDefaultMotionState *shapeMotionState = NULL; 
        btCollisionShape* shape = new btSphereShape((btScalar)1);
        btVector3 inertia(0,0,0);
        shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(posx, posy, posz))); 
        btScalar mass(1);
        shape->calculateLocalInertia(mass, inertia);
        btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
        rigidBody = new btRigidBody(shapeRigidBodyCI);
        rigidBody->setRestitution(1);
        //rigidBody->setUserIndex(5);
        rigidBody->setUserPointer(this);
        //rigidBody->setUserIndex(5);
//rigidBody->setUserIndex(5);
        worldStuff->dynamicsWorld->addRigidBody(rigidBody);
    }
    if(type == 64) {
	btDefaultMotionState *shapeMotionState = NULL; 
	btCollisionShape* shape=new btBoxShape(btVector3(.5,.5,.5));
	btVector3 inertia(0,0,0);
	shapeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(8.5, -23, 16))); 
	btScalar mass(0);
	shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, shapeMotionState, shape, inertia);
	rigidBody = new btRigidBody(shapeRigidBodyCI);
        rigidBody->setUserIndex(64); 
	worldStuff->dynamicsWorld->addRigidBody(rigidBody);
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
    }
    if(type != 67) {
        rigidBody->setActivationState(DISABLE_DEACTIVATION); 
    }
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
 
float x = 0;
void Object::Update(unsigned int dt) { 
if(physics == 67) {
model = glm::mat4(1.0f);
return;
}
  x += .001;
  btTransform trans;
  btScalar m[16]; 
  trans.setIdentity();
  if(physics == 0) {
   trans = rigidBody->getWorldTransform();
 /*  if(mousex == 0) {
       mousex = 1;
   }
   if(mousey == 0) {
       mousey = 1;
   }*/
   //trans.setRotation(btQuaternion(btVector3(1, 1, 1), (float)mousex/(float)mousey));
   //mousex on y
   //mousey on x

   btQuaternion quaternion1 = btQuaternion(btVector3(0, 1, 0), (mousex)/-700.0);
    btQuaternion quaternion2 = btQuaternion(btVector3(1, 0, 0), mousey/-800.0);
     btQuaternion quaternion3 = btQuaternion(btVector3(0, 0, 1), rotationAmount);
    trans.setRotation(quaternion1*quaternion2*quaternion3);
    rigidBody->setLinearVelocity(btVector3(0,0,0) );
    rigidBody->setAngularVelocity(btVector3(0,0,0) );
 // trans.setRotation(quaternion1);

  //  trans.setRotation(btQuaternion(btVector3(1, 0, 0), x));
  // trans.setRotation(btQuaternion(btVector3(0, 0, 1), x));
   //rigidBody->setWorldTransform(trans);
   rigidBody->getMotionState()->setWorldTransform(trans);
   }
   else if(physics != 67 && physics != 99) {
       btVector3 velocity = rigidBody->getLinearVelocity();
       float speedx,speedy,speedz;
       float max = 2;
       speedx = velocity[0];
       speedy = velocity[1];
       speedz = velocity[2];
       
       if(velocity[0] > max) {
           speedx = max;
       }
       else if(velocity[0] < -max) {
           speedx = -max;
       }
       if(velocity[1] > max) {
           speedy = max;
       }
       else if(velocity[1] < -max) {
           speedy = -max;
       }
       else if(velocity[2] > max) {
           speedz = max;
       }
       else if(velocity[2] < -max) {
           speedz = -max;
       }
        if(speedy  <5) {
      //	std::cout <<speedy << '\n';
        }
        rigidBody->setLinearVelocity(btVector3(speedx,speedy,speedz) );
      
       btVector3 avelocity = rigidBody->getAngularVelocity();
     //rigidBody->setRollingFriction(10.0f);
       max = 5;
       speedx = avelocity[0];
       speedy = avelocity[1];
       speedz = avelocity[2];
       
       if(velocity[0] > max) {
           speedx = max;
       }
       else if(velocity[0] < -max) {
           speedx = -max;
       }
       if(velocity[1] > max) {
           speedy = max;
       }
       else if(velocity[1] < -max) {
           speedy = -max;
       }
       else if(velocity[2] > max) {
           speedz = max;
       }
       else if(velocity[2] < -max) {
           speedz = -max;
       }
       rigidBody->setAngularVelocity(btVector3(speedx,speedy,speedz) );
   }
  worldStuff->dynamicsWorld->stepSimulation((float)dt/(float)1000, 100); 
  if(physics != 0)
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

