#include "engine.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <SDL2/SDL_mixer.h>
/** 
 * engine 
 * This runs the game
 */
//Unused variables
bool lFlipper = false;
bool rFlipper = false;
bool pullBack = false;


bool bright = true; //brightness
bool gamePlaying = false; //is the game playing?
float allowClick = true; // unused, i wanted to prevent the net from spinnning when clinking menus though
float gameTime = 0; //game time
int maxSeconds = 0; // max seconds for the current session
float rotationAmount= 0; // how much the net will be rotated left or right

//sound stuff
Mix_Music *beeMusic; 
Mix_Chunk *gudSound;
Mix_Chunk *badSound;
Mix_Chunk *beez;
Mix_Chunk *beez2;

//x and y pos of mouse
  int mousex;
  int mousey;

float timePulled = 0; //unused
bool mute = false;
float purpleStrength =0;//unused

//volume
int soundVolume = 40; 
int musicVolume = 100;

float adjustDiffuse = 0; //diffuse adjustmet
float n= 6.0; // beelight strength adjustment

/** 
 * Engine
 * The Constructor for the engine
 * @param string name - the name of the window, int width - the width of the window, int height of the window
 */
Engine::Engine(string name, int width, int height)
{
//set up the audio stuff
Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2000);
  Mix_AllocateChannels(10);
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
Mix_Volume(-1,soundVolume);
Mix_VolumeMusic(musicVolume);
beeMusic =Mix_LoadMUS("../Audio/BeeMusic3.wav");
gudSound =Mix_LoadWAV("../Audio/GudSound.wav");
badSound =Mix_LoadWAV("../Audio/badSound.wav");
beez =Mix_LoadWAV("../Audio/bees1.wav");
beez2 =Mix_LoadWAV("../Audio/bees.wav");
}

/** 
 * Engine
 * The Constructor for the engine, but with a full screen
 * @param string name - the name of the window
 */
Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;

}

/** 
 * ~Engine
 * The destructor of the engine
 * also removes sound stuff
 */
Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
Mix_FreeMusic(beeMusic);
Mix_FreeChunk(gudSound);
Mix_FreeChunk(badSound);
Mix_FreeChunk(beez);
}

/** 
 * Initialize
 * Initialize everything and run the program
 * This is where we add menus and detect interaction
 * @return bool if it was successful
 */
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
//Uint32 SDL_GetMouseState(int* x,
                       //  int* y)
  while(m_running)
  {
    // Update the DT
    if(!mute) { //mute/unmute sound
        Mix_Volume(-1,soundVolume);
        Mix_VolumeMusic(musicVolume);

    }
    m_DT = getDT();
    if(gamePlaying) { //calculate amount of time played
        gameTime += m_DT;
    }
    if(gamePlaying && gameTime/1000.0f >= maxSeconds) { //check if gameover
          std::cout << "game over" << "\n";
          gameTime = 0;
          gamePlaying = false;
          Mix_FadeOutMusic(0);
    } 
    SDL_GetMouseState(&mousex,&mousey); //used for rotation of net
    mousex -= 400;
    mousey += 150;
    mousey *= -1;
  //  std::cout << "MOUSEX: " << mousex << " MOUSEY: " << mousey << '\n';
    if(mousex > 500) {
        mousex = 500;
    }
    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      ImGui_ImplSDL2_ProcessEvent(&m_event);
      Keyboard();
    }
  //  allowClick = true;
    if(rotateLeft) {
    rotationAmount -= .1; //consider multiplying by DT if it's not 0.
}
if(rotateRight) {
 rotationAmount += .1;
}
//std::cout << getDT()<< '\n';
    // Update and render the graphics
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);

	ImGui::NewFrame();
	m_graphics->Update(m_DT);
	m_running = m_running && m_graphics->Render();
{
ImGui::Begin("Menu");//menu stuff
     if (ImGui::BeginMenu("Start")) {
          //  allowClick = false;
            if(ImGui::Button("30 Seconds") && !gamePlaying) {
                maxSeconds = 30;
                gamePlaying = true;
                m_graphics->reloadBees();
                gameTime = 0;             
                Mix_PlayMusic(beeMusic,-1);
                Mix_PlayChannel(-1, beez, 0 );

            }
            if(ImGui::Button("60 Seconds") && !gamePlaying) {
                maxSeconds = 60;
                gamePlaying = true;
                m_graphics->reloadBees();
                gameTime = 0;
                Mix_PlayMusic(beeMusic,-1);
                Mix_PlayChannel(-1, beez, 0 );
            }
            if(ImGui::Button("90 Seconds")&& !gamePlaying) {
                maxSeconds = 90;
                gamePlaying = true;
                m_graphics->reloadBees();
                gameTime = 0;
                Mix_PlayMusic(beeMusic,-1);
                Mix_PlayChannel(-1, beez, 0 );
            }
              
     ImGui::EndMenu(); 
     }
     if(ImGui::Button("Stop") && gamePlaying) {
         gamePlaying = false;
         maxSeconds = 0;
         Mix_FadeOutMusic(0);
        // allowClick = false;
     }
     if(ImGui::Button("Dark/Bright")) {
         bright = !bright;         
        // allowClick = false;
     }
      ImGui::SliderFloat("Ambient Light", &m_graphics->amb,0 , 3);
      ImGui::SliderFloat("Diffuse Light", &adjustDiffuse,-10 , 10);
      ImGui::SliderFloat("Specular Light", &m_graphics->spec_cube,0 , 20);
      ImGui::SliderFloat("Bee Light Strength Reduction",&n ,4, 10);
     if(ImGui::Button("Default Lighting")) { 
          m_graphics->amb = .9;
          adjustDiffuse = 0;
          m_graphics->spec_cube = 10;
          n = 6.0f;
     }
     if(ImGui::Button("Per Fragment")) {
              m_graphics->m_shader->Initialize();
	      m_graphics->m_shader->AddShader(GL_VERTEX_SHADER, 0);
	      m_graphics->m_shader->AddShader(GL_FRAGMENT_SHADER, 0);
	      m_graphics->m_shader->Finalize();
	      m_graphics->m_shader->Enable();       
     }
     if(ImGui::Button("Per Vertex")) {
              m_graphics->m_shader->Initialize();
	      m_graphics->m_shader->AddShader(GL_VERTEX_SHADER, 1);
	      m_graphics->m_shader->AddShader(GL_FRAGMENT_SHADER, 1);
	      m_graphics->m_shader->Finalize();
	      m_graphics->m_shader->Enable();       
     }
     ImGui::SliderInt("Sound Volume", &soundVolume,0 , 128);
      ImGui::SliderInt("Music Volume", &musicVolume,0 , 128);
  
     if(ImGui::Button("Mute/Unmute")) {
         mute = !mute;  
         if(mute) {  
             Mix_Volume(-1,0);
             Mix_VolumeMusic(0);     
         }
         else {
              Mix_Volume(-1,soundVolume);
              Mix_VolumeMusic(musicVolume);
         }
     }
ImGui::End();
}
 ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // Swap to the Window
    m_window->Swap();

  }
ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
unsigned int a;

/** 
 * Keyboard
 * Detect Keys and mouse buttons Pressed
 */
void Engine::Keyboard()
{
 
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  if(m_event.type == SDL_MOUSEBUTTONDOWN && allowClick)
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
//ambient light
	else if(m_event.key.keysym.sym == SDLK_a)
        {
	  a=6;
	}
	else if(m_event.key.keysym.sym == SDLK_s)
        {
	  a=7;
	}
//spotlight
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
/**
 * getDT
 * get the time since the previous frame
 * @return unsigned int the time spent since the previous frame in milliseconds
 */
unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}
/**
 * GetCurrentTimeMillis
 * get the current time in milliseconds
 * @return long long the current time in milliseconds
 */
long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
