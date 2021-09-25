# invoke SourceDir generated makefile for uartlogging.pem4f
uartlogging.pem4f: .libraries,uartlogging.pem4f
.libraries,uartlogging.pem4f: package/cfg/uartlogging_pem4f.xdl
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\uartlogging_EK_TM4C1294XL_TI/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\uartlogging_EK_TM4C1294XL_TI/src/makefile.libs clean

