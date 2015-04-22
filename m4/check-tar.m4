AC_DEFUN([AC_PROG_TAR_J],
[AC_MSG_CHECKING([for a tar that supports -J])
TAR_J=""
res=""
if tar -cJf /dev/null /dev/null 2>-; then res=yes; else res=no; fi
ac_cv_path_tar=`which tar`
AS_IF([test "x$res"=xyes], [TAR_J="$ac_cv_path_tar -J"],
[AC_MSG_RESULT([no])
AC_MSG_FAILURE([no tar found.])
])
AC_SUBST([TAR_J])
AC_MSG_RESULT([$TAR_J])
])
