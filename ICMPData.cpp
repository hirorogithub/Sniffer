//
// Created by curi on 17-4-25.
//

#include "ICMPData.h"

ICMPData::ICMPData(const BasicData &basicData){
    init(basicData);

}

// ICMP协议解析
void ICMPData::icmp_protocal_parse() {
    struct ip *ip_head = (struct ip *)(proto_buf - sizeof(struct ip));
    struct icmphdr *icmp_head = (struct icmphdr *)proto_buf;

    char format_buf[50];
    sprintf(format_buf,"%s", inet_ntoa(ip_head->ip_src));
    srcIP = format_buf;
    sprintf(format_buf,"%s", inet_ntoa(ip_head->ip_dst));
    dstIP = format_buf;
    sprintf(format_buf,"%u", icmp_head->type);
    this->type = icmp_head->type;
    sprintf(format_buf,"%u", icmp_head->code);
    this->code = icmp_head->code;


}

string ICMPData::toString() {
    return BasicData::toString()+
            "TCP源IP: "+srcIP+
            "TCP目标IP: "+dstIP+"\n"+
            "类型: "+ type+
            "代码: "+ code+"\n";
}
