/////////////////////////////////////
// the "entry point" to the program.
/////////////////////////////////////
#include "KA24DE.hpp"

static KA24DE engine;

int main(int argc, char* args[])
{
    int exitCode {0};
    if(!engine.init())
    {
        SDL_Log("Unable to initialize program \n");
        exitCode = 1;
        return exitCode;
    }

    if(!engine.render())
    {
        SDL_Log("Renderer failed to initalize \n");
        exitCode = 2;
        return exitCode;
    }
    else
    {
        engine.update();
    }

    return exitCode;
}
