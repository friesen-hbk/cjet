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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "jet_random.h"

static FILE *dev_urandom = NULL;

int init_random(void)
{
	dev_urandom = fopen("/dev/urandom", "r");
	if (dev_urandom == NULL) {
		return -1;
	} else {
		return 0;
	}
}

void close_random(void)
{
	if (dev_urandom != NULL) {
		fclose(dev_urandom);
	}
}

void cjet_get_random_bytes(void *bytes, size_t num_bytes)
{
	int ret = fread(bytes, 1, num_bytes, dev_urandom);
	/* Ignore return value deliberately.
	 * There is no good error handling when this call fails
	 * besides shutting down cjet completely.
	 */
	(void)ret;
}
