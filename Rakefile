def execute(cmd)
  system "#{cmd}" or exit
end

def compiler clang
  clang ? "CC=/usr/bin/clang CXX=/usr/bin/clang++" : ""
end

def test_switch run_test
  "-DENABLE_TEST=#{run_test ? 'on' : 'off'}"
end

def cmake_cmd args
  "#{compiler args[:clang]} cmake #{test_switch args[:test]} -DCMAKE_BUILD_TYPE=Debug .."
end

def do_install(path)
  system "cd #{path}/build && sudo make install"
end

def do_test(path, modular)
  execute "cd #{path}/build && test/#{modular}-test"
end

def do_build(path, args, &action)
  execute "mkdir -p #{path}/build && cd #{path}/build && #{cmake_cmd args} && make" 
  action.call
end

def do_clean(m)
  system "sudo rm -rf /usr/local/include/#{m}"
  system "sudo rm -rf /usr/local/lib/lib#{m}.a"
end

DEPS = %w[ccinfra hamcrest options]

task :deps_clone do
  system "rm -rf lib"
  system "git clone https://github.com/MagicBowen/ccinfra.git lib/ccinfra"
  system "git clone https://github.com/ccup/options.git lib/options"
  system "git clone https://github.com/horance-liu/hamcrest.git lib/hamcrest"
end

task :deps_uninstall do
  DEPS.each do |m|
    do_clean(m)
  end
end

task :deps_clean => :deps_uninstall do
  DEPS.each do |m|
    system "cd lib/#{m} && rm -rf build"
  end 
end

task :deps_gcc do
  DEPS.each do |m|
    do_build("lib/#{m}", clang:false, test:false) { do_install("lib/#{m}") }
  end
end

task :deps_clang do
  DEPS.each do |m|
    do_build("lib/#{m}", clang:true, test:false) { do_install("lib/#{m}") }
   end
end

task :deps => [:deps_clone, :deps_clang]

task :uninstall do
  do_clean(:magellan)
end 

task :gcc => :uninstall do
  do_build(".", clang:false, test:false) { do_install(".") }
  do_build(".", clang:false, test:true)  { do_test(".", :magellan) }
end

task :clang => :uninstall do
  do_build(".", clang:true, test:false) { do_install(".") }
  do_build(".", clang:true, test:true)  { do_test(".", :magellan) }
end

task :clean => :uninstall do |task|
  system "rm -rf build"
end

task :default => :clang
