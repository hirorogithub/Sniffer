#include "BasicData.h"

BasicData::BasicData()
{

}

void BasicData::init(const BasicData &val){
    srcMac=val.srcMac;
    dstMac=val.dstMac;
    protocol_type=val.protocol_type;
    ip_ver=val.ip_ver;
    head_len=val.head_len;
    total_len=val.total_len;
    id=val.id;
    mf=val.mf;
    df=val.df;
    offset=val.offset;
    ttl=val.ttl;
    ip_p = val.ip_p;
    proto_buf = val.proto_buf;
    length = val.length;
}

void BasicData::data_link_layer_parse(uint8_t *_proto_buf, int _length){
    this->proto_buf = _proto_buf;
    this->length = _length;

    char format_buf[50];

     struct ether_header *eth_head = ( struct ether_header *)proto_buf;

    //源Mac
    for(int i = 0; i < ETHER_ADDR_LEN - 1; i++){
        sprintf(format_buf,"%02x:",eth_head->ether_shost[i]);
        srcMac+=format_buf;
    }
    sprintf(format_buf,"%02x",eth_head->ether_shost[ETHER_ADDR_LEN-1]);
    srcMac+=format_buf;

    //目标Mac
    for(int i = 0; i < ETHER_ADDR_LEN - 1; i++){
        sprintf(format_buf,"%02x:",eth_head->ether_dhost[i]);
        dstMac+=format_buf;
    }
    sprintf(format_buf,"%02x",eth_head->ether_dhost[ETHER_ADDR_LEN-1]);
    dstMac+=format_buf;

    //协议类型
    uint16_t proto_type = ntohs(eth_head->ether_type);
    for (int i = 0; i < sizeof(eth_proto_id)/sizeof(*eth_proto_id); ++i) {
        if (proto_type == eth_proto_id[i]) {
            this->protocol_type = eth_proto_str[i];
            break;
        }
    }

    proto_buf += sizeof(struct ether_header);
    length -= sizeof(struct ether_header);

    return ip_protocal_parse();
}

void BasicData::ip_protocal_parse() {
     struct ip *ip_head = ( struct ip *) proto_buf;

    struct protoent *proto = getprotobynumber(ip_head->ip_p);


//    assert(proto != NULL);
    this->protocol_type += '(' + proto->p_name + ')';


    proto_buf += sizeof(struct ip);
    length -= sizeof(struct ip);

    char format_buf[50];

    sprintf(format_buf,"%u", ip_head->ip_v);
    ip_ver = format_buf;
    sprintf(format_buf,"%u", ip_head->ip_hl * 4);
    head_len = format_buf;
    sprintf(format_buf,"%u", ntohs(ip_head->ip_len));
    total_len = to_string(ntohs(ip_head->ip_len));
    sprintf(format_buf,"%2X", ip_head->ip_id);
    id = format_buf;
    sprintf(format_buf,"%u", (ip_head->ip_off) & (1u << 13));
    mf = format_buf;
    sprintf(format_buf,"%u", (ip_head->ip_off) & (1u << 14));
    df = format_buf;
    sprintf(format_buf,"%u", ip_head->ip_off);
    offset = format_buf;
    sprintf(format_buf,"%u", ip_head->ip_ttl);
    ttl = format_buf;
    ip_p = ip_head->ip_p;
}

string BasicData::toString() {
    string result = "";
    result  +=  "源Mac: "+srcMac+
                "目标Mac: "+dstMac+
                "协议类型: "+protocol_type+
                "IP版本: "+ip_ver+"\n"+
                "首部长度: "+head_len+
                "总长度: "+total_len+
                "标识: "+id+
                "MF: "+mf+
                "DF: "+df+
                "片偏移: "+offset+
                "TTL: "+ttl+"\n";
    return result;
}
