#include <fstream>
#include <stdint.h>
#include <string.h>

#include "user_string_parsing.h"

using namespace std;

/// Наше входящее сообщение будет находиться тут.
char buf[512];

/// Метод эмитирует приход нового сообщения.
void get_data ( char* b, int n ) {
	switch( n ) {
		case 0: memcpy( b, "fsdfhsd",		sizeof("fsdfhsd") );		break;
		case 1: memcpy( b, "read",			sizeof("read") );			break;
		case 2: memcpy( b, "set",			sizeof("set") );			break;
		case 3: memcpy( b, "set sfdf",		sizeof("set sfdf") );		break;
		case 4: memcpy( b, "set 21",		sizeof("set 21") );			break;
		case 5: memcpy( b, "read",			sizeof("read") );			break;
	}
}

int main ( void ) {
	user_string_parsing_class		usp;

	for ( int l = 0; l < 6; l++ ) {
		get_data( buf, l );
		usp.start_parsing( buf );
	}

    return 0;
}
