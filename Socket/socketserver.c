#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // Creazione del socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    // Configurazione dell'indirizzo del server
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Binding
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Errore nel binding");
        exit(EXIT_FAILURE);
    }

    // In attesa di connessioni
    if (listen(serverSocket, 5) == -1) {
        perror("Errore nell'ascolto delle connessioni");
        exit(EXIT_FAILURE);
    }

    printf("Server in ascolto sulla porta %d...\n", PORT);

    // Accettazione di una connessione
    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen)) == -1) {
        perror("Errore nell'accettazione della connessione");
        exit(EXIT_FAILURE);
    }

    printf("Connessione accettata da %s\n", inet_ntoa(clientAddr.sin_addr));

    // Ricezione del messaggio dal client
    if (recv(clientSocket, buffer, BUFFER_SIZE, 0) == -1) {
        perror("Errore nella ricezione del messaggio");
        exit(EXIT_FAILURE);
    }

    printf("Messaggio ricevuto dal client: %s\n", buffer);

    // Invio della risposta al client
    const char *response = "Messaggio ricevuto dal server. Grazie!";
    if (send(clientSocket, response, strlen(response), 0) == -1) {
        perror("Errore nell'invio della risposta al client");
        exit(EXIT_FAILURE);
    }

    // Chiusura delle connessioni
    close(clientSocket);
    close(serverSocket);

    return 0;
}
