#pragma once
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/ip6.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IPHDR_SZ sizeof(struct ip6_hdr)

struct packet {
    uint8_t protocol;
    char target_ip_address[39];
    char source_ip_address[39];
    __u_int target_port;
    __u_int source_port;
};

void create_ip6_hdr(struct packet *packet);
void create_udp_header(char *pkt, struct packet *);