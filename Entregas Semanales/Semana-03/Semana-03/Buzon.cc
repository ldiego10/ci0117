#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "Buzon.h"
#define LABEL_SIZE 64
#define KEY 0xA12345

Buzon::Buzon(){
   this->id = msgget( KEY, 0600 | IPC_CREAT );
   if(-1 == this->id){
   	perror("");
   	exit(1);
   }
   this->creador = getpid();
}

Buzon::~Buzon(){
    int resultado;
    if (this->creador == getpid()){
        resultado = msgctl(this->id, IPC_RMID, NULL);
        if(-1 == this->id){
            perror("Buzon::~Buzon");
            exit(2);
        }
    }
}

int Buzon::Enviar(char *mensaje, int cantidad, long tipo){
    int resultado;
    m.tipo = tipo;
    m.times = cantidad;
    strcpy(m.label, mensaje);
    resultado = msgsnd(this->id, (const void *) &m, sizeof(m), IPC_NOWAIT);
    if(-1 == resultado){
    	perror("Buzon::Enviar");
        exit(3);
    }
    return resultado;
}

int Buzon::Recibir( void *mensaje, long tipo ){
    int resultado = 1;
    m.tipo = tipo;
    strcpy(m.label, (const char *)mensaje);
    int tamano = sizeof(m);
    resultado = msgrcv(this->id, &m, tamano, tipo, IPC_NOWAIT);
    if(1 == resultado){
    	perror("Buzon::Recibir");
    	exit(4);
    }
    return resultado;
}

int Buzon::Enviar( double respPi, long tipo){
    int resultado;
    p.tipo = tipo;
    p.piResp = respPi;
    resultado = msgsnd(this->id, (const void *) &p, sizeof(p), IPC_NOWAIT);
    return resultado;
}

int Buzon::Recibir(double piRespuesta, long tipo){
    int resultado = 1;
    p.tipo = tipo;
    p.piResp = piRespuesta;
    resultado = msgrcv(this->id, &p, sizeof(p), tipo, IPC_NOWAIT);
    return resultado;
}

int Buzon::Enviar( long sumaUno, long tipo){
    int resultado;
    s.tipo = tipo;
    s.sumaU = sumaUno;
    resultado = msgsnd(this->id, (const void *) &s, sizeof(s), IPC_NOWAIT);
    return resultado;
}
int Buzon::Recibir( long sumaResp, long tipo){
    int resultado = 1;
    s.tipo = tipo;
    s.sumaU = sumaResp;
    resultado = msgrcv(this->id, &s, sizeof(s), tipo, IPC_NOWAIT);
    return resultado;
}
