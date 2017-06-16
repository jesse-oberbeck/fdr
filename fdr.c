#define _GNU_SOURCE

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "black_adder.c"




int build_sock(int portno)
{

    char port_num[8];
    snprintf(port_num, sizeof(port_num), "%hu", portno);

    struct addrinfo *results;
    struct addrinfo type = {0};
    type.ai_family = PF_UNSPEC;
    type.ai_socktype = SOCK_DGRAM;

    int err = getaddrinfo("localhost", port_num, &type, &results);
    if(err != 0) {
        fprintf(stderr, "Could not parse address: %s\n", gai_strerror(err));
        return 2;
    }

    int sd = socket(results->ai_family, results->ai_socktype, 0);
    if(sd < 0) {
        perror("Could not create socket");
        freeaddrinfo(results);
        return 3;
    }

    int flag = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

    err = bind(sd, results->ai_addr, results->ai_addrlen);
    if(err < 0) {
        perror("Could not create bind");
        close(sd);
        freeaddrinfo(results);
        return 4;
    }

    freeaddrinfo(results);

    for(;;) {
        ssize_t sent = 0;
        int a[512] = {0};
        int b[512] = {0};
        int c[512] = {0};
        char string[512] = {'\0'};
        char buf[512]; //Large buffer in case of Liam.
        struct sockaddr_storage client;
        socklen_t client_sz = sizeof(client);
        char ip[INET6_ADDRSTRLEN];
        //unsigned short port;

        ssize_t received = recvfrom(sd, buf, sizeof(buf), 0,
                (struct sockaddr *)&client, &client_sz);
        if(received < 0) {
            perror("Problem receiving");
        }

        if(received == 512) {
            buf[received-1] = '\0';

        } else {
            buf[received] = '\0';
        }

        if(client.ss_family == AF_INET6) {
            inet_ntop(client.ss_family,
                    &((struct sockaddr_in6 *)&client)->sin6_addr,
                    ip, sizeof(ip));
            portno = ntohs(((struct sockaddr_in6 *)&client)->sin6_port);

        } else {
            inet_ntop(client.ss_family,
                    &((struct sockaddr_in *)&client)->sin_addr,
                    ip, sizeof(ip));
            portno = ntohs(((struct sockaddr_in *)&client)->sin_port);
        }

        switch(buf[0]){

            case('F'):
                //Move over, eliminating the switch.
                memmove(buf, buf + 1, strlen(buf));
                //Zero out "c" in case it has been used.
                memset(c, 0, sizeof(int) * 512);
                //Turn string from packet to number.
                int fnum = strtol(buf, NULL, 10);
                //Run fibonacci function, result in "c".
                fibo(fnum, a, b, c);
                //Turn result into a string.
                stringify(c, string);
                printf("BUF F: %s\n", buf);
                printf("RES F: %s\n", string);

                sent = sendto(sd, string, sizeof(string), 0,
                                (struct sockaddr *)&client, client_sz);
                        if(sent < 0) {
                            perror("Problem sending");
                        }

                break;

            case('D'):
                //Move over, eliminating the switch.
                memmove(buf, buf + 1, strlen(buf));
                //Convert to hex.
                char * hex_str = to_hex(buf);
                printf("BUF D: %s\n", hex_str);
                sent = sendto(sd, hex_str, strlen(hex_str), 0,
                                (struct sockaddr *)&client, client_sz);
                        if(sent < 0) {
                            perror("Problem sending");
                        }
                break;

            case('R'):
                //Move over, eliminating the switch.
                memmove(buf, buf + 1, strlen(buf));
                //Convert roman numeral to decimal.
                
                char * roman_str = roman(buf);
                printf("BUF R: %s%c\n", roman_str, '\0');
                sent = sendto(sd, roman_str, sizeof(roman_str), 0,
                                (struct sockaddr *)&client, client_sz);
                        if(sent < 0) {
                            perror("Problem sending");
                        }
                break;
            default:
                perror("Invalid packet recieved.");
                break;
        }
    }

}

int main(void)
{
    int portno = getuid();
    int first_child_check = fork();
    if(first_child_check == 0)
    {
        build_sock(portno);
        exit(0);
    }
    else if(first_child_check == -1)
    {
        exit(1);
    }

    portno = portno + 1000;
    int second_child_check = fork();
    if(second_child_check == 0)
    {
        build_sock(portno);
        exit(0);
    }
    else if(second_child_check == -1)
    {
        exit(1);
    }

    portno = portno + 1000;
    int third_child_check = fork();
    if(third_child_check == 0)
    {
        build_sock(portno);
        exit(0);
    }
    else if(third_child_check == -1)
    {
        exit(1);
    }

    waitpid(-1, NULL, 0);
    return(0);
}










