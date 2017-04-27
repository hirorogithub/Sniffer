#include "Manager.h"
#include "ICMPData.h"
#include "TCPData.h"
#include "UDPData.h"

// 设置/取消网卡的混杂模式
bool Manager::set_network_promise(bool choose)
{
    struct ifreq ifr;
    bzero(&ifr, sizeof(ifr));

//    assert(net_name != NULL);
    strcpy(ifr.ifr_name, net_name.c_str());

    if (ioctl(fd, SIOCGIFFLAGS, &ifr) < 0) {
        ps_debug("set_network_promise:");
        return false;
    }

    if (choose) {
        ifr.ifr_flags |= IFF_PROMISC;
    } else {
        ifr.ifr_flags &= ~IFF_PROMISC;
    }

    if (ioctl(fd, SIOCSIFFLAGS, &ifr) < 0) {
        ps_debug("set_network_promise:");
        return false;
    }

    return true;
}


// 初始化捕获套结字
int Manager::init_socket(string net_name, protocol_t proto_type, bool is_promise)
{

    if ((fd = socket(AF_PACKET, SOCK_RAW, htons(proto_type))) < 0 ) {
        ps_debug("init socket:");
        return -1;
    }

    if (is_promise) {
        if (!set_network_promise(true)) {
            close(fd);
            return -1;
        }
    }

    int recv_size = RECV_BUF_SIZE;
    if (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &recv_size, sizeof(int)) < 0) {
        ps_debug("init socket:");
        close(fd);
        return -1;
    }

    struct ifreq ifr;
    bzero(&ifr, sizeof(ifr));
    strcpy(ifr.ifr_name, net_name.c_str());

    if (ioctl(fd, SIOCGIFINDEX, &ifr) < 0) {
        ps_debug("init socket:");
        close(fd);
        return -1;
    }

    struct sockaddr_ll sock_ll;

    bzero(&sock_ll, sizeof(sock_ll));
    sock_ll.sll_family = AF_PACKET;
    sock_ll.sll_ifindex = ifr.ifr_ifindex;
    sock_ll.sll_protocol = htons(proto_type);

    if (bind(fd, (struct sockaddr *)&sock_ll, sizeof(sock_ll)) < 0) {
        ps_debug("bind:");
        close(fd);
        return -1;
    }

    return fd;
}


// 销毁捕获套结字
void Manager::drop_socket()
{
    this->net_name = net_name;
    set_network_promise(false);
    close(fd);
}

// 捕获数据包一次
BasicData Manager::capture_socket_once()
{
    //uint8_t recv_buf[RECV_BUF_SIZE];
    socklen_t socklen;
    int size;

    bzero(recv_buf, RECV_BUF_SIZE);
    size = recvfrom(fd, recv_buf, RECV_BUF_SIZE, 0, NULL, &socklen);

    BasicData tmpData;
    tmpData.data_link_layer_parse(recv_buf, size);

    return tmpData;
}

Manager::Manager(string net_name, protocol_t proto_type, bool is_promise){
    this->net_name = net_name;
    this->isRunning = false;
    this->dataList = new BasicData*[maxLen];
    this->recv_buf = this->buf;
    if(init_socket(net_name,protocol_ip,false)<0){
        exit(EXIT_FAILURE);
    }

}


void Manager::ps_debug(char *debug_info)
{
#ifdef PS_DEBUG
    perror(debug_info);
#else
    // TODO
#endif
}



bool Manager::start(){
    if(isRunning==false){

        BasicData tmpData;

        for (int i = 0; i < maxLen; ++i) {

            tmpData = capture_socket_once();

            if(current_id/maxLen>0){
                delete dataList[current_id%maxLen];
            }
            cout<<"ID: "<<i+1<<endl;
            if(tmpData.ip_p==IPPROTO_ICMP){

                dataList[current_id%maxLen] = new ICMPData(tmpData);
                ((ICMPData*)dataList[current_id%maxLen])->icmp_protocal_parse();
                cout<<((ICMPData*)dataList[current_id%maxLen])->toString()<<endl;
            }else if(tmpData.ip_p==IPPROTO_TCP){

                dataList[current_id%maxLen] = new TCPData(tmpData);
                ((TCPData*)dataList[current_id%maxLen])->tcp_protocal_parse();
                cout<<((TCPData*)dataList[current_id%maxLen])->toString()<<endl;

            }else if(tmpData.ip_p==IPPROTO_UDP){

                dataList[current_id%maxLen] = new UDPData(tmpData);
                ((UDPData*)dataList[current_id%maxLen])->udp_protocal_parse();
                cout<<((UDPData*)dataList[current_id%maxLen])->toString()<<endl;


            }

            current_id++;
        }
        stop();

    }
    return true;

}

bool Manager::stop(){
    isRunning=false;
}

Manager::~Manager() {
    drop_socket();
    for(int i=0;i<maxLen;i++){
        delete dataList[i];
    }
    delete dataList;


}

