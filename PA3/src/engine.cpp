
#include "engine.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

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
bool reverse = false;
 int typeReverse = 1;


void Engine::Run()
{
  m_running = true;
/////////////////////////////// 
    SDL_Window* window = m_window->GetWindow();
    SDL_GLContext gl_context = m_window->GetgContext();
///////////////////////////////
    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("version #330");
    
    // Setup style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();   
    
    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      ImGui_ImplSDL2_ProcessEvent(&m_event);
      Keyboard();
    }
    if(reverse) {
        m_graphics->Reverse(typeReverse);
        reverse = false;
    }
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        
        ImGui::NewFrame();
        // Update and render the graphics

{
ImGui::Begin("Hello, World!");
ImGui::Text("Some text.");
ImGui::End();
}
     ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 
     m_graphics->Update(m_DT);
     m_graphics->Render();
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Swap to the Window
    m_window->Swap();
    
  }
   ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    // handle key down events here
    if (m_event.key.keysym.sym == SDLK_a)
    {
      typeReverse = 1; //all
      reverse = true;
      
    }
    else if(m_event.key.keysym.sym == SDLK_s) {
       reverse = true;
       typeReverse =  2; //orbit
    }
    else if(m_event.key.keysym.sym == SDLK_d) {
       reverse = true;
       typeReverse =  3; //cube
    }
    else if(m_event.key.keysym.sym == SDLK_f) {
       reverse = true;
       typeReverse = 4; //pause
    }
    else if(m_event.key.keysym.sym == SDLK_z) {
         m_graphics->UpdateIndex();
    }
    else if(m_event.key.keysym.sym == SDLK_ESCAPE) {
       m_running = false;
    }
  }
  else if(m_event.type == SDL_MOUSEBUTTONDOWN)
  {   
      if(m_event.button.button == SDL_BUTTON_LEFT) {
          typeReverse =  2;
          reverse = true;   
      }
      else if(m_event.button.button == SDL_BUTTON_RIGHT) {
          typeReverse =  3;
          reverse = true;   
      } 
      else if(m_event.button.button == SDL_BUTTON_MIDDLE) {
          typeReverse =  1;
          reverse = true;   
      } 
 
  }
  
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
