TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#==================================================
# build a support library

PROD_HOST += HideWindow

# xxxRecord.h will be created from xxxRecord.dbd
#DBDINC += xxxRecord
# install HideWindow.dbd into <top>/dbd
#DBD += HideWindow.dbd

# specify all source files to be compiled and added to the library
HideWindow_SRCS += hidewindow.cc

HideWindow_LIBS += $(EPICS_BASE_HOST_LIBS)
HideWindow_SYS_LIBS_WIN32 += kernel32 user32

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

