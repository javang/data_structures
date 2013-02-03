import os
import os.path
import glob
from buildtools.colorizer import colorizer
import buildtools.ErrorColor as ErrorColor

def check_headers(conf, files):
    for d in files:
        if not conf.CheckCXXHeader(d):
            print "Could not find the required header",d
            quit()


#################################
# Options file
#################################

# directories in the project
fn_config = 'scons_config.py'

#################################
# Config
#################################
home=os.environ["HOME"]
path=os.environ["PATH"]
term = os.environ["TERM"]

variables = Variables(fn_config)
variables.Add("build_dir", "directory to build the library", default="build")
variables.Add("install_dir", "directory to install the library", default="lib")
variables.Add(PathVariable("google_test_dir",
     "directory containg the google_test, include, and lib directories",""))
variables.Add("compiler", "The compiler to use", default="g++")


#################################
# Environment
#################################

env = Environment(variables=variables)
env['ENV'] = {'PATH': path, 'TERM': term, 'HOME': home }
env['CPPPATH'] = ["#include", "/usr/include"] # the symbol "#" means the directory where SConstruct is
env['CXXFLAGS'] = ["-std=c++0x", "-fPIC", "-g"]
env["CXX"] = env["compiler"]

buf = ErrorColor.ErrorColor()
buf.env = env
env['SPAWN'] = buf.buffered_spawn
# for nice compiling colors
col = colorizer()
col.colorize(env)



conf = Configure(env)
conf.CheckCXXHeader("iostream")
env = conf.Finish()

build_dir = env['build_dir']
install_dir = env['install_dir']
VariantDir(build_dir, "src", duplicate=False)
dstruct = SConscript("%s/SConscript" % build_dir, exports=['env'])
VariantDir(install_dir, ".", duplicate=False)
Install(install_dir, dstruct)


#################################
# Build and install tests
#################################

env_tests = env.Clone()
conf_tests = Configure(env_tests)

build_path = os.path.abspath(build_dir)
test_build_dir = os.path.join(build_dir, "test")
test_install_dir = os.path.join(install_dir,"test")
google_test_dir = env_tests["google_test_dir"]
env_tests['LIBPATH'] = [build_path]
env_tests['LIBPATH'].append( os.path.join(google_test_dir, "lib"))
env_tests['CPPPATH'].append(os.path.join(google_test_dir, "include"))

if not conf_tests.CheckLibWithHeader("gtest", "gtest/gtest.h", "c++"):
    print "Google Test Library not found. Test are not built"
else:
    env_tests = conf_tests.Finish()
    VariantDir(test_build_dir, "test", duplicate=False)
    tests_exec, input_files = SConscript("%s/SConscript" % test_build_dir,
                                         exports=['env_tests'])
# Do not install the tests
#    VariantDir(test_install_dir, ".", duplicate=False)
#    Install(test_install_dir, [tests_exec])
#    input_dir = os.path.join(test_install_dir, "input")
#    VariantDir(input_dir, ".", duplicate=False)
#    Install(input_dir, [ input_files])


