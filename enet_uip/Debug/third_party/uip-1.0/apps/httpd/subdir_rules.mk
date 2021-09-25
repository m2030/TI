################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
third_party/uip-1.0/apps/httpd/httpd.obj: C:/ti/TivaWare_C_Series-2.1.4.178/third_party/uip-1.0/apps/httpd/httpd.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --include_path="C:/Users/mfathy/workspace_v9_2/enet_uip" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c1294xl" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/third_party/uip-1.0" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/third_party/uip-1.0/uip" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/third_party/uip-1.0/apps" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/utils" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=TARGET_IS_TM4C129_RA0 --define=DEBUG_OUTPUT --define=UIP_OFFLOAD_ICMP_CHKSUM --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="third_party/uip-1.0/apps/httpd/$(basename $(<F)).d_raw" --obj_directory="third_party/uip-1.0/apps/httpd" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


