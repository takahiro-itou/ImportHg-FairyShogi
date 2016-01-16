#! /bin/bash -x

mkdir  -p  .Config  \
  &&  aclocal  -I  .Config  \
  &&  autoheader  \
  &&  automake  --add-missing  --copy  --foreign  \
  &&  autoconf

(cd  .Config  \
  &&  chmod  u+rx  compile  depcomp  install-sh  missing
)

