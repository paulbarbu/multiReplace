import stat
import os
import pwd
import grp

from functions import *

class Path(object):
    '''Blueprint for Path objects

    A path to a directory has a trailing '/', a file path doesn't
    '''

    #TODO cache the stat response, maybe a new class? Cache

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

    def setPerm(self, rights):
        '''Set the specified permissions on the path pointed by self._path

        Rights parameter must be passed as an octal value, eg: 0550, 0775, 0777
        '''
        pass

    def getOwner(self):
        '''Get the owner's path name into _owner and the UID into _uid


        Return a list [_uid, _owner]
        If the path does not exist, returns None
        '''

        if self.exists():
            path_stat = os.stat(self._path)
            self._uid = path_stat[stat.ST_UID]

            self._owner = pwd.getpwuid(self._uid)[0]

            return [self._uid, self._owner]

    def getGroup(self):
        '''Get the group name and GID that has permissions on _path

        Populate _group and _gid, returns [_gid, _group]
        '''

        if self.exists():
            path_stat = os.stat(self._path)
            self._gid = path_stat[stat.ST_GID]

            self._group = grp.getgrgid(self._gid)[0]

            return [self._gid, self._group]

    def make(self, parentMustExist = False):
        '''Create a path

        parentMustExist parameter specifies whether the path will be created if
        the leading directories exists or if they will be created too(the whole
        structure will be created), see 'mkdir -p'

        If the path is a file, it will be touch'ed, else a directory will be
        created
        '''
        pass
