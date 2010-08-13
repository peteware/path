# -*- python -*-
import os
#env = Environment(tools=['mingw'], ENV = {'PATH' : os.environ['PATH']})
env = Environment(CPPPATH=['#include'], CCFLAGS=['-g', '-Wall', '-O3'])
Export("env")
for dir in ['src', os.path.join('tests', 'pathtest'), os.path.join('tests', 'search')]:
    SConscript(dirs = dir, 
               variant_dir = os.path.join('build', 'Debug', dir), duplicate = 0)
#'tests/pathtest/SConscrtipt',
