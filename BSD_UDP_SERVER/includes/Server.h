#ifndef BSD_UDP_SERVER_SERVER_H
#define BSD_UDP_SERVER_SERVER_H
#include "includes.h"

class Server
{
private:

	_socket *server;
	_sock_addr *server_addr, *client_addr;
	std::map<uint8_t *, std::set<Package>> put_packages;
	std::map<uint8_t *, uint32_t> check_sum;

	//удаление server, server_addr, client_addr
	void _clear();

	//формула расчета контрольной суммы
	uint32_t crc32c(uint32_t crc, const unsigned char *buf, size_t len);

	//Расчет контрольной суммы для файла
	void calc_check_sum(const std::set<Package>& packages, uint32_t& crc32c_sum);

public:

	Server(int type, const char *ip, const unsigned short port);

	~Server();
	//Запрет на присваивание
	Server operator = (const Server &other) = delete;
	//Запрет на копирование
	Server(const Server& server) = delete;
	//Реализация перемещения
	Server(Server&& other);
	//Запуск сервера
	void start(bool work);
};
#endif
