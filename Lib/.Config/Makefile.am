
##
##    ライブラリのビルドとインストール。
##

##
##    List of Directories.
##

SRCTOPDIR       =  @top_srcdir@
INCTOPDIR       =  $(SRCTOPDIR)/Include/FairyShogi
INCLIBDIR       =  $(INCTOPDIR)/.Config

CNF_SRCTOPDIR   =  @top_builddir@
CNF_INCTOPDIR   =  $(CNF_SRCTOPDIR)/Include/FairyShogi
CNF_INCLIBDIR   =  $(CNF_INCLIBDIR)/.Config

##
##    List of Source and Header Files.
##

NOINSTHEADERS        =

INCLIBHEADERS        =

NODISTHEADERS        =  \
        $(INCLIBDIR)/ConfiguredFairyShogi.h

##
##    Compile and Link Options.
##

##
##    List of Installs.
##

fairyshogi_includedir              =  $(includedir)/FairyShogi
fairyshogi_include_HEADERS         =  $(INCLIBHEADERS)

dist_noinst_HEADERS                =  $(NOINSTHEADERS)
nodist_fairyshogi_include_HEADERS  =  $(NODISTHEADERS)

fairyshogi_libdir                  =  $(libdir)
fairyshogi_config_libdir           =  $(dshogi_libdir)/.Config
fairyshogi_config_lib_LTLIBRARIES  =
fairyshogi_config_lib_LIBRARIES    =

