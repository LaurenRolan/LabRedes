// testecli.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
	#include <winsock2.h>
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#define	SOCKET	int
	#define INVALID_SOCKET  ((SOCKET)~0)
#endif


#define PORTA_CLI 2352 // porta TCP do cliente
#define PORTA_SRV 2032 // porta TCP do servidor
#define STR_IPSERVIDOR "143.54.12.91"
#define BUFFER_SIZE 1250

void log(unsigned long *cont);


int main(int argc, char* argv[])
{
  SOCKET s;
  struct sockaddr_in  s_cli, s_serv;

#ifdef _WIN32
	 WSADATA wsaData;
  
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		printf("Erro no startup do socket\n");
		exit(1);
	}
#endif
  

  // abre socket TCP
  if ((s = socket(AF_INET, SOCK_STREAM, 0))==INVALID_SOCKET)
  {
    printf("Erro iniciando socket\n");
    return(0);
  }

  // seta informacoes IP/Porta locais
  s_cli.sin_family = AF_INET;
  s_cli.sin_addr.s_addr = htonl(INADDR_ANY);
  s_cli.sin_port = htons(PORTA_CLI);

  // associa configuracoes locais com socket
  if ((bind(s, (struct sockaddr *)&s_cli, sizeof(s_cli))) != 0)
  {
    printf("erro no bind\n");
    close(s);
    return(0);
  }

  // seta informacoes IP/Porta do servidor remoto
  s_serv.sin_family = AF_INET;
  s_serv.sin_addr.s_addr = inet_addr(STR_IPSERVIDOR);
  s_serv.sin_port = htons(PORTA_SRV);

  // connecta socket aberto no cliente com o servidor
  if(connect(s, (struct sockaddr*)&s_serv, sizeof(s_serv)) != 0)
  {
    //printf("erro na conexao - %d\n", WSAGetLastError());
    printf("erro na conexao");
    close(s);
    exit(1);
  }

#if 0
  // envia mensagem de conexao - aprimorar para dar IP e porta
  if ((send(s, "Conectado\n", 11,0)) == SOCKET_ERROR);
  {
    printf("erro na transmissão - %d\n", WSAGetLastError());
    closesocket(s);
    return 0;
  }
#endif

  char str[BUFFER_SIZE];
  unsigned long cont;
  clock_t ultimo = clock();

  while(1)
  {
    clock_t atual = clock();
    
    if ((send(s, (const char *)&str, sizeof(str),0)) < 0)
    {
      printf("erro na transmissão\n");
      close(s);
      return 0;
    }
    cont++;
    if(atual >= (ultimo + CLOCKS_PER_SEC)) {
	log(&cont);
	ultimo = atual;
    }
  }

  // fecha socket e termina programa
  printf("Fim da conexao\n");
  close(s);
  return 0;
}

void log(unsigned long *cont) {
	fprintf(stderr, "%lu bits/seg\n", (*cont)*BUFFER_SIZE*8);
	*cont = 0;
}
