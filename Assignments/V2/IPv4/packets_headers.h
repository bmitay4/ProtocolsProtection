#pragma once
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IPHDR_SZ sizeof(struct iphdr)

struct packet {
    uint8_t protocol;
    char target_ip_address[15];
    char source_ip_address[15];
    __u_int target_port;
    __u_int source_port;
};
struct tcp_pseudo_header {
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t tcp_length;

    struct tcphdr tcp;
};

struct udp_pseudo_header {
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t udp_length;

    struct udphdr udp;
};

struct iphdr generate_ipv4hdr(struct packet *);
struct tcphdr generate_tcphdr(struct packet *);
struct tcp_pseudo_header generate_ptcphdr(struct packet *);
struct udphdr generate_udphdr(struct packet *);
struct udp_pseudo_header generate_pudphdr(struct packet *);

void create_tcp_header(char *pkt, struct packet *);
void create_udp_header(char *pkt, struct packet *);

unsigned short checksum(unsigned short *ptr, int nbytes);