require 'mkmf'

def sys(cmd)
  puts "  -- #{cmd}"
  unless ret = xsystem(cmd)
    raise "#{cmd} failed, please report issue on http://github.com/brianmario/ohsnap"
  end
  ret
end

if `which make`.strip.empty?
  STDERR.puts "\n\n"
  STDERR.puts "***************************************************************************************"
  STDERR.puts "*************** make required (apt-get install make build-essential) =( ***************"
  STDERR.puts "***************************************************************************************"
  exit(1)
end

snappy_ver = "snappy-1.1.2"
src = File.basename("#{snappy_ver}.tar.gz")
dir = File.basename(src, '.tar.gz')

CWD = File.expand_path(File.dirname(__FILE__))
Dir.chdir("#{CWD}/src") do
  FileUtils.rm_rf(dir) if File.exists?(dir)

  sys("tar zxvf #{src}")
  Dir.chdir(dir) do
    sys("./configure --prefix=#{CWD}/dst/ --disable-shared --enable-static --with-pic")
    sys("make install")
  end
end

FileUtils.cp "#{CWD}/dst/lib/libsnappy.a", "#{CWD}/libsnappy_ext.a"

$INCFLAGS[0,0] = " -I#{CWD}/dst/include "
$LDFLAGS << " -L#{CWD} "

dir_config 'snappy'
unless have_library 'snappy_ext' and have_header 'snappy-c.h'
  STDERR.puts "\n\n"
  STDERR.puts "***************************************************************************************"
  STDERR.puts "********* error compiling and linking libsnappy. please report issue on github ********"
  STDERR.puts "***************************************************************************************"
  exit(1)
end

segments = CONFIG['LDSHARED'].split(' ')
segments[0] = "$(CXX)"
CONFIG['LDSHARED'] = segments.join(' ')

$CFLAGS << ' -Wall'
$CFLAGS << ' -Wextra -O0 -ggdb3' if ENV['DEBUG']

create_makefile("ohsnap/ohsnap")
