#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int s;
    char buffer[100];
    struct sockaddr_in server;

    // 1. Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Specify server IP and port
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. Connect to server
    connect(s, (struct sockaddr *)&server, sizeof(server));

    // 4. Send data to server
    strcpy(buffer, "Hello from Client");
    send(s, buffer, strlen(buffer) + 1, 0);

    // 5. Receive data from server
    recv(s, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // 6. Close socket
    close(s);

    return 0;
}