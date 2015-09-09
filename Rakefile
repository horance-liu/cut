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

def do_build(args)
  execute "mkdir -p build && cd build && #{cmake_cmd args} && make && sudo make install" 
end

def do_test(args)
  do_build(args)
  execute "cd build && test/magellan-test && cd lib && l0-infra/test/l0-infra-test && hamcrest/test/hamcrest-test"
end

task :uninstall do |task|
  %w[l0-infra hamcrest magellan].each do |modular|
    system "sudo rm -rf /usr/local/include/#{modular}"
    system "sudo rm -rf /usr/local/lib/lib#{modular}.a"
  end
end 

task :gcc => :uninstall do
  do_build(clang:false, test:false)
  do_test(clang:false, test:true)
end

task :clang => :uninstall do
  do_build(clang:true, test:false)
  do_test(clang:true, test:true)
end

task :clean => :uninstall do |task|
  system "rm -rf build"
end

task :default => :clang
