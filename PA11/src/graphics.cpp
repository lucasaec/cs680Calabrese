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
        if(object2->getUserIndex() == 5 && object1->getUserIndex() == 2) {
           std::cout << "Wow! 2 points!!!" << '\n';
           //score += 2;
          // collideOnce = true;
           //allowCollision = false; 
           //std::cout << "-----" << '\n';
          // object2->getUserPointer();
           
        }
        if(object2->getUserIndex() == 2) {
 std::cout << "Wow! 2 points!!!" << '\n';
           btRigidBody * bod =  static_cast<btRigidBody*>(object1->getUserPointer());
           std::cout << bod;
           bod->setLinearVelocity(btVector3(0,0,0) );
           //object1->setUserIndex2(88);
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
  
 
m_cube = new Object("stick.obj",2,0,-4.5,-3.5,0,"Gold.jpeg");
list1.push_back(m_cube);


//list1.push_back( new Object("skybox.obj",2,0,0,0,67,"wood.jpg") );

list1.push_back(new Object("FunBox.obj",2,0,-15,15,99,"metal.jpg") );

for(int beez = 0; beez < 10; beez++) {
list1.push_back( new Object("Bee.obj",2,0,-4.5,0,4,"Bee.jpg") );
}
for(int beez = 0; beez < 10; beez++) {
list1.push_back( new Object("Bee.obj",2,0,-4.5,3,4,"Bee.jpg") );
}
for(int beez = 0; beez < 10; beez++) {
list1.push_back( new Object("Bee.obj",2,0,-4.5,5,4,"Bee.jpg") );
}
list1.push_back( new Object("GlassR.obj",2,0,-15,15,99,"Glass.jpg") );
list1.push_back( new Object("GlassL.obj",2,0,-15,15,99,"Glass.jpg") );
glassT = new Object("GlassTop.obj",2,0,-15,15,99,"Glass.jpg"); //4
list1.push_back(glassT);
 
list1.push_back( new Object("GlassF.obj",2,0,-15,15,99,"Glass.jpg") );



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
glEnable(GL_BLEND);
//glCullFace(GL_CULL_FACE);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::keys(unsigned int key) {
    a = key;
}


void Graphics::Update(unsigned int dt) {

    for(int beeNumber = list1.size() -31-5; beeNumber < list1.size() - 4; beeNumber++) {
       glm::vec4 BeePos = list1.at(beeNumber)->GetModel() * glm::vec4(0,0,0,1);
       if(BeePos.y < -28 && BeePos.x <= 2 && BeePos.x >= -4 && BeePos.z > 8.5  && BeePos.z < 14) { //May need to add more boundries later
        list1.at(beeNumber)->rigidBody->applyCentralImpulse(btVector3(0,1,0));
       }
    } // x less 2 and bigger -4 , y less than -30, z less than 14 > 8.5
  //  glm::vec4 BeePos = list1.at(list1.size()-6)->GetModel() * glm::vec4(0,0,0,1);
   // std::cout << BeePos.x << " " << BeePos.y << " " << BeePos.z << "\n";
 /* if(a == 1) {
          list1.at(list1.size()-6)->rigidBody->applyCentralImpulse(btVector3(4,0,0));
    }
    if(a == 2) {
         list1.at(list1.size()-6)->rigidBody->applyCentralImpulse(btVector3(-4,0,0));
    }
    if(a == 3) {
      list1.at(list1.size()-6)->rigidBody->applyCentralImpulse(btVector3(0,0,4));
    }
    if(a == 4) {
      list1.at(list1.size()-6)->rigidBody->applyCentralImpulse(btVector3(0,0,-4));
    }
     if(a == 6) {
      list1.at(list1.size()-6)->rigidBody->applyCentralImpulse(btVector3(0,50,0));
      std::cout << "cool";
    }*/
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
camera+=1;
}
if(a==17)
{
cam+=1;
}
if(a==18)
{
cam-=1;
}
if(a==19)
{
camera-=1;
}
if(a==20)
{
cam1+=1;
}
if(a==21)
{
cam1-=1;
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
    
 
//glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(glassT->GetModel() ) );
  //        glassT->Render();
 for(unsigned int x = 0; x < list1.size(); x++) {
          if(x >31) { //MAKES GLASS TRANSPARENT be careful where you add objects
              glUniform1f(m_shader->GetUniformLocation("opacity"),.4);
          }
          else {
               glUniform1f(m_shader->GetUniformLocation("opacity"),1);
          }
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

