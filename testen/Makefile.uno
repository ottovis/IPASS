#############################################################################
#
# makefile.due common settings for Arduino Uno projects
#
# (c) Wouter van Ooijen (www.voti.nl) 2017
#
# This file is in the public domain.
# 
#############################################################################

# settings for Arduino Due projects
TARGET            := arduino_uno
SERIAL_PORT       ?= COM4
CONSOLE_BAUDRATE  := 2400

# defer to the Makefile.shared
include           $(RELATIVE)/Makefile.link
