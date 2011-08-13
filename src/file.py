import path

class File(object):
    '''Handle Path objects pointing at files
    '''

    def __init__(self, p = None):
        '''Instantiate using a path object

        @param p a path object
        '''

        if isinstance(p, path.Path):
            self._path = p
        else:
            self._path = None

    def setPath(self, p = None):
        '''Change the self._path attribute

        @param path a path object

        If the provided argument is a path object the property will be changed,
        else it won't
        '''

        if isinstance(p, path.Path):
            self._path = p

    def replace(self, tokens):
        '''Use the tokens and make replacements in the file

        @param tokens a dictionary containing pairs (target, replacement) strings

        @return number of replacements made
        '''
        pass
