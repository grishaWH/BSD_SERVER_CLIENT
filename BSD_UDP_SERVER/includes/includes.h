#ifndef BSD_UDP_CLIENT_INCLUDES_H
#define BSD_UDP_CLIENT_INCLUDES_H
#include <iostream>
#include <set>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <stddef.h>
#include <stdint.h>
#include <array>
#include <map>
#include <list>

#define POLY 0x82f63b78
#define NUM_BYTE_ID 8
#define NUM_BYTE_DATA_PACKAGE 1455
#define PORT 12345
#define IP "127.0.0.1"
#define ERROR_SOCKET "Error: can't create socket"
#define ERROR_BINDING "Error: can't binding server to addr"
#define ERROR_RECV "Error: couldn't receive package"
#define ERROR_SEND "Error: couldn't send package"
#define SERVER_START "SERVER START"
#define CONFIGURATION_ADDRES "Configuration address..."
#define CONFIGURATION_SOCKET "Configuration socket..."
#define DESTROY_ADDR "Address destroyed"
#define DESTROY_SOCKET "Socket destroyed"
#define SERVER_CLOSE "SERVER CLOSED"

#include "Package.h"
#include "Socket.h"
#include "Server.h"

#endif
