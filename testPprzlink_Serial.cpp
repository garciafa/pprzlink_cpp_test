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
#include <pprzlink/BoostSerialPortDevice.h>
#include <pprzlink/PprzTransport.h>
#include <pprzlink/IvyLink.h>

pprzlink::Transport *pprzTransport;


void ivyMessageCallback(std::string ac_id, pprzlink::Message msg)
{
  msg.setSenderId(0);
  size_t fieldIndex=0;
  bool foundAcId=false;
  do {
    if (msg.getDefinition().getField(fieldIndex).getName()=="ac_id")
    {
      foundAcId=true;
    }
    else
    {
      ++fieldIndex;
    }
  } while(fieldIndex < msg.getDefinition().getNbFields() && !foundAcId);
  if (foundAcId)
  {
    if (msg.getDefinition().getField(fieldIndex).getType().getBaseType() == pprzlink::BaseType::UINT8)
    {
      uint8_t dest_id;
      msg.getField(fieldIndex, dest_id);
      msg.setReceiverId(dest_id);
    }
    else
    {
      // ac_id is a string
      std::string dest_id_str;
      msg.getField(fieldIndex, dest_id_str);
      std::stringstream sstr(dest_id_str);
      uint8_t dest_id;
      sstr >> dest_id;
      msg.setReceiverId(dest_id);
    }
    msg.setComponentId(0);

    pprzTransport->sendMessage(msg);
  }
}

int main(int argc, char **argv)
{
  try
  {
    pprzlink::MessageDictionary dict("/home/garciafa/paparazzi/var/messages.xml");
    boost::asio::io_service ioService;

    auto *dev  = new pprzlink::BoostSerialPortDevice(ioService,"/dev/ttyUSB0");
    dev->setBaudrate(pprzlink::BoostSerialPortDevice::Baudrate(57600));

    pprzTransport = new pprzlink::PprzTransport(dev, dict);

    pprzlink::IvyLink ivy(dict,"C++Link","127.255.255.255:2010",true);

    // Start reception on the serial line
    dev->startReception();

    // Bind to ivy messages that need to be forwarded
    ivy.BindMessage(dict.getDefinition("MISSION_CIRCLE"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("REMOTE_GPS_SMALL"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("END_MISSION"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("TCAS_RESOLVE"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("WINDTURBINE_STATUS"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("ACINFO"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("MISSION_CUSTOM"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("RC_5CH"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("MISSION_CIRCLE_LLA"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("MISSION_SEGMENT_LLA"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("GUIDED_SETPOINT_NED"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("RC_4CH"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("SETTING"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("BLOCK"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("REMOTE_GPS"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("PAYLOAD_COMMAND"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("KEY_EXCHANGE_GCS"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("WIND_INFO"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("GOTO_MISSION"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("GET_SETTING"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("MISSION_SEGMENT"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("BOOZ_NAV_STICK"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("ACINFO_LLA"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("MISSION_GOTO_WP_LLA"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("COPILOT_STATUS_DL"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("HITL_UBX"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("VIDEO_ROI"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("DESIRED_SETPOINT"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("EMERGENCY_CMD"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("MISSION_PATH_LLA"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("BOOZ2_FMS_COMMAND"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("EXTERNAL_MAG_RAW"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("SET_ACTUATOR"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("EXTERNAL_FILTER_SOLUTION"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("RTCM_INJECT"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("FORMATION_STATUS"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("MISSION_PATH"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("REMOTE_GPS_LOCAL"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("DCF_REG_TABLE"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("JOYSTICK_RAW"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("FORMATION_SLOT"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("NEXT_MISSION"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("COMMANDS_RAW"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("GPS_INJECT"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("DGPS_RAW"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("HITL_INFRARED"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("CAMERA_PAYLOAD_DL"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("ROTORCRAFT_CAM_STICK"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("CAMERA_SNAPSHOT_DL"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("RC_3CH"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("MOVE_WP"), ivyMessageCallback);
    ivy.BindMessage(dict.getDefinition("MISSION_GOTO_WP"), ivyMessageCallback);

    while (1)
    {
      ioService.run_for(std::chrono::milliseconds(10));

      if (pprzTransport->hasMessage())
      {
        std::unique_ptr<pprzlink::Message> msg = pprzTransport->getMessage();
        if (msg)
        {
          // Send all messages to IVY bus
          ivy.sendMessage(*msg);

          // If the message is an ALIVE message add the aircraft to the list of known aircraft
          if (msg->getDefinition().getName()=="ALIVE")
          {

          }
        }
      }
    }

    // Wait for messages incoming messages
    
    // send outgoing messages
  }
  catch (pprzlink::pprzlink_exception &e)
  {
    std::cerr << "Error : " << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
