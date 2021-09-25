# invoke SourceDir generated makefile for hello.pem4f
hello.pem4f: .libraries,hello.pem4f
.libraries,hello.pem4f: package/cfg/hello_pem4f.xdl
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\hello_EK_TM4C1294XL_TI/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\hello_EK_TM4C1294XL_TI/src/makefile.libs clean

