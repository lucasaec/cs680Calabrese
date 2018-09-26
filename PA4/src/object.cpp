#include "object.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "glm/ext.hpp"
#include <stdio.h>

#include <stdlib.h>    
#include <time.h>
extern std::string *objs;
extern int length;
using namespace std;
int currentFile = 0;

std::string * objInfo;
// vector v int v;
// &v[0]
//json c++
bool randColor = false;
//make color kd
std::string objectReader(std::string f) {
//std::cout << f;
 //std::cout << f;
    std::string code = "";
    std::ifstream file;
    char c;
    file.open(f);

    if(!file.is_open()) {
        return "";
    }
    file.get(c);
    while (!file.eof())  {
        code = code + c;
        file.get(c);
    }

    //std::cout << code;
    file.clear();
    file.close();
    return code;

}

std::vector<Vertex> getVertices(std::string f) {
std::srand(std::time(0));
    std::string code = "";
    std::ifstream file;
    char c;
   
    file.open(f);

    if(!file.is_open()) {
       
    }
   


    //std::cout << code;
   
 

    std::vector<Vertex> list;
    int a = 0;
    //substring = q;
    int l = 0;
    int m = 0;
    int t = 0;


    float x;
    float y;
    float z;
    

 
   int indz = 0;
   std::string q = " 1  v  ";
 
 char kay;
 while (!file.eof())  {
//cout << c;
        //code = code + c;
        file.get(c);
        kay = c;
        file.get(c);
        if(kay == 'v' && c == ' ') {
            break;
        }
    }
//cout << c;
code = code + "v ";
cout << code;
while(q.find("v ", a) != std::string::npos) {


 
 
if(file.eof()) {
 cout << f;
    break;
}
 file.get(c);
 while (c != '\n' && !file.eof())  {
//cout << c;
        code = code + c;
        file.get(c);
    }

//cout << "\n";
q = "";
q = code + "\n";
code = "";
//cout << q;

if (q.substr(0,2 ) != "v ") {
cout << q;

break;
}

    t = q.find("v ", a);
    l = q.find(" ", t+2);
  //  std::cout <<   q.substr(t+2, l - t-2 ) << " ";
x = std::stof(q.substr(t+2, l - t-2 ));

    m = l;
    l = q.find(" ", l+1);

cout << x << ' ';

 //  std::cout <<   q.substr(m, l-m );
 //   std::cout <<   q.substr(m,1 );
y = std::stof( q.substr(m, l - m ) );
    m=l;
    l = q.find('\n', l);

cout << y << ' ';

 //   std::cout <<  q.substr(m, l - m ) << "\n";
z = std::stof( q.substr(m, l - m ));
//std::cout <<   q.substr(m,1 ) << '\n'; 
    a = t+1;
cout << z << '\n';
//cout << '\n';

//glm::vec3 normal = glm::cross(y - x, z - x);
//normal = glm::normalize(final);

Vertex vzq = {glm::vec3(x,y,z),glm::vec3(0.3412, 0.8784, 0.7765)};
//vzq.vertex =  new glm::vec3(x,y,z);
list.push_back(vzq);
a=0;
l = 0;
m = 0;
t = 0;


indz++;
}

 file.close();
    return list;
}







std::vector<unsigned int> getFrags(std::string f) {
std::string code = "";
    std::ifstream file;
    char c;
   
    file.open(f);

    if(!file.is_open()) {
       
    }
   
  

    //std::cout << code;
   
 

    std::vector<unsigned int> list;
    int a = 0;
    //substring = q;
    int l = 0;
    int m = 0;
    int t = 0;
    int n = 0;


    unsigned int x;
    unsigned int y;
    unsigned int z;
    
    

 
   int indz = 0;
   std::string q = " 1  f  ";
 char kay;
 while (!file.eof())  {
//cout << ("" + c);
        //code = code + c;
        file.get(c);
        kay = c;
        file.get(c);
        if(kay == 'f' && c == ' ') {
            break;
      }
}
code = code + "f ";
q = code;
//cout << c;

while (!file.eof())  {
//cout << c;
        
        file.get(c);
        code = code + c;
      if(c == '\n') {
            break;
      }
}
 // code = code + "\n";
  //cout << "|" << code << "|";
while(q.find("f", a) != std::string::npos) {


 
 
if(file.eof()) {
  //  cout << f;
    break;
}
 file.get(c);
 while (c != '\n' && !file.eof())  {
//cout << c;
        code = code + c;
        file.get(c);
    }
 //cout << "||||" << code << "|||||" << "\n";
//cout << "\n";
q = "";
q = code + "\n";
code = "";
cout <<q;
//cout << q;


    n = q.find("/", t+2);

if (q.substr(0,2 ) != "f ") {
break;
}
    t = q.find("f ", a);
    l = q.find(" ", t+2);

    if (q.find("/", t+2) != std::string::npos) {
           
        n=l;
    }
    
 //   std::cout <<   q.substr(t+2, n - t-2 );
x = std::stoul(q.substr(t+2, n-t-2));

n = q.find("/", l+1);
    m = l;
    l = q.find(" ", l+1);

    if (q.find("/", t+2) != std::string::npos) {
        n=l;
    }
cout << x << ' ';

//   std::cout <<   q.substr(m, n-m );
 //   std::cout <<   q.substr(m,1 );
y = std::stoul( q.substr(m, n - m ) );
    n = q.find("/", l+1);
    m=l;
    l = q.find('\n', l);

    if (q.find("/", t+2) != std::string::npos) {
           
        n=l;
    }
cout << y << ' ';

  //  std::cout <<  q.substr(m, n - m ) << "\n";
z = std::stoul( q.substr(m, n - m ));
//std::cout <<   q.substr(m,1 ) << '\n'; 
    a = t+1;
cout << z << '\n';
//cout << '\n';
//vzq.vertex =  new glm::vec3(x,y,z);
list.push_back(x);
list.push_back(y);
list.push_back(z);
a=0;
l = 0;
m = 0;
t = 0;
n = 0;

indz++;
}
 file.close();
  return list;
}




void Object::getAll(std::string f) {

     if(length > 2 && objs[2] == "r") {
         randColor = true;
     }

	    std::ifstream file;
	    file.open(f);
            std::string header;
	    char line[400];

            float x,y,z;

            unsigned int a,b,c;
            unsigned int extra;

      bool switch1 = false;

      float boxColorx;
      float boxColory;
      float boxColorz;

      float boxColorx2;
      float boxColory2;
      float boxColorz2;

      std::string header2;

        std::ifstream file2;
        std::string f2 = "../mats/";
        std::string temp;

        srand (time(NULL));

	while(!file.eof()) {

     
	  file >> header;
          //cout << header;
	  if(header == "v") {
              //0.3412, 0.8784, 0.7765)
              file >> x >> y >> z;
Vertex vzq = {glm::vec3(x,y,z),glm::vec3(x,y,z)};
if( objs[currentFile+1] == "box2.obj" && !randColor) {

              if(y > 1 && y < 3) {
                 vzq = {glm::vec3(x,y,z),glm::vec3(boxColorx,boxColory , boxColorz)};
                 
              }
              else {
         
	           vzq = {glm::vec3(x,y,z),glm::vec3(boxColorx2, boxColory2, boxColorz2)};
                  
              }
}
else if(objs[currentFile+1] == "dragon.obj" && !randColor) {
     vzq = {glm::vec3(x,y,z),glm::vec3(boxColorx,boxColory , boxColorz)};
}
else {
              float q,w,e;
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
//cout << q << "\n";
vzq = {glm::vec3(x,y,z),glm::vec3(q,w,e)};
}
              
              Vertices.push_back(vzq);

           //  cout << x << " " << y << " " << z << "\n";
              
	  }
          else if(header == "mtllib") {
              if( objs[currentFile+1] == "box2.obj" ||objs[currentFile+1] ==  "dragon.obj") {
              file >> temp;
              f2 = f2 + temp;
              file2.open(f2);
              if(!file2.is_open()) {
                  randColor = true;
              }
              while(file2.is_open() && !file2.eof()) {
                  file2 >> header2;
                 // cout << header2 << '\n';
                  if(header2 == "Kd") {
                    if(!switch1) {
                        
                        file2 >> boxColorx >> boxColory >> boxColorz; 
                      //  cout <<  boxColorx  << " " <<  boxColory  << " " <<  boxColorz  << "\n";
                        switch1 = true;
                    }
                    else {
                        file2 >> boxColorx2 >> boxColory2 >> boxColorz2;  
                       // cout <<  boxColorx2  << " " <<  boxColory2  << " " <<  boxColorz2  << "\n";  
                    }
                  } 
                  else {
                        file2.getline(line, 255);
                  }
              }
              header2 = "";
              }  
               file2.close();
          }
	  else if(header == "f") {
               //f 4//1 2//1 1//1
               
              file >> a;
              if(file.peek() == '/') {
                  file >> line >> b >> line >> c >> line;
              }
              else {
                   file >> b >> c;
              }
              Indices.push_back(a);
	      Indices.push_back(b);
              Indices.push_back(c);
            //  cout << "|";
         //     cout << a << " " << b << " " << c << "\n";       
	  }
	  else {
	      file.getline(line, 255);
              
	  }
	  header = "";


	}
        file.close();
}


Object::Object()
{  

/*
Vertices = {
    {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}


  };

 Indices = {
    1, 2, 3
*/  
 


if(currentFile+1 < length) {
  std::string b;
 
      std::string string1 = "../Obj/" + objs[currentFile+1];

    //  b = objectReader(string1);

   //Vertices  = getVertices(string1);
//getVertices(string1);
   // Indices = getFrags(string1);

 //Indices = getFrags(string1);//Probably not the right name
   getAll(string1);
 

  
  //cout << vecs.at(0)[0] << '\n';
   //cout << vecs.at(0)[1] << "\n";
currentFile++;
}
 

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  angle = 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

cout << "complete";
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}






void Object::Update(unsigned int dt)
{
  model = glm::mat4(1.0f);
  angle +=  dt * M_PI/1000; 
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

