# -*- coding: utf-8 -*-
import os
import tempfile
import shutil

import magic

from exception import *
from functions import *
import path

class File(object):
    '''Handle Path objects pointing at files
    '''

    def __init__(self, p = None, cache = None):
        '''Instantiate using a path object

        @param p a path object that must be pointing to a file
        '''

        self._cache = cache

        if isinstance(p, path.Path) and os.path.isfile(p.getPath()):
            self._path = p
        else:
            self._path = None

    def setPath(self, p = None):
        '''Change the self._path attribute

        @param path a path object

        @return bool True if the path was set, else False

        If the provided argument is a path object the property will be changed,
        else it won't
        '''

        if isinstance(p, path.Path) and os.path.isfile(p.getPath()):
            if self._cache:
                if self._cache.getItem(self._path.getPath()):
                    self._cache.delete(self._path.getPath()) #invalidate cache

            self._path = p

            return True

        return False

    def getMime(self):
        '''Get the Mime type of a file

        @throws InexistentPathError

        @return string containing the Mime type

        This function depends on the python-magic module:
        https://github.com/ahupp/python-magic
        '''

        if self._path and self._path.exists():
            if self._cache:
                mime_type = self._cache.getItem(self._path.getPath())

                if not mime_type: #cache miss
                    mime = magic.Magic(mime=True)
                    mime_type = mime.from_file(self._path.getPath())

                    self._cache.add(self._path.getPath(), mime_type) #validate cache

            else:
                mime = magic.Magic(mime=True)
                mime_type = mime.from_file(self._path.getPath())

            return mime_type
        else:
            raise InexistentPathError(self._path)

    def replace(self, tokens):
        '''Use the tokens and make replacements in the file

        @param tokens a dictionary containing tuples (target, replacement)

        @return number of replacements made
        '''

        replacements = 0

        temp_fh, temp_path = tempfile.mkstemp(suffix='mR')
        temp_file = open(temp_path, 'w')

        with open(self._path.getPath(), 'r') as f:
            line = f.readline()

            while '' != line:
                for t in tokens:
                    line = line.replace(t[0], t[1])

                #TODO: edit distance

                temp_file.write(line)

                line = f.readline()

        temp_file.close()
        os.close(temp_fh)
        os.remove(self._path.getPath())
        shutil.move(temp_path, self._path.getPath())

        return replacements



