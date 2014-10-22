require 'rake'
require 'rake/extensiontask'
require 'bundler/gem_tasks'

Rake::ExtensionTask.new('ohsnap') do |ext|
  ext.lib_dir = File.join 'lib', 'ohsnap'
end

require 'rake/testtask'
Rake::TestTask.new('test') do |t|
  t.test_files = FileList['test/*_test.rb']
  t.ruby_opts += ['-rubygems'] if defined? Gem
end
task 'test' => [:compile]
