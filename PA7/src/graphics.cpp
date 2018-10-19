#include "graphics.h"
#include <vector>
#include <json.hpp>
#include <fstream>
#include <math.h> 
using namespace nlohmann;
float speed=2.0;
float rotated=0.0;
Graphics::Graphics()
{
    index = -1;
}
extern int lookAtIndex;
Graphics::~Graphics()
{

}
std::vector<Object*> list1;
std::vector<Object*> oGlist;
std::vector<Object*> scaledList;
/**
 * Allows you to update the index of the planet you are currently on
 *
 */
void Graphics::UpdateIndex() {
     index++;
     if(index >= (int) list1.size() ) {
         index = -1;
     }
}


bool Graphics::Initialize(int width, int height)
{
    json j;
    std::ifstream i("../objects/planets.json");
    i >> j;
   
    json j2;
    std::ifstream i2("../objects/scaleView.json");
    i2 >> j2;
   
    

    glewExperimental = GL_TRUE;
    auto status = glewInit();
    glGetError();

    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }

   GLuint vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   m_camera = new Camera();
   if(!m_camera->Initialize(width, height))
   {
     printf("Camera Failed to Initialize\n");
     return false;
   }

/**
* Instructions on how to add objects
* Constructor: (float distance1, float speed1, float speed21, signed int direction1, signed int direction21, unsigned int pause1, float double21,  float scale1)
*  distance1 = distance from parent
*  speed1 = speed of all rotation
*  direction1 = 
*
*
*
*/
  scaledView = false;
   std::string objectName = "smoothSphere.obj";
   float dist = 0;
   float orbit = 0;
   float spin = 0;
   float scale = 0;
   float year = 365;
   int spinDir = 1;
   std::string objName = "";
   std::string texName = "";

  float dsScale =  .00001;    

  dist = j["Sun"]["distance"];
  orbit = j["Sun"]["OrbitSpeed"];
  spin = j["Sun"]["SpinSpeed"];
  scale = j["Sun"]["Scale"];
  objName = j["Sun"]["object"];
  texName = j["Sun"]["Texture"];
//  spinDir = j["Sun"]["SpinDir"];
   m_cube = new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName );
   list1.push_back(m_cube);
   
   dist = j2["Sun"]["distance"];
  orbit = j2["Sun"]["OrbitSpeed"];
  spin = j2["Sun"]["SpinSpeed"];
  scale = j2["Sun"]["Scale"];
  objName = j2["Sun"]["object"];
  texName = j2["Sun"]["Texture"];
   scaledList.push_back(new Object(dist,orbit,spin,1,spinDir,1,1,scale,objName, texName) );


dist = j["Mercury"]["distance"];
  orbit = j["Mercury"]["OrbitSpeed"];
  spin = j["Mercury"]["SpinSpeed"];
  scale = j["Mercury"]["Scale"];
  objName = j["Mercury"]["object"];
 texName = j["Mercury"]["Texture"];
  // spinDir = j["Mecury"]["SpinDir"];

  

   m_cube->children.push_back(new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName) ); 
   m_cube->children.at(0)->parent = m_cube;
   m_cube->children.at(0)->level =1;
   list1.push_back(m_cube->children.at(0));
  
   

 dist = j2["Mercury"]["distance"];
  orbit = j2["Mercury"]["OrbitSpeed"];
  spin = j2["Mercury"]["SpinSpeed"];
  scale = j2["Mercury"]["Scale"];
  objName = j2["Mercury"]["object"];
 texName = j2["Mercury"]["Texture"];
   scaledList.push_back(new Object(dist,orbit,spin,1,spinDir,1,1,scale,objName, texName) );
   scaledList.at(1)->parent = scaledList.at(0);

dist = j["Venus"]["distance"];
  orbit = j["Venus"]["OrbitSpeed"];
  spin = j["Venus"]["SpinSpeed"];
  scale = j["Venus"]["Scale"];
  objName = j["Venus"]["object"];
 texName = j["Venus"]["Texture"];
 //spinDir = j["Venus"]["SpinDir"];
 
   m_cube->children.push_back(new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName) ); 
   m_cube->children.at(1)->parent = m_cube;
   m_cube->children.at(1)->level =1;
   list1.push_back(m_cube->children.at(1));
 

dist = j2["Venus"]["distance"];
  orbit = j2["Venus"]["OrbitSpeed"];
  spin = j2["Venus"]["SpinSpeed"];
  scale = j2["Venus"]["Scale"];
  objName = j2["Venus"]["object"];
 texName = j2["Venus"]["Texture"];
 //spinDir = j["Venus"]["SpinDir"];
 scaledList.push_back(new Object(dist,orbit,spin,1,spinDir,1,1,scale,objName, texName) );
 scaledList.at(2)->parent = scaledList.at(0);


  dist = j["Earth"]["distance"];
  orbit = j["Earth"]["OrbitSpeed"];
  spin = j["Earth"]["SpinSpeed"];
  scale = j["Earth"]["Scale"];
  objName = j["Earth"]["object"];
 texName = j["Earth"]["Texture"];
//spinDir = j["Earth"]["SpinDir"];
 
   m_cube->children.push_back(new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName) ); 
   m_cube->children.at(2)->parent = m_cube;
   m_cube->children.at(2)->level =1;
   list1.push_back(m_cube->children.at(2));
   

dist = j2["Earth"]["distance"];
  orbit = j2["Earth"]["OrbitSpeed"];
  spin = j2["Earth"]["SpinSpeed"];
  scale = j2["Earth"]["Scale"];
  objName = j2["Earth"]["object"];
 texName = j2["Earth"]["Texture"];
scaledList.push_back(new Object(dist,orbit,spin,1,spinDir,1,1,scale,objName, texName) );
   scaledList.at(3)->parent = scaledList.at(0);


  dist = j["Mars"]["distance"];
  orbit = j["Mars"]["OrbitSpeed"];
  spin = j["Mars"]["SpinSpeed"];
  scale = j["Mars"]["Scale"];
  objName = j["Mars"]["object"];
 texName = j["Mars"]["Texture"];
//spinDir = j["Mars"]["SpinDir"];
 
   m_cube->children.push_back(new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName) ); 
   m_cube->children.at(3)->parent = m_cube;
   m_cube->children.at(3)->level =1;
   list1.push_back(m_cube->children.at(3));


  dist = j2["Mars"]["distance"];
  orbit = j2["Mars"]["OrbitSpeed"];
  spin = j2["Mars"]["SpinSpeed"];
  scale = j2["Mars"]["Scale"];
  objName = j2["Mars"]["object"];
 texName = j2["Mars"]["Texture"];
//spinDir = j["Mars"]["SpinDir"];
scaledList.push_back(new Object(dist,orbit,spin,1,spinDir,1,1,scale,objName, texName) );
   scaledList.at(4)->parent = scaledList.at(0);

 dist = j["Jupiter"]["distance"];
  orbit = j["Jupiter"]["OrbitSpeed"];
  spin = j["Jupiter"]["SpinSpeed"];
  scale = j["Jupiter"]["Scale"];
  objName = j["Jupiter"]["object"];
 texName = j["Jupiter"]["Texture"];
//spinDir = j["Jupiter"]["SpinDir"];

   m_cube->children.push_back(new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName) ); 
   m_cube->children.at(4)->parent = m_cube;
   m_cube->children.at(4)->level =1;
   list1.push_back(m_cube->children.at(4));


 dist = j2["Jupiter"]["distance"];
  orbit = j2["Jupiter"]["OrbitSpeed"];
  spin = j2["Jupiter"]["SpinSpeed"];
  scale = j2["Jupiter"]["Scale"];
  objName = j2["Jupiter"]["object"];
 texName = j2["Jupiter"]["Texture"];
scaledList.push_back(new Object(dist,orbit,spin,1,spinDir,1,1,scale,objName, texName) );
   scaledList.at(5)->parent = scaledList.at(0);



dist = j["Saturn"]["distance"];
  orbit = j["Saturn"]["OrbitSpeed"];
  spin = j["Saturn"]["SpinSpeed"];
  scale = j["Saturn"]["Scale"];
  objName = j["Saturn"]["object"];
 texName = j["Saturn"]["Texture"];
//spinDir = j["Saturn"]["SpinDir"];


   m_cube->children.push_back(new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName) ); 
   m_cube->children.at(5)->parent = m_cube;
   m_cube->children.at(5)->level =1;
   list1.push_back(m_cube->children.at(5));


dist = j2["Saturn"]["distance"];
  orbit = j2["Saturn"]["OrbitSpeed"];
  spin = j2["Saturn"]["SpinSpeed"];
  scale = j2["Saturn"]["Scale"];
  objName = j2["Saturn"]["object"];
 texName = j2["Saturn"]["Texture"];
 scaledList.push_back(new Object(dist,orbit,spin,1,spinDir,1,1,scale,objName, texName) );
   scaledList.at(6)->parent = scaledList.at(0);

dist = j["Uranus"]["distance"];
  orbit = j["Uranus"]["OrbitSpeed"];
  spin = j["Uranus"]["SpinSpeed"];
  scale = j["Uranus"]["Scale"];
  objName = j["Uranus"]["object"];
 texName = j["Uranus"]["Texture"];
//spinDir = j["Uranus"]["SpinDir"];

   m_cube->children.push_back(new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName) ); 
   m_cube->children.at(6)->parent = m_cube;
   m_cube->children.at(6)->level =1;
   list1.push_back(m_cube->children.at(6));

  


dist = j2["Uranus"]["distance"];
  orbit = j2["Uranus"]["OrbitSpeed"];
  spin = j2["Uranus"]["SpinSpeed"];
  scale = j2["Uranus"]["Scale"];
  objName = j2["Uranus"]["object"];
 texName = j2["Uranus"]["Texture"];
 scaledList.push_back(new Object(dist,orbit,spin,1,spinDir,1,1,scale,objName, texName) );
    scaledList.at(7)->parent = scaledList.at(0);

dist = j["Neptune"]["distance"];
  orbit = j["Neptune"]["OrbitSpeed"];
  spin = j["Neptune"]["SpinSpeed"];
  scale = j["Neptune"]["Scale"];
  objName = j["Neptune"]["object"];
 texName = j["Neptune"]["Texture"];
//spinDir = j["Neptune"]["SpinDir"];

   m_cube->children.push_back(new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName) ); 
   m_cube->children.at(7)->parent = m_cube;
   m_cube->children.at(7)->level =1;
   list1.push_back(m_cube->children.at(7));
   
  
dist = j2["Neptune"]["distance"];
  orbit = j2["Neptune"]["OrbitSpeed"];
  spin = j2["Neptune"]["SpinSpeed"];
  scale = j2["Neptune"]["Scale"];
  objName = j2["Neptune"]["object"];
 texName = j2["Neptune"]["Texture"];
//spinDir = j["Neptune"]["SpinDir"];
scaledList.push_back(new Object(dist,orbit,spin,1,spinDir,1,1,scale,objName, texName) );
   scaledList.at(8)->parent = scaledList.at(0);

dist = j["Pluto"]["distance"];
  orbit = j["Pluto"]["OrbitSpeed"];
  spin = j["Pluto"]["SpinSpeed"];
  scale = j["Pluto"]["Scale"];
  objName = j["Pluto"]["object"];
 texName = j["Pluto"]["Texture"];
//spinDir = j["Pluto"]["SpinDir"];

   m_cube->children.push_back(new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName) ); 
   m_cube->children.at(8)->parent = m_cube;
   m_cube->children.at(8)->level =1;
   list1.push_back(m_cube->children.at(8));


dist = j2["Pluto"]["distance"];
  orbit = j2["Pluto"]["OrbitSpeed"];
  spin = j2["Pluto"]["SpinSpeed"];
  scale = j2["Pluto"]["Scale"];
  objName = j2["Pluto"]["object"];
 texName = j2["Pluto"]["Texture"];
//spinDir = j["Neptune"]["SpinDir"];
scaledList.push_back(new Object(dist,orbit,spin,1,spinDir,1,1,scale,objName, texName) );
   scaledList.at(9)->parent = scaledList.at(0);

 scale = j["Saturn"]["Scale"];
objName = j["Ring"]["object"];
 texName = j["Ring"]["Texture"];
 spin = j["Ring"]["SpinSpeed"];
//spinDir = j["Ring"]["SpinDir"];
   
   list1.push_back( new Object(0,0,spin/year,1,spinDir,1,1,scale*dsScale*.7,objName, texName) );
list1.at(10)->parent = list1.at(6);

dist = j["Moon"]["distance"];
  orbit = j["Moon"]["OrbitSpeed"];
  spin = j["Moon"]["SpinSpeed"];
  scale = j["Moon"]["Scale"];
  objName = j["Moon"]["object"];
 texName = j["Moon"]["Texture"];
//spinDir = j["Moon"]["SpinDir"];

list1.push_back( new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale,objName, texName));
    list1.at(11)->parent = list1.at(3);

dist = j["Phobos"]["distance"];
  orbit = j["Phobos"]["OrbitSpeed"];
  spin = j["Phobos"]["SpinSpeed"];
  scale = j["Phobos"]["Scale"];
  objName = j["Phobos"]["object"];
 texName = j["Phobos"]["Texture"];

list1.push_back( new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale*40,objName, texName));
    list1.at(12)->parent = list1.at(4);

dist = j["Europa"]["distance"];
  orbit = j["Europa"]["OrbitSpeed"];
  spin = j["Europa"]["SpinSpeed"];
  scale = j["Europa"]["Scale"];
  objName = j["Europa"]["object"];
 texName = j["Europa"]["Texture"];

list1.push_back( new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale*4,objName, texName));
    list1.at(13)->parent = list1.at(5);

dist = j["Titan"]["distance"];
  orbit = j["Titan"]["OrbitSpeed"];
  spin = j["Titan"]["SpinSpeed"];
  scale = j["Titan"]["Scale"];
  objName = j["Titan"]["object"];
 texName = j["Titan"]["Texture"];

list1.push_back( new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale*4,objName, texName));
    list1.at(14)->parent = list1.at(6);



dist = j["Ariel"]["distance"];
  orbit = j["Ariel"]["OrbitSpeed"];
  spin = j["Ariel"]["SpinSpeed"];
  scale = j["Ariel"]["Scale"];
  objName = j["Ariel"]["object"];
 texName = j["Ariel"]["Texture"];

list1.push_back( new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale*15,objName, texName));
    list1.at(15)->parent = list1.at(7);

dist = j["Triton"]["distance"];
  orbit = j["Triton"]["OrbitSpeed"];
  spin = j["Triton"]["SpinSpeed"];
  scale = j["Triton"]["Scale"];
  objName = j["Triton"]["object"];
 texName = j["Triton"]["Texture"];

list1.push_back( new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale*10,objName, texName));
    list1.at(16)->parent = list1.at(8);



dist = j["Charon"]["distance"];
  orbit = j["Charon"]["OrbitSpeed"];
  spin = j["Charon"]["SpinSpeed"];
  scale = j["Charon"]["Scale"];
  objName = j["Charon"]["object"];
 texName = j["Charon"]["Texture"];

list1.push_back( new Object(dist*dsScale,orbit/year,spin/year,1,spinDir,1,1,scale*dsScale*3,objName, texName));
    list1.at(17)->parent = list1.at(9);



   i2.close();
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

 
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }


  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }


  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  return true;
}

/** 
 * Iteratively calls update within object.cpp
 *
 */
void Graphics::Update(unsigned int dt)
{
 if(!scaledView) {
  for(unsigned int x = 0; x < list1.size(); x++) {
      list1.at(x)->Update(dt);
  }
}
else {
 for(unsigned int x = 0; x < scaledList.size(); x++) {
     scaledList.at(x)->Update(dt);
  }
}
}
void Graphics::Recenter() {
     m_camera->view = glm::lookAt( glm::vec3(0.0, 8.0, -16.0), //Eye Position
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up
    lookAtIndex= -1;
      speed=0.75;
      rotated=0;
}
/**
* Call this to reverse stuff
* Reverses based on current index
*/
void Graphics::Reverse(int x) {
    if(index == -1) {
        IterativeReverse(x);
    }
    else {
        list1.at(index)->Reverse(x);
    }
}

/**
 * Don't call this, Reverse will call it
 */
void Graphics::IterativeReverse(int mode) {
   
   for(unsigned int x = 0; x < list1.size(); x++) {        
       list1.at(x)->Reverse(mode);         
   }
}
void Graphics::camerachange(int p){
p1=p;
}

/**
 * Call this to render all objects in the list.
 */
void Graphics::IterativeRender(Object* obj) {
if(!scaledView) {
      for(unsigned int x = 0; x < list1.size(); x++) {
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(list1.at(x)->GetModel()));
          list1.at(x)->Render();   
      }
}
else {
       for(unsigned int x = 0; x < scaledList.size(); x++) {
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(scaledList.at(x)->GetModel()));
          scaledList.at(x)->Render();   
      }
}

}

/**
 * Renders stuff
 */

void Graphics::Render()
{
int indix = 2;
if(p1==1)
{
speed+=0.009;

//std::cout<<speed<<"\n";
}
else if(p1==2)
{
speed-=0.009;

}
else if (p1==3)
{
rotated+=0.1;
}
else if(p1 == 4)
{
rotated-=0.1;
}
if(lookAtIndex  > -1) {
    indix = lookAtIndex;

glm::mat4 c = list1.at(indix)->model2;
float angle7 = rotated*M_PI;

glm::vec4 d = c * glm::vec4(0.0, 0.0, 0.0, 1.0);
float angle = rotated;
glm::vec3 eye = glm::vec3(cos(angle),0,sin(angle));
//eye +=  glm::vec3(d.x + 3*list1.at(indix)->sc + speed, d.y, d.z);
eye =  3*list1.at(indix)->sc*speed*eye;
eye +=  glm::vec3(d.x, d.y, d.z);
 m_camera->view = glm::lookAt(eye, //Eye Position
                      glm::vec3(d.x, d.y, d.z), //Focus point
                      glm::vec3(0.0, 1, 0));

//focus point should be position of planet
// eye position should be focus point + some direction + zoom

} else {
 float angle = rotated;
   glm::vec3 eye2 = glm::vec3(cos(angle),0,sin(angle));
  eye2 =  10*speed*eye2;
eye2 +=  glm::vec3(0.0, 0, 0);
 
    m_camera->view = glm::lookAt(eye2, //Eye Position
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up
}




  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_shader->Enable();

  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  IterativeRender(m_cube);
  
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}

