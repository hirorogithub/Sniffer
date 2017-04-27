//
// Created by curi on 17-4-25.
//

#ifndef SNIFFER_TCPDATA_H
#define SNIFFER_TCPDATA_H
#include "BasicData.h"

class TCPData: public BasicData
{
public:
    string srcIP;
    string dstIP;
    string remind_len;
    TCPData(const BasicData &BasicData);

    // TCP协议解析
    void tcp_protocal_parse();

    string toString();

};


#endif //SNIFFER_TCPDATA_H
