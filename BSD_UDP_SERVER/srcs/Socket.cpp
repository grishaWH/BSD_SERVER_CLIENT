#include "../includes/includes.h"

_sock_addr::_sock_addr() {
	addr = new struct sockaddr_in;
	addr->sin_family = AF_INET;
}

_sock_addr::_sock_addr(unsigned short port) {
	addr = new struct sockaddr_in;
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(port);
}

_sock_addr::_sock_addr(const char *ip, unsigned short port) {
	std::cout << CONFIGURATION_ADDRES << std::endl;
	addr = new struct sockaddr_in;
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = inet_addr(ip);
	addr->sin_port = htons(port);
}

_sock_addr::~_sock_addr() {
	std::cout << DESTROY_ADDR << std::endl;
	delete addr;
	addr = nullptr;
}

_socket::_socket(int type) {
	std::cout << CONFIGURATION_SOCKET << std::endl;
	_sd = socket(PF_INET, type, 0);
	if (_sd == -1) {
		std::cerr << ERROR_SOCKET << std::endl;
		exit(1);
	}
}

_socket::~_socket() {
	std::cout << DESTROY_SOCKET << std::endl;
	close(_sd);
}

int _socket::_bind(_sock_addr *addr) {
	int _err = bind(_sd, reinterpret_cast<sockaddr *>(addr->get_addr()), sizeof(struct sockaddr_in));
	if (_err == -1) {
		std::cerr << ERROR_BINDING << std::endl;
	}
	return _err;
}

int _socket::_send(_sock_addr *addr, const Package &pack) {
	int _err = sendto(_sd
			, (char *)&pack
			, sizeof(Package)
			, 0
			, reinterpret_cast<sockaddr *>(addr->get_addr())
			, sizeof(struct sockaddr_in)
	);
	if (_err <= 0) {
		std::cerr << ERROR_SEND << std::endl;
	}
	return _err;
}

int _socket::_recv(_sock_addr *addr, Package &pack) {
	socklen_t len = sizeof(sockaddr_in);
	int _err = recvfrom(_sd
			, &pack
			, sizeof(Package)
			, 0
			, reinterpret_cast<sockaddr *>(addr->get_addr())
			, &len
	);
	if (_err <= 0) {
		std::cerr << ERROR_RECV << std::endl;
	}
	return _err;
}
