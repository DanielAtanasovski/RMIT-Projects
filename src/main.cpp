#include <iostream>

#include "App.h"
#include "MainApp.h"

int main(int argc, char **argv)
{
    //App* app = new App("Default App");
    App* app = new MainApp("Hello World", false, 1920, 1080);

    if (app->Init() != 0) {
        std::cout << "APP::INIT::ERROR: Failed to init app" << std::endl;
        return 1;
    }
    app->Run();
    app->Done();

    return 0;
}
