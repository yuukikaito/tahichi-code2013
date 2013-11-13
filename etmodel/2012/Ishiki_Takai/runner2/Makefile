# Target specific macros
TARGET = Runner2

NXTOSEK_ROOT = ../../..

# nxtway_gs_balancer library desiged for NXTway-GS two wheeled self-balancing robot
USER_INC_PATH= $(NXTOSEK_ROOT)/ecrobot/nxtway_gs_balancer
USER_LIB = nxtway_gs_balancer

# using NXT standard tires (not Motorcycle tires)
#USER_DEF = NXT_STD_TIRE

# User application source
TARGET_SOURCES := \
	com/balancer_param.c \
	controller/Runner.c \
	controller/Monitor.c \
	controller/RunActions.c \
	controller/CalibrateActions.c \
	unit/BumperUnit.c \
	unit/LineMonitorUnit.c \
	unit/DisplayUnit.c \
	unit/HornUnit.c \
	unit/TimerUnit.c \
	unit/CommunicationUnit.c \
	unit/BalancerUnit.c \
	unit/BlockMonitorUnit.c \
	controller/initDevice.c

# OSEK OIL file
TOPPERS_OSEK_OIL_SOURCE := ./prog.oil

# below part should not be modified
O_PATH ?= build
include $(NXTOSEK_ROOT)/ecrobot/ecrobot.mak
