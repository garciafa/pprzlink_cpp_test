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
#include <pprzlink/IvyLink.h>

void printMsgInfo(pprzlink::MessageDictionary dict, std::string const & name)
{
  auto def = dict.getDefinition(name);
  std::string className = dict.getClassName(def.getClassId());
  std::cout << "Found definition of message " << def.getName() << "("<< def.getId() << ") in class " << className << "(" <<def.getClassId() << ")" << std::endl;
  for (int i=0;i<def.getNbFields();++i)
  {
    std::cout << "\t" << def.getField(i).getName() << " : " << def.getField(i).getType().toString() << std::endl;
  }
}

void ivyMessageCallback(std::string ac_id, pprzlink::Message msg)
{
  std::cout << ac_id << " sent " << msg.toString() << std::endl;
}

void verboseBind(pprzlink::IvyLink &link, const pprzlink::MessageDictionary &dict, std::string msgName)
{
  std::cout << "Binding to " << msgName << "\n";
  link.BindMessage(dict.getDefinition(msgName), ivyMessageCallback);
}

int main(int argc, char **argv)
{
  try
  {
    pprzlink::MessageDictionary dict("/home/garciafa/paparazzi/var/messages.xml");
    pprzlink::IvyLink link(dict, "TestPprzLinkIvy", "127.255.255.255:2010", true);

    link.BindMessage(dict.getDefinition("KEY_EXCHANGE_GCS"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("SHAPE"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("INTRUDER"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("DC_SHOT"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("TCAS_RA"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("AUTOPILOT_VERSION"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("INFO_MSG"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("TELEMETRY_ERROR"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("BAT_LOW"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("SVSINFO"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("WAYPOINT_MOVED"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("INFLIGH_CALIB"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("TELEMETRY_STATUS"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("INFLIGH_CALIB"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("ENGINE_STATUS"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("FLY_BY_WIRE"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("WIND"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("DL_VALUES"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("AP_STATUS"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("SURVEY_STATUS"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("SEGMENT_STATUS"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("CIRCLE_STATUS"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("CAM_STATUS"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("FLIGHT_PARAM"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("NEW_AIRCRAFT"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("CONFIG"), ivyMessageCallback);

    link.BindMessage(dict.getDefinition("ALIVE"), ivyMessageCallback);
    link.BindMessage(dict.getDefinition("GPS_INT"), ivyMessageCallback);

    sleep(1);
    pprzlink::Message msg(dict.getDefinition("INFO_MSG"));
    msg.addField("msg",std::string("Coucou la bas"));

    msg.setSenderId("ground");
    link.sendMessage(msg);
/*
    sleep(1);

    msg=pprzlink::Message(dict.getDefinition("ALIVE"));
    std::vector<uint8_t> md5sum={4,225,49,200,16,162,240,125,202,199,63,182,169,192,163,35};
    msg.addField("md5sum",md5sum);
    link.sendMessage(("201"),msg);
*/
    sleep(100);
  }
  catch (pprzlink::pprzlink_exception &e)
  {
    std::cerr << "Error : " << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
