################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
lwip-1.4.1/apps/httpserver_raw/fs.obj: D:/ti/Hercules/HALCoGen\ EMAC\ Driver\ with\ lwIP\ Demonstration/v00.03.00/lwip-1.4.1/apps/httpserver_raw/fs.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/ports/hdk/check" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/ports/hdk/include/netif" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/ports/hdk/include" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/ports/hdk/netif" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/ports/hdk" --include_path="D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/apps/httpserver_raw" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/src/include/ipv4" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/TMS570LC43x/HALCoGen-TMS570LC43x/include" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/example/hdk/inc" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/src/include" -g --define=_TMS570LC43x_ --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="lwip-1.4.1/apps/httpserver_raw/$(basename $(<F)).d_raw" --obj_directory="lwip-1.4.1/apps/httpserver_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

lwip-1.4.1/apps/httpserver_raw/httpd.obj: D:/ti/Hercules/HALCoGen\ EMAC\ Driver\ with\ lwIP\ Demonstration/v00.03.00/lwip-1.4.1/apps/httpserver_raw/httpd.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/ports/hdk/check" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/ports/hdk/include/netif" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/ports/hdk/include" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/ports/hdk/netif" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/ports/hdk" --include_path="D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/apps/httpserver_raw" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/src/include/ipv4" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/TMS570LC43x/HALCoGen-TMS570LC43x/include" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/example/hdk/inc" --include_path="D:/ti/Hercules/HALCoGen EMAC Driver with lwIP Demonstration/v00.03.00/lwip-1.4.1/src/include" -g --define=_TMS570LC43x_ --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="lwip-1.4.1/apps/httpserver_raw/$(basename $(<F)).d_raw" --obj_directory="lwip-1.4.1/apps/httpserver_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


