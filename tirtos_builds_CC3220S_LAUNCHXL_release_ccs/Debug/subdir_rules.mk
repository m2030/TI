################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-571276543:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-571276543-inproc

build-571276543-inproc: ../release.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"D:/ti/ccs920/xdctools_3_60_01_27_core/xs" --xdcpath= xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4 -p ti.platforms.simplelink:CC3220S -r release -c "D:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-571276543 ../release.cfg
configPkg/compiler.opt: build-571276543
configPkg/: build-571276543


