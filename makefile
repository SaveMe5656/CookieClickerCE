# ----------------------------
# Makefile Options
# ----------------------------

NAME = Cookie
ICON = icon.png
DESCRIPTION = "Cookie Clicker - vAlpha 0.1"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
