
#include "engine.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

   int lookAtIndex = -1; 
extern std::vector<Object*> list1;
float speedChange=1;
extern float speed; 

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
bool reverse1 = false;
 int typeReverse = 1;

static bool disableClick=true;
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
    ImGui_ImplOpenGL3_Init("#version 130");

  
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
    if(reverse1) {
        m_graphics->Reverse(typeReverse);
        reverse1 = false;
    }
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        
        ImGui::NewFrame();
        // Update and render the graphics
bool boolean = true;

{
ImGui::Begin("Menu");
{
                 
                static bool affectAll=false;
                
                ImGui::SliderFloat("Speed", &speedChange,0 , 20);
                 ImGui::SliderFloat("Zoom", &speed,.75 , 20);
            
           //     ImGui::Checkbox("Affect All", &affectAll);
                ImGui::Checkbox("Disable Clicks", &disableClick);


  if (ImGui::BeginMenu("Zoom In"))
            {
            int choice = -1;
            if(ImGui::Button("Sun")) {
                 choice = 0;
                 ImGui::NextColumn();
                 if(m_graphics->scaledView && speed > .75) {
                      speed = .75;
                 }
            }
            if(ImGui::Button("Mercury")) {
                 choice = 1;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Venus")) {
                 choice = 2;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Earth")) {
                 choice = 3;

                 ImGui::NextColumn();
            }
            if(ImGui::Button("Moon")) {
                 choice = 11;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Mars")) {
                 choice = 4;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Phobos")) {
                 choice = 12;
                 ImGui::NextColumn();
              if(m_graphics->scaledView && speed > -3) {
                      speed = -3;
                 }
            }
            if(ImGui::Button("Jupiter")) {
                 choice = 5;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Europa")) {
                 choice = 13;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Saturn")) {
                 choice = 6;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Titan")) {
                 choice = 14;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Uranus")) {
                 choice = 7;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Ariel")) {
                 choice = 15;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Neptune")) {
                 choice = 8;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Tritan")) {
                 choice = 16;
                 ImGui::NextColumn();
            }
            if(ImGui::Button("Pluto")) {
                 choice = 9;
                 ImGui::NextColumn();
            }
	    if(ImGui::Button("Charon")) {
                 choice = 17;
                 ImGui::NextColumn();
            }
//insert code to select planet
            if(choice > -1 && choice < list1.size()) {
                lookAtIndex = choice;
            }

                ImGui::EndMenu();
            }
          if(ImGui::Button("Reverse Orbit")) {
	       reverse1 = true;
	       typeReverse = 2; 
  
	  }
	  else if(ImGui::Button("Reverse Spin")) { 
	       reverse1 = true;
	       typeReverse = 3; 
	      
	  }
          else if(ImGui::Button("Scaled View")) {
              m_graphics->scaledView = !m_graphics->scaledView;
          }
  /*     if(ImGui::Button("Undo Changes")) {
                 //Add code to revert back to normal settings
                 ImGui::NextColumn();
       }*/
       if(ImGui::Button("Reset View")) {
                 //Add code to reset view
                 m_graphics->Recenter();
                 ImGui::NextColumn();
       }

      
}
ImGui::End();
}
  
 
     m_graphics->Update(m_DT);
     m_graphics->Render();

   ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
  else if (m_event.type == SDL_KEYUP) {
      m_graphics->camerachange(0);
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    // handle key down events here
    if (m_event.key.keysym.sym == SDLK_a)
    {
      typeReverse = 1; //all
      reverse1 = true;
      
    }
    else if(m_event.key.keysym.sym == SDLK_s) {
       reverse1 = true;
       typeReverse =  2; //orbit
    }
    else if(m_event.key.keysym.sym == SDLK_d) {
       reverse1 = true;
       typeReverse =  3; //cube
    }
    else if(m_event.key.keysym.sym == SDLK_f) {
       reverse1 = true;
       typeReverse = 4; //pause
    }
    else if(m_event.key.keysym.sym == SDLK_c) {
       m_graphics->Recenter();
    }
    else if(m_event.key.keysym.sym == SDLK_z) {
         m_graphics->UpdateIndex();
    }
    else if(m_event.key.keysym.sym == SDLK_ESCAPE) {
       m_running = false;
    }

   if( m_event.key.keysym.sym == SDLK_UP)
   { 
        m_graphics -> camerachange(1);
   }
   else if( m_event.key.keysym.sym == SDLK_DOWN)
   { 
       m_graphics -> camerachange(2);
   } 
   else if( m_event.key.keysym.sym == SDLK_LEFT)
   {
       m_graphics -> camerachange(3);
   } 
   else if( m_event.key.keysym.sym == SDLK_RIGHT)
  { 
      m_graphics -> camerachange(4);
  } 
  else if( m_event.key.keysym.sym == SDLK_z)
  { 
      m_graphics -> camerachange(5);
  } 
  

  }
  else if(m_event.type == SDL_MOUSEBUTTONDOWN && !disableClick)
  {   
      if(m_event.button.button == SDL_BUTTON_LEFT) {
          typeReverse =  2;
          reverse1 = true;   
      }
      else if(m_event.button.button == SDL_BUTTON_RIGHT) {
          typeReverse =  3;
          reverse1 = true;   
      } 
      else if(m_event.button.button == SDL_BUTTON_MIDDLE) {
          typeReverse =  1;
          reverse1 = true;   
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
