#! /bin/bash -x

mkdir  -p  .Config  \
  &&  aclocal  -I  .Config  \
  &&  automake  --add-missing  --copy  --foreign  \
  &&  autoconf

