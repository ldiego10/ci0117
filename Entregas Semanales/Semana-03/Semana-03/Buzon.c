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


Buzon::Buzon(){
   this->id = msgget(IPC_PRIVATE, IPC_CREAT | 0600);
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

int Buzon::Enviar( char *mensaje, int cantidad, long tipo){
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
/*
int Buzon::Recibir(long tipo, struct msgbuf * persona){
    int resultado;
    resultado = msgrcv(this->id, (void *)persona, sizeof(struct msgbuf), tipo, 0);
    if(-1 == resultado){
    	perror("Buzon::Recibir");
    	exit(6);
    }
    return resultado;
}*/
