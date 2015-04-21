#!/bin/sh

INPUT=${1:-/dev/stdin}
OUTPUT=${2:-/dev/stdout}

if [ "$INPUT" = "-" ]; then
  INPUT=/dev/stdin
fi

if [ "$OUTPUT" = "-" ]; then
  OUTPUT=/dev/stdout
fi

if [ ! -r "$INPUT" ]; then
  echo "Usage: $(basename $0) [js api file] [output c header file]"
  exit 1
fi

exec > $OUTPUT

echo "static const char *kSource_common_api = "
tr -d '\r' < "$INPUT" | sed 's:["\\]:\\&:g;s:.*:    "&\\n":'
echo ";"
