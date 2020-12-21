#ifndef BSD_UDP_CLIENT_SOCKET_H
#define BSD_UDP_CLIENT_SOCKET_H

class _sock_addr {
private:
	struct sockaddr_in *addr;

public:

	_sock_addr();

	_sock_addr(unsigned short port);

	_sock_addr(const char *ip, unsigned short port);

	void set_ip(const char *ip) { addr->sin_addr.s_addr = inet_addr(ip); }

	void set_port(const unsigned short port) { addr->sin_port = htons(port); }

	struct sockaddr_in *get_addr() const { return addr; }

	char *get_ip() const { return inet_ntoa(addr->sin_addr); }

	unsigned short get_port() const { return ntohs(addr->sin_port); }

	~_sock_addr();

};

struct _socket {
private:
	int _sd;
public:

	_socket(int type);

	~_socket();

	int _bind(_sock_addr* addr);

	int _send(_sock_addr* addr, const Package& pack);

	int _recv(_sock_addr* addr, Package& pack);

};
#endif
