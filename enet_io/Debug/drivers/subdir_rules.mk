################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
drivers/pinout.obj: D:/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c1294xl/drivers/pinout.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --include_path="C:/Users/mfathy/workspace_v9_2/enet_io" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c1294xl" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178/third_party/lwip-1.4.1/src/include" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178/third_party/lwip-1.4.1/src/include/ipv4" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178/third_party/lwip-1.4.1/apps" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178/third_party/lwip-1.4.1/ports/tiva-tm4c129/include" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178/third_party" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=TARGET_IS_TM4C129_RA0 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


