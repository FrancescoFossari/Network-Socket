#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Creazione del socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    // Configurazione dell'indirizzo del server
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);

    // Connessione al server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Errore nella connessione al server");
        exit(EXIT_FAILURE);
    }

    // Invio del messaggio al server
    const char *message = "Ciao, questo messaggio arriva dal lato client!";
    if (send(clientSocket, message, strlen(message), 0) == -1) {
        perror("Errore nell'invio del messaggio al server");
        exit(EXIT_FAILURE);
    }

    printf("Messaggio inviato al server: %s\n", message);

    // Ricezione della risposta dal server
    if (recv(clientSocket, buffer, BUFFER_SIZE, 0) == -1) {
        perror("Errore nella ricezione della risposta dal server");
        exit(EXIT_FAILURE);
    }

    printf("Risposta ricevuta dal server: %s\n", buffer);

    // Chiusura della connessione
    close(clientSocket);

    return 0;
}
