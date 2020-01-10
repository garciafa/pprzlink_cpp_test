# Hey Emacs, this is a -*- makefile -*-
#
# Copyright (C) 2019 Fabien Garcia <fabien.garcia@enac.fr>
#
# This file is part of paparazzi.
#
# paparazzi is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# paparazzi is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with paparazzi; see the file COPYING.  If not, see
# <http://www.gnu.org/licenses/>.
#

Q?=@

MAKE = make

PPRZLINK_DIR?=../pprzlink

BASE_DIR=$(PWD)/C++
LIB_DIR=$(BASE_DIR)/lib
INCLUDE_DIR=$(BASE_DIR)/include

SRC_IVY=testPprzlink_Ivy.cpp
OBJ_IVY=$(patsubst %.cpp,%.o,$(SRC_IVY))

SRC_SERIAL=testPprzlink_Serial.cpp
OBJ_SERIAL=$(patsubst %.cpp,%.o,$(SRC_SERIAL))

INCLUDE_FLAG=-I$(INCLUDE_DIR)
CXXFLAGS= --std=c++17 -Wall -fPIC -flto $(INCLUDE_FLAG)
LDFLAGS= -L$(LIB_DIR) -lpprzlink++ -livy -lpthread -ltinyxml2

all: installcpp testPprzlink_Ivy testPprzlink_Serial QtMessages

installcpp:
	$(Q)DESTDIR=$(PWD) make -C $(PPRZLINK_DIR) libpprzlink++-install

QtMessages: $(OBJ_MESSAGES)
	$(Q)qmake QtMessagesSrc/QtMessages.pro -o QtMessagesSrc/Makefile
	$(Q)${MAKE} -C QtMessagesSrc

testPprzlink_Ivy: $(OBJ_IVY)
	$(Q)$(CXX) -Wl,-rpath,$(LIB_DIR) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

testPprzlink_Serial: $(OBJ_SERIAL)
	$(Q)$(CXX) -Wl,-rpath,$(LIB_DIR) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	$(Q)rm -f *.o testPprzlink_Ivy testPprzlink_Serial QtMessages *~

.PHONY: clean installcpp all
