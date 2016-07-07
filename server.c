#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int CreaSocket(int Porta) 
{
  int sock,errore;
  struct sockaddr_in temp;

  //Creazione socket
  sock=socket(AF_INET,SOCK_STREAM,0);
  //indirizzo
  temp.sin_family=AF_INET;
  temp.sin_addr.s_addr=INADDR_ANY;
  temp.sin_port=htons(Porta);

  //Il socket deve essere non bloccante
  errore=fcntl(sock,F_SETFL,O_NONBLOCK);

  
  errore=bind(sock,(struct sockaddr*) &temp,sizeof(temp));

  errore=listen(sock,10);
 
return sock;
} 



void ChiudiSocket(int sock)
{
  close(sock);
  return;
}



int main()
{
  

  char  buffer[512];
  int DescrittoreSocket,NuovoSocket;
  int exitCond=0;
  int Quanti;

  DescrittoreSocket=CreaSocket(1745);
  printf("Server: Attendo connessioni...\n");
  while (!exitCond)
  {
    //Test sul socket: accept non blocca, ma il ciclo while continua
    //l'esecuzione fino all'arrivo di una connessione.
    if ((NuovoSocket=accept(DescrittoreSocket,0,0))!=-1)
    {
      //Lettura dei dati dal socket (messaggio ricevuto)
      if ((Quanti=read(NuovoSocket,buffer,sizeof(buffer)))<0)
      {
         printf("errore: %d", errno);
         ChiudiSocket(NuovoSocket);
      }
      else
      {
         //Aggiusto la lunghezza 
         buffer[Quanti]=0;
         //Elaborazione dati ricevuti
         if (strcmp(buffer,"exit")==0)
              exitCond=1;
         else printf("Server: %s \n",buffer);
      }
      //Chiusura del socket temporaneo
      ChiudiSocket(NuovoSocket);
    }
  }
  //Chiusura del socket
  ChiudiSocket(DescrittoreSocket);
  printf("Server: Terminato.\n");
  

  return 0;
}


