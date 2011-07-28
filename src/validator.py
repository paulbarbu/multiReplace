class PathValidator(object):
    '''Class for validating path objects

    '''

    def __init__(self, *paths):
        '''Make a list of all the supplied path objects
        '''
        self.paths = []

        for path in paths:
            self.paths.append(path)

    def validate(self):
        '''Check which paths are valid, which not

        Return a dictionary, paths as keys and True or False as value, depending
        on the existence of the paths
        '''
