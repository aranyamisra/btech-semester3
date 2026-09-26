#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int s, ns, a, b, result;
    char op;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(s, (struct sockaddr *)&server, sizeof(server));
    listen(s, 5);

    printf("Server waiting...\n");
    ns = accept(s, (struct sockaddr *)&client, &len);

    recv(ns, &a, sizeof(a), 0);
    recv(ns, &b, sizeof(b), 0);
    recv(ns, &op, sizeof(op), 0);

    switch(op)
    {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
    }

    send(ns, &result, sizeof(result), 0);

    close(ns);
    close(s);

    return 0;
}