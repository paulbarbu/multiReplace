import stat
import os
import pwd
import grp

from functions import *

class Path(object):
    '''Blueprint for Path objects

    A path to a directory has a trailing '/', a file path doesn't
    '''

    #TODO implement Cache
    #TODO self._exists, will be set by exists()
    #TODO enhanced docs

    def __init__(self, path = None):
        self._path = None

        if path:
            self._path = path

    def getPath(self):
        return self._path

    def setPath(self, path):
        if path:
            self._path = path

    def exists(self):
        '''Check if a file exists at the path pointed by self._path

        '''

        if not os.path.exists(self._path):
            return False

        return True

    def hasRights(self, r = True, w = False, x = False):
        '''Check if the current user has read, write or execute rights on
        self._path
        '''
        pass

    def getPerm(self):
        '''Get the octal representation of the current permissions on self._path

        if the path is inexistent it returns None
        '''

        if self.exists():
            path_stat = os.stat(self._path)
            full_permissions = path_stat[stat.ST_MODE]

            #return just the interesting bits
            return oct(full_permissions)[-4:]
        else:
            raise InexistentPathError(self._path)

    def setPerm(self, rights):
        '''Set the specified permissions on the path pointed by self._path

        @throws InexistentPathError if the path doesn't exist
        @param rights must be passed as an octal value, eg: 0550, 0775, 0777

        @retval bool, True is chmod succeeded, otherwise False
        '''

        if self.exists():
            try:
                os.chmod(self._path, rights)
            except OSError as detail:
                raise detail

            return True
        else:
            raise InexistentPathError(self._path)

    def getOwner(self):
        '''Get the owner's path name into _owner and the UID into _uid


        Return a list [_uid, _owner]
        If the path does not exist, returns None
        '''
        #TODO use User class

        if self.exists():
            path_stat = os.stat(self._path)
            self._uid = path_stat[stat.ST_UID]

            self._owner = pwd.getpwuid(self._uid)[0]

            return [self._uid, self._owner]
        else:
            raise InexistentPathError(self._path)

    def getGroup(self):
        '''Get the group name and GID that has permissions on _path

        Populate _group and _gid, returns [_gid, _group]
        '''

        if self.exists():
            path_stat = os.stat(self._path)
            self._gid = path_stat[stat.ST_GID]

            self._group = grp.getgrgid(self._gid)[0]

            return [self._gid, self._group]
        else:
            raise InexistentPathError(self._path)

    def make(self, parentMustExist = False):
        '''Create a path

        parentMustExist parameter specifies whether the path will be created if
        the leading directories exists or if they will be created too(the whole
        structure will be created), see 'mkdir -p'

        If the path is a file, it will be touch'ed, else a directory will be
        created
        '''
        pass

class InexistentPathError(Exception):
    '''This exception is raised when trying to access or use an inexistent path

    '''

    def __init__(self, path):
        self._path = path

    def __str__(self):
        return self._path
