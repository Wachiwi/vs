// Fabian Vetter (Teammitglied: David Schwarzmann)
#include <string.h>
#include <netdb.h>

#include "vs_socket.h"


void handleErrorAndExit(char* message){
    printf("ERROR> %s (%s)\n", message, strerror(errno));
    exit(EXIT_FAILURE);
}

void prepareSendMessage(int mode, char* buffer){
	buffer[0] = mode+48; //wegen ASCII Tabelle
	buffer[1] = ',';
	
	//rewind(stdin);
	//fseek(stdin, 0, SEEK_SET);
	freopen("/dev/tty", "rw", stdin);
	
	if(mode != VS_EXIT_COMMAND && mode != VS_SHUTDOWN_COMMAND){
		
		printf("Nachricht eingeben:\n");
		fgets(buffer + 2, VS_SERVER_READ_BUFFER_SIZE-2, stdin);
	}
	
	buffer[VS_SERVER_READ_BUFFER_SIZE-1]=VS_MESSAGE_DELIMITOR; // End of Message
}

int main(int argc, char *argv[]){
	
	char *hostname, *portno;
	int i, sd, input_mode;
	socklen_t addrlen_server;
	
	struct hostent *hp, *gethostbyname();
	struct sockaddr_in serveraddr;	
	
	char buffer[VS_SERVER_READ_BUFFER_SIZE];
	
	// Prüfen ob Hostname + Port angegeben wurden
	if(argc<3){
		fprintf(stderr,"\nBitte wie folgt aufrufen: %s hostname port\n", argv[0]);
		exit(0);
	}	
	
	hostname = (char *)malloc(strlen(argv[1])-2);	
	portno = (char *)malloc(strlen(argv[2])-2);
	
	strncpy(hostname, argv[1], strlen(argv[1]));
	strncpy(portno, argv[2], strlen(argv[2]));
	
	printf("Der TCP-Socket-Client-Textumwandlung ist gestartet\n");
	printf("Gefundener Kommandozeilenparameter IP/Host: %s\n",hostname);
	printf("Gefundener Kommandozeilenparameter Port:    %s\n",portno);
	
	// IPv4 Protokollfamilie, Datagram-Socket, automatische Protokollwahl (Bei Datagram-Socket: UDP)
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        handleErrorAndExit("Erstellen des Sockets fehlgeschlagen.");
    }
	
	// Hostname auflösen
    if((hp = gethostbyname(hostname)) == NULL)
    {
        handleErrorAndExit("Server nicht gefunden.");
    }
	
	// Server Adresse/Port festlegen
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(portno));
    bcopy((char *)hp->h_addr, (char *)&serveraddr.sin_addr.s_addr, hp->h_length);

	// Verbinden
	if (connect(sd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0){
		handleErrorAndExit("Connect failed");
	}
	
	
	// Format der API
	// 1,<TEXT>\0	--> uppercase
	// 2,<TEXT>\0 	--> lowercase
	// 0\0			--> exit
	// 9\0			--> Server shutdown
		
	// Verbindung wurde erfolgreich aufgebaut und es können ab jetzt Befehle gesendet werden
	printf("\nVerbindung hergestellt: %s %s\n",hostname,portno);
	
	
	// Hauptmenu
	do
	{
		// buffer leeren
		bzero(buffer, sizeof(buffer));
		
		// Ausgabe + Kommando lesen
		printf("Erwarte Befehl:\n");
		printf("\t%d:exit\n",VS_EXIT_COMMAND);
		printf("\t%d:uppercase\n",VS_UPPER_COMMAND);
		printf("\t%d:lowercase\n",VS_LOWER_COMMAND);
		printf("\t%d:server shutdown\n",VS_SHUTDOWN_COMMAND);
		scanf("%d",&input_mode);
		
		// Auswertung des Kommandos
		switch(input_mode)
		{
			case VS_EXIT_COMMAND: //Exit
				prepareSendMessage(input_mode, buffer);
				break;
			case VS_UPPER_COMMAND: //uppercase
				prepareSendMessage(input_mode, buffer);
				break;
			case VS_LOWER_COMMAND: //lowercase
				prepareSendMessage(input_mode, buffer);
				break;
			case VS_SHUTDOWN_COMMAND: //server shutdown
				prepareSendMessage(input_mode, buffer);
				break;
			default: printf("Input Error. Enter again\n");
				break;
		}
		
		// Senden der Nachricht
		if(sendto(sd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0){
			handleErrorAndExit("Fehler Beim Senden.");
		}
		printf("\nGesendete Nachricht: %s\n", buffer);
		
		// Antwort empfangen
		/*if(recvfrom(sd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serveraddr, &addrlen_server) < 0){
			handleErrorAndExit("Fehler beim Empfangen.");
		}*/
		
		// Versuch mit read()
		int res = read(sd, buffer, sizeof(buffer));
		if(res < 0) {
			handleErrorAndExit("Fehler beim Empfangen.");
		}
		
		
		printf("\nEmpfangene Nachricht: %s\n", buffer);		
		
	}	while(input_mode != VS_EXIT_COMMAND && input_mode != VS_SHUTDOWN_COMMAND);
	
	// Verbindung schließen
	close(sd);
	printf("\nVerbindung getrennt\n");
	return 0;
}  