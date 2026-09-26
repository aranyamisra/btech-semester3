#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    int s, a, b, result;
    char op;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(s, (struct sockaddr *)&server, sizeof(server));

    recvfrom(s, &a, sizeof(a), 0,
             (struct sockaddr *)&client, &len);
    recvfrom(s, &b, sizeof(b), 0,
             (struct sockaddr *)&client, &len);
    recvfrom(s, &op, sizeof(op), 0,
             (struct sockaddr *)&client, &len);

    switch(op)
    {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
    }

    sendto(s, &result, sizeof(result), 0,
           (struct sockaddr *)&client, len);

    close(s);

    return 0;
}