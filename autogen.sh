#!/bin/sh

AUTORECONF=`which autoreconf`

if [ -z $AUTORECONF ]; then
  echo "*** autoreconf not found, please install autoconf ***"
fi

$AUTORECONF -fvi
