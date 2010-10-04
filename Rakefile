require 'rubygems'
require 'rake'

begin
  require 'jeweler'
  Jeweler::Tasks.new do |gem|
    gem.name = "protomsg"
    gem.summary = "Protocol Message Buffers for C"
    gem.description = "Protocol Message Buffers for C. This gem generates C socket code for reading and writing messages described in the protomsg DSL."
    gem.email = "me@willcannings.com"
    gem.homepage = "http://github.com/willcannings/protomsg"
    gem.authors = ["Will Cannings"]
    gem.add_development_dependency "thoughtbot-shoulda", ">= 0"
    gem.executables = ["protomsg"]
    gem.files = ["lib/**/*.rb", "lib/templates/**/*.h", "bin/*"]
  end
  Jeweler::GemcutterTasks.new
rescue LoadError
  puts "Jeweler (or a dependency) not available. Install it with: gem install jeweler"
end

require 'rake/testtask'
Rake::TestTask.new(:test) do |test|
  test.libs << 'lib' << 'test'
  test.pattern = 'test/**/test_*.rb'
  test.verbose = true
end

begin
  require 'rcov/rcovtask'
  Rcov::RcovTask.new do |test|
    test.libs << 'test'
    test.pattern = 'test/**/test_*.rb'
    test.verbose = true
  end
rescue LoadError
  task :rcov do
    abort "RCov is not available. In order to run rcov, you must: sudo gem install spicycode-rcov"
  end
end

task :test => :check_dependencies

task :default => :test

require 'rake/rdoctask'
Rake::RDocTask.new do |rdoc|
  version = File.exist?('VERSION') ? File.read('VERSION') : ""

  rdoc.rdoc_dir = 'rdoc'
  rdoc.title = "protomsg #{version}"
  rdoc.rdoc_files.include('README*')
  rdoc.rdoc_files.include('lib/**/*.rb')
end
