class InexistentPathError(Exception):
    '''This exception is raised when trying to use an inexistent path

    '''

    def __init__(self, path):
        self._path = path

    def __str__(self):
        return 'The path does not exist: {0}'.format(self._path)

#TODO error code
class NotSetError(Exception):
    '''Raised when the user's property is needed, but not set
    '''

    def __init__(self, prop):
        self._prop = prop

    def __str__(self):
        return 'Cannot use a property before it\'s set: {0}'\
                .format(self._prop)

class InexistentCacheKey(Exception):
    '''Raised when trying to access an inexistent dictionary entry by its key
    '''
    def __init__(self, key):
        self._key = key

    def __str__(self):
        return 'Inexistent key entry: {0}'.format(self._key)
