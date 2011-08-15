multiReplace
============

This is an extensible, cross-platform, command line tool written in Python for fast
find & replace strings in multiple files at a time.

The strings and their replacement are stored in \*.ini files(config files) as pairs.

For the C version of this program checkout branch C.

Configs
=======

No standard config is supplied!
Please create your own, suitable for your needs.

__ATTENTION__:
If replacing special characters the config file's encoding must be the same as
the file's in which the replacements are made, else the matching will fail.

Basic usage
===========

`./mr -p path/to/directory_or_file -c path/to/config/default.ini -s section`

Options
=======

    -h, --help              display this help information  
    -s ..., --section=...   the config section you want to use for replacement  
    -p ..., --path=...      the path to the dir or to the file the string should be replaced in  
    -c ..., --config=...    the path to the configuration file where the replacement strings should be read  
    -r, --recursive         is the path is a directory it will be walked recursively  

## Examples:

    ./mr.py -s ro -p ~/subs -c ~/cfg.ini
    ./mr.py -s ro -p ~/subs -c ~/cfg.ini -r
    ./mr.py -s ro -p ~/file.srt -c ~/cfg.ini
    ./mr.py --section ro --path ~/file.srt --config ~/cfg.ini


Dependencies
============
* File.getMime depends on [Python-magic](https://github.com/ahupp/python-magic 'Python-magic')
* File.getEncoding depends on [chardet](http://chardet.feedparser.org/ 'chardet')

History
=======

2. multiReplace written in C, now becomes Pythonic multiReplace

1. Original name: subEDIT
Its original purpose was to replace characters in subtitles, now its purpose is
generally to replace strings in files.

License
=======

(C) Copyright 2011 Paul Barbu

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
