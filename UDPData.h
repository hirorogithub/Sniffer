//
// Created by curi on 17-4-25.
//

#ifndef SNIFFER_UDPDATA_H
#define SNIFFER_UDPDATA_H

#include "BasicData.h"
class UDPData: public BasicData
{
public:
    string srcIP;
    string dstIP;
    string frame_len;
    string remind_len;
    UDPData(const BasicData & BasicData);

    // UDP协议解析
    void udp_protocal_parse();

    string toString();

};

#endif //SNIFFER_UDPDATA_H
