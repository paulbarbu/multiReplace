#! /usr/bin/env python2.7

'''PyMultiReplace, replacement made easy

This program is designed to replace multiple strings or characters
in multiple files at a time

Usage: ./mr.py [option]

Options:
-h, --help              display this help information
-s ..., --section=...   the config section you want to use for replacement
-p ..., --path=...      the path to the dir or to the file the string should be replaced in
-c ..., --config=...    the path to the configuration file where the replacement strings should be read
-r, --recursive         is the path is a directory it will be walked recursively

Examples:
./mr.py -s ro -p ~/subs -c ~/cfg.ini
./mr.py -s ro -p ~/subs -c ~/cfg.ini -r
./mr.py -s ro -p ~/file.srt -c ~/cfg.ini
./mr.py --section ro --path ~/file.srt --config ~/cfg.ini
'''

import getopt
import sys
import logging
import os
import ConfigParser

import err
from path import Path
from cache import Cache
from collection import RunCollection
from iniconfig import IniConfig
from file import File
from functions import *


def main(argv):
    section = ''
    recursive = False

    logLevel = logging.WARNING

    total_files = 0
    total_replacements = 0

    logging.basicConfig(level=logLevel, format='%(levelname)s: %(message)s')

    pathsCache = Cache()

    path = Path(cache = pathsCache)
    configPath = Path(cache = pathsCache)

    try:
        opts, args = getopt.getopt(argv, 'hrs:p:c:',
                ['help', 'recursive', 'section=', 'path=', 'config='])
    except getopt.GetoptError as detail:
        logging.error(detail)
    else:
        for opt, arg in opts:
            if opt in ('-h', '--help'):
                print __doc__
                sys.exit(0)

            elif opt in ('-r', '--recursive'):
                recursive = True

            elif opt in ('-s', '--section'):
                section = arg

            elif opt in ('-p', '--path'):
                path.setPath(arg)

            elif opt in ('-c', '--config'):
                configPath.setPath(arg)

    if not section:
        logging.error(err.err_msg.format(3, err.error[3]))
        sys.exit(1)

    if not path.exists():
        logging.error(err.err_msg.format(1, err.error[1].format('path',
            path.getPath())))
        sys.exit(1)

    if not path.hasRights(True, True):
        logging.error(err.err_msg.format(2, err.error[2].format(path.getPath(),
            'read and write')))
        sys.exit(1)

    if not configPath.exists():
        logging.error(err.err_msg.format(1, err.error[1].format('config path',
            configPath.getPath())))
        sys.exit(1)

    if not configPath.hasRights():
        logging.error(err.err_msg.format(2,
            err.error[2].format(configPath.getPath(), 'read')))
        sys.exit(1)

    configFile = IniConfig(configPath)

    try:
        tokens = configFile.parse(section)
    except ConfigParser.NoSectionError:
        logging.error(err.err_msg.format(5, err.error[5].format(section)))
        sys.exit(1)

    if not tokens:
        logging.error(err.err_msg.format(4,
            err.error[4].format(section, configPath.getPath())))
        sys.exit(1)

    starting(section=section, path=path.getPath(), config=configPath.getPath(),
            r = recursive)

    if os.path.isdir(path.getPath()):
        fileCollection = path.getFilesByMime('text', recursive)

    else:
        fileCollection = RunCollection(File(path))

    if fileCollection:
        total_files = fileCollection.countItems()
        total_replacements = fileCollection.map(File.replace, postponeException = False, tokens = tokens)

    ending(total_replacements[0], total_files)

if __name__ == '__main__':
    main(sys.argv[1:])
