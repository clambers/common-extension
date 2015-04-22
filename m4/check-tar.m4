m4_define([CHECK_TAR_OPTION],
[printf 'checking whether tar accepts -$1...']
[if tar c$1f /dev/null /dev/null >&- 2>&-; then $2=yes; else $2=no; fi]
[printf '%s\n' "$$2"])
