#include <SDL2/SDL.h>
#include <iostream>
#undef main;

using namespace std;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

class CPoint
{
public:
    double x, y;
};

bool init() {
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Can't init SDL: " << SDL_GetError() << endl;
    }

    win = SDL_CreateWindow("Примитивы", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        cout << "Can't create window: " << SDL_GetError() << endl;
        ok = false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL) {
        cout << "Can't create renderer: " << SDL_GetError() << endl;
        ok = false;
    }
    return ok;
}

void quit() {
    SDL_DestroyWindow(win);
    win = NULL;

    SDL_DestroyRenderer(ren);
    ren = NULL;

    SDL_Quit;
}

int main(int arhc, char** argv) {
    if (!init()) {
        quit();
        system("pause");
        return 1;
    }

    CPoint vertex1 = { 10, 10 };
    CPoint vertex2 = { 90, 30 };
    CPoint vertex3 = { 10, 90 };

    SDL_Vertex triangleVertex[3] =
    {
     {
      { vertex1.x, vertex1.y }, 
      { 0, 200, 0, 0xFF },
      { 0.f, 0.f }
     },
     {
      { vertex2.x, vertex2.y },
      { 0, 200, 0, 0xFF },
      { 0.f, 0.f }
     },
     {
      { vertex3.x, vertex3.y },
      { 0, 200, 0, 0xFF },
      { 0.f, 0.f }
     }
    };

    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(ren);
    

    /*SDL_Rect rect1 = { 10, 10, 50, 50 };
    SDL_RenderFillRect(ren, &rect1);

    SDL_Rect rect2 = { 70, 10, 50, 50 };
    SDL_RenderDrawRect(ren, &rect2);*/

    SDL_RenderGeometry(ren, NULL, triangleVertex, 3, NULL, 0);

    SDL_SetRenderDrawColor(ren, 0xff, 0x00, 0x00, 0xFF);

    SDL_RenderDrawLine(ren, vertex1.x, vertex1.y, vertex2.x, vertex2.y);
    SDL_RenderDrawLine(ren, vertex2.x, vertex2.y, vertex3.x, vertex3.y);
    SDL_RenderDrawLine(ren, vertex3.x, vertex3.y, vertex1.x, vertex1.y);

    SDL_RenderPresent(ren);

    SDL_Delay(5000);

    quit();
    return 0;
}