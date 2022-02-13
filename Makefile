CCFLAGS=/nologo /W4 /ZI
CCLINK=Gdi32.lib User32.lib
EXENAME=pong-win32


all:
	IF NOT EXIST obj MKDIR obj
	IF NOT EXIST bin MKDIR bin
	cl $(CCFLAGS) src\*.cpp /Fo.\obj\ $(CCLINK) /Fe$(EXENAME).exe
	IF EXIST *.exe MOVE *.exe bin
	IF EXIST *.idb MOVE *.idb bin
	IF EXIST *.ilk MOVE *.ilk bin
	IF EXIST *.pdb MOVE *.pdb bin

