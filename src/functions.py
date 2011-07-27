def dbg(*params, **keywords):
    for param in params:
        print 'DEBUG: <%s>' % param

    for k in keywords:
        print 'DEBUG %(key)s: %(val)s' % {'key': k, 'val': keywords[k]}

def starting(lang, path, config, log):
    print 'Lang: {0}\nPath: {1}\nConfig: {2}\nLog level: {3}'.\
            format(lang, path, config, log)
