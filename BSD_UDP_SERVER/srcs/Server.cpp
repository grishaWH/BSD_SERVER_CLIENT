#include "../includes/includes.h"

void Server::_clear() {
	delete server;
	delete server_addr;
	delete client_addr;
	server = nullptr;
	server_addr = nullptr;
	client_addr = nullptr;
}

uint32_t Server::crc32c(uint32_t crc, const unsigned char *buf, size_t len) {
	int k;
	crc = ~crc;
	while (len--) {
		crc ^= *buf++;
		for (k = 0; k < 8; k++)
			crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
	}
	return ~crc;
}

void Server::calc_check_sum(const std::set<Package> &packages, uint32_t &crc32c_sum) {
	for (auto package : packages) {
		crc32c_sum |= crc32c(0, (unsigned char *)package.data, NUM_BYTE_DATA_PACKAGE);
	}
}

Server::Server(int type, const char *ip, const unsigned short port)
		: server(new _socket(type))
		, server_addr(new _sock_addr(ip, port))
		, client_addr(new _sock_addr)
{
	if (server->_bind(server_addr) < 0) {
		_clear();
		exit(1);
	}
	std::cout << SERVER_START << std::endl;
}

Server::~Server() {
	std::cout << SERVER_CLOSE << std::endl;
	_clear();
}

Server::Server(Server &&other) {
	server = other.server;
	server_addr = other.server_addr;
	client_addr = other.client_addr;
	put_packages = std::move(other.put_packages);
	check_sum = std::move(other.check_sum);
	other.client_addr = nullptr;
	other.server_addr = nullptr;
	other.server = nullptr;
}

void Server::start(bool work) {
	while (work) {
		Package pack;
		if (server->_recv(server_addr, pack) <= 0)
			continue ;
		std::cout << "Recieved put package #" << pack.seq_number << "\n";
		auto& packages = put_packages[pack.id];
		packages.insert(pack);
		if (pack.seq_total == packages.size()) {
			auto& crc32c_sum = check_sum[pack.id];
			if (crc32c_sum == 0)
				calc_check_sum(packages, crc32c_sum);
			memcpy(pack.data, reinterpret_cast<uint8_t *>(&std::to_string(crc32c_sum)[0]), NUM_BYTE_DATA_PACKAGE);
		}
		pack.type = static_cast<uint8_t>(PackageType::ACK);
		server->_send(server_addr, pack);
	}
}
