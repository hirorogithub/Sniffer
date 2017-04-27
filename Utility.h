//
// Created by curi on 17-4-25.
//

#ifndef SNIFFER_UTILITY_H
#define SNIFFER_UTILITY_H

#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <arpa/inet.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <iostream>
#include <string>

typedef enum {
    protocol_all = ETH_P_ALL,
    protocol_ip = ETH_P_IP,
    protocol_ipv6 = ETH_P_IPV6,
    protocol_arp = ETH_P_ARP,
    protocol_rarp = ETH_P_RARP
} protocol_t;


// 以太网帧的类型
const int eth_proto_id[] = {
        ETHERTYPE_PUP, ETHERTYPE_SPRITE, ETHERTYPE_IP, ETHERTYPE_ARP,
        ETHERTYPE_REVARP, ETHERTYPE_AT, ETHERTYPE_AARP, ETHERTYPE_VLAN,
        ETHERTYPE_IPX, ETHERTYPE_IPV6, ETHERTYPE_LOOPBACK
};

// 以太网帧类型对应的含义
const std::string eth_proto_str[] = {
        "XEROX PUP", "SPRITE", "IP", "ARP",
        "RARP", "APPLE-PROTOCOL", "APPLE-ARP", "802.1Q",
        "IPX", "IPV6", "LOOPBACK"
};


#endif //SNIFFER_UTILITY_H
