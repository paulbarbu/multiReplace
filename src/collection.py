from functions import *
from exception import *

class Collection(object):
    '''Collection class

    It holds a list of objects
    '''

    def __init__(self, *objects):
        self._items = []

        for obj in objects:
            self._items.append(obj)

    def map(self, callback, *args, **kargs):
        '''Call every callback on the objects in the collection

        @throws EmptyCollectionError if this method is called on an empty
        collection

        @param callback a function object to be called on the objects
        @param *args an argument list for passing to the callback function
        @param *kargs a keyed argument list to pass the the callback

        @return a list with the retvals values

        Usage:
        col.map(Path.getPerm)          this will call Path.getPerm() on every
        item in the collection col

        col2.map(Path.make, True))      this will call Path.make(True) on every
        item in the collection col2
        '''

        result = []

        if self._items:
            for obj in self._items:
                try:
                    result.append(callback(obj, *args, **kargs))
                except Exception as detail:
                    raise detail

            return result
        else:
            raise EmptyCollectionError('map')
