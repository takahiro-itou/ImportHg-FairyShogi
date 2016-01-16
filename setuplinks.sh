#! /bin/bash  -x

##
##  コマンド。
##

LN_H='ln -f '
LN_S='ln -sf '
RM_F='rm -f '

##
##  定数宣言。
##

testcommondir='.TestsCommon'

##
##
##

if [ ! -d  Lib/${testcommondir}/Tests ] ; then
    mkdir  -p  Lib/${testcommondir}/Tests
    (cd  Lib/${testcommondir}/Tests  \
      &&  ${LN_S}  ../../Tests/.TestsCommon/Makefile.am)
fi

for  dir  in  Common  Game  Interface  ; do
    if [ -d Lib/${dir}/Tests ] ; then
        (cd  Lib/${dir}/Tests  \
          &&  ${RM_F}  Makefile.am  \
          &&  ${LN_H}  ../../${testcommondir}/Tests/Makefile.am)
    fi
done

