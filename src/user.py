import pwd

from exception import *

class User(object):
    '''User blueprint

    '''

    def __init__(self, uid = None, name = None, cache = None):
        '''
        self._name, user's name, string
        self._uid, user's UID, int
        '''
        self._uid = uid
        self._name = name
        self._cache = cache

    def setName(self, name):
        '''Set's the user's name
        '''

        if self._cache:
            pwnam = self._cache.getItem(self._name)
            if pwnam:
                self._cache.delete(self._name) #invalidate cache

            pwuid = self._cache.getItem(self._uid)
            if pwuid:
                self._cache.delete(self._uid) #invalidate cache

        self._name = name

    def setUID(self, uid):
        '''Sets the user's UID
        '''

        if self._cache:
            pwuid = self._cache.getItem(self._uid)
            if pwuid:
                self._cache.delete(self._uid) #invalidate cache

            pwnam = self._cache.getItem(self._name)
            if pwnam:
                self._cache.delete(self._name) #invalidate cache

        self._uid = uid

    def getUID(self):
        '''Get the UID of the user

        @throws NotSetError if trying to use this method before the user's name
        is set
        @throws KeyError when the user is not found

        Populate _uid and return it
        '''

        if self._name:
            if self._cache:
                pwnam = self._cache.getItem(self._name)

                if not pwnam:
                    pwnam = pwd.getpwnam(self._name)
                    self._cache.add(self._name, pwnam)

                self._uid = pwnam[2]

            else:
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
            if self._cache:
                pwuid = self._cache.getItem(self._uid)

                if not pwuid:
                    pwuid = pwd.getpwuid(self._uid)
                    self._cache.add(self._uid, pwuid)

                self._name = pwuid[0]

            else:
                try:
                    self._name = pwd.getpwuid(self._uid)[0]
                except KeyError as detail:
                        raise detail

            return self._name
        else:
            raise NotSetError('UID')
