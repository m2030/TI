# invoke SourceDir generated makefile for mutex.pem4f
mutex.pem4f: .libraries,mutex.pem4f
.libraries,mutex.pem4f: package/cfg/mutex_pem4f.xdl
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\mutex_EK_TM4C1294XL_TI/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\mutex_EK_TM4C1294XL_TI/src/makefile.libs clean

