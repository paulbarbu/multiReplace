import pwd
from functions import *

class User(object):
    '''User blueprint

    '''

    def __init__(self, uid = None, name = None):
        '''
        self._name, user's name, string
        self._uid, user's UID, int
        '''
        self._uid = uid
        self._name = name

    def setName(self, name):
        '''Set's the user's name
        '''
        self._name = name

    def setUID(self, uid):
        '''Sets the user's UID
        '''
        self._uid = uid

    def getUID(self):
        '''Get the UID of the user

        @throws NotSetError if trying to use this method before the user's name
        is set
        @throws KeyError when the user is not found

        Populate _uid and return it
        '''

        if self._name:
            try:
                self._uid = pwd.getpwnam(self._name)[2]
            except KeyError as detail:
                raise detail

            return self._uid
        else:
            raise NotSetError('name')

    def getName(self):
        '''Get the user's name

        @throws NotSetError if trying to use this method before the UID is set
        @throws KeyError when the UID is not found

        Populate _name and return it
        '''
        if self._uid:
            try:
                self._name = pwd.getpwuid(self._uid)[0]
            except KeyError as detail:
                    raise detail

            return self._name
        else:
            raise NotSetError('UID')

#TODO error code
class NotSetError(Exception):
    '''Raised when the user's property is needed, but not set
    '''

    def __init__(self, prop):
        self._prop = prop

    def __str__(self):
        return 'Cannot use a property before it\'s set: {0}'\
                .format(self._prop)
