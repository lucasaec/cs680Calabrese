#include "object.h"
#inlcude "shader.h"
#include <assimp/Importer.hpp> //includes the importer, which is used to read our obj file
#include <assimp/scene.h> //includes the aiScene object
#include <assimp/postprocess.h> //includes the postprocessing variables for the importer
#include <assimp/color4.h> //includes the aiColor4 object, which is used to handle the colors from the mesh objects
#include <assimp/material.h> 
#include <stdlib.h> 
Object::Object()
{  
std::vector<Vertex> Vertices;
std::vector<unsigned int> Indices;
unsigned int random = 0;
Assimp::Importer importer;
std::string input;
std::cout << "Please enter a file name. (dragon.obj or box2.obj)" << '\n';
std::cin >> input;
input = "../objects/" + input;
std::cout << "Would you like the colors to be random? Enter 1 for yes 0 for no" << '\n';
std::cin >> random;




const aiScene *scene = importer.ReadFile(input, aiProcess_Triangulate);//aiProcessPreset_TargetRealtime_Fast has the configs you'll need

aiMesh *mesh = scene->mMeshes[0];


aiMaterial* mat = scene->mMaterials[1];
aiColor4D color (0.f,0.f,0.f,0.f);
aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&color);

angle = 0.0f;
float q,w,e;
float x,y,z;

for(int i = 0; i < mesh->mNumVertices; i++) {
              x = mesh->mVertices[i].x;
              y = mesh->mVertices[i].y;
              z = mesh->mVertices[i].z;
		q = mesh->mIndices[i].x;
		w = mesh->mIndices[i].y;

/*          if(random == 1) {
            
              float xq=1, xw=1, xe=1;
              if(rand() % 4 == 0) {
                  xq*= -1;
              }
              if(rand() % 4 == 0) {
                  xw*= -1;
              }
              if(rand() % 4 == 0) {
                  xe*= -1;
              }
           

              q =(x/y/z*xq*(float)(rand() % 10) ) +  (float)1/((rand() % 100 + 1) );
              w = (y/z/x*xw*(float)(rand() % 10) ) +  (float)1/((rand() % 100 + 1) );
              e = (z/x/y*xe*(float)(rand() % 10) ) +  (float)1/((rand() % 100 + 1) );
      
       q=(rand()%100)/100.0;
	w=(rand()%100)/100.0;
	e=(rand()%100)/100.0;


  }*/
       
   Vertex vzq = {glm::vec3(x,y,z),glm::vec2(q,w)};
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
 

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	glGenTextures(1, &aTexture);
	//glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, aTexture);
        glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, , , 0, GL_RGBA, GL_UNSIGNED_BYTE, ,);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glUniformi(aTexture,0);
}




//gSampler= 


Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}
 //float x = 0.0f;
void Object::Update(unsigned int dt)
{
  angle += dt * M_PI/1000;
  model = glm::mat4(1.0f); 
 model = glm::rotate(model,  (angle), glm::vec3(.5, 0, 0.0));
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render(shader* s)
{
  s->GetUniformLocation(
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, aTexture);
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uvs));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glUniformi(gSampler,0);
  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
  

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

