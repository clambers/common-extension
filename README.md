libcommon
=========

libcommon is a Tizen extension containing all shared JLR assets. It exposes a
simple interface to reach these assets in a generic way.

The impetus for the project came from the need to share assets (e.g. CSS, JS,
images) between different Tizen web applications. Maybe we wanted a branding
image in the corner of all our apps, or possibly a navigation menu at the
bottom of every app. We simply couldn't duplicate the assets in every project,
so this was born.

API reference
-------------

| Purpose               | JS                      | Returns         |
| --------------------- | ----------------------- | --------------- |
| Get extension version | [`getVersion(cb)`][1]   | Version string  |
| Get asset path        | [`getPath(rel, cb)`][2] | Path URI string |

[1]: #getversioncb
[2]: #getpathrel-cb

Detailed documentation
----------------------

##### getVersion(cb)

###### Params

*cb*: return callback

###### Description

This function returns a string containing the version of libcommon.

* * *

##### getPath(rel, cb)

###### Params

*rel*: a relative path string

*cb*: return callback

###### Description

This function returns a URI pointing to the absolute path on the filesystem of
the asset you want to retrieve. *rel* is the path of the asset relative to
where it was installed.

###### Notes

The string returned by this function is suitable for passing directly to
`tizen.filesystem.resolve()`.

Licensing
---------

libcommon is licensed under [LGPLv3][3].

Copyright (C) 2015 Jaguar Land Rover Automotive PLC.

[3]: https://www.gnu.org/licenses/lgpl-3.0.txt
