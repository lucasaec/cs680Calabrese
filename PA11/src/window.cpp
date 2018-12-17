#include <window.h>
/**
 * Where we handle functions related to the window
 */

/**
 * Window
 * Constructor for the window class
 */
Window::Window()
{
  gWindow = NULL;
}

/**
 * ~Window
 * Destructor for the window class
 */
Window::~Window()
{
  SDL_StopTextInput();
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
 

  SDL_Quit();
}
/**
 * GetWindow
 * Returns the window
 * @return SDL_Window* gWindow -pointer to the window
 */
SDL_Window* Window::GetWindow() {
    return (gWindow);
}
/**
 * GetgContext
 * Returns the window
 * @return SDL_GLContext gContext -pointer to the gContext
 */
SDL_GLContext Window::GetgContext() {
    return (gContext);
}
/**
 * Initialize
 * Initialize the window
 * @params const string &name the title of the window
 *         int* width the width of the window
 *         int* height the height of the window
 * @return SDL_GLContext gContext -pointer to the gContext
 */
bool Window::Initialize(const string &name, int* width, int* height)
{
    // Start SDL
  if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
  {
    printf("SDL failed to initialize: %s\n", SDL_GetError());
    return false;
  }

  


  // Start OpenGL for SDL
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );

  // Create window
  SDL_DisplayMode current;
  SDL_GetCurrentDisplayMode(0, &current);
  
  //use for fullscreen
  if (*height == 0 && *width == 0)
  {
    *height = current.h;
    *width = current.w;
  }

  gWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *width, *height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
  if(gWindow == NULL)
  {
    printf("Widow failed to create: %s\n", SDL_GetError());
    return false;
  }

  // Create context
  gContext = SDL_GL_CreateContext(gWindow);
  if(gContext == NULL)
  {
    printf("OpenGL context not created: %s\n", SDL_GetError());
    return false;
  }

  // Use VSync
  if(SDL_GL_SetSwapInterval(1) < 0)
  {
    printf("Unable to use VSync: %s\n", SDL_GetError());
    return false;
  }

  return true;
 

}
/**
 * Swap
 * Swaps the window
 */
void Window::Swap()
{
  SDL_GL_SwapWindow(gWindow);
}

