//
// Created by curi on 17-4-25.
//

#ifndef SNIFFER_MANAGER_H
#define SNIFFER_MANAGER_H
#include "BasicData.h"
#include "Utility.h"
using namespace std;

class Manager
{
public:

    Manager(string net_name, protocol_t proto_type, bool is_promise);
    bool set_network_promise(bool choose);
    int init_socket(string net_name, protocol_t proto_type, bool is_promise);
    void drop_socket();
    BasicData capture_socket_once();
    bool start();
    bool stop();
    void ps_debug(char *debug_info);
    ~Manager();

    static const int RECV_BUF_SIZE = 4096;
    int maxLen = 30;
    BasicData** dataList;


private :
    string net_name;
    int current_id = 0;
    int fd ;
    bool isRunning = false;

    uint8_t buf[RECV_BUF_SIZE];
    uint8_t* recv_buf;
};

#endif //SNIFFER_MANAGER_H
