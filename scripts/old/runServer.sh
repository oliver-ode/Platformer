echo "Make sure to add .cpp files to g++ if they are new!"
g++ -o serverRunnable.out src/mainServer.cpp src/server/networking/server.cpp deps/glad/glad.c -Ibuild/include -lSDL2 -lSDL2_net -ldl
./serverRunnable.out