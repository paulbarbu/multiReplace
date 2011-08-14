#! /usr/bin/env python2.7

'''PyMultiReplace, replacement made easy

This program is designed to replace multiple strings or characters
in multiple files at a time

Usage: ./mr.py [option]

Options:
-h, --help              display this help information
-v, --verbose           display detailed information
-l ..., --lang=...      the config section you want to use for replacement
-p ..., --path=...      the path to the dir or to the file the string should be
replaced in
-c ..., --config=...    the path to the configuration file where the replacement
strings should be read

TODO: add examples
'''

#TODO: Readme.md for every branch
#TODO: swap branches master <-> python, then 'python' becomes 'C'

import getopt
import sys
import logging
import os

import err
from functions import *
from path import Path

def main(argv):
    lang = 'default'
    logLevel = logging.WARNING

    path = Path()
    config = Path()

    try:
        opts, args = getopt.getopt(argv, 'hvl:p:c:',
                ['help', 'verbose', 'lang=', 'path=', 'config='])
    except getopt.GetoptError as detail:
        logging.error(detail)
    else:
        for opt, arg in opts:
            if opt in ('-h', '--help'):
                print __doc__
                sys.exit(0)
            elif opt in ('-v', '--verbose'):
                logLevel = logging.INFO
            elif opt in ('-l', '--lang'):
                lang = arg
            elif opt in ('-p', '--path'):
                path = setPath(arg)
            elif opt in ('-c', '--config'):
                config = setPath(arg)

    logging.basicConfig(level=logLevel,
                        format='%(levelname)s: %(message)s')

    if not path.getPath():
        path.setPath(os.getcwd())


    starting(lang=lang, path=path.getPath(), config=config.getPath(), log=logLevel)

if __name__ == '__main__':
    main(sys.argv[1:])
