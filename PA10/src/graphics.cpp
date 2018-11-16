#include "graphics.h"
#include "BulletUp.h"
extern bool lFlipper;
extern bool rFlipper;
BulletUp* worldStuff; 
std::vector<Object*> list1;
int balls = 0;
Graphics::Graphics() 
{
    worldStuff = new BulletUp();
    worldStuff->a = 10;
    amb = 0.0;
    spec_tab=0.7;
    spec_cube=0.5;
    spec_cyl=0.5;
    spec_sphere= 0.9;
    x=0.0;
	cam=0.0;
	camera=0.0;
cam1=0.0;
}

Graphics::~Graphics()
{

}


bool Graphics::Initialize(int width, int height)
{
worldStuff->Initialize();
 
  #if !defined(__APPLE__) && !defined(MACOSX)
    glewExperimental = GL_TRUE;

    auto status = glewInit();
    glGetError();
    
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
  m_camera = new Camera1();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Create the object
  m_table = new Object("table4.obj",4,0,0,0,0,"tron.jpg");
  list1.push_back(m_table);
  
  m_cylinder = new Object("flipper2.obj",2,2,2,2,3,"tron1.jpg");
  list1.push_back(m_cylinder);



  
  m_cube = new Object("sphere.obj",2,-10,2.0,2,4,"tron3.jpg");
  list1.push_back(m_cube);

  m_sphere = new Object("sphere.obj",3,-2,15,-2,4,"tron3.jpg");
  list1.push_back(m_sphere);

  list1.push_back(new Object("bumper.obj",2,-3.5,2,8,8,"tron1.jpg") );
  list1.push_back(new Object("bumper.obj",2,0,2,4,8,"tron1.jpg") );
  list1.push_back(new Object("bumper.obj",2,3.5,2,8,8,"tron1.jpg") );
  list1.push_back(new Object("bumper.obj",2,3.5,2,0,8,"tron1.jpg") );
  list1.push_back(new Object("bumper.obj",2,-3.5,2,0,8,"tron1.jpg") );
  

  list1.push_back(new Object("wall.obj",0,0,0,-2.7,0,"tron2.jpg") );
 list1.push_back(new Object("tri.obj",0,0,0,0,0,"tron2.jpg") );
 list1.push_back(new Object("tri2.obj",0,0,0,0,0,"tron2.jpg") );
 list1.push_back(new Object("tri3.obj",0,0,0,0,0,"tron2.jpg") );
list1.push_back(new Object("tri4.obj",0,0,0,0,0,"tron2.jpg") );

  l_flipper = new Object("flipper3.obj",2,-2,2,2,11,"tron1.jpg");
  list1.push_back(l_flipper);
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

void Graphics::keys(unsigned int key) {
    a = key;
}

void Graphics::Update(unsigned int dt) {
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
    if(a == 6) {
        amb+=0.005;
    }
    if(a == 7) {
       amb-=0.005;
    } 
    if (a==8) {
       spec_tab+=0.01;
    }
    if (a==9) {
       spec_tab-=0.01;
    } 
    if (a==10) {
       spec_cube+=0.01;
    }
    if (a==11) { 
       spec_cube-=0.01;
    }
    if(a==12) { 
       spec_cyl+=0.01;
     }
    if(a==13) {
        spec_cyl-=0.01;
    }
    if (a==14) {
        spec_sphere+=0.01;
    }
    if (a==15) {
        spec_sphere-=0.01;
    }
    if (a==22) {
        x+=0.01;
    }
    if(a==23 && x > -0.2) {
        x-=0.01;
    }
if(a==16)
{
camera+=0.05;
}
if(a==17)
{
cam+=0.05;
}
if(a==18)
{
cam-=0.05;
}
if(a==19)
{
camera-=0.05;
}
if(a==20)
{
cam1+=0.05;
}
if(a==21)
{
cam1-=0.05;
}
    if(rFlipper) {
        m_cylinder->rigidBody->applyTorqueImpulse(btVector3(0,-15,0) );
    }
    else {
        m_cylinder->rigidBody->applyTorqueImpulse(btVector3(0,.3,0) );
    }
    for(unsigned int i=0; i<list1.size(); i++) {
        list1.at(i)->Update(dt);
    }
}

bool Graphics::Render() {
    bool rebool = true;
    glm::mat4 c;
    glm::vec4 d;
    c = m_cube->model;
    d = c * glm::vec4(0.0, 0.0, 0.0, 1.0);

  m_camera->view = glm::lookAt( glm::vec3(0.0+cam, 0.0+35+cam1,0.0-30+camera), //Eye Position
                      glm::vec3(0, 0, 0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0));
m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_shader->Enable(); // Start the correct program
   
    glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
    glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 


    //std::cout << d[0] << " "  << d[1] << " "  << d[2] << "\n";
    if(balls == 3) {
    std::cout << "GAME OVER" <<"\n";
    return false;
    }
    if(d[2] < -18 && d[0] > -9) {
    /*delete m_cube->rigidBody;
    delete m_cube->objTriMesh;
    delete m_cube->shape;
    m_cube->rigidBody = NULL;
    m_cube->objTriMesh = NULL;
    m_cube->shape = NULL;
    delete m_cube;
    m_cube = NULL;*/
    m_cube = new Object("sphere.obj",2,-10,2.0,2,4,"tron3.jpg");
    list1.at(2) = m_cube;
    balls++;
    std::cout << "Strike: " << balls <<"\n";
    }
    glUniform4f(m_shader->GetUniformLocation("AmbientProduct"),0.5,0.5,0.5,1); 
   // glUniform4f(m_shader->GetUniformLocation("spotLightPosition"),d[0],20,d[2],1);
   // glUniform1f(m_shader->GetUniformLocation("spotLightStrength"),x);
    glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),.5,.5,.5,.1);
    glUniform1f(m_shader->GetUniformLocation("Shininess"),1.0);
    glUniform4f(m_shader->GetUniformLocation("LightPosition"),0,10,0,0);
glUniform4f(m_shader->GetUniformLocation("ballposition"),d[0],d[1],d[2],0);
glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cube,spec_cube,spec_cube,1);

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
  //  glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cube,spec_cube,spec_cube,1);
    m_cube->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_table->GetModel()));
    glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_tab,spec_tab,spec_tab,1);
    m_table->Render();

    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder->GetModel()));
    glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cyl,spec_cyl,spec_cyl,1);
    m_cylinder->Render();

    //glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_sphere->GetModel()));
    //glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_sphere,spec_sphere,spec_sphere,1);
   // m_sphere->Render();

if(a==50)
{
glUniform1f(m_shader->GetUniformLocation("spot"),1.0);
glUniform4f(m_shader->GetUniformLocation("LightPosition"),0,50,0,0);
}
else if(a==51)
glUniform1f(m_shader->GetUniformLocation("spot"),0.0);
    


 for(unsigned int x = 4; x < list1.size(); x++) {
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(list1.at(x)->GetModel()));
          list1.at(x)->Render();   
      } 
  
  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
  return true;
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

