/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <QmlExtension/QPing.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#ifdef WIN32
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
#endif

QPing::QPing(QObject* parent) {
}

QPing::~QPing() {
}

int QPing::pingHost(QString url) 
{   
#ifdef WIN32
    HANDLE hIcmpFile;
    DWORD dwRetVal = 0;
    char SendData[32] = "Data Buffer";
    LPVOID ReplyBuffer = NULL;
    DWORD ReplySize = 0;
    struct in_addr addr;
    std::string string_host = url.toAscii();
    const char* host = string_host.c_str();

    if (isalpha(host[0])) {
        struct hostent * remoteHost = gethostbyname(host);

        if (remoteHost == NULL) {
            return 0;
        }

        if (remoteHost->h_addrtype == AF_INET) {
            int i = 0;

            while (remoteHost->h_addr_list[i]) {
                addr.s_addr = *(u_long *)remoteHost->h_addr_list[i++];
                break;
            }
        }
    } else {
        addr.s_addr = inet_addr(host);

        if (addr.s_addr == INADDR_NONE) {
            return 0;
        } 
    }

    hIcmpFile = IcmpCreateFile();
    if (hIcmpFile == INVALID_HANDLE_VALUE) {
        return 0;
    }    

    ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
    ReplyBuffer = (VOID*) malloc(ReplySize);
    if (ReplyBuffer == NULL) {
        return 0;
    }    

    return IcmpSendEcho(hIcmpFile, addr.s_addr, SendData, sizeof(SendData), 
        NULL, ReplyBuffer, ReplySize, 1000);
#else
    return 0;
#endif
}

QPing *QPing::qmlAttachedProperties(QObject *obj) {
    return new QPing(obj);
}