#! /bin/bash -x

mkdir  -p  .Config  \
  &&  aclocal  -I  .Config  \
  &&  autoheader  \
  &&  automake  --add-missing  --copy  --foreign  \
  &&  autoconf

