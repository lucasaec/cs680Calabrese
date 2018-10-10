#include "object.h"
#include <math.h> 
extern float speedChange;

Object::Object()
{  
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
 
Object::Object(float distance1, float speed1, float speed21,  signed int direction1, signed int direction21, unsigned int pause1, float double21,  float scale1)
{  
  level = 0;

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
   angle +=  dt * M_PI/1000* direction * pause * speed * speedChange; 
   if(direction != direction2) {
       angle2 +=  dt * M_PI/1000* direction2 * pause * speed * speedChange;
   }
   angle2 +=  dt * M_PI/1000* direction2 * pause * speed2 * speedChange;

   if(parent == NULL) {
       model =  glm::mat4(1.0f);
   }
   else {
       model = glm::mat4(1.0f) * parent->model2;
   }

   model = glm::translate(model, glm::vec3(distance*sin(angle), 0.0, distance*cos(angle)));
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
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

