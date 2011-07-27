from functions import *
class Path(object):
    '''Blueprint for Path objects


flavius | nu, hasMinRights(550) de exemplu să returneze true/false                                                                     │
paullik | pai si atunci isValid() va verifica os.exists() si hasMinights() nu?                                                         │
paullik | si atunci scap de self._r si self._w, ii cer userului direct drepturile in octal                                             │
flavius | os.path.exists() in isValid(), atât                                                                                          │
flavius | de fapt ai putea redenumi isValid in exists :)                                                                               │
paullik | si atunci in mr.py cand vreau sa vad daca e bun path-ul meu verific hasMinRights, pt ca deja verific exists() in constructor │
flavius | pe mr nu m-am uitat inca                                                                                                     │
flavius | imediat                                                                                                                      │
paullik | ok                                                                                                                           │
flavius | da
    '''

    def __init__(self, path = None, r = True, w = False):
        self._r = r
        self._w = w
        self._path = path

        if self._path and self.isValid(r, w):
            self._path = path

    def getPath(self):
        return self._path

    def setPath(self, path):
        if path and self.isValid(path, self._r, self._w):
            self._path = path

    def isValid(self, path, r = True, w = False):
        '''Check the validity of a path
        It checks whether a file or directory exists at the location pointed by path
        If the file or directory exists it must be non-empty, else False is
        returned

        If the method is used like this:
        path1.isValid(False, True)

        Then write permissions will be checked, but read permissions won't.

        '''
        import os

        if not os.path.exists(path):
            return False
        elif 0 == os.path.getsize(path):
            return False
        elif r and not os.access(path, os.R_OK):
            return False
        elif w and not os.access(path, os.W_OK):
            return False

        return True
