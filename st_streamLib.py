#$Id: st_streamLib.py,v 1.2 2008/02/22 00:53:50 golpa Exp $
def generate(env, **kw):
	if not kw.get('depsOnly',0):
		env.Tool('addLibrary', library = ['st_stream'])

def exists(env):
	return 1
