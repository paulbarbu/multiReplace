def dbg(*params, **keywords):
    for param in params:
        print 'DEBUG: <%s>' % param

    for k in keywords:
        print 'DEBUG %(key)s: %(val)s' % {'key': k, 'val': keywords[k]}

def starting(section, path, config, r):
    print 'Section: {0}\nPath: {1}\nConfig: {2}\nRecursive: {3}'.\
            format(section, path, config, r)

def ending(n_replacements, n_files):
    print 'Made {0} replacements in {1} files!'.format(n_replacements, n_files)
