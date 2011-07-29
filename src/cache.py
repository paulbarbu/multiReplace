class Cache(object):
    '''Class for caching
    '''

    def __init__(self, content = None):
        self._content = content

    def set(self, content):
        '''Fills the cache

        @param content the value the will be assigned to self._content
        '''
        self._content = content

    def get(self):
        '''Returns the contents of the cache
        '''
        return self._content

    def empty(self):
        '''Empties the cache

        Sets self._content to None
        '''
        self._content = None

    def isEmpty(self):
        '''Checks whether the cache is empty

        @return bool True if the cache is empty(None or ''), otherwise False
        '''

        if self._content:
            return False

        return True
