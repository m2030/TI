# invoke SourceDir generated makefile for uartecho.pem4f
uartecho.pem4f: .libraries,uartecho.pem4f
.libraries,uartecho.pem4f: package/cfg/uartecho_pem4f.xdl
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\uartecho_EK_TM4C1294XL_TI/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\uartecho_EK_TM4C1294XL_TI/src/makefile.libs clean

