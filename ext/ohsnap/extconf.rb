require 'mkmf'
require 'rbconfig'

have_header "byteswap.h"
have_header "CoreFoundation/CoreFoundation.h"

$CFLAGS << ' -Wall -Wextra -O0 -ggdb3' if ENV['DEBUG']

create_makefile("ohsnap/ohsnap")
