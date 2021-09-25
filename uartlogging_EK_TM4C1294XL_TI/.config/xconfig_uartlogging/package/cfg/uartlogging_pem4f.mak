#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.arm.elf.M4F{1,0,16.9,4
#
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/uartlogging_pem4f.oem4f.dep
package/cfg/uartlogging_pem4f.oem4f.dep: ;
endif

package/cfg/uartlogging_pem4f.oem4f: | .interfaces
package/cfg/uartlogging_pem4f.oem4f: package/cfg/uartlogging_pem4f.c package/cfg/uartlogging_pem4f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4f $< ...
	$(ti.targets.arm.elf.M4F.rootDir)/bin/armcl -c  -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/mfathy/workspace_v9_2/uartlogging_EK_TM4C1294XL_TI" --include_path="C:/Users/mfathy/workspace_v9_2/uartlogging_EK_TM4C1294XL_TI" --include_path="C:/ti/tirtos_tivac_2_14_04_31/products/TivaWare_C_Series-2.1.1.71b" --include_path="C:/ti/tirtos_tivac_2_14_04_31/packages/ti/drivers/wifi/cc3100/Simplelink" --include_path="C:/ti/tirtos_tivac_2_14_04_31/packages/ti/drivers/wifi/cc3100/Simplelink/Include" --include_path="C:/ti/ti-cgt-arm_16.9.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi   -qq -pdsw225 -ms --fp_mode=strict --endian=little -mv7M4 --abi=eabi --float_support=fpv4spd16 -eo.oem4f -ea.sem4f   -Dxdc_cfg__xheader__='"xconfig_uartlogging/package/cfg/uartlogging_pem4f.h"'  -Dxdc_target_name__=M4F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_16_9_4 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M4F.rootDir)/include/rts -I$(ti.targets.arm.elf.M4F.rootDir)/include  -fs=./package/cfg -fr=./package/cfg -fc $<
	$(MKDEP) -a $@.dep -p package/cfg -s oem4f $< -C   -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/mfathy/workspace_v9_2/uartlogging_EK_TM4C1294XL_TI" --include_path="C:/Users/mfathy/workspace_v9_2/uartlogging_EK_TM4C1294XL_TI" --include_path="C:/ti/tirtos_tivac_2_14_04_31/products/TivaWare_C_Series-2.1.1.71b" --include_path="C:/ti/tirtos_tivac_2_14_04_31/packages/ti/drivers/wifi/cc3100/Simplelink" --include_path="C:/ti/tirtos_tivac_2_14_04_31/packages/ti/drivers/wifi/cc3100/Simplelink/Include" --include_path="C:/ti/ti-cgt-arm_16.9.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi   -qq -pdsw225 -ms --fp_mode=strict --endian=little -mv7M4 --abi=eabi --float_support=fpv4spd16 -eo.oem4f -ea.sem4f   -Dxdc_cfg__xheader__='"xconfig_uartlogging/package/cfg/uartlogging_pem4f.h"'  -Dxdc_target_name__=M4F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_16_9_4 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M4F.rootDir)/include/rts -I$(ti.targets.arm.elf.M4F.rootDir)/include  -fs=./package/cfg -fr=./package/cfg
	-@$(FIXDEP) $@.dep $@.dep
	
package/cfg/uartlogging_pem4f.oem4f: export C_DIR=
package/cfg/uartlogging_pem4f.oem4f: PATH:=$(ti.targets.arm.elf.M4F.rootDir)/bin/;$(PATH)
package/cfg/uartlogging_pem4f.oem4f: Path:=$(ti.targets.arm.elf.M4F.rootDir)/bin/;$(PATH)

package/cfg/uartlogging_pem4f.sem4f: | .interfaces
package/cfg/uartlogging_pem4f.sem4f: package/cfg/uartlogging_pem4f.c package/cfg/uartlogging_pem4f.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4f -n $< ...
	$(ti.targets.arm.elf.M4F.rootDir)/bin/armcl -c -n -s --symdebug:none -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/mfathy/workspace_v9_2/uartlogging_EK_TM4C1294XL_TI" --include_path="C:/Users/mfathy/workspace_v9_2/uartlogging_EK_TM4C1294XL_TI" --include_path="C:/ti/tirtos_tivac_2_14_04_31/products/TivaWare_C_Series-2.1.1.71b" --include_path="C:/ti/tirtos_tivac_2_14_04_31/packages/ti/drivers/wifi/cc3100/Simplelink" --include_path="C:/ti/tirtos_tivac_2_14_04_31/packages/ti/drivers/wifi/cc3100/Simplelink/Include" --include_path="C:/ti/ti-cgt-arm_16.9.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi   -qq -pdsw225 --endian=little -mv7M4 --abi=eabi --float_support=fpv4spd16 -eo.oem4f -ea.sem4f   -Dxdc_cfg__xheader__='"xconfig_uartlogging/package/cfg/uartlogging_pem4f.h"'  -Dxdc_target_name__=M4F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_16_9_4 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M4F.rootDir)/include/rts -I$(ti.targets.arm.elf.M4F.rootDir)/include  -fs=./package/cfg -fr=./package/cfg -fc $<
	$(MKDEP) -a $@.dep -p package/cfg -s oem4f $< -C  -n -s --symdebug:none -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/mfathy/workspace_v9_2/uartlogging_EK_TM4C1294XL_TI" --include_path="C:/Users/mfathy/workspace_v9_2/uartlogging_EK_TM4C1294XL_TI" --include_path="C:/ti/tirtos_tivac_2_14_04_31/products/TivaWare_C_Series-2.1.1.71b" --include_path="C:/ti/tirtos_tivac_2_14_04_31/packages/ti/drivers/wifi/cc3100/Simplelink" --include_path="C:/ti/tirtos_tivac_2_14_04_31/packages/ti/drivers/wifi/cc3100/Simplelink/Include" --include_path="C:/ti/ti-cgt-arm_16.9.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi   -qq -pdsw225 --endian=little -mv7M4 --abi=eabi --float_support=fpv4spd16 -eo.oem4f -ea.sem4f   -Dxdc_cfg__xheader__='"xconfig_uartlogging/package/cfg/uartlogging_pem4f.h"'  -Dxdc_target_name__=M4F -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_16_9_4 -O2  $(XDCINCS) -I$(ti.targets.arm.elf.M4F.rootDir)/include/rts -I$(ti.targets.arm.elf.M4F.rootDir)/include  -fs=./package/cfg -fr=./package/cfg
	-@$(FIXDEP) $@.dep $@.dep
	
package/cfg/uartlogging_pem4f.sem4f: export C_DIR=
package/cfg/uartlogging_pem4f.sem4f: PATH:=$(ti.targets.arm.elf.M4F.rootDir)/bin/;$(PATH)
package/cfg/uartlogging_pem4f.sem4f: Path:=$(ti.targets.arm.elf.M4F.rootDir)/bin/;$(PATH)

clean,em4f ::
	-$(RM) package/cfg/uartlogging_pem4f.oem4f
	-$(RM) package/cfg/uartlogging_pem4f.sem4f

uartlogging.pem4f: package/cfg/uartlogging_pem4f.oem4f package/cfg/uartlogging_pem4f.mak

clean::
	-$(RM) package/cfg/uartlogging_pem4f.mak
