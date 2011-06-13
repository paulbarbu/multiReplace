multiReplace
=======

This is an extensible, cross-platform, command line tool written in C for fast
find & replace strings in multiple files at a time.

The strings and their replacement are stored in \*.ini files as pairs.

Defaults
========

Default path: ./files

Default configuration file: ./config/default.ini

Default language: first to be found in the configuration file

Configs
=======

Just a test config for now...

Basic usage
===========

./mr -p path/to/directory\_or\_file -c path/to/config/default.ini -l section

Compilation
============

Just use 'make' in multiReplace's root directory

History
=======

Original name: subEDIT
Its original purpose was to replace characters in subtitles, now its purpose is
generally to replace strings in files

License
=======

(C) Copyright 2011 PauLLiK

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
