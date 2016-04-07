@echo off
::取消文件所有属性
attrib -r -a -s -h *.* /s /d
::执行批量删除操作
@for /r %%i in (
*.aps *.idb *.ncb *.obj *.pch *.sbr *.tmp *.pdb *.bsc *.ilk *.res *.tlog unsuccessfulbuild *.DLL.bi *.cache
*.sdf *.dep *.ipch *.tlog *.exp *.hpj *.opt *.mdp *.plg *.clw *.log *.lastbuildstate *.user *.metagen
) do (
del /f /q "%%i")

::删除空目录
for /f "tokens=*" %%i in ('dir/s/b/ad^|sort /r') do rd "%%i"


@echo 清理完成！



