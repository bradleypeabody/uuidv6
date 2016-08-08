#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <uuid/uuid.h>

/* Converts UUID version 1 to version 6 in place. */
void uuidv1tov6(uuid_t u) {

	uint64_t ut;
	unsigned char *up = (unsigned char *)u;

	// load ut with the first 64 bits of the UUID
	ut = ((uint64_t)ntohl(*((uint32_t*)up))) << 32;
	ut |= ((uint64_t)ntohl(*((uint32_t*)&up[4])));

	// dance the bit-shift...
	ut = 
		((ut >> 32) & 0x0FFF) | // 12 least significant bits
		(0x6000) | // version number
		((ut >> 28) & 0x0000000FFFFF0000) | // next 20 bits
		((ut << 20) & 0x000FFFF000000000) | // next 16 bits
		(ut << 52); // 12 most significant bits

	// store back in UUID
	*((uint32_t*)up) = htonl((uint32_t)(ut >> 32));
	*((uint32_t*)&up[4]) = htonl((uint32_t)(ut));

}

int main(int argc, char **argv) {

	uuid_t u;
	char str[37];

	uuid_generate_time(u);

	uuid_unparse(u, str);
	printf("UUIDv1: %s\n", str);

	uuidv1tov6(u);

	uuid_unparse(u, str);
	printf("UUIDv6: %s\n", str);

	return 0;
}

