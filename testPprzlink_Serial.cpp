/*
 * Copyright 2019 garciafa
 * This file is part of PprzLinkCPP
 *
 * PprzLinkCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PprzLinkCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ModemTester.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/** \file testPprzlink.cpp
 *
 *
 */

/*
 * Copyright 2019 garciafa
 * This file is part of PprzLinkCPP
 *
 * PprzLinkCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PprzLinkCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ModemTester.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/** \file test.cpp
 *
 *
 */

#include <cstdlib>
#include <iostream>
#include <pprzlink/MessageDictionary.h>
#include <pprzlink/Message.h>
#include <pprzlink/Device.h>
#include <pprzlink/Transport.h>

void printMsgInfo(pprzlink::MessageDictionary dict, std::string const & name)
{
  auto def = dict.getDefinition(name);
  std::string className = dict.getClassName(def.getClassId());
  std::cout << "Found definition of message " << def.getName() << "(" << def.getId() << ") in class " << className << "(" << def.getClassId() << ")" << std::endl;
  for (int i=0;i<def.getNbFields();++i)
  {
    std::cout << "\t" << def.getField(i).getName() << " : " << def.getField(i).getType().toString() << std::endl;
  }
}

void messageCb(std::string ac_id, pprzlink::Message msg)
{
  std::cout << ac_id << " sent " << msg.toString() << std::endl;
}

int main(int argc, char **argv)
{
  try
  {
    pprzlink::MessageDictionary dict("/home/garciafa/paparazzi/var/messages.xml");

    // TODO Create a serial line link with transparent transport
    pprzlink::Device dev;
    pprzlink::Transport<pprzlink::Device> *t;

    // Wait for messages incoming messages
    
    // send outgoing messages
  }
  catch (pprzlink::pprzlink_exception &e)
  {
    std::cerr << "Error : " << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
