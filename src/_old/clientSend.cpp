#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>

// "127.0.0.1" represents localhost
#define SERVERIP "127.0.0.1"

// The port of the server that we shall send packets to
#define SERVERPORT 1616

// Since we are probably running both sever and client
// on the same machine they need to have different ports
#define CLIENTPORT 1666

int main()
{
	// First we have to initalize SDLNet itself
	if( SDLNet_Init() )
	{
		SDL_Log("Unable to initialize SDLNet: %s", SDLNet_GetError());
        return 1;
	}

	// Open the desired port
	UDPsocket socket = SDLNet_UDP_Open( CLIENTPORT );
	if(socket == NULL){
		SDL_Log("Failed SDLNet_UDP_Open: %s", SDLNet_GetError());
		return 2;
	}
	else{
		SDL_Log("Opened UDP connection on port %i", CLIENTPORT);
	}

	// Ask SDLNet to allocate a packet for us with a given size
	const int PACKET_SIZE = 256;
	UDPpacket* packet = SDLNet_AllocPacket(PACKET_SIZE);
	if(packet == NULL){
		SDL_Log("Failed SDLNet_AllockPacket: %s", SDLNet_GetError());
		return 4;
	}

	// This function isn't strictly necessary as it dosen't open any ports or anything
	// but it is a nice way of setting up our address structure which we will use
	// in later functions for sending data
	IPaddress destAddress;
	if( SDLNet_ResolveHost(&destAddress, SERVERIP, SERVERPORT)){
		SDL_Log("Failed SDLNet_ResolveHost: %s", SDLNet_GetError());
		return 3;
	}
	else
	{
		SDL_Log("Destination Address: %s:%i", SERVERIP, SDLNet_Read16(&destAddress.port));
	}

	// Set the destination of the packet
	packet->address.host = destAddress.host;
	packet->address.port = destAddress.port;




	// Fill the packet with data
	const char data[] = "123456123456000000000000000000000000000000000000123456123456000000000000000000000000000000000000";
    // packet->data=&data;
	strcpy((char*)packet->data, data);
    
    std::cout<<packet->data<<std::endl;
    //std::cout<<sizeof(packet->data)<<std::endl;
	


    
    packet->len = sizeof(data);
	// Send the packet!
    SDLNet_UDP_Send( socket, -1, packet );

	// Cleanup
	SDLNet_FreePacket( packet ); // Don't forget to free the packet!
	SDLNet_Quit();
	return 0;
}