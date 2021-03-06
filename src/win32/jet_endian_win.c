/*
*The MIT License (MIT)
*
* Copyright (c) <2017> <Stephan Gatzka>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include <stdint.h>
#include <winsock2.h>

#include "jet_endian.h"

uint16_t jet_be16toh(uint16_t big_endian_16bits)
{
	return ntohs(big_endian_16bits);
}

uint32_t jet_be32toh(uint32_t big_endian_32bits)
{
	return ntohl(big_endian_32bits);
}

uint64_t jet_be64toh(uint64_t big_endian_64bits)
{
	return ntohll(big_endian_64bits);
}

uint16_t jet_htobe16(uint16_t host_endian_16bits)
{
	return htons(host_endian_16bits);
}

uint32_t jet_htobe32(uint32_t host_endian_32bits)
{
	return htonl(host_endian_32bits);
}

uint64_t jet_htobe64(uint64_t host_endian_64bits)
{
	return htonll(host_endian_64bits);
}
