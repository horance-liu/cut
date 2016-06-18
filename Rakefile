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

DEPS = %w[cub hamcrest options]

task :deps_clone do
  system "rm -rf lib/cub"
  system "git clone https://github.com/ccup/cub.git lib/cub"
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

task :deps_build, [:compiler] => :deps_uninstall do |task, args| 
  args.with_defaults(:compiler => 'clang')

  DEPS.each do |m|
    do_build("lib/#{m}", clang:args.compiler == 'clang', test:false) { 
      do_install("lib/#{m}") 
    }
   end
end

task :deps_test, [:compiler] => :deps_build do |task, args| 
  args.with_defaults(:compiler => 'clang')

  DEPS.each do |m|
    do_build("lib/#{m}", clang:args.compiler == 'clang', test:true) { 
      do_test("lib/#{m}", m) 
    }
   end
end

task :deps => [:deps_clone, :deps_build]

task :uninstall do
  do_clean(:cut)
end 

task :build, [:compiler] => :uninstall do |task, args| 
  args.with_defaults(:compiler => 'clang')
  
  do_build(".", clang:args.compiler == 'clang', test:false) { 
    do_install(".") 
  }
end

task :test, [:compiler] => :build do |task, args|
  args.with_defaults(:compiler => 'clang')

  do_build(".", clang:args.compiler == 'clang', test:true)  { 
    do_test(".", :cut) 
  }
end

task :clean => :uninstall do |task|
  system "rm -rf build"
end

task :default => :build
