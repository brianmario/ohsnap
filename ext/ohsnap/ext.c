#include <ruby.h>
#include "snappy-c.h"

static VALUE rb_mOhsnap_compress(VALUE self, VALUE rb_data) {
	snappy_status err;
	const char *data;
	char *out;
	size_t out_len=0;
	size_t data_len;
	VALUE rb_out;

	rb_out   = Qnil;
	data     = RSTRING_PTR(rb_data);
	data_len = RSTRING_LEN(rb_data);

	out_len = snappy_max_compressed_length(data_len);
	out = (char*)xmalloc(out_len);

	err = snappy_compress(data, data_len, out, &out_len);

	if (err != SNAPPY_OK) {
		xfree(out);
		rb_raise(rb_eIOError, "There was an error compressing the data");
	}

	rb_out = rb_str_new(out, out_len);
	xfree(out);

	return rb_out;
}

static VALUE rb_mOhsnap_decompress(VALUE self, VALUE rb_compressed_data) {
	snappy_status err;
	const char *compressed_data;
	size_t compressed_data_len=0;
	char *out;
	size_t out_len=0;
	VALUE rb_out;

	rb_out              = Qnil;
	compressed_data     = RSTRING_PTR(rb_compressed_data);
	compressed_data_len = RSTRING_LEN(rb_compressed_data);

	err = snappy_uncompressed_length(compressed_data, compressed_data_len, &out_len);
	if (err != SNAPPY_OK) {
		rb_raise(rb_eArgError, "Unable to determine uncompressed length, input is corrupt");
	}

	out = (char*)xmalloc(out_len);
	err = snappy_uncompress(compressed_data, compressed_data_len, out, &out_len);
	if (err != SNAPPY_OK) {
		xfree(out);
		rb_raise(rb_eIOError, "There was an error uncompressing the data");
	}

	rb_out = rb_str_new(out, out_len);
	xfree(out);

	return rb_out;
}

void Init_ohsnap() {
	VALUE rb_mOhsnap = rb_define_module("Ohsnap");

	rb_define_method(rb_mOhsnap, "compress", (VALUE(*)(ANYARGS))rb_mOhsnap_compress, 1);
	rb_define_method(rb_mOhsnap, "decompress", (VALUE(*)(ANYARGS))rb_mOhsnap_decompress, 1);
}
