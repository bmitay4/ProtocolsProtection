#include "packets_settings.h"

#include <time.h>

// ---- PACKET HEADER BEGIN ---- //
struct ip6_hdr generate_ip6_hdr(char *pkt, struct packet *packet) {
    struct ip6_hdr ip6_header;
    ip6_header.ip6_ctlun.ip6_un2_vfc = 6;
    ip6_header.ip6_ctlun.ip6_un1.ip6_un1_flow = htonl((6 << 28) | (0 << 20) | 0);
    ip6_header.ip6_ctlun.ip6_un1.ip6_un1_plen = sizeof(struct udphdr);
    ip6_header.ip6_ctlun.ip6_un1.ip6_un1_nxt = IPPROTO_UDP;
    ip6_header.ip6_ctlun.ip6_un1.ip6_un1_hlim = 255;

    printf("%d\n", *ip6_header.ip6_dst.__in6_u.__u6_addr32);
    printf("%d\n", *ip6_header.ip6_dst.__in6_u.__u6_addr16);
    printf("%d\n", *ip6_header.ip6_dst.__in6_u.__u6_addr8);

    inet_pton(AF_INET6, packet->target_ip_address, &(ip6_header.ip6_dst));
    inet_pton(AF_INET6, packet->source_ip_address, &(ip6_header.ip6_src));

    return ip6_header;
}
void create_udp_header(char *pkt, struct packet *packet) {
    struct udphdr udp;
    udp.uh_sport = htons(packet->source_port);
    udp.uh_dport = htons(packet->target_port);
    // printf("%s\n", pkt);

    udp.uh_ulen = htons(sizeof(struct udphdr));
    udp.check = 0;
    memcpy(pkt + sizeof(struct ip6_hdr), &udp, sizeof(struct udphdr));
}
// ---- PACKET HEADER END ---- //

// ---- GENERATE RANDOM VALUES ---- //
// char get_num() {
//     char str[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
//     return str[rand() % 16];
// }
// char get_octet() {
//     char octet[4];
//     for (size_t i = 0; i < 4; i++)
//         octet[i] = get_num();

//     return octet;
// }

void generate_values(char *ip_buff, __u_int *port) {
    // srand(time(NULL));  //Get different random result
    int round = 32, octet = 0;
    char str[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    for (size_t i = 0; i < 32; i = i + 4) {
        if (i == 0)
            sprintf(ip_buff, "%x%x%x%x", rand() % 16, rand() % 16, rand() % 16, rand() % 16);
        else
            sprintf(ip_buff + i, ":%x%x%x%x", rand() % 16, rand() % 16, rand() % 16, rand() % 16);
    }

    // sprintf(ip_buff,
    //         "%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c",
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16],
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16],
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16],
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16]);

    *port = (rand() & 0xFFFF);

    // printf("%s-%d\n", ip_buff, *port);
}

// ---- PACKET CREATION ---- //
void create_packet(char *pkt, struct packet *packet) {
    generate_values(packet->source_ip_address, &packet->source_port);
    // struct ip6_hdr iph = generate_ip6_hdr(pkt, packet);

    struct ip6_hdr ip6_header;
    ip6_header.ip6_ctlun.ip6_un2_vfc = 6;
    ip6_header.ip6_ctlun.ip6_un1.ip6_un1_flow = htonl((6 << 28) | (0 << 20) | 0);
    ip6_header.ip6_ctlun.ip6_un1.ip6_un1_plen = sizeof(struct udphdr);
    ip6_header.ip6_ctlun.ip6_un1.ip6_un1_nxt = IPPROTO_UDP;
    ip6_header.ip6_ctlun.ip6_un1.ip6_un1_hlim = 255;

    // printf("%d\n", *ip6_header.ip6_dst.__in6_u.__u6_addr32);
    // printf("%d\n", *ip6_header.ip6_dst.__in6_u.__u6_addr16);
    // printf("%d\n", *ip6_header.ip6_dst.__in6_u.__u6_addr8);

    inet_pton(AF_INET6, packet->target_ip_address, &(ip6_header.ip6_dst));
    inet_pton(AF_INET6, packet->source_ip_address, &(ip6_header.ip6_src));

    memcpy(pkt, &ip6_header, sizeof(struct ip6_hdr));
    create_udp_header(pkt, packet);
}