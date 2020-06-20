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

int main(){
	/*
	General initialization for both client and server
	*/
	if(SDLNet_Init()){
		SDL_Log("Unable to initialize SDLNet: %s", SDLNet_GetError());
        return 1;
	}

	// Open the desired port
	UDPsocket socketSend = SDLNet_UDP_Open(CLIENTPORT);
	UDPsocket socketRecieve = SDLNet_UDP_Open(SERVERPORT);
	if(socketSend == NULL || socketRecieve == NULL){
		SDL_Log("Failed SDLNet_UDP_Open: %s", SDLNet_GetError());
		return 2;
	}
	else{
		SDL_Log("Opened UDP connection on port %i and %i", CLIENTPORT, SERVERPORT);
	}

	// Ask SDLNet to allocate a packet for us with a given size
	const int PACKET_SIZE = 256;
	UDPpacket* packetRecv = SDLNet_AllocPacket(PACKET_SIZE);
	UDPpacket* packetSend = SDLNet_AllocPacket(PACKET_SIZE);
	if(packetSend == NULL || packetRecv == NULL){
		SDL_Log("Failed SDLNet_AllockPacket: %s", SDLNet_GetError());
		return 4;
	}
	
	/*
	Initialization for client
	*/
	IPaddress destAddress;
	if(SDLNet_ResolveHost(&destAddress, SERVERIP, SERVERPORT)){
		SDL_Log("Failed SDLNet_ResolveHost: %s", SDLNet_GetError());
		return 3;
	}
	else{
		SDL_Log("Destination Address: %s:%i", SERVERIP, SDLNet_Read16(&destAddress.port));
	}
	packetSend->address.host = destAddress.host;
	packetSend->address.port = destAddress.port;

	std::cout<<"If this is going to be acting as a server type 1, if it is a client type 2"<<std::endl;
	int setup;
	std::cin>>setup;
	bool server = false;
	if(setup==1)server=true;

	//Sending
	if(server==false){
		// Fill the packet with data
		const char data[] = "123456123456000000000000";
		// packet->data=&data;
		strcpy((char*)packetSend->data, data);
		
		std::cout<<packetSend->data<<std::endl;
		//std::cout<<sizeof(packet->data)<<std::endl;
		


		
		packetSend->len = sizeof(data);
		// Send the packet!
		SDLNet_UDP_Send( socketSend, -1, packetSend );
	}

	//Recieving
	while(server){
		// Check the socket for incoming packets
		int recv_result = SDLNet_UDP_Recv(socketRecieve, packetRecv);
		if( recv_result > 0 ){
			// The address field of the packet contains the source address
			SDL_Log("Received data from %s:%i", SDLNet_ResolveIP(&packetRecv->address), SDLNet_Read16(&packetRecv->address.port));
			// Ensure the data is null terminated so someone doesn't hack us!
			packetRecv->data[ packetRecv->maxlen-1 ] = 0;
			// Print out the contents of the packet
			//SDL_Log( "Data: \"%s\"", packet->data );
            std::cout<<"Data: "<<packetRecv->data<<std::endl;
			server = false;

            // int holder = (int)packetRecv->data;
		}
		else if( recv_result < 0 ){
			SDL_Log( "Failed SDLNet_UDP_Recv" );
			return 5;
		}
		// If we didn't receive anything, wait so we don't max out the CPU
		SDL_Delay(200);
	}

	SDLNet_FreePacket(packetSend);
	SDLNet_FreePacket(packetRecv);
	SDLNet_Quit();
	return 0;
}