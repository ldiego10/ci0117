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
#define KEY 0xA134

Buzon::Buzon(int x){
   this->id = msgget( x, 0600 | IPC_CREAT );
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

int Buzon::Enviar(int valorV, long tipo){
    int resultado;
    pa.tipo = tipo;
    pa.valor = valorV;
    resultado = msgsnd(this->id, (const void *) &pa, sizeof(pa), IPC_NOWAIT);
    if(-1 == resultado){
    	perror("Buzon::Enviar");
        exit(3);
    }
    return resultado;
}
int Buzon::Recibir(int valorV, long tipo){
    int resultado = 1;
    pa.tipo = tipo;
    pa.valor = valorV;
    resultado = msgrcv(this->id, &pa, sizeof(pa), tipo, IPC_NOWAIT);
    return resultado;
}
