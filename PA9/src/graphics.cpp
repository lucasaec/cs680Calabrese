#include "graphics.h"
#include "BulletUp.h"

 BulletUp* worldStuff; 
Graphics::Graphics()
{
worldStuff = new BulletUp();
worldStuff->a = 10;
amb = 0.0;
spec_tab=0.0;
spec_cube=0.0;
spec_cyl=0.0;
spec_sphere = 0.0;
}

Graphics::~Graphics()
{

}
std::vector<Object*> list;
bool Graphics::Initialize(int width, int height)
{
worldStuff->Initialize();
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
  //std::cout << "Please choose a file for a table: bowl.obj or table4.obj" << "\n";
  //std::string response;
 // cin >> response;

  m_table = new Object("table4.obj",4,0,0,0,0);

  list.push_back(m_table);
  


  m_cylinder = new Object("cylinder.obj",2,2,2,2,2);

  list.push_back(m_cylinder);
  m_cube = new Object("cube.obj",2,-3,2.0,2,3);
 
  list.push_back(m_cube);
  m_sphere = new Object("sphere.obj",3,-2,15,-2,4);

   list.push_back(m_sphere);
  
  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER,0))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER,0))
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
void Graphics::keys(unsigned int key)
{

a=key;

}

void Graphics::Update(unsigned int dt)
{
 
      if(a == 1) {

          m_cube->rigidBody->applyCentralImpulse(btVector3(.5,0,0));
      
      }
      if(a == 2) {

          m_cube->rigidBody->applyCentralImpulse(btVector3(-.5,0,0));
      
      }
      if(a == 3) {

          m_cube->rigidBody->applyCentralImpulse(btVector3(0,0,.5));
      
      }
      if(a == 4) {

          m_cube->rigidBody->applyCentralImpulse(btVector3(0,0,-.5));
      
      }
      if(a == 5) {

          m_cube->rigidBody->applyCentralImpulse(btVector3(0,1,0));
      }
    
  if(a == 6)
{
   amb+=0.005;
 }
if (a == 7)
{
   amb-=0.005;
} 
if (a==8)
{spec_tab+=0.01;
}
if (a==9)
{spec_tab-=0.01;
}
if (a==10)
{spec_cube+=0.01;
}
if (a==11)
{spec_cube-=0.01;
}
if (a==12)
{spec_cyl+=0.01;
}
if (a==13)
{spec_cyl-=0.01;
}
if (a==14)
{spec_sphere+=0.01;
}
if (a==15)
{spec_sphere-=0.01;
}
for(unsigned int i=0; i<list.size(); i++)
{
list.at(i)->Update(dt);
}

}

void Graphics::Render()
{
 
glm::mat4 c;
c = m_cube->model;
glm::vec4 d = c * glm::vec4(0.0, 0.0, 0.0, 1.0);
//vec3 eye =  glm::vec3(0, 0, 0);
/*
  m_camera->view = glm::lookAt( glm::vec3(d.x*10, d.y*3, d.z*3), //Eye Position
                      glm::vec3(d.x, d.y, d.z), //Focus point
                      glm::vec3(0.0, 1.0, 0.0));
*/
  //clear the screen
//std::cout << d.x << ' ' << d.y << ' ' << d.z << '\n';
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 
  //Shader

  // Render the object
  //glUniform4f(m_shader->GetUniformLocation("LightPosition"),0,20,0,0);
  glUniform4f(m_shader->GetUniformLocation("AmbientProduct"),amb,amb,amb,1);
 // glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),0,0,0,1);
 // glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_tab,spec_tab,spec_tab,1);
 // glUniform1f(m_shader->GetUniformLocation("Shininess"),1.0);

glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
glUniform4f(m_shader->GetUniformLocation("LightPosition"),0,10,0,0);

  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),1,0,0.5,1);
  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cube,spec_cube,spec_cube,1);
  glUniform1f(m_shader->GetUniformLocation("Shininess"),1.0);
  m_cube->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_table->GetModel()));
 glUniform4f(m_shader->GetUniformLocation("LightPosition"),0,10,0,0);

  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),0.5,0.5,0.1,1);
  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_tab,spec_tab,spec_tab,1);
  glUniform1f(m_shader->GetUniformLocation("Shininess"),1.0);
  m_table->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder->GetModel()));
 glUniform4f(m_shader->GetUniformLocation("LightPosition"),0,10,0,0);

  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),0,0,1,1);
  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cyl,spec_cyl,spec_cyl,1);
  glUniform1f(m_shader->GetUniformLocation("Shininess"),1.0);
  m_cylinder->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_sphere->GetModel()));
  glUniform4f(m_shader->GetUniformLocation("LightPosition"),0,10,0,0);
  
  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),0,1,1,1);
  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_sphere,spec_sphere,spec_sphere,1);
  glUniform1f(m_shader->GetUniformLocation("Shininess"),1.0);
  m_sphere->Render();


 /*for(unsigned int x = 0; x < list.size(); x++) {
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(list.at(x)->GetModel()));
          list.at(x)->Render();   
      } 
*/
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

