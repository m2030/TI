#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/simplelink_cc32xx_sdk_3_30_01_02/source;C:/ti/simplelink_cc32xx_sdk_3_30_01_02/kernel/tirtos/packages
override XDCROOT = C:/ti/ccs920/xdctools_3_60_01_27_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/simplelink_cc32xx_sdk_3_30_01_02/source;C:/ti/simplelink_cc32xx_sdk_3_30_01_02/kernel/tirtos/packages;C:/ti/ccs920/xdctools_3_60_01_27_core/packages;..
HOSTOS = Windows
endif
