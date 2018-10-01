#include "object.h"
#include <assimp/Importer.hpp> //includes the importer, which is used to read our obj file
#include <assimp/scene.h> //includes the aiScene object
#include <assimp/postprocess.h> //includes the postprocessing variables for the importer
#include <assimp/color4.h> //includes the aiColor4 object, which is used to handle the colors from the mesh objects
#include <assimp/material.h> 
Object::Object()
{  

Assimp::Importer importer;
std::string input;
std::cin >> input;
input = "../objects/" + input;
const aiScene *scene = importer.ReadFile(input, aiProcess_Triangulate);//aiProcessPreset_TargetRealtime_Fast has the configs you'll need
//std::cout << scene->mMeshes[0];
aiMesh *mesh = scene->mMeshes[0];

//unsigned int* mIndices = face->mIndices;

aiMaterial* mat = scene->mMaterials[1];
aiColor4D color (0.f,0.f,0.f,0.f);

aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&color);
std::cout << color.r << '\n';
std::cout << color.g << '\n';
std::cout << color.b << '\n';


std::cout << mesh->HasVertexColors(0) << '\n';
  angle = 0.0f;

for(int i = 0; i < mesh->mNumVertices; i++) {
//std::cout << mesh->mVertices[i].x  << ' ';
//std::cout << mesh->mVertices[i].y << ' ';
//std::cout << mesh->mVertices[i].z << '\n';
   Vertex vzq = {glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),glm::vec3(color.r, color.g, color.b)};
   Vertices.push_back(vzq);
}
aiMesh *mesh2 = scene->mMeshes[0];
for(int i = 0; i < mesh->mNumVertices; i++) {
std::cout << mesh2->mVertices[i].x  << ' ';
std::cout << mesh2->mVertices[i].y << ' ';
std::cout << mesh2->mVertices[i].z << '\n';
  // Vertex vzq = {glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),glm::vec3(color.r, color.g, color.b)};
  // Vertices.push_back(vzq);
}

for(int i = 0; i < mesh->mNumFaces; i++) {
aiFace face = mesh->mFaces[i];
unsigned int* mIndices = face.mIndices;
//std::cout << face.mIndices[0] << ' ';
//std::cout << face.mIndices[1] << ' ';
//std::cout << face.mIndices[2] << '\n';
Indices.push_back(mIndices[0]);
Indices.push_back(mIndices[1]);
Indices.push_back(mIndices[2]);
}
//aiColor3D color (0.f,0.f,0.f);
//aiMaterial* mat = aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&color);

for(int i = 0; i < mesh->mNumFaces; i++) {
aiFace face = mesh2->mFaces[i];
unsigned int* mIndices = face.mIndices;
std::cout << face.mIndices[0] << ' ';
std::cout << face.mIndices[1] << ' ';
std::cout << face.mIndices[2] << '\n';
//Indices.push_back(mIndices[0]);
//Indices.push_back(mIndices[1]);
//Indices.push_back(mIndices[2]);
}
for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
    aiString mtlName =  scene->mMeshes[i]->mName;
   // std::cout << mtlName.data << '\n';
}

std::cout << mesh->GetNumColorChannels() << '\n';

std::cout << mesh->mColors[0] << '\n';

std::cout << scene->HasMaterials() << '\n'; 


  angle = 0.0f;
 

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

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

