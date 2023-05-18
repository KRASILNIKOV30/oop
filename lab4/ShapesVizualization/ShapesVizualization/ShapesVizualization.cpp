#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#undef main

using namespace std;

int SCREEN_WIDTH = 1040;
int SCREEN_HEIGHT = 800;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

class CPoint
{
public:
    double x, y;
};

bool init() {
    bool ok = true;

    win = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    SDL_Quit();
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
    std::vector<CPoint> v = { vertex1, vertex2, vertex3 };

    SDL_Vertex* vertexes{ new SDL_Vertex[v.size()] };
    for (int i = 0; i < v.size(); i++)
    {
        vertexes[i] =
        {
            { (float)v[i].x, (float)v[i].y },
            { 0xff, 0xff, 0xff}
        };
    }

    SDL_Vertex triangleVertex[4] =
    {
     {
      { vertex1.x, vertex1.y }, 
        {0xff, 0xff, 0xff}
     },
     {
      { vertex2.x, vertex2.y },
     
     },
     {
      { vertex3.x, vertex3.y },
      
     },
     {
      { 100, 100 },

     }
    };

    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff);

    SDL_RenderGeometry(ren, NULL, triangleVertex, 4, NULL, 0);

    SDL_SetRenderDrawColor(ren, 0xff, 0x00, 0x00, 0xFF);

    SDL_RenderDrawLine(ren, vertex1.x, vertex1.y, vertex2.x, vertex2.y);
    SDL_RenderDrawLine(ren, vertex2.x, vertex2.y, vertex3.x, vertex3.y);
    SDL_RenderDrawLine(ren, vertex3.x, vertex3.y, vertex1.x, vertex1.y);

    SDL_RenderPresent(ren);
    
    SDL_Event e;
    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
        }
    }

    quit();
    return 0;
}