#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/ip6.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "packets_headers.h"
void generate_values(char *, __u_int *);
void create_packet(char *packet, struct packet *);