import stat
import os
import pwd
import grp

from functions import *
from user import User

class Path(object):
    '''Blueprint for Path objects

    A directory path has a trailing '/', a file path doesn't
    '''

    #TODO implement Cache, User, Group, PathValidator

    def __init__(self, path = None):
        self._path = None
        self._owner = None
        self._group = None
        self._gid = None
        self._exists = False

        if path:
            self._path = path
            self.exists()

    def getPath(self):
        '''Returns the current path

        '''
        #TODO check the trailing slash
        return self._path

    def setPath(self, path):
        '''Sets self._path

        @param path string representing the path
        '''
        if path:
            self._path = path
            self.exists()

    def exists(self):
        '''Checks if a file or directory exists at the path pointed by self._path

        It also sets self._exists

        @return bool
        '''

        self._exists = True

        if not os.path.exists(self._path):
            self._exists = False;

        return self._exists

    def hasRights(self, r = True, w = False, x = False):
        '''Check if the current user has read, write or execute rights on
        self._path

        @throws InexistentPathError if the path doesn't exist

        @param r bool value indicating if read permissions will be checked
        @param w bool value indicating if write permissions will be checked
        @param x bool value indicating if execute permissions will be checked

        @return bool
        '''
        pass

    def getPerm(self):
        '''Get the octal representation of the current permissions on self._path

        @throws InexistentPathError if the path doesn't exist
        '''

        if self._exists:
            path_stat = os.stat(self._path)#TODO: USE cache
            full_permissions = path_stat[stat.ST_MODE]

            #return just the interesting bits
            return oct(full_permissions)[-4:]
        else:
            raise InexistentPathError(self._path)

    def setPerm(self, rights):
        '''Set the specified permissions on the path pointed by self._path

        @throws InexistentPathError if the path doesn't exist
        @throws the same exceptions as os.chmod() if it fails

        @param rights must be passed as an octal value, eg: 0550, 0775, 0777

        @retval bool, True is chmod succeeded, otherwise False
        '''

        if self._exists:
            try:
                os.chmod(self._path, rights)
            except OSError as detail:
                raise detail

            return True
        else:
            raise InexistentPathError(self._path)

    def getOwner(self):
        '''Gets the path's owner, if it's not already set it will be set

        @throws InexistentPathError if the path doesn't exist

        @return an User object
        '''

        if self._exists:

            if not self._owner:
                path_stat = os.stat(self._path)#TODO: USE cache
                uid = path_stat[stat.ST_UID]

                owner = User(uid = uid)

                self._owner = owner

            return self._owner
        else:
            raise InexistentPathError(self._path)

    def getGroup(self):
        '''Get the group name and GID that has permissions on _path

        @throws InexistentPathError if the path doesn't exist

        It populates _group and _gid
        @return [_gid, _group]
        '''

        #TODO: Group class

        if self._exists:
            path_stat = os.stat(self._path)#TODO: USE cache
            self._gid = path_stat[stat.ST_GID]

            self._group = grp.getgrgid(self._gid)[0]

            return [self._gid, self._group]
        else:
            raise InexistentPathError(self._path)

    def make(self, overwrite = False, parentMustExist = False):
        '''Create a file or dir at the location pointed by path

        @throws the same exceptions as open(), os.makedirs() and os.mkdir()

        @param overwrite bool, if True the FILE will be overwritten if it
        exists
        @param parentMustExist specifies whether the path will be created ONLY if
        the leading directories exists or if they will be created too(the whole
        structure will be created), see 'mkdir -p'

        @return bool True if the path was created, False otherwise

        If the path is a file, it will be touch'ed, else a directory [structure]
        will be created

        A directory path has a trailing '/', a file path doesn't

        Also self._exists is set to True if the creation was successful
        '''

        if self._exists and overwrite or not self._exists:
            if self._path[-1] == os.sep: #create a dir [structure]
                if parentMustExist:
                    self._path = self._path[:-1]
                    parent = os.path.split(self._path)[0]

                    if os.path.exists(parent):
                        try:
                            os.mkdir(self._path)
                        except OSError as detail:
                            raise detail
                    else:
                        return False
                else:
                    try:
                        os.makedirs(self._path)
                    except OSError as detail:
                        raise detail
            else: #create a file
                parent, file_name = os.path.split(self._path)

                if parentMustExist:
                    if os.path.exists(parent):
                        try:
                            open(self._path, 'w').close()
                        except IOError as detail:
                            raise detail
                    else:
                        return False
                else:
                    try:
                        os.makedirs(parent)
                    except OSError as detail:
                        raise detail

                    try:
                        open(self._path, 'w').close()
                    except IOError as detail:
                        raise detail

            self._exists = True
            return True
        else:
            return False

class InexistentPathError(Exception):
    '''This exception is raised when trying to use an inexistent path

    '''

    def __init__(self, path):
        self._path = path

    def __str__(self):
        return self._path
