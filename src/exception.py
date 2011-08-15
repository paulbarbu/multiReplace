class InexistentPathError(Exception):
    '''This exception is raised when trying to use an inexistent path

    '''

    def __init__(self, path):
        self._path = path

    def __str__(self):
        return 'The path does not exist: {0}'.format(self._path)

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

class EmptyCollectionError(Exception):
    '''Raised when an action is performed on an empty collection
    '''

    def __init__(self, action):
        self._action = action

    def __str__(self):
        return 'Cannot {0} an empty collection!'.format(self._action)

class HybridException(Exception):
    '''This exception is used in RunCollection, when postPoneException is True
    '''

    def __init__(self):
        self._exceptions = []
        self._retvals = []

    def hasExceptions(self):
        '''
        @return bool True, if the self._exceptions list is not empty, else False
        '''

        if not self._exceptions:
            return False

        return True

    def addException(self, ex):
        '''Adds an exception to self._exceptions

        @param ex an exception object

        @return bool True if the exception was added, else False
        '''

        if isinstance(ex, Exception):
            self._exceptions.append(ex)

            return True

        return False

    def addRetval(self, retval):
        '''Adds the retval to self._retvals

        @param retval any value returned by a callback
        '''

        if type(retval) is list:
            self._retvals.extend(retval)
        else:
            self._retvals.append(retval)

    def getRetvals(self):
        '''
        @return self._retvals
        '''

        return self._retvals

    def __str__(self):
        '''
        @return a block of text consisting of every exception's string
        '''

        exceptionText = '\n'

        for ex in self._exceptions:
            exceptionText += ex.__str__() + '\n'

        return exceptionText




