//
// Created by curi on 17-4-25.
//

#include "Manager.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[]){

    Manager manager("eth1",protocol_ip, false);
    manager.start();

//    for(int i=0;i<manager.maxLen;i++){
//        cout<<manager.dataList[i]->srcMac<<endl;
//    }
}
