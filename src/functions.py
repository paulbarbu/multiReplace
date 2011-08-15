def dbg(*params, **keywords):
    for param in params:
        print 'DEBUG: <%s>' % param

    for k in keywords:
        print 'DEBUG %(key)s: %(val)s' % {'key': k, 'val': keywords[k]}

def starting(section, path, config, r):
    print 'Section: {0}\nPath: {1}\nConfig: {2}\nRecursive: {3}'.\
            format(section, path, config, r)

def ending(n_replacements, n_files):
    print 'Made {0} replacements in {1} file(s)!'.format(n_replacements, n_files)

def lev(s1, s2):
    if len(s1) < len(s2):
        return lev(s2, s1)
    if not s1:
        return len(s2)

    previous_row = xrange(len(s2) + 1)
    for i, c1 in enumerate(s1):
        current_row = [i + 1]
        for j, c2 in enumerate(s2):
            insertions = previous_row[j + 1] + 1 # j+1 instead of j since previous_row and current_row are one character longer
            deletions = current_row[j] + 1       # than s2
            substitutions = previous_row[j] + (c1 != c2)
            current_row.append(min(insertions, deletions, substitutions))
        previous_row = current_row

    return previous_row[-1]
