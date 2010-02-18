# -*- python -*-
# $Id: SConscript,v 1.10 2009/07/15 18:33:54 glastrm Exp $
# Authors: James Peachey peachey@lheamail.gsfc.nasa.gov
# Version: st_stream-00-06-01

Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

st_streamLib = libEnv.StaticLibrary('st_stream', listFiles(['src/*.cxx']))

progEnv.Tool('st_streamLib')
test_st_streamBin = progEnv.Program('test_st_stream', listFiles(['src/test/*.cxx']))

progEnv.Tool('registerTargets', package = 'st_stream',
             staticLibraryCxts = [[st_streamLib, libEnv]],
             includes = listFiles(['st_stream/*.h']),
             testAppCxts = [[test_st_streamBin, progEnv]],
             data = listFiles(['data/*'], recursive = True))
