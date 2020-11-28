#include <stdlib.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

#include "Socket.h"

Socket::Socket(){
    this->socketID = socket(AF_INET, SOCK_STREAM, 0);

}
Socket::Socket(int sockfd, int domain){
    this->socketID = sockfd;
    this->socketID = socket(AF_INET, SOCK_STREAM, 0);
}
Socket::Socket(int sockfd){
    this->socketID=sockfd;

}
Socket::~Socket(){

}

int Socket::Connect(char* c,int puerto){
    struct sockaddr_in serv_addr; 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(puerto); 
    inet_pton(AF_INET, c, &serv_addr.sin_addr);
    connect(socketID, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    return 0;
}

void Socket::Close(){
    
}

int Socket::Read(void* c,int puerto){
    read(socketID, c, puerto);
    return 0;
}

int Socket::Write(void* c,int puerto){
    write(socketID, c, puerto);
    return 0;
}

int Socket::Listen(int puerto){
    listen(socketID, puerto);
    return 0;
}

int Socket::Bind(int puerto){
    struct sockaddr_in address; 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( puerto ); 
    bind(socketID, (struct sockaddr *)&address, sizeof(address));
    return 0;
}

Socket* Socket::Accept(){
    struct sockaddr_in address; 
	int addrlen = sizeof(address); 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT );
    return new Socket(accept(socketID, (struct sockaddr *)&address, (socklen_t*)&addrlen));

}
