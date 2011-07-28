class User(object):
    '''User blueprint
    '''

    def __init__(self):
        '''Gets the user under the program is run

        self._name, user's name, string
        self._uid, user's UID, int
        self._groups, list of groups the user belongs to
        '''
        pass

    def getUID(self):
        '''Get the UID

        Populate _uid and return it
        '''

    def getGroups(self):
        '''Gets the list of groups the user belongs to

        This method populates _groups and returns that list
        '''
        pass

    def belongsTo(self, group):
        '''Check whether the user belongs to a group
        '''
