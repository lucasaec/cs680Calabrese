#include "graphics.h"
#include "BulletUp.h"
#include <SDL2/SDL_mixer.h>
extern bool lFlipper;
extern bool rFlipper;
extern bool pullBack;
extern bool gamePlaying;
extern float timePulled;
extern float gameTime;
extern bool bright;
extern int maxSeconds;
extern float purpleStrength;
extern Mix_Chunk *gudSound;
extern Mix_Chunk *badSound;
extern Mix_Chunk *beez2;
extern float adjustDiffuse;
int choice = 0;
bool formation1 = true;
  int digit1 = 0;
  int digit2 = 0;
   int digit3 = 4;
  int digit4 = 4;
extern float n; //Bee light Strength Reduction
bool allowCollision = true;
extern float strengthReduction;
BulletUp* worldStuff; 
std::vector<Object*> Glass;
std::vector<Object*> Bees;
std::vector<Object*> Other;
std::vector<Object*> Score;
std::vector<Object*> Score2;
std::vector<Object*> Time1;
std::vector<Object*> Time2;
std::vector<Object*> Lights;
int balls = 0;
int score = 0;
int beesGone = 0;
bool farLeft = false;
static void afunction(btDynamicsWorld *world, btScalar timeStep) {
    int nMfolds = world->getDispatcher()->getNumManifolds();
    bool collideOnce = false;
    //printf("numManifolds = %d\n",numManifolds);
    for (int cMfold=0;cMfold<nMfolds;cMfold++) { 
        btPersistentManifold* persistentFold =  worldStuff->dispatcher->getManifoldByIndexInternal(cMfold);
        const btCollisionObject* object1 = (persistentFold->getBody0());
        const btCollisionObject* object2 = (persistentFold->getBody1());
       
        if(gamePlaying) {
            if(object2->getUserIndex() == 54 && object1->getUserIndex() != 2 && object1->getUserIndex() != 45) {
                 Object* obj = static_cast<Object*>(object1->getUserPointer());
                 if(!obj->contactNet) {
                    //std::cout << "collisionDetect" << "\n";
                    Mix_PlayChannel(-1, beez2, 0 );
                    obj->contactNet = true;
                 }
            }
        }
        if(object1->getUserIndex() == 64 && object2->getUserIndex() != 2 && object2->getUserIndex() != 45) {
        //std::cout << "Cool"<< '\n';
            Object* obj =  static_cast<Object*>(object2->getUserPointer());
           // std::cout << obj->beePoints << '\n';
            score += obj->beePoints;
            if(gamePlaying) {
                if(obj->beePoints > 0) {
                    Mix_PlayChannel(-1, gudSound, 0 );
                }
                else {
                    Mix_PlayChannel(-1, badSound, 0 );
                }
            }
            if(score < 0) { 
                score = 0;
            }
           
            Bees.erase(Bees.begin() + (obj->beeIndex - beesGone ) );
            for(int beez = 0; beez < Bees.size(); beez++) {
                Bees.at(beez)->beeIndex = beez;
            }
         //   std::cout << "beeSize: " <<  Bees.size() << '\n';
           //  std::cout << "beeIndex: " <<  obj->beeIndex - beesGone << '\n';
            worldStuff->dynamicsWorld->removeRigidBody(obj->rigidBody);
            if(gamePlaying) {
                std::cout  << "Score: " << score << '\n';
            }
        }
        if(object2->getUserIndex() == 2 && object1->getUserIndex() != 64) {
 
           btRigidBody * bod =  (static_cast<Object*>(object1->getUserPointer()) )->rigidBody;
       //    std::cout << bod;
 btVector3 velocity = bod->getLinearVelocity();
       float speedx,speedy,speedz;
       float max = .03;
       speedx = velocity[0];
       speedy = velocity[1];
       speedz = velocity[2];
       
       if(velocity[0] > max) {
           speedx = max;
       }
       else if(velocity[0] < -max) {
           speedx = -max;
       }
       if(velocity[1] > max) {
           speedy = max;
       }
       else if(velocity[1] < -max) {
           speedy = -max;
       }
       else if(velocity[2] > max) {
           speedz = max;
       }
       else if(velocity[2] < -max) {
           speedz = -max;
       }
        bod->setLinearVelocity(btVector3(speedx,speedy,speedz) );
           //object1->setUserIndex2(88);
          // std::cout << object2->getUserIndex() << '\n'; 
          //object1->getUserIndex2();
          
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
    amb = 0.9;
    spec_cube=10;
    x=0.0;
	cam=0.0;
	camera=0.0;
cam1=0.0;
}

Graphics::~Graphics() {
}


void Graphics::reloadBees() {
        if(Bees.size() == 40) {
            return;
        } 
        for(int beez = 0; beez < Bees.size(); beez++) {
            worldStuff->dynamicsWorld->removeRigidBody(Bees.at(beez)->rigidBody);
        }
	Bees.clear();
	for(int beez = 0; beez < 40; beez++) { //note to self, figure out how to prevent bees from exiting the box
	    if(beez < 9) {
	       Bees.push_back( new Object("Bee.obj",2,0,-30,0,4,"RedBee.png") );
	       Bees.at(beez)->beePoints = -2;
	       Bees.at(beez)->beeIndex = beez;
	    }
	    else if (beez < 29) {
		Bees.push_back( new Object("Bee.obj",2,0,-30,3,4,"Bee.jpg") );
		Bees.at(beez)->beePoints = 1;
		Bees.at(beez)->beeIndex = beez;
	    }
	    else {
	       Bees.push_back( new Object("Bee.obj",2,0,-30.5,5,4,"GreenBee.png") );
	       Bees.at(beez)->beePoints = 3;
	       Bees.at(beez)->beeIndex = beez;
	    }
	}
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
  
 Other.push_back( new Object("skybox.obj",2,0,0,0,67,"Daylight Box UV.png") );
 Other.push_back( new Object("soundDetect.obj",2,0,-4.5,-3.5,54,"Daylight Box UV.png") );
Other.push_back(new Object("stick.obj",2,0,-4.5,-3.5,0,"Gold.jpeg"));

Other.push_back( new Object("detector.obj",2,0,-15,15,64,"Gold.jpeg") );


Other.push_back(new Object("FunBox.obj",2,0,-15,15,99,"metal.jpg") );
Other.push_back(new Object("titlePlate.obj",2,0,-15,15,99,"title.png") );
Other.push_back(new Object("wall.obj",2,0,-15,15,99,"tree.png") );
Other.push_back(new Object("Frame3.obj",2,0,-15,15,99,"Gold.jpeg") );
Other.push_back(new Object("Frame1.obj",2,0,-15,15,99,"Gold.jpeg") );
Other.push_back(new Object("Frame2.obj",2,0,-15,15,99,"Gold.jpeg") );
Other.push_back(new Object("thing.obj",2,0,-15,15,99,"gold.png") );
for(int beez = 0; beez < 40; beez++) { //note to self, figure out how to prevent bees from exiting the box
    if(beez < 9) {
       Bees.push_back( new Object("Bee.obj",2,0,-30,0,4,"RedBee.png") );
       Bees.at(beez)->beePoints = -2;
       Bees.at(beez)->beeIndex = beez;
    }
    else if (beez < 29) {
        Bees.push_back( new Object("Bee.obj",2,0,-30,3,4,"Bee.jpg") );
        Bees.at(beez)->beePoints = 1;
        Bees.at(beez)->beeIndex = beez;
    }
    else {
       Bees.push_back( new Object("Bee.obj",2,0,-30.5,5,4,"GreenBee.png") );
       Bees.at(beez)->beePoints = 3;
       Bees.at(beez)->beeIndex = beez;
    }
}
//std::cout << Bees.size();
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"Null.png") );
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"0.png") );
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"1.png") );
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"2.png") );
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"3.png") );
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"4.png") );
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"5.png") );
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"6.png") );
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"7.png") );
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"8.png") );
Score.push_back( new Object("digitPoints1.obj",2,0,0,0,67,"9.png") );

Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"Null.png") );
Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"0.png") );
Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"1.png") );
Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"2.png") );
Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"3.png") );
Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"4.png") );
Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"5.png") );
Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"6.png") );
Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"7.png") );
Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"8.png") );
Score2.push_back( new Object("digitPoints2.obj",2,0,-15,15,67,"9.png") );

Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"Null.png") );
Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"0.png") );
Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"1.png") );
Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"2.png") );
Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"3.png") );
Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"4.png") );
Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"5.png") );
Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"6.png") );
Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"7.png") );
Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"8.png") );
Time1.push_back( new Object("digitTime1.obj",2,0,-15,15,67,"9.png") );

Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"Null.png") );
Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"0.png") );
Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"1.png") );
Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"2.png") );
Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"3.png") );
Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"4.png") );
Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"5.png") );
Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"6.png") );
Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"7.png") );
Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"8.png") );
Time2.push_back( new Object("digitTime2.obj",2,0,-15,15,67,"9.png") );


Other.push_back( new Object("pot.obj",2,0,-15,15,99,"red.png") );
Other.push_back( new Object("holder.obj",2,0,-15,15,99,"Gold.jpeg") );
Lights.push_back( new Object("light1.obj",2,0,-15,15,99,"BeeLight.png") );
Lights.push_back( new Object("light2.obj",2,0,-15,15,99,"BeeLight.png") );
Lights.push_back( new Object("light3.obj",2,0,-15,15,99,"BeeLight.png") );
Lights.push_back( new Object("light4.obj",2,0,-15,15,99,"BeeLight.png") );
Lights.push_back( new Object("light5.obj",2,0,-15,15,99,"BeeLight.png") );
Lights.push_back( new Object("light6.obj",2,0,-15,15,99,"BeeLight.png") );
Glass.push_back( new Object("GlassR.obj",2,0,-15,15,99,"Glass.jpg") );
Glass.push_back( new Object("GlassL.obj",2,0,-15,15,99,"Glass.jpg") );
glassT = new Object("GlassTop.obj",2,0,-15,15,99,"Glass.jpg"); //4
Glass.push_back(glassT);
 
Glass.push_back( new Object("GlassF.obj",2,0,-15,15,99,"Glass.jpg") );



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
  worldStuff->dynamicsWorld->stepSimulation(dt, 60); 
if(gamePlaying) {

    for(int beeNumber = 0; beeNumber < Bees.size(); beeNumber++) {
       glm::vec4 BeePos = Bees.at(beeNumber)->GetModel() * glm::vec4(0,0,0,1);
       if(BeePos.y < -25 && BeePos.x <= 2 && BeePos.x >= -4 && BeePos.z > 8.5  && BeePos.z < 14) { //May need to add more boundries later
        Bees.at(beeNumber)->rigidBody->applyCentralImpulse(btVector3(0,1,0));
       }// Jar Spot: 9.79652 -22.8617 16.285
       if(BeePos.y < -40) {
           //std::cout << "glitched ball, modify timestep" << "\n";
       }
       if(BeePos.y < -30) {
           Bees.at(beeNumber)->contactNet = false;
          // std::cout << "just checking" << "\n";
       }
    } 
}
   
 //glm::vec4 LightPos = Lights.at(4)->GetModel() * glm::vec4(0,0,0,1);
 //std::cout << "LightPos.x: " << LightPos.x << " LightPos.y: " << LightPos.y << " LightPos.z: " << LightPos.z << "\n";
//ambient light  
  if(a == 6 && amb<=2.5) {
        amb+=0.005;
    }
    if(a == 7&& amb>=-0.5) {
       amb-=0.005;
    } 
//spotlight
    if (a==8 && n<=10) {
       n+=0.01;
    }
    if (a==9 && n>=4) {
      n-=0.01;
    } 

    if (a==10 && spec_cube<=20.0) {// key 3 lol

       spec_cube+=0.05;
    }
    if (a==11 && spec_cube>=0.0) { 

       spec_cube-=0.05;
    }
   
if(a==16 && camera<=11)
{
camera+=1;
}
if(a==17 && cam<=30)
{
cam+=1;
}
if(a==18 && cam >=-35)
{
cam-=1;
}
if(a==19 && camera>=-50)
{
camera-=1;
}
if(a==20&& cam1<=15)
{
cam1+=1;
}
if(a==21&&cam1>=-50)
{
cam1-=1;
}
  
    for(unsigned int i=0; i<Other.size(); i++) {
        Other.at(i)->Update(dt);
    }
    for(unsigned int i=0; i<Bees.size(); i++) {
        Bees.at(i)->Update(dt);
    }
    for(unsigned int i=0; i<Lights.size(); i++) {
        Lights.at(i)->Update(dt);
    }
    for(unsigned int i=0; i<Glass.size(); i++) {
        Glass.at(i)->Update(dt);
    }
 
  
  Score.at(digit1)->Update(dt);
  Score2.at(digit2)->Update(dt);
  Time1.at(digit3)->Update(dt);
  Time2.at(digit4)->Update(dt);
}
void Graphics::Fire(float force) {
    if(farLeft) {
        //launcher->rigidBody->applyCentralImpulse(btVector3(0,0,force));
    }
}
bool Graphics::Render() {
    bool rebool = true;
    float reduce = .6;
    float zero = 1;
    if(bright) {
       reduce = 0;
       zero = 1;
    }
    else {
       zero = 0;
    }
  
  m_camera->view = glm::lookAt( glm::vec3(0.0+cam, 0.0+35+cam1,0.0-30+camera), //Eye Position
                      glm::vec3(0, 0, 0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0));
m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
 m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_shader->Enable(); // Start the correct program
   
    glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
    glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

/** Christina please make the skybox brighter, But i don't want to see any seams **/
 glUniform4f(m_shader->GetUniformLocation("AmbientProduct"),1.1-reduce,1.1-reduce,1.1-reduce,1); 
    glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),1-reduce+adjustDiffuse,1-reduce+adjustDiffuse,1-reduce+adjustDiffuse,1);
    glUniform1f(m_shader->GetUniformLocation("Shininess"),1);
    glUniform4f(m_shader->GetUniformLocation("LightPosition"),0,0,0,0);
glUniform4f(m_shader->GetUniformLocation("ballposition"),0,0,0,0);
glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),0,0,0,1);
glUniform1f(m_shader->GetUniformLocation("opacity"),1);
glUniform1f(m_shader->GetUniformLocation("strength"),n);
glUniform1f(m_shader->GetUniformLocation("purpleStrength"),purpleStrength);
  //this renders the skybox
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(Other.at(0)->GetModel()));
          Other.at(0)->Render();  
  
 
    
    glUniform4f(m_shader->GetUniformLocation("AmbientProduct"),amb-reduce,amb-reduce,amb-reduce,1); 

    glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),.5-reduce+adjustDiffuse,.5-reduce+adjustDiffuse,.5-reduce+adjustDiffuse,.1);
    glUniform1f(m_shader->GetUniformLocation("Shininess"),100);
    glUniform4f(m_shader->GetUniformLocation("LightPosition"),0,-4,10,0);//(moves it very far away)
glUniform4f(m_shader->GetUniformLocation("ballposition"),0,0,0,0);
glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cube,spec_cube,spec_cube,1);




   


    //glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_sphere->GetModel()));
    //glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_sphere,spec_sphere,spec_sphere,1);
   // m_sphere->Render();



glUniform1f(m_shader->GetUniformLocation("opacity"),1);
 
//glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(glassT->GetModel() ) );
  //        glassT->Render();
  if(gamePlaying) {
      digit1 = score/10 + 1;
      digit2 = score % 10 + 1;
      digit3 = (maxSeconds-(int)gameTime/1000)/10 + 1;
      digit4 = (maxSeconds-(int)gameTime/1000) % 10 + 1;
  }
  else {
    digit3 = 0;
    digit4 = 0;   
    score = 0;
  }
  glm::vec4 LightPos[1];
  float probablyZ = 25;
  choice = (int)gameTime/200 % 6;
   if(choice == 0) {
      LightPos[0] = glm::vec4(8.5,-9.9,probablyZ,1);//-10 to the right, to to the left
   }
   if(choice == 4) {
      LightPos[0] = glm::vec4(-.5,-23,probablyZ,1);
   }
   if(choice == 2) {
      LightPos[0] = glm::vec4(-9.4,-10.7,probablyZ,1);
   }
   if(choice == 3) {
      LightPos[0] = glm::vec4(8.5,-18.5,probablyZ,1);//-10 to the right, to to the left 
   }
   if(choice == 1) {
      LightPos[0] = glm::vec4(-.5,-12.6,probablyZ,1);
   }
   if(choice == 5) {
      LightPos[0] = glm::vec4(-9.4,-18,probablyZ,1);
   }
  
     
      glUniform4fv(m_shader->GetUniformLocation("LightPos"), 3, glm::value_ptr(LightPos[0]) ); 
  glUniform4f(m_shader->GetUniformLocation("PAmbientProduct"),1,0,1,1); 
  glUniform4f(m_shader->GetUniformLocation("PDiffuseProduct"),1,0,1,1);
  glUniform4f(m_shader->GetUniformLocation("PSpecularProduct"),1,0,1,1);
   
  if(gamePlaying) {
      glUniform4f(m_shader->GetUniformLocation("LAmbientProduct"),amb,amb,amb,1); 
      glUniform4f(m_shader->GetUniformLocation("LDiffuseProduct"),.9,.9,0,1);
      glUniform4f(m_shader->GetUniformLocation("LSpecularProduct"),spec_cube,spec_cube,spec_cube,1);
  }
  else {
      glUniform4f(m_shader->GetUniformLocation("LAmbientProduct"),0,0,0,1); 
      glUniform4f(m_shader->GetUniformLocation("LDiffuseProduct"),0,0,0,.1);
      glUniform4f(m_shader->GetUniformLocation("LSpecularProduct"),0,0,0,1);
  }
  glUniform4f(m_shader->GetUniformLocation("AmbientProduct"),amb,amb,amb,1); 
  glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),.5,.5,.5,.1);
    
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(Score.at(digit1)->GetModel()));
  Score.at(digit1)->Render(); 
glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(Score2.at(digit2)->GetModel()));
  Score2.at(digit2)->Render();

  
 glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(Time1.at(digit3)->GetModel()));
  Time1.at(digit3)->Render(); 
 glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(Time2.at(digit4)->GetModel()));
  Time2.at(digit4)->Render(); 
  glUniform4f(m_shader->GetUniformLocation("AmbientProduct"),amb-reduce,amb-reduce,amb-reduce,1); 
    glUniform4f(m_shader->GetUniformLocation("DiffuseProduct"),.5-reduce+adjustDiffuse,.5-reduce+adjustDiffuse,.5-reduce+adjustDiffuse,.1);
  
 for(unsigned int x = 1; x < Other.size(); x++) {   
          if(Other.at(x)->physics != 64 && Other.at(x)->physics != 54) {
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(Other.at(x)->GetModel()));
          Other.at(x)->Render();   
          }
          if(x > Other.size() - 3) {
           glUniform1f(m_shader->GetUniformLocation("Shininess"),5);
          }
          else {
             glUniform1f(m_shader->GetUniformLocation("Shininess"),150);
          }
  } 
glUniform1f(m_shader->GetUniformLocation("Shininess"),10);
glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cube,spec_cube,spec_cube,1);
  for(unsigned int x = 0; x < Bees.size(); x++) {   
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(Bees.at(x)->GetModel()));
          Bees.at(x)->Render();   
  } 
glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cube*zero,spec_cube*zero,spec_cube*zero,1);
glUniform1f(m_shader->GetUniformLocation("Shininess"),10);
  glUniform1f(m_shader->GetUniformLocation("opacity"),.7);
//glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cube,spec_cube,spec_cube,1);
  for(unsigned int x = 0; x < Lights.size(); x++) {   
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(Lights.at(x)->GetModel()));
          Lights.at(x)->Render();   
  } 
glUniform4f(m_shader->GetUniformLocation("SpecularProduct"),spec_cube-reduce*9,spec_cube-reduce*9,spec_cube-reduce*9,1);
  glUniform1f(m_shader->GetUniformLocation("opacity"),.3);
  for(unsigned int x = 0; x < Glass.size(); x++) {   
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(Glass.at(x)->GetModel()));
          Glass.at(x)->Render();   
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

