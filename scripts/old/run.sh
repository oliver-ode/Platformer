echo "Make sure to add .cpp files to g++ if they are new!"
g++ -o runnable.out src/client/game/main.cpp src/client/game/game.cpp src/client/game/player.cpp src/client/game/event_handler.cpp deps/glad/glad.c -Ibuild/include -lSDL2 -lSDL2_net -ldl
./runnable.out