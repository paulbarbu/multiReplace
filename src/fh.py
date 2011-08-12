class FileHandler(object):
    '''Handle Path objects pointing at files
    '''

    def __init__(self, path = None):
        '''Instantiate using a pth object

        @param path a path object
        '''

        self._path = path

    def replace(self, tokens):
        '''Use the tokns and make replacements in self._path

        @param tokens a dictionary containing pairs (target, replacement) strings

        @return number of replacements made
        '''
        pass

    #TODO: maybe inherit Path: Path -> File -> ConfigFile
