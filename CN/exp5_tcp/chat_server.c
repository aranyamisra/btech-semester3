#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int s, ns;
    char buffer[100];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    // 1. Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Assign IP and port
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    // 3. Bind socket with IP and port
    bind(s, (struct sockaddr *)&server, sizeof(server));

    // 4. Listen for client request
    listen(s, 5);

    printf("Server waiting for client...\n");

    // 5. Accept client request
    ns = accept(s, (struct sockaddr *)&client, &len);

    // 6. Receive data from client
    recv(ns, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    // 7. Send data to client
    strcpy(buffer, "Hello from Server");
    send(ns, buffer, strlen(buffer) + 1, 0);

    // 8. Close sockets
    close(ns);
    close(s);

    return 0;
}