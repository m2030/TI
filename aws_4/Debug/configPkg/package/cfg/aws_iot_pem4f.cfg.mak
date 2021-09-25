# invoke SourceDir generated makefile for aws_iot.pem4f
aws_iot.pem4f: .libraries,aws_iot.pem4f
.libraries,aws_iot.pem4f: package/cfg/aws_iot_pem4f.xdl
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\aws_4/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\mfathy\workspace_v9_2\aws_4/src/makefile.libs clean

