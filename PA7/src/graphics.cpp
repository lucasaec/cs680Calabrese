#include "graphics.h"
#include <vector>
Graphics::Graphics()
{
    index = -1;
}

Graphics::~Graphics()
{

}
std::vector<Object*> list;

/**
 * Allows you to update the index of the planet you are currently on
 *
 */
void Graphics::UpdateIndex() {
     index++;
     if(index >= (int) list.size() ) {
         index = -1;
     }
}


bool Graphics::Initialize(int width, int height)
{
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

   m_cube = new Object(0,.1,.1,1,1,1,1,1.3);
   list.push_back(m_cube);

 
   m_cube->children.push_back(new Object(10,1.0f,1.0f,1,1,1,3,.7f) ); 
   m_cube->children.at(0)->parent = m_cube;
   m_cube->children.at(0)->level =1;
   list.push_back(m_cube->children.at(0));

  m_cube->children.at(0)->children.push_back(new Object(15,3,3,1,1,1,3,.4) ); 
  
  m_cube->children.at(0)->children.at(0)->parent= m_cube->children.at(0);
  m_cube->children.at(0)->children.at(0)->level =2;
  list.push_back(m_cube->children.at(0)->children.at(0));
 
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

  return true;
}

/** 
 * Iteratively calls update within object.cpp
 *
 */
void Graphics::Update(unsigned int dt)
{
 
  for(unsigned int x = 0; x < list.size(); x++) {
      list.at(x)->Update(dt);
  }
}
void Graphics::Recenter() {
     m_camera->view = glm::lookAt( glm::vec3(0.0, 8.0, -16.0), //Eye Position
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up
    index = -1;
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
        list.at(index)->Reverse(x);
    }
}

/**
 * Don't call this, Reverse will call it
 */
void Graphics::IterativeReverse(int mode) {
   
   for(unsigned int x = 0; x < list.size(); x++) {        
       list.at(x)->Reverse(mode);         
   }
}

/**
 * Call this to render all objects in the list.
 */
void Graphics::IterativeRender(Object* obj) {
      for(unsigned int x = 0; x < list.size(); x++) {
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(list.at(x)->GetModel()));
          list.at(x)->Render();   
      }
}

/**
 * Renders stuff
 */
void Graphics::Render()
{
int indix = 2;
if(index > -1) {
    indix = index;
glm::mat4 a = list.at(indix)->GetModel();
glm::mat4 c = list.at(indix)->model2;
 glm::vec4 b = a * glm::vec4(1.0, 1.0, 1.0, 1.0);
glm::vec4 d = c * glm::vec4(1.0, 1.0, 1.0, 1.0);
 std::cout << indix << '\n';

 m_camera->view = glm::lookAt( glm::vec3(d[0], 0, d[2]-10*(list.at(indix)->sc)), //Eye Position
                      glm::vec3(d[0]-1, 0, d[2]), //Focus point
                      glm::vec3(0.0, 1, 0));

} else {
     Recenter();
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

