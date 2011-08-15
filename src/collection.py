from exception import *

class RunCollection(object):
    '''Collection class

    It holds a list of objects
    '''

    def __init__(self, *objects):
        self._items = []

        for obj in objects:
            self._items.append(obj)

    def add(self, obj):
        self._items.append(obj)

    def map(self, callback, postponeException = False, *args, **kargs):
        '''Call every callback on the objects in the collection

        @throws EmptyCollectionError if this method is called on an empty
        collection
        @throws HybridException

        @param callback a function object to be called on the objects
        @param postponeException bool, if set to True and the callback raised
        exceptions a HybridException will be raised after the iteration,
        else the exceptions will be raised during the iteration
        @param *args an argument list for passing to the callback function
        @param *kargs a keyed argument list to pass the the callback

        @return a list with the retvals values

        Usage:
        col.map(Path.getPerm)
            -> this will call Path.getPerm() on every item in the collection col

        col2.map(Path.make, True)
            -> this will call Path.make(True) on every item in the collection col2

        col.map(Path.make, postponeException = True, overwrite = True)
            -> this will call map(postponeException = True) and
            Path.make(overwrite = True), so if you want to postpone exceptions
            you'll have to use only keyword arguments
        '''

        result = []
        hException = HybridException()

        if self._items:
            for obj in self._items:
                try:
                    result.append(callback(obj, *args, **kargs))
                except Exception as ex:
                    if postponeException:
                        hException.addException(ex)
                    else:
                        raise ex

            if hException.hasExceptions():
                hException.addRetval(result)
                raise hException

            return result

        else:
            raise EmptyCollectionError('map')

    def countItems(self):
        '''
        @return the number of items stored in the collection
        '''
        return len(self._items)
