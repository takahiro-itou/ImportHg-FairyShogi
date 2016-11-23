
##----------------------------------------------------------------
##
##    モジュールの設定。
##

Set (MODULE_DIR_NAME       "Common")
Set (MODULE_OUTPUT_NAME    "Common")
Set (MODULE_TITLE          "Common")

Set (INCLIB_SOURCE_DIR     "${INCLUDE_SOURCE_DIR}/${MODULE_DIR_NAME}")
Set (INCLIB_BINARY_DIR     "${INCLUDE_BINARY_DIR}/${MODULE_DIR_NAME}")

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

Set (LIBRARY_SOURCE_FILES
)

Set (INCLIB_HEADER_FILES
        ${INCLIB_SOURCE_DIR}/ActionView.h
        ${INCLIB_SOURCE_DIR}/DefaultShogiPieces.h
        ${INCLIB_SOURCE_DIR}/FairyShogiConst.h
        ${INCLIB_SOURCE_DIR}/FairyShogiSettings.h
        ${INCLIB_SOURCE_DIR}/FairyShogiTypes.h
        ${INCLIB_SOURCE_DIR}/HelperMacros.h
        ${INCLIB_SOURCE_DIR}/MersenneTwister.h
        ${INCLIB_SOURCE_DIR}/ViewBuffer.h
)

Set (MODULE_NEEDS_LIBRARIES
)

##----------------------------------------------------------------
##
##    ビルドとインストールの設定。
##

Include (${COMMON_CMAKE_DIR}/BuildLibraryCommon.cmake)

##----------------------------------------------------------------
##
##    テストの設定。
##

Add_SubDirectory (Tests)

