require File.expand_path('../test_helper', __FILE__)

require 'ohsnap'

class OhsnapTest < MiniTest::Test
  TEXT = "a"*1024*1024

  def test_compression
    compressed = Ohsnap.compress(TEXT)

    assert TEXT.bytesize > compressed.bytesize
  end

  def test_decompression
    compressed   = Ohsnap.compress(TEXT)
    decompressed = Ohsnap.decompress(compressed)

    assert TEXT.bytesize == decompressed.bytesize
    assert_equal TEXT, decompressed
  end
end
