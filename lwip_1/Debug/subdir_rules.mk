################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/mfathy/workspace_v9_2/lwip_1" --include_path="C:/Users/mfathy/workspace_v9_2/lwip_1/Third Party/LWIP/src/include" --include_path="C:/Users/mfathy/workspace_v9_2/lwip_1/Third Party/LWIP/src/include/lwip" --include_path="C:/Users/mfathy/workspace_v9_2/lwip_1/Third Party/LWIP/src/include/lwip/ipv4" --include_path="C:/Users/mfathy/workspace_v9_2/lwip_1/Third Party/LWIP/src/include/ipv4/lwip" --include_path="C:/Users/mfathy/workspace_v9_2/lwip_1/Third Party/LWIP/system" --include_path="C:/Users/mfathy/workspace_v9_2/lwip_1/Third Party/LWIP/system/arch" --include_path="C:/Users/mfathy/workspace_v9_2/lwip_1/Third Party/LWIP/src/include/netif" --include_path="C:/Users/mfathy/workspace_v9_2/lwip_1/Third Party/LWIP/src/include/posix" --include_path="C:/Users/mfathy/workspace_v9_2/lwip_1/Third Party/LWIP/src/include/posix/sys" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" --define=ccs="ccs" --define=__packed=__attribute__((__packed__)) --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


