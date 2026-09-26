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
    socklen_t len = sizeof(server);

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter string: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    sendto(s, buffer, strlen(buffer) + 1, 0,
           (struct sockaddr *)&server, len);

    recvfrom(s, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&server, &len);

    printf("Reversed string: %s\n", buffer);

    close(s);

    return 0;
}