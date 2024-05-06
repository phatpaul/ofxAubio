ofxAubio
========

[ofxAubio](https://aubio.org/ofxAubio) is an
[openFrameworks](http://openframeworks.cc) [addon](http://www.ofxaddons.com)
for [aubio](https://aubio.org).

Install
-------

### Linux

Clone `ofxAubio` in your addons folder:

    $ cd /path/to/of_root/addons
    $ git clone git://git.aubio.org/git/ofxAubio/

Install `aubio` library and headers, on Debian/Ubuntu:

    $ sudo sudo apt-get install libaubio-dev

Select projectGenerator, select 'update project', then select the path of
`example_aubioDemo`, `/path/to/of_root/addons/ofxAubio/example_aubioDemo`.

In the generated project edit `config.make` and add/edit this line to this:

    PROJECT_LDFLAGS=-laubio

Build the example:
```sh
make
```
Run the example:
```sh
make RunRelease
```

### MacOSX

Fetch `ofxAubio` and `aubio.framework` from inside your openFrameworks root:

    $ cd /path/to/of_root/addons
    $ git clone git://git.aubio.org/git/ofxAubio/
    $ cd ofxAubio
    $ ./scripts/fetch_aubio_osx_framework.sh

Select projectGenerator, select 'update project', then select the path of
`example_aubioDemo`, `/path/to/of_root/addons/ofxAubio/example_aubioDemo`.

Open `example_aubioDemo.xcodeproject`, drag `aubio.framework` into to it,
placing it in `frameworks / 3rd party frameworks`.

Project Homepage
----------------

The home page of ofxAubio can be found at: https://aubio.org/ofxAubio/

Copyright and License Information
---------------------------------

Copyright (C) 2003-2015 Paul Brossier <piem@aubio.org>

ofxAubio is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.
