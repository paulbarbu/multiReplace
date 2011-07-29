import pwd
from functions import *

class User(object):
    '''User blueprint

    The name is independent from the UID, the only condition is that _name must
    be set when calling getUidByName() and _uid must be set when calling
    getNameByUid(), else NameNotSet or UidNotSet will be raised
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

    def setUid(self, uid):
        '''Sets the user's UID
        '''
        self._uid = uid

    def getUidByName(self):
        '''Get the UID of the user

        @throws NameNotSet if trying to use this method before the user's name
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
            raise NameNotSet()

    def getNameByUid(self):
        '''Get the user's name by his UID

        @throws UIDNotSet if trying to use this method before the UID is set
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
            raise UidNotSet()

class NameNotSet(Exception):
    '''Raised when the user's name is needed, but not set
    '''
    pass

class UidNotSet(Exception):
    '''Raised when the UID is needed, but not set
    '''
    pass
