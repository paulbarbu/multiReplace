class Cache(object):
    '''Class for caching
    '''

    def __init__(self, content = {}):
            self._content = content

    def add(self, key, item, overwrite = False):
        '''Adds the dict {key: item} to self._content

        If overwrite is True, then if that key already exists it will be
        overwritten
        '''

        if overwrite and key in self._content or key not in self._content:
            self._content[key] = item

    def get(self):#TODO getItem
        '''Returns the contents of the cache
        '''
        return self._content

    def empty(self):
        '''Empties the cache

        Clears the self._content dictionary
        '''
        self._content.clear()

    def delete(self, key):
        '''Deletes the item with 'key' from the cache

        @throws InexistentCacheKey if the key doesn't exists in
        self._content

        @return the deleted item's value
        '''

        if key in self._content:
            deleted_item = self._content[key]
            del self._content[key]

            return deleted_item
        else:
            raise InexistentCacheKey(key)


    def isEmpty(self):
        '''Checks whether the cache is empty

        @return bool True if the cache is empty, otherwise False
        '''

        if self._content:
            return False

        return True

class InexistentCacheKey(Exception):
    '''Raised when trying to access an inexistent dictionary entry by its key
    '''
    def __init__(self, key):
        self._key = key

    def __str__(self):
        return self._key
