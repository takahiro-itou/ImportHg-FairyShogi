#! /bin/bash  -x

##
##  コマンド。
##

LN_H='ln -f '
LN_S='ln -sf '
RM_F='rm -f '

##
##  シンボリックリンクの確認
##

${RM_F}  .Config/TestConf.txt
touch    .Config/TestConf.txt
${LN_S}  .Config/TestConf.txt  .Config/TestLink
if [ -L  .Config/TestLink ] ; then
    echo  'Symbolic Link Enabled.'
else
    echo  'Cannot Create Symbolic Link. Use Hard Link...'
    LN_S=${LN_H}
fi
${RM_F}  .Config/TestConf.txt  .Config/TestLink

##
##  定数宣言。
##

testcommondir='.TestsCommon'

##
##
##

if [ ! -d  Lib/${testcommondir}/Tests ] ; then
    mkdir  -p  Lib/${testcommondir}/Tests
fi

if [ -d  Lib/${testcommondir}/Tests ] ; then
    (cd  Lib/${testcommondir}/Tests  \
      &&  ${RM_F}  Makefile.am  \
      &&  ${LN_S}  ../../Tests/.TestsCommon/Makefile.am)
fi

for  dir  in  Common  Game  Interface  ; do
    if [ -d Lib/${dir}/Tests ] ; then
        (cd  Lib/${dir}/Tests  \
          &&  ${RM_F}  Makefile.am  \
          &&  ${LN_H}  ../../${testcommondir}/Tests/Makefile.am)
    fi
done

