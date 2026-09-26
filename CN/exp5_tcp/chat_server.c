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

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(s, (struct sockaddr *)&server, sizeof(server));
    listen(s, 5);

    printf("Server started. Waiting for client...\n");

    ns = accept(s, (struct sockaddr *)&client, &len);

    while (1)
    {
        recv(ns, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;

        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        send(ns, buffer, strlen(buffer) + 1, 0);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(ns);
    close(s);

    return 0;
}