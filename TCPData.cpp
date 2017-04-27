//
// Created by curi on 17-4-25.
//

#include "TCPData.h"

TCPData::TCPData(const BasicData & basicData){
    init(basicData);
}

// TCP协议解析
void TCPData::tcp_protocal_parse()
{
    struct ip *ip_head = ( struct ip *)(proto_buf - sizeof(struct ip));
    struct tcphdr *tcp_head = ( struct tcphdr *)proto_buf;
    proto_buf += sizeof(struct tcphdr);
    length -= sizeof(struct tcphdr);

    char format_buf[50];

    this->srcIP = string(inet_ntoa(ip_head->ip_src))+':'+to_string(tcp_head->source);
    this->dstIP = string(inet_ntoa(ip_head->ip_dst))+':'+to_string(tcp_head->dest);
    this->remind_len = length;
}

string TCPData::toString() {
    return BasicData::toString()+
           "TCP源IP: "+srcIP+
           "TCP目标IP: "+dstIP+
           "剩余长度:"+ to_string(length)+"\n";
}
