import ConfigParser

class Config(object):
    '''Parse configuration files
    '''

    def __init__(self, path = None):
        '''
        @param path a Path object to the config file
        '''

        self._path = path

    def parse(self, section = None):
        '''Parse the config file

        @param section string representing the section of the config to be
        parsed

        @return a dictionary of tokens, form: (key, value)
        '''
        pass

    def createDefault(self, content, overwrite = False):
        '''Sets a default config file at self._path

        @param content the content to be written
        @param overwrite bool, if True the contents of a possibly existing file
        will be overwritten

        @return bool  True for success, else False
        '''
        pass
    #TODO: a file is a Path with contents, maybe use inheritance Path -> File?
