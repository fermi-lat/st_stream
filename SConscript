# -*- python -*-
# $Id: SConscript,v 1.6 2008/03/19 20:40:12 glastrm Exp $
# Authors: James Peachey peachey@lheamail.gsfc.nasa.gov
# Version: st_stream-00-05-02

Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('st_streamLib', depsOnly = 1)
st_streamLib = libEnv.StaticLibrary('st_stream', listFiles(['src/*.cxx']))

progEnv.Tool('st_streamLib')
test_st_streamBin = progEnv.Program('test_st_stream', listFiles(['src/test/*.cxx']))

progEnv.Tool('registerObjects', package = 'st_stream', libraries = [st_streamLib], includes = listFiles(['st_stream/*.h']), testApps = [test_st_streamBin],
             data = listFiles(['data/*'], recursive = True))
