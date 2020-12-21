#include "../includes/includes.h"

Package::Package(uint32_t _seq_number
, uint32_t _seq_total
, PackageType _type
, uint8_t *_id
, uint8_t *_data
)
: seq_number(_seq_number)
, seq_total(_seq_total)
, type(uint8_t(_type))
{
	memcpy(id, _id, NUM_BYTE_ID);
	memcpy(data, _data, NUM_BYTE_DATA_PACKAGE);
}

bool operator < (const Package& lhs, const Package& rhs) {
	return lhs.seq_number < rhs.seq_number;
}
