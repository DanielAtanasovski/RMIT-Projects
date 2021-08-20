#include <iostream>

#include "App.h"
#include "MainApp.h"

int main(int argc, char **argv)
{
    //App* app = new App("Default App");
    App* app = new MainApp("Hello World", false);

    if (app->Init() != 0) {
        std::cout << "APP::INIT::ERROR: Failed to init app" << std::endl;
        return 1;
    }
    app->Run();
    app->Done();

    return 0;
}
