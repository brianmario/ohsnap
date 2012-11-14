#include <ruby.h>
#include "snappy.h"

static VALUE rb_mOhsnap_compress(VALUE self, VALUE rb_data) {
	struct snappy_env env;
	size_t max_compressed_size=0;
	int err;
	const char *data;
	char *out;
	size_t out_len=0;
	size_t data_len;
	VALUE rb_out;

	rb_out   = Qnil;
	data     = RSTRING_PTR(rb_data);
	data_len = RSTRING_LEN(rb_data);

	err = snappy_init_env(&env);
	if (err < 0) {
		rb_raise(rb_eNoMemError, "Out of memory");
	}

	max_compressed_size = snappy_max_compressed_length(data_len);
	out = xmalloc(max_compressed_size);

	err = snappy_compress(&env, data, data_len, out, &out_len);
	if (err < 0) {
		xfree(out);
		rb_raise(rb_eIOError, "There was an error compressing the data");
	}

	snappy_free_env(&env);

	rb_out = rb_str_new(out, out_len);
	xfree(out);

	return rb_out;
}

static VALUE rb_mOhsnap_decompress(VALUE self, VALUE rb_compressed_data) {
	bool ret;
	int err;
	const char *compressed_data;
	size_t compressed_data_len=0;
	char *out;
	size_t out_len=0;
	VALUE rb_out;

	rb_out              = Qnil;
	compressed_data     = RSTRING_PTR(rb_compressed_data);
	compressed_data_len = RSTRING_LEN(rb_compressed_data);

	ret = snappy_uncompressed_length(compressed_data, compressed_data_len, &out_len);
	if (!ret) {
		rb_raise(rb_eArgError, "Unable to determine uncompressed length, input is corrupt");
	}

	out = xmalloc(out_len);
	err = snappy_uncompress(compressed_data, compressed_data_len, out);
	if (err < 0) {
		xfree(out);
		rb_raise(rb_eIOError, "There was an error uncompressing the data");
	}

	rb_out = rb_str_new(out, out_len);
	xfree(out);

	return rb_out;
}

void Init_ohsnap() {
	VALUE rb_mOhsnap = rb_define_module("Ohsnap");

	rb_define_method(rb_mOhsnap, "compress", rb_mOhsnap_compress, 1);
	rb_define_method(rb_mOhsnap, "decompress", rb_mOhsnap_decompress, 1);
}
