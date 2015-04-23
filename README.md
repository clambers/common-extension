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

| Purpose               | JS                 | Returns         |
| --------------------- | ------------------ | --------------- |
| Get extension version | `getVersion(cb)`   | Version string  |
| Get asset path        | `getPath(rel, cb)` | Path URI string |

Detailed documentation
----------------------

##### getVersion(cb)

*cb*: return callback

This function returns a string containing the version of libcommon.

##### getPath(rel, cb)

*rel*: a relative path string

*cb*: return callback

This function returns a URI pointing to the absolute path on the filesystem of
the asset you want to retrieve. *rel* is the path of the asset relative to
where it was installed.

* * *

###### Notes:

The string returned by this function is suitable for passing directly to
`tizen.filesystem.resolve()`.
