#include <getopt.h>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#pragma once

struct globalArgs_t {
    uint16_t port16;
    const char *hostCONST;
    const char *dir_NameCONST;
} globalArgs;

static const char *optString = "h:p:d:?";

void displayUsage(const char *prg_name) {
    puts("stepik final task simple epoll http-server");
    printf("%s -h <ip> -p <port> -d <directory>/n", prg_name);
    exit(EXIT_FAILURE);
}

void getCommandLine(const int &argc, char **argv, sockaddr_in &s_in, std::string& serv_dir) {
    int arg = 0;
    globalArgs.port16 = 0;
    globalArgs.hostCONST = nullptr;
    globalArgs.dir_NameCONST = nullptr;
    arg = getopt(argc, argv, optString);

    while (arg != -1) {
        switch (arg) {
            case ('h'):
                globalArgs.hostCONST = optarg;
                break;
            case ('d'):
                globalArgs.dir_NameCONST = optarg;
                break;
            case ('p'):
                globalArgs.port16 = atoi(optarg);
                break;
            case '?':
                displayUsage(argv[0]);
                break;
            default:
                break;
        }
        arg = getopt(argc, argv, optString);
    }

    if(argc<4) {displayUsage(argv[0]);exit(1);}
    s_in.sin_addr.s_addr = inet_addr(globalArgs.hostCONST);
    s_in.sin_port = htons(globalArgs.port16);
    serv_dir =  globalArgs.dir_NameCONST;

}