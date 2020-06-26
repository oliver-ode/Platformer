#include "client/engine.h"
#include <iostream>
#include "server/networking/server.h"

int exitSuccess(){
    std::cout<<"Engine exited successfully."<<std::endl;
    return EXIT_SUCCESS;
}
int exitFailure(const char *message){
    std::cerr<<"Engine exited with error: \""<<message<<"\"."<<std::endl;
    return EXIT_FAILURE;
}


int main(){
    std::cout<<"What do you want to run: server(1) or client(2)"<<std::endl;
    int id;
    std::cin>>id;
    
    if(id==1){
        std::cout<<"Launching server"<<std::endl;
        server::Server server(8);
        server.run(sf::seconds(8));
    }
    else if(id==2){
        std::cout<<"Launching client"<<std::endl;
        client::Engine app;
        switch(app.runClient()){
            case client::Engine::Status::Exit:
            case client::Engine::Status::Ok:
                return exitSuccess();
            case client::Engine::Status::GLInitError:
                return exitFailure("OpenGL failed to initilise correctly");
        }
        return exitFailure("Unkown error");
    }
}