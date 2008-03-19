#$Id: SConscript,v 1.5 2008/02/26 16:23:28 glastrm Exp $

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
