echo "Make sure to add .cpp files to g++ if they are new!"
g++ -o runnable.out src/main.cpp src/game.cpp src/player.cpp src/event_handler.cpp deps/glad/glad.c -Ibuild/include -lSDL2 -lSDL2_net -ldl
./runnable.out