/*
 *The MIT License (MIT)
 *
 * Copyright (c) <2016> <Stephan Gatzka>
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

#ifndef CJET_WEBSOCKET_H
#define CJET_WEBSOCKET_H

#include <stdbool.h>
#include <stdint.h>

#include "buffered_socket.h"
#include "http_connection.h"
#include "http-parser/http_parser.h"

#define SEC_WEB_SOCKET_KEY_LENGTH 24
#define SEC_WEB_SOCKET_GUID_LENGTH 36

enum header_field {
	HEADER_UNKNOWN,
	HEADER_SEC_WEBSOCKET_KEY,
	HEADER_SEC_WEBSOCKET_VERSION,
	HEADER_SEC_WEBSOCKET_PROTOCOL,
};

struct websocket {
	struct http_connection *connection;
	struct buffered_socket *bs;

	uint8_t sec_web_socket_key[SEC_WEB_SOCKET_KEY_LENGTH + SEC_WEB_SOCKET_GUID_LENGTH];
	enum header_field current_header_field;

	struct {
		unsigned int fin: 1;
		unsigned int opcode: 4;
		unsigned int mask: 1;
	} ws_flags;
	uint64_t length;
	uint8_t mask[4];
	void (*on_error)(struct websocket *s);
	int (*text_message_received)(struct websocket *s, char *msg, size_t length);
	int (*text_frame_received)(struct websocket *s, char *msg, size_t length, bool is_last_frame);
	int (*binary_message_received)(struct websocket *s, char *msg, size_t length);
	int (*binary_frame_received)(struct websocket *s, char *msg, size_t length, bool is_last_frame);
	int (*close_received)(struct websocket *s, char *msg, size_t length);
};

void websocket_init(struct websocket *ws, struct http_connection *connection);
void websocket_free(struct websocket *ws);
enum bs_read_callback_return websocket_read_header_line(void *context, char *buf, ssize_t len);
int websocket_upgrade_on_header_field(http_parser *p, const char *at, size_t length);
int websocket_upgrade_on_headers_complete(http_parser *parser);
int websocket_upgrade_on_header_value(http_parser *p, const char *at, size_t length);
int websocket_send_text_frame(struct websocket *s, bool shall_mask, uint32_t mask, const char *payload, size_t length);
int websocket_send_binary_frame(struct websocket *s, bool shall_mask, uint32_t mask, const char *payload, size_t length);

#endif