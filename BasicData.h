//
// Created by curi on 17-4-25.
//

#ifndef SNIFFER_BASICDATA_H
#define SNIFFER_BASICDATA_H

#include <string>
#include "Utility.h"

using namespace std;
class BasicData
{
public:
    BasicData();
    void init (const BasicData &val);
    string srcMac;
    string dstMac;
    string protocol_type;
    string ip_ver;
    string head_len;
    string total_len;
    string id;
    string mf;
    string df;
    string offset;
    string ttl;

    int ip_p;
    uint8_t *proto_buf;
    int length;
    // 数据链路层解析
    void data_link_layer_parse(uint8_t *_proto_buf, int _length);

    // 网络层协议及其高层协议解析
    void ip_protocal_parse();

    string toString();

};


#endif //SNIFFER_BASICDATA_H
