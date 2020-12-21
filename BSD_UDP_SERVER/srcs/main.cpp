//#include <iostream>
//#include <set>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <fcntl.h>
//#include <arpa/inet.h>
//#include <zconf.h>
//#include <stddef.h>
//#include <stdint.h>
//#include <array>
//#include <map>
//#include <list>
//
//#define POLY 0x82f63b78
//#define NUM_BYTE_ID 8
//#define NUM_BYTE_DATA_PACKAGE 1455
//#define PORT 12345
//#define IP "127.0.0.1"
//#define ERROR_SOCKET "Error: can't create socket"
//#define ERROR_BINDING "Error: can't binding server to addr"
//#define ERROR_RECV "Error: couldn't receive package"
//#define ERROR_SEND "Error: couldn't send package"
//#define SERVER_START "SERVER START"
//#define CONFIGURATION_ADDRES "Configuration address..."
//#define CONFIGURATION_SOCKET "Configuration socket..."
//#define DESTROY_ADDR "Address destroyed"
//#define DESTROY_SOCKET "Socket destroyed"
//#define SERVER_CLOSE "SERVER CLOSED"
//
//enum PackageType {
//	ACK = 0,
//	PUT = 1,
//};
//
//struct Package
//{
//	Package() = default;
//
//	Package(uint32_t _seq_number
//		 , uint32_t _seq_total
//		 , const PackageType& type
//		 , uint8_t *_id
//		 , uint8_t *_data
//	)
//	: seq_number(_seq_number)
//	, seq_total(_seq_total)
//	, type(static_cast<uint8_t>(type))
//	{
//		memcpy(id, _id, NUM_BYTE_ID);
//		memcpy(data, _data, NUM_BYTE_DATA_PACKAGE);
//	}
//
//	uint32_t seq_number; // номер пакета
//	uint32_t seq_total; // количество пакетов с данными
//	uint8_t type; // тип пакета: 0 == ACK, 1 == PUT
//	uint8_t id[NUM_BYTE_ID];// 8 байт - идентификатор, отличающий один файл от другого
//	uint8_t data[NUM_BYTE_DATA_PACKAGE];// после заголовка и до конца UDP пакета идут данные
//};
//
//bool operator < (const Package& lhs, const Package& rhs) {
//	return lhs.seq_number < rhs.seq_number;
//}
//
//
//class _sock_addr {
//private:
//	struct sockaddr_in *addr;
//
//public:
//
//	_sock_addr() {
//		addr = new struct sockaddr_in;
//		addr->sin_family = AF_INET;
//	}
//
//	_sock_addr(unsigned short port) {
//		addr = new struct sockaddr_in;
//		addr->sin_family = AF_INET;
//		addr->sin_addr.s_addr = INADDR_ANY;
//		addr->sin_port = htons(port);
//	}
//
//	_sock_addr(const char *ip, unsigned short port) {
//		std::cout << CONFIGURATION_ADDRES << std::endl;
//		addr = new struct sockaddr_in;
//		addr->sin_family = AF_INET;
//		addr->sin_addr.s_addr = inet_addr(ip);
//		addr->sin_port = htons(port);
//	}
//
//	void set_ip(const char *ip) { addr->sin_addr.s_addr = inet_addr(ip); }
//
//	void set_port(const unsigned short port) { addr->sin_port = htons(port); }
//
//	struct sockaddr_in *get_addr() const { return addr; }
//
//	char *get_ip() const { return inet_ntoa(addr->sin_addr); }
//
//	unsigned short get_port() const { return ntohs(addr->sin_port); }
//
//	~_sock_addr() {
//		std::cout << DESTROY_ADDR << std::endl;
//		delete addr;
//		addr = nullptr;
//	}
//
//};
//
//struct _socket {
//private:
//	int _sd;
//public:
//
//	_socket(int type) {
//		std::cout << CONFIGURATION_SOCKET << std::endl;
//		_sd = socket(PF_INET, type, 0);
//		if (_sd == -1) {
//			std::cerr << ERROR_SOCKET << std::endl;
//			exit(1);
//		}
//	}
//
//	~_socket() {
//		std::cout << DESTROY_SOCKET << std::endl;
//		close(_sd);
//	}
//
//	int _bind(_sock_addr* addr) {
//		int _err = bind(_sd, reinterpret_cast<sockaddr *>(addr->get_addr()), sizeof(struct sockaddr_in));
//		if (_err == -1) {
//			std::cerr << ERROR_BINDING << std::endl;
//		}
//	}
//
//	int _send(_sock_addr* addr, const Package& pack) {
//		int _err = sendto(_sd, &pack, sizeof(pack), 0, reinterpret_cast<sockaddr *>(addr->get_addr()), sizeof(struct sockaddr_in));
//		if (_err <= 0) {
//			std::cerr << ERROR_SEND << std::endl;
//		}
//		return _err;
//	}
//
//	int _recv(_sock_addr* addr, Package& pack) {
//		socklen_t len = sizeof(sockaddr_in);
//		int _err = recvfrom(_sd, (char *)&pack, sizeof(Package), 0, reinterpret_cast<sockaddr *>(addr->get_addr()), &len);
//		if (_err <= 0) {
//			std::cerr << ERROR_RECV << std::endl;
//		}
//		return _err;
//	}
//
//};

//class Server
//{
//private:
//
//	_socket *server;
//	_sock_addr *server_addr, *client_addr;
//	std::map<uint8_t *, std::set<Package>> put_packages;
//	std::map<uint8_t *, uint32_t> check_sum;
//
//	void _clear() {
//		delete server;
//		delete server_addr;
//		delete client_addr;
//		server = nullptr;
//		server_addr = nullptr;
//		client_addr = nullptr;
//	}
//
//	uint32_t crc32c(uint32_t crc, const unsigned char *buf, size_t len)
//	{
//		int k;
//		crc = ~crc;
//		while (len--) {
//			crc ^= *buf++;
//			for (k = 0; k < 8; k++)
//				crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
//		}
//		return ~crc;
//	}
//
//	void calc_check_sum(const std::set<Package>& packages, uint32_t& crc32c_sum) {
//		for (auto package : packages) {
//			crc32c_sum += crc32c(0, (unsigned char *)package.data, NUM_BYTE_DATA_PACKAGE);
//		}
//	}
//
//public:
//	Server(int type, const char *ip, const unsigned short port)
//	: server(new _socket(type))
//	, server_addr(new _sock_addr(ip, port))
//	, client_addr(new _sock_addr)
//	{
//		if (server->_bind(server_addr) < 0) {
//			_clear();
//			exit(1);
//		}
//		std::cout << SERVER_START << std::endl;
//	}
//
//	~Server() {
//		std::cout << SERVER_CLOSE << std::endl;
//		_clear();
//	}
//
//	Server operator = (const Server &other) = delete;
//
//	Server(const Server& server) = delete;
//
//	Server(Server&& other) {
//		server = other.server;
//		server_addr = other.server_addr;
//		client_addr = other.client_addr;
//		other.client_addr = nullptr;
//		other.server_addr = nullptr;
//		other.server = nullptr;
//	}
//
//	void start(bool work) {
//		while (work) {
//			Package pack;
//			if (server->_recv(server_addr, pack) <= 0)
//				continue ;
//			std::cout << "Recieved put package #" << pack.seq_number << "\n";
//			auto& packages = put_packages[pack.id];
//			packages.insert(pack);
//			if (pack.seq_total == packages.size()) {
//				auto& crc32c_sum = check_sum[pack.id];
//				if (crc32c_sum == 0)
//					calc_check_sum(packages, crc32c_sum);
//				memcpy(pack.data, reinterpret_cast<uint8_t *>(&std::to_string(crc32c_sum)[0]), NUM_BYTE_DATA_PACKAGE);
//			}
//			pack.type = static_cast<uint8_t>(PackageType::ACK);
//			server->_send(server_addr, pack);
//		}
//	}
//};

#include "../includes/includes.h"

int main()
{
	Server server(SOCK_DGRAM, IP, PORT);
	server.start(true);
	return 0;
}