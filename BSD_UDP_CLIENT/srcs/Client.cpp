#include "../includes/includes.h"

void Client::_clear() {
	delete client;
	delete client_addr;
	delete server_addr;
	client = nullptr;
	client_addr = nullptr;
	server_addr = nullptr;
}

uint32_t Client::crc32c(uint32_t crc, const unsigned char *buf, size_t len) {
	int k;
	crc = ~crc;
	while (len--) {
		crc ^= *buf++;
		for (k = 0; k < 8; k++)
			crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
	}
	return ~crc;
}

void Client::cmp_check_sums(Package &ack_package, uint8_t *id) {
	uint32_t crc32c_from_server = atoi((char *)(ack_package.data));
	std::cout << "\n==>\t\t\t\t\t\tRESULT\t\t\t\t\t\t\t<==\n";
	std::cout << "==>\tSize one package: " << sizeof(Package) << " bytes\t\t\t\t\t\t<==\n";
	std::cout << "==>\tPut packages [" << ack_package.seq_total << "] were sent to the server\t\t\t<==\n";
	std::cout << "==>\tAck packages [" << ack_package.seq_total << "] were received from the server\t<==\n";
	std::cout << "==>\tSum from client: [" << check_sum[id] << "]\t\t\t\t\t\t<==\n";
	std::cout << "==>\tSum from server: [" << crc32c_from_server << "]\t\t\t\t\t\t<==\n";
	std::cout << "==>\t\t\t\t\t\tEND\t\t\t\t\t\t\t\t<==\n";
	std::cout << std::endl;
}

void Client::formation_packages(uint8_t *id, uint8_t *file) {
	uint8_t *ptr_file = file;
	uint32_t num_packages = SIZE_FILE / NUM_BYTE_DATA_PACKAGE + SIZE_FILE % NUM_BYTE_DATA_PACKAGE;
	auto& put_packages = array_packages[id];
	auto& count_crc32c = check_sum[id];
	for (uint32_t i = 0; i < num_packages; i++)
	{
		put_packages.push_back(Package(i, num_packages, PackageType::PUT, id, ptr_file));
		count_crc32c |= crc32c(0, static_cast<const unsigned char *>(put_packages.back().data), NUM_BYTE_DATA_PACKAGE);
		ptr_file += NUM_BYTE_DATA_PACKAGE;
	}
}

void Client::send_random_order(Package &ack, uint8_t *id) {
	auto& put_package = array_packages[id];
	bool flag = true, new_index = true;
	uint32_t random_index = 0;
	std::set<uint32_t> num_random_index;
	int TESTER = 0;
	while (flag) {
		if (new_index) {
			random_index = random() % put_package.size();
			num_random_index.insert(random_index);
		}
		std::cout << "Client send put package #" << put_package[random_index].seq_number << std::endl;
		client->_send(client_addr, put_package[random_index]);
		if (client->_recv(client_addr, ack) <= 0) {
			new_index = false;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue ;
		}
		std::cout << "Client recieved ack package #" << ack.seq_number << "\n";
		if (ack.seq_total == num_random_index.size()) {
			flag = false;
		}
		TESTER++;
		new_index = true;
	}
	std::cout << "TESTCOUNT: " << TESTER * 1472 << std::endl;
}

Client::Client(int type, const char *ip, unsigned short port)
		: client(new _socket(type))
		, client_addr(new _sock_addr(ip, port))
		, server_addr(new _sock_addr)
{
	std::cout << CLIENT_START << std::endl;
}

Client::Client(Client &&other) {
	client = other.client;
	server_addr = other.server_addr;
	client_addr = other.client_addr;
	array_packages = std::move(other.array_packages);
	check_sum = std::move(other.check_sum);
	other.client_addr = nullptr;
	other.server_addr = nullptr;
	other.client = nullptr;
}

Client::~Client() {
	std::cout << CLIENT_CLOSE << std::endl;
	_clear();
}

void Client::start(uint8_t *id, uint8_t *file) {
	formation_packages(id, file);
	Package ack;
	send_random_order(ack, id);
	cmp_check_sums(ack, id);
}
