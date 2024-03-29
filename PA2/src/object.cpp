#include "object.h"

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

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
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}
signed int direction = 1;
signed int direction2 = 1;
unsigned int pause = 1;
float double2 = 1.0; //double cube

float angle2;
/**
 * Cube and orbit rotate in same direction means
 * cube rotate in opposite direction freezes cube like since it rotates one increment forward and one increment back
 * cube rotate in positive and orbit in positive likey increments by 2
 * cube rotate in back and forward there for must increment by 3 since one is to cancel out the other direction, and the two
 * are meant to rotate at the same speed
 *
 * 1 increment in the same direction causes the cube to always face toward the center. So it is rotating.4
 * 1 increment  in different directions causes the cube to stop and not change the direction its facing since the rotations 
 * cancel out
 * 2 increment in opposite directions causes the cube to rotate in the opposite direction so wit will not face toward the center
 * but it will not rotate at the correct speed.
 * 3 increment in opposite direction causes cube to rotate at correct speed
 */
void Object::Update(unsigned int dt)
{
 // float a = (dt * M_PI/1000* direction) * pause;
  //float b = (dt * M_PI/1000* direction2 * double2) * pause;
 // std::cout << "ANGLE ADD1: " << a;
  //std::cout << "\n";
  //std::cout << "ANGLE ADD2: " << b;
 // std::cout << "\n";
  //std::cout << "\n";

  angle +=  dt * M_PI/1000* direction * pause; 
  angle2 +=  dt * M_PI/1000* direction2 * double2 * pause;
  //x+=1;
  //model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, x));
  //model = glm::rotate(model, (angle), glm::vec3(0.0, 1.0, 0.0));
  // model = glm::rotate(model, (angle), glm::vec3(0.0, 1.0, 0.0));

   model = glm::rotate(glm::mat4(1.0f),  (angle), glm::vec3(0.0, 1.0, 0.0));
   model = glm::translate(model, glm::vec3(0.0, 0.0, 7.0));
   model = glm::rotate(model,  (angle2), glm::vec3(0.0, 1.0, 0.0));
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
           double2 = 3;
        }
    }
    else if (x == 2) { //orbit
        direction = direction*-1;
        double2 = 1.0;
        if(direction != direction2) {        
            double2 = 3;
        }
        
    }
    else if (x == 3) {//cube
        direction2 = direction2 * -1;
        double2 = 1.0;
        if(direction != direction2) {
            double2 = 3;
        }
    } 
    
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

