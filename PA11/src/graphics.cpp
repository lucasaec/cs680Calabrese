#include "graphics.h"
#include "BulletUp.h"

extern bool lFlipper;
extern bool rFlipper;
extern bool pullBack;
extern float timePulled;
bool allowCollision = true;
BulletUp* worldStuff; 
std::vector<Object*> list1;
int balls = 0;
int score = 0;
bool farLeft = false;
static void afunction(btDynamicsWorld *world, btScalar timeStep) {
    int nMfolds = world->getDispatcher()->getNumManifolds();
    bool collideOnce = false;
    //printf("numManifolds = %d\n",numManifolds);
    for (int cMfold=0;cMfold<nMfolds;cMfold++) { 
        btPersistentManifold* persistentFold =  worldStuff->dispatcher->getManifoldByIndexInternal(cMfold);
        const btCollisionObject* object1 = (persistentFold->getBody0());
        const btCollisionObject* object2 = (persistentFold->getBody1());
        if(object1->getUserIndex() == 2 || object2->getUserIndex() == 2) {
           std::cout << "Wow! 2 points!!!" << '\n';
           score += 2;
          // collideOnce = true;
           //allowCollision = false; 
           std::cout << "-----" << '\n';
        }
    }
    /* if(!collideOnce) {
         allowCollision = true;
         std::cout << "CoolBeans!!!" << '\n';
     }*/
}
Graphics::Graphics() 
{
    allowCollision = true;
    worldStuff = new BulletUp();
    worldStuff->a = 10;
    amb = 0.5;
    spec_tab=0.3;
    spec_cube=0.5;
   spotlight_strength=0.3;
    spot_rad= 0.0;
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
  
 
m_cube = new Object("test.obj",2,0,0,0,0,"wood.jpg");
list1.push_back(m_cube);


  list1.push_back(new Object("testCube.obj",2,0,15,0,2,"wood.jpg") );

list1.push_back(new Object("FunBox.obj",2,0,-15,15,99,"wood.jpg") );



 


  m_shader = new Shader();

worldStuff->dynamicsWorld->setInternalTickCallback(afunction);
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
          //m_cube->rigidBody->applyCentralImpulse(btVector3(.5,0,0));
    }
    if(a == 2) {
        // m_cube->rigidBody->applyCentralImpulse(btVector3(-.5,0,0));
    }
    if(a == 3) {
       //  m_cube->rigidBody->applyCentralImpulse(btVector3(0,0,.5));
    }
    if(a == 4) {
      //   m_cube->rigidBody->applyCentralImpulse(btVector3(0,0,-.5));
    }
    if(a == 5) {
     //    m_cube->rigidBody->applyCentralImpulse(btVector3(0,1,0));
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
   if(a==12&&spotlight_strength<0.8) { 
       spotlight_strength+=0.01;
     }
    if(a==13&&spotlight_strength>0.01) {
        spotlight_strength-=0.01;
    }
    if (a==14) {
        spot_rad+=0.005;
    }
    if (a==15) {
        spot_rad-=0.005;
    }
   
if(a==16)
{
camera+=0.1;
}
if(a==17)
{
cam+=0.1;
}
if(a==18)
{
cam-=0.1;
}
if(a==19)
{
camera-=0.1;
}
if(a==20)
{
cam1+=0.1;
}
if(a==21)
{
cam1-=0.1;
}
  
    for(unsigned int i=0; i<list1.size(); i++) {
        list1.at(i)->Update(dt);
    }
}
void Graphics::Fire(float force) {
    if(farLeft) {
        //launcher->rigidBody->applyCentralImpulse(btVector3(0,0,force));
    }
}
bool Graphics::Render() {
    bool rebool = true;
   
  
  m_camera->view = glm::lookAt( glm::vec3(0.0+cam, 0.0+35+cam1,0.0-30+camera), //Eye Position
                      glm::vec3(0, 0, 0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0));
m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_shader->Enable(); // Start the correct program
   
    glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
    glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 


    
  
 
    
    glUniform4f(m_shader->GetUniformLocation("AmbientProduct"),amb,amb,amb,1); 
   // glUniform4f(m_shader->GetUniformLocation("spotLightPosition"),d[0],20,d[2],1);
   // glUniform1f(m_shader->GetUniformLocation("spotLightStrength"),x);
    glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),.5,.5,.5,.1);
    glUniform1f(m_shader->GetUniformLocation("Shininess"),1.0);
    glUniform4f(m_shader->GetUniformLocation("LightPosition"),10,50,0,0);
glUniform4f(m_shader->GetUniformLocation("ballposition"),0,0,0,0);
glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cube,spec_cube,spec_cube,1);
glUniform1f(m_shader->GetUniformLocation("spotlight_strength"),spotlight_strength);
glUniform1f(m_shader->GetUniformLocation("spotlight_radius"),spot_rad);



   


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
    


 for(unsigned int x = 0; x < list1.size(); x++) {
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

