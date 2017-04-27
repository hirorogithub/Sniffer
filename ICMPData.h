//
// Created by curi on 17-4-25.
//

#ifndef SNIFFER_ICMPDATA_H
#define SNIFFER_ICMPDATA_H

#include "BasicData.h"

class ICMPData : public BasicData
{
public:
    string srcIP;
    string dstIP;
    string type;
    string code;
    ICMPData(const BasicData &BasicData);

    // ICMP协议解析
    void icmp_protocal_parse();

    string toString();

};
#endif //SNIFFER_ICMPDATA_H
