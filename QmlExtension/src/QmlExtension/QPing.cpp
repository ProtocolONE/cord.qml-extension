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
/*
#ifdef WIN32

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <winternl.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
#endif
*/
QPing::QPing(QObject* parent) {
}

QPing::~QPing() {
}

void QPing::sync(QString url) 
{   
  /*
#ifdef WIN32
    struct in_addr addr;
    std::string string_host = url.toLocal8Bit();
    const char* host = string_host.c_str();

    if (isalpha(host[0])) {
        struct hostent * remoteHost = gethostbyname(host);

        if (remoteHost == NULL) {
            emit this->failed();
            return;
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
            emit this->failed();
            return;
        } 
    }

    HANDLE icmpFile = IcmpCreateFile();
    if (icmpFile == INVALID_HANDLE_VALUE) {
        emit this->failed();
        return;
    }    

    char sendData[32] = "Data Buffer";
    char replyBuffer[sizeof(ICMP_ECHO_REPLY) + sizeof(sendData)];

    DWORD dwRetVal = IcmpSendEcho(icmpFile, addr.s_addr, sendData, sizeof(sendData), 
        NULL, replyBuffer, sizeof(replyBuffer), 1000);

    if (dwRetVal) {
        PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)replyBuffer;
        emit this->success(pEchoReply->RoundTripTime);
        IcmpCloseHandle(icmpFile);
        return;
    }

    IcmpCloseHandle(icmpFile);
    emit this->failed();
#else*/
    emit this->failed();
    qDebug() << "This function, not Implemented";
    return;       
//#endif
}

void QPing::start(const QString& url) 
{   
//     if (watcher.isRunning()) {
//         qDebug() << "Warning, ping allready in progress";
//         return;
//     }
// 
//     QFuture<void> result = QtConcurrent::run(this, &QPing::sync, url);
//     watcher.setFuture(result);
}
