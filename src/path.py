class Path(object):
    '''Blueprint for Path objects

    '''

    def __init__(self, path = None):
        self._path = None

        if path and self.exists(path):
            self._path = path

    def getPath(self):
        return self._path

    def setPath(self, path):
        if path and self.exists(path):
            self._path = path

    def exists(self, path):
        '''Check if a file exists at the path pointed by self._path

        '''
        import os

        if not os.path.exists(path):
            return False

        return True

    def hasRights(self, r = True, w = False, x = False):
        '''Check if the current user has read, write or execute rights on
        self._path
        '''
        pass

    def getPerm(self):
        '''Get the octal representation of the current permissions on self._path
        '''
        pass

    def setPerm(self, rights):
        '''Set the specified permissions on the path pointed by self._path

        Rights parameter must be passed as an octal value, eg: 0550, 0775, 0777
        '''
        pass

    def getOwner(self):
        '''Get the owner of the path into _owner and return it
        '''
        pass

    def getGroup(self):
        '''Get the group that has permissions on _path

        Populate _group and return its value
        '''
