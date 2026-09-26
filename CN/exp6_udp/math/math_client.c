#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int s, a, b, result;
    char op;
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    printf("Enter operator: ");
    scanf(" %c", &op);

    sendto(s, &a, sizeof(a), 0,
           (struct sockaddr *)&server, len);
    sendto(s, &b, sizeof(b), 0,
           (struct sockaddr *)&server, len);
    sendto(s, &op, sizeof(op), 0,
           (struct sockaddr *)&server, len);

    recvfrom(s, &result, sizeof(result), 0,
             (struct sockaddr *)&server, &len);

    printf("Result = %d\n", result);

    close(s);

    return 0;
}