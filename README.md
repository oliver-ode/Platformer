# Platformer

The idea behind this game is a sort of platformer dungeon crawler game. Some of the main goals and ideas for it are:
* Randomly generated caves/dungeons
* Multiplayer exploration
* Server wide market and trading system
* Item gathering, crafting and upgrading systems

## Structure of the repository
The 3 main folders currently are `src`, `scripts` and `helpers`. 

`src` has the actual source code of the game split up into 3 different areas `client` which stores the client side code. `server` stores the server side code and `common` stores code that is common between the two - mainly network type declarations.

`scripts` stores shell scripts that are used for compiling the code. It currently uses g++. I want to use CMake at some point, but I just have not got around to it yet.

`helpers` stores helper functions. Currently they are all in python and these are not designed to be run while the game is running. Currently the "main attractions" are the `randomMap_X.py` files which store different algorithms for making random cave systems. It also includes two files that turn the "map file" itself into an image for testing purposes and the other way around too.

## How to run
If you want to run the game `cd` into the `Platformer` directory and type `sh scripts/compile.sh`. It should take a couple seconds and then a new file called `runnable.out` should have appeared. To now run it type `./runnable.out` and you must have at least 2 instances running (1 being a server and 1 being a client). Make sure to start the server before the client.