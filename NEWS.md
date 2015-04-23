News/Changelog
==============

New in version 0.2:
-------------------

  * The string that `getPath()` returns is now a proper URI (i.e. prefixed
    with "file://") instead of an LFS-style string. This makes it easier for
    consumption by `tizen.filesystem.resolve()` and its friends.

  * All functions in the C API have been renamed. Now they all have the same
    camel-cased name as the JS API, prefixed with `common_` (e.g.
    `common_getVersion()`).
