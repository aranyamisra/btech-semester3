#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int s;
    char buffer[100];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(s, (struct sockaddr *)&server, sizeof(server));

    printf("Server started. Waiting for client...\n");

    while (1)
    {
        recvfrom(s, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)&client, &len);

        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;

        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        sendto(s, buffer, strlen(buffer) + 1, 0,
               (struct sockaddr *)&client, len);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(s);
    return 0;
}