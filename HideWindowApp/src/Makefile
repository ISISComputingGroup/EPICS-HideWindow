TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#==================================================
# build a support library

PROD_HOST += HideWindow SetQuickEditMode RunWithGlobalLock RunHidden
PROD_HOST += SetWindowCloseButton CheckFileAccess

# specify all source files to be compiled and added to the library
HideWindow_SRCS += hidewindow.cc
SetQuickEditMode_SRCS += SetQuickEditMode.cc
RunWithGlobalLock_SRCS += RunWithGlobalLock.cc
SetWindowCloseButton_SRCS += SetWindowCloseButton.cc
RunHidden_SRCS += runhidden.cc
CheckFileAccess_SRCS += CheckFileAccess.cc

HideWindow_LIBS += $(EPICS_BASE_HOST_LIBS)
HideWindow_SYS_LIBS_WIN32 += kernel32 user32

SetQuickEditMode_LIBS += $(EPICS_BASE_HOST_LIBS)
SetQuickEditMode_SYS_LIBS_WIN32 += kernel32 user32

RunWithGlobalLock_LIBS += $(EPICS_BASE_HOST_LIBS)
RunWithGlobalLock_SYS_LIBS_WIN32 += kernel32 user32

RunHidden_LDFLAGS_WIN32 += -subsystem:windows
RunHidden_SYS_LIBS_WIN32 += kernel32 user32

SetWindowCloseButton_LIBS += $(EPICS_BASE_HOST_LIBS)
SetWindowCloseButton_SYS_LIBS_WIN32 += kernel32 user32

CheckFileAccess_LIBS += $(EPICS_BASE_HOST_LIBS)
CheckFileAccess_SYS_LIBS_WIN32 += kernel32 user32

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

