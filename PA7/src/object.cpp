#include "object.h"
#include <math.h> 
#include <assimp/Importer.hpp> //includes the importer, which is used to read our obj file
#include <assimp/scene.h> //includes the aiScene object
#include <assimp/postprocess.h> //includes the postprocessing variables for the importer
#include <assimp/color4.h> //includes the aiColor4 object, which is used to handle the colors from the mesh objects
#include <assimp/material.h> 
extern float speedChange;

Object::Object()
{  
Assimp::Importer importer;
const aiScene *scene = importer.ReadFile("../objects/sphere.obj", aiProcess_Triangulate);
float q,w;
q=0;
w=0;
float x,y,z;

image = new Magick::Image("../objects/sun.jpg");
image->write(&m_blob, "RGBA");

glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D,texture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

aiMesh *mesh = scene->mMeshes[0];
   
 




    
    
	for(int i = 0; i < mesh->mNumVertices; i++) {
		      x = mesh->mVertices[i].x;
		      y = mesh->mVertices[i].y;
		      z = mesh->mVertices[i].z;
//std::cout << x << '\n';
	  if(mesh->HasTextureCoords(0) ) {   
	      const aiVector3D& texcoords = (mesh->mTextureCoords[0][i]);
	      q = texcoords.x;
	      w = texcoords.y;

	     // std::cout << q << '\n';
	  }
    


	   Vertex vzq = {glm::vec3(x,y,z),glm::vec2(1,1)};
	   q = 0; 
	   w = 0;
	   Vertices.push_back(vzq);
	}


	for(int i = 0; i < mesh->mNumFaces; i++) {
	    aiFace face = mesh->mFaces[i];
	    unsigned int* mIndices = face.mIndices;
	    Indices.push_back(mIndices[0]);
	    Indices.push_back(mIndices[1]);
	    Indices.push_back(mIndices[2]);   
	}


  
  angle = 0.0f;
  direction = 1;
  direction2 = 1;
  pause = 1;
  double2 = 1.0;
  distance = 7;
  speed = 1;
  speed2 = 1;
  sc = 1;  
  parent = NULL;
  level = 0;  

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}
 


Object::Object(float distance1, float speed1, float speed21,  signed int direction1, signed int direction21, unsigned int pause1, float double21,  float scale1, std::string objName, std::string textName)
{  
  level = 0;
 
 Assimp::Importer importer;
const aiScene *scene = importer.ReadFile("../objects/" + objName, aiProcess_Triangulate);
float q,w;
q=0;
w=0;
float x,y,z;
aiMesh *mesh = scene->mMeshes[0];
   
 
image = new Magick::Image("../objects/" + textName);
image->write(&m_blob, "RGBA");

glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D,texture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 



    
    
	for(int i = 0; i < mesh->mNumVertices; i++) {
		      x = mesh->mVertices[i].x;
		      y = mesh->mVertices[i].y;
		      z = mesh->mVertices[i].z;
//std::cout << x << '\n';
	  if(mesh->HasTextureCoords(0) ) {   
	      const aiVector3D& texcoords = (mesh->mTextureCoords[0][i]);
	      q = texcoords.x;
	      w = texcoords.y;

	     // std::cout << q << '\n';
	  }
    


	   Vertex vzq = {glm::vec3(x,y,z),glm::vec2(q,w)};
	   q = 0; 
	   w = 0;
	   Vertices.push_back(vzq);
	}


	for(int i = 0; i < mesh->mNumFaces; i++) {
	    aiFace face = mesh->mFaces[i];
	    unsigned int* mIndices = face.mIndices;
	    Indices.push_back(mIndices[0]);
	    Indices.push_back(mIndices[1]);
	    Indices.push_back(mIndices[2]);   
	}
  // The index works at a 0th index
 
  
  direction = direction1;
  direction2 = direction21;
  pause = pause1;
  double2 = double21;
  distance = distance1; 
  
  speed = speed1;
  speed2 = speed21;
  sc = scale1;  
  parent = NULL;

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
 //double cube

float angle2;

void Object::Update(unsigned int dt)
{
float divideBy = 1;
if( divideBy == 0) {
    divideBy = 1;
}

   angle +=  dt * M_PI/1000* direction * pause * speed * speedChange; //speed is orbit speed
   if(direction != direction2) {
       angle2 +=  dt * M_PI/1000* direction2 * pause * speed * speedChange * 2 /divideBy;
   }
   angle2 +=  dt * M_PI/1000* direction2 * pause * speed2 * speedChange; //speed2 is spin speed
   float lower = 0;
   if(parent == NULL) {
       model =  glm::mat4(1.0f);
       
   }
   else {
      // lower = 2.0f;
       model = glm::mat4(1.0f) * parent->model2;
   }

   model = glm::translate(model, glm::vec3(distance*sin(angle), lower, distance*cos(angle)));
   model2 = glm::mat4(1.0f) * model;
   model = glm::rotate(model,  (angle), glm::vec3(0.0, 1.0, 0.0));
   model = glm::rotate(model,  (angle2), glm::vec3(0.0, 1.0, 0.0));
   model = glm::scale(model, glm::vec3(1.0*sc,1.0*sc,1.0*sc) );
} 

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Reverse(int x) {
    pause = 1;
    if(x == 4) {
        pause = 0;
    }
    else if(x == 1) { //orbit & cube
        direction = direction * -1;
        direction2 = direction2 * -1;
        double2 = 1.0;
        if(direction != direction2) {        
           double2 = 1;
        }
    }
    else if (x == 2) { //orbit
        direction = direction*-1;
        double2 = 1.0;
        if(direction != direction2) {        
            double2 = 1;
        }
        
    }
    else if (x == 3) {//cube
        direction2 = direction2 * -1;
        double2 = 1.0;
        if(direction != direction2) {
            double2 = 1;
        }
    } 
    
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texture));

glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

