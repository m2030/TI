# invoke SourceDir generated makefile for httpget.pem4f
httpget.pem4f: .libraries,httpget.pem4f
.libraries,httpget.pem4f: package/cfg/httpget_pem4f.xdl
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\httpget_EK_TM4C1294XL_TI/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\httpget_EK_TM4C1294XL_TI/src/makefile.libs clean

