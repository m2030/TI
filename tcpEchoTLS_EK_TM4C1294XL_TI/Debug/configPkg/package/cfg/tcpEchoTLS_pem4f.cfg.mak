# invoke SourceDir generated makefile for tcpEchoTLS.pem4f
tcpEchoTLS.pem4f: .libraries,tcpEchoTLS.pem4f
.libraries,tcpEchoTLS.pem4f: package/cfg/tcpEchoTLS_pem4f.xdl
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\tcpEchoTLS_EK_TM4C1294XL_TI/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\tcpEchoTLS_EK_TM4C1294XL_TI/src/makefile.libs clean

