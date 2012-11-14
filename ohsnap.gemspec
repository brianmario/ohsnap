# encoding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'ohsnap/version'

Gem::Specification.new do |gem|
  gem.name          = "ohsnap"
  gem.version       = Ohsnap::VERSION
  gem.authors       = ["Brian Lopez"]
  gem.email         = ["seniorlopez@gmail.com"]
  gem.description   = %q{Ruby library for the Snappy compression algorithm}
  gem.summary       = %q{Ruby library for the Snappy compression algorithm}
  gem.homepage      = "https://github.com/brianmario/ohsnap"
  gem.extensions    = ["ext/ohsnap/extconf.rb"]

  gem.files         = `git ls-files`.split($/)
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.require_paths = ["lib"]

  # tests
  gem.add_development_dependency 'rake-compiler', ">= 0.8.1"
end
