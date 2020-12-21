#ifndef BSD_UDP_CLIENT_PACKAGE_H
#define BSD_UDP_CLIENT_PACKAGE_H

enum PackageType {
	ACK = 0,
	PUT = 1,
};

struct Package
{
	Package() = default;

	Package(uint32_t _seq_number
			, uint32_t _seq_total
			, PackageType _type
			, uint8_t *_id
			, uint8_t *_data
	);

	uint32_t seq_number; // номер пакета
	uint32_t seq_total; // количество пакетов с данными
	uint8_t type; // тип пакета: 0 == ACK, 1 == PUT
	uint8_t id[NUM_BYTE_ID];// 8 байт - идентификатор, отличающий один файл от другого
	uint8_t data[NUM_BYTE_DATA_PACKAGE];// после заголовка и до конца UDP пакета идут данные
};

bool operator < (const Package& lhs, const Package& rhs);

#endif
