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
void Graphics::UpdateIndex() {

     index++;
     if(index >= (int) list.size() ) {
         index = -1;
     }
    //cout << index;
}


bool Graphics::Initialize(int width, int height)
{

  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Create the object
  m_cube = new Object(0,.1,1,1,1,1,1.3);
  list.push_back(m_cube);
//float distance1, float speed1,  signed int direction1, signed int direction21, unsigned int pause1, float double21,  float scale1
  m_cube->children.push_back(new Object(6,1,1,1,1,3,.7) ); 
  m_cube->children.at(0)->parent = m_cube;
  m_cube->children.at(0)->level =1;
  list.push_back(m_cube->children.at(0));
/**
will need to set angle later so that you can change the position
  m_cube->children.push_back(new Object(8,1,1,1,1,3,.7) ); 
  m_cube->children.at(1)->parent = m_cube;
  m_cube->children.at(1)->level =1;
  list.push_back(m_cube->children.at(1));
**/
  m_cube->children.at(0)->children.push_back(new Object(3,3,1,1,1,3,.4) ); 
  
  m_cube->children.at(0)->children.at(0)->parent= m_cube->children.at(0);
  m_cube->children.at(0)->children.at(0)->level =2;
  list.push_back(m_cube->children.at(0)->children.at(0));
  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
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

void Graphics::Update(unsigned int dt)
{
  // Update the object
  if(index == -1) {
      RecursiveUpdate(m_cube, dt);
  }
  else {
      //list.at(index)->Update(dt);
      RecursiveUpdate(m_cube, dt);
  }
}

void Graphics::Reverse(int x) {
    if(index == -1) {
        RecursiveReverse(x, m_cube);
    }
    else {
        list.at(index)->Reverse(x);
    }
    //m_cube->Reverse(x);
}

void Graphics::RecursiveReverse(int y,Object * obj) {
 
      obj->Reverse(y);
      //cout << obj->distance << '\n';
      //cout << obj->children.size() << '\n';
      if(obj->children.empty() ) {
          //cout << "empty" << '\n';
      }
      else {
           for(unsigned int x = 0; x < obj->children.size(); x++) {
               //cout << x << '\n';
               RecursiveReverse(y, obj->children.at(x));
               
           }
      }
}


void Graphics::RecursiveRender(Object* obj) {
      glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(obj->GetModel()));
      obj->Render();
      //cout << obj->distance << '\n';
      //cout << obj->children.size() << '\n';
      if(obj->children.empty() ) {
          //cout << "empty" << '\n';
      }
      else {
           for(unsigned int x = 0; x < obj->children.size(); x++) {
               //cout << x << '\n';
               RecursiveRender(obj->children.at(x));
               
           }
      }
      
}

void Graphics::RecursiveUpdate(Object* obj, unsigned int dt) {
      obj->Update(dt);
      
      if(obj->children.empty() ) {
          return;
      }
      else {
           for(unsigned int x = 0; x < obj->children.size(); x++) {
               RecursiveUpdate(obj->children.at(x),dt);
           }
      }
      
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  // Render the object
   //cout << "-----" << '\n';
  RecursiveRender(m_cube);
  
  // Get any errors from OpenGL
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

