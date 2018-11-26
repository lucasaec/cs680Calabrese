
#include "engine.h"
bool lFlipper = false;
bool rFlipper = false;
bool pullBack = false;

float rotationAmount= 0;


  int mousex;
  int mousey;
float timePulled = 0;
Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}
 bool rotateLeft = false;
  bool rotateRight = false;
void Engine::Run()
{
  m_running = true;

//Uint32 SDL_GetMouseState(int* x,
                       //  int* y)
  while(m_running)
  {
    // Update the DT
    m_DT = getDT();
    SDL_GetMouseState(&mousex,&mousey);
    mousex -= 400;
    mousey += 150;
    mousey *= -1;
   // std::cout << "MOUSEX: " << mousex << " MOUSEY: " << mousey << '\n';
    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();
    }
  
    if(rotateLeft) {
    rotationAmount -= .1; //cinsider multiplying by DT if it's not 0.
}
if(rotateRight) {
 rotationAmount += .1;
}
//std::cout << getDT()<< '\n';
    // Update and render the graphics
    m_graphics->Update(m_DT);
    m_running = m_running && m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}
unsigned int a;

void Engine::Keyboard()
{
 
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  if(m_event.type == SDL_MOUSEBUTTONDOWN)
  {   
      if(m_event.button.button == SDL_BUTTON_LEFT) {
          rotateLeft = true;
          rotateRight = false;
      }
      else if(m_event.button.button == SDL_BUTTON_RIGHT) {
          rotateRight = true;
          rotateLeft = false;
      } 
  }
  if(m_event.type == SDL_MOUSEBUTTONUP)
  {   
      if(m_event.button.button == SDL_BUTTON_LEFT) {
          rotateLeft = false;
      }
      else if(m_event.button.button == SDL_BUTTON_RIGHT) {
          rotateRight = false;
      } 
  }
  if (m_event.type == SDL_KEYDOWN)
  {
    // handle key down events here
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
  
	else if(m_event.key.keysym.sym == SDLK_LEFT)
        {
	a=1;
	}
	else if(m_event.key.keysym.sym == SDLK_RIGHT)
        {
	a=2;
	}
		else if(m_event.key.keysym.sym == SDLK_UP)
        {
	a=3;
	}
	else if(m_event.key.keysym.sym == SDLK_DOWN)
        {
	a=4;
	}
         else if(m_event.key.keysym.sym == SDLK_SPACE)
        {
	  a=5;
	}
	else if(m_event.key.keysym.sym == SDLK_a)
        {
	  a=6;
	}
	else if(m_event.key.keysym.sym == SDLK_s)
        {
	  a=7;
	}
	else if(m_event.key.keysym.sym == SDLK_1)
        {
	  a=8;
	}
	else if(m_event.key.keysym.sym == SDLK_2)
        {
	  a=9;
	}
	else if(m_event.key.keysym.sym == SDLK_3)
        {
	  a=10;
	}
	else if(m_event.key.keysym.sym == SDLK_4)
        {
	  a=11;
	}
	else if(m_event.key.keysym.sym == SDLK_5)
        {
	  a=12;
	}
	else if(m_event.key.keysym.sym == SDLK_6)
        {
	  a=13;
	}
	else if(m_event.key.keysym.sym == SDLK_7)
        {
	  a=14;
	}
	else if(m_event.key.keysym.sym == SDLK_8)
        {
	  a=15;
	}
if (m_event.key.keysym.sym == SDLK_KP_8)
{
a=16;
}
else if(m_event.key.keysym.sym == SDLK_KP_4)
{
a=17;
}
else if(m_event.key.keysym.sym == SDLK_KP_6)
{
a=18;
}
else if(m_event.key.keysym.sym == SDLK_KP_5)
{
a=19;
}
else if(m_event.key.keysym.sym == SDLK_KP_1)
{
a=20;
}
else if(m_event.key.keysym.sym == SDLK_KP_2)
{
a=21;
}



     if(m_event.key.keysym.sym == SDLK_b)
     {
		      m_graphics->m_shader->Initialize();
		      m_graphics->m_shader->AddShader(GL_VERTEX_SHADER, 1);
		      m_graphics->m_shader->AddShader(GL_FRAGMENT_SHADER, 1);
		      m_graphics->m_shader->Finalize();
		      m_graphics->m_shader->Enable();
        
        
        }
        else if(m_event.key.keysym.sym == SDLK_n)
        {
		      m_graphics->m_shader->Initialize();
		      m_graphics->m_shader->AddShader(GL_VERTEX_SHADER, 0);
		      m_graphics->m_shader->AddShader(GL_FRAGMENT_SHADER, 0);
		      m_graphics->m_shader->Finalize();
		      m_graphics->m_shader->Enable();
		      
		      
        }
if(m_event.key.keysym.sym == SDLK_p)
	a=50;
if(m_event.key.keysym.sym == SDLK_l)
	a=51;
}
else if(m_event.type == SDL_KEYUP)
{
  a = 0;
}  
m_graphics->keys(a);


}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}