#ifndef BSD_UDP_CLIENT_CLIENT_H
#define BSD_UDP_CLIENT_CLIENT_H

class Client {
private:
	_socket *client;
	_sock_addr *client_addr, *server_addr;
	std::map<uint8_t *, std::vector<Package>> array_packages;
	std::map<uint8_t *, uint32_t> check_sum;

	void _clear();

	uint32_t crc32c(uint32_t crc, const unsigned char *buf, size_t len);

	void cmp_check_sums(Package& ack_package, uint8_t id[]);

	void formation_packages(uint8_t *id, uint8_t *file);

	void send_random_order(Package& ack, uint8_t *id);

public:

	Client(int type, const char *ip, unsigned short port);

	Client operator = (const Client &other) = delete;

	Client(const Client& server) = delete;

	Client(Client&& other);

	~Client();

	void start(uint8_t id[], uint8_t file[]);
};
#endif
