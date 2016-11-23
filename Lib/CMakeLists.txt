
##----------------------------------------------------------------
##
##    Package Configurations.
##    パッケージ設定。
##

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

Add_SubDirectory (Tests)
Add_SubDirectory (.Config)

Add_SubDirectory (Common)
Add_SubDirectory (Game)
Add_SubDirectory (Engine)
Add_SubDirectory (Interface)

If ( ENABLE_WIN32 )
  Add_SubDirectory (Win32)
EndIf()

