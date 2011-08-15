import ConfigParser
import os

import file
import path
from exception import *

class IniConfig(file.File):
    '''Parse configuration files
    '''

    def __init__(self, p = None, cache = None):
        '''
        @param path a Path object to the config file
        '''

        self._cache = cache

        if isinstance(p, path.Path) and os.path.isfile(p.getPath()):
            self._path = p
            self._cfg = ConfigParser.RawConfigParser()
        else:
            self._path = None
            self._cfg = None

    def parse(self, section = None):
        '''Parse the config file

        @throws ConfigParser.Error
        @throws InexistentPathError

        @param section string representing the section of the config to be
        parsed

        @return a list of tuples, form: (key, value) contained in the
        section or False if trying to parse anything else but a text file

        The key and value strings returned are utf-8 encoded
        '''

        if self._path and self._path.exists():

            if -1 != super(self.__class__, self).getMime().find('text'):
                self._cfg.read(self._path.getPath())

                try:
                    tokens = self._cfg.items(section)
                except ConfigParser.Error as detail:
                    raise detail

                cfgEncoding = super(self.__class__, self).getEncoding()
                result = []
                for t in tokens:
                    result.append((unicode(t[0], cfgEncoding).encode('utf-8'),
                                   unicode(t[1], cfgEncoding).encode('utf-8')))

                return result
            else:
                return False
        else:
            raise InexistentPathError(self._path)
