################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
examples/%.obj: ../examples/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/wolfssl-master" --include_path="C:/Users/mfathy/workspace_v9_2/tcpEchoTLS_EK_TM4C1294XL_TI" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/ndk_2_24_03_35/packages/ti/ndk/inc/bsd" --include_path="C:/Users/mfathy/workspace_v9_2/tcpEchoTLS_EK_TM4C1294XL_TI" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="C:/ti/tirtos_tivac_2_16_00_08/packages/ti/drivers/wifi/cc3100/Simplelink" --include_path="C:/ti/tirtos_tivac_2_16_00_08/packages/ti/drivers/wifi/cc3100/Simplelink/Include" --include_path="D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --define=ENABLE_MQTT_TLS --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=WOLFSSL_TIRTOS --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="examples/$(basename $(<F)).d_raw" --obj_directory="examples" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


