#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
using namespace std;

class Window
{
  public:
    Window();
    ~Window();
    bool Initialize(const string &name, int* width, int* height);
    void Swap();
     SDL_Window* GetWindow();
    SDL_GLContext GetgContext();


	static Mix_Chunk *pointsSound;
	static Mix_Music *background_music;
  private:
    SDL_Window* gWindow;
    SDL_GLContext gContext;
};

#endif /* WINDOW_H */
