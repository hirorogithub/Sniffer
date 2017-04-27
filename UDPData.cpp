//
// Created by curi on 17-4-25.
//

#include "UDPData.h"

UDPData::UDPData(const BasicData & basicData){
    init(basicData);
}

// UDP协议解析
void UDPData::udp_protocal_parse()
{
     struct ip *ip_head = ( struct ip *)(proto_buf - sizeof(struct ip));
     struct udphdr *udp_head = ( struct udphdr *)proto_buf;
    proto_buf += sizeof(struct udphdr);
    length -= sizeof(struct udphdr);

    this->srcIP = string(inet_ntoa(ip_head->ip_src))+':'+to_string(udp_head->source);
    this->dstIP = string(inet_ntoa(ip_head->ip_dst))+':'+to_string(udp_head->dest);
    this->remind_len = length;
    this->frame_len = to_string(ntohs(udp_head->len));
}


string UDPData::toString() {
    return BasicData::toString()+
           "TCP源IP: "+srcIP+
           "TCP目标IP: "+dstIP+"\n"+
           "数据报长度: "+frame_len+
           "剩余长度:"+ to_string(length)+"\n";
}
