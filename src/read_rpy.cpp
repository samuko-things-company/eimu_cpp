#include <sstream>
#include <iostream>
#include <unistd.h>

#include <chrono>

#include <iomanip>

#include "eimu.hpp"

EIMU imu;

void delay_ms(unsigned long milliseconds)
{
  usleep(milliseconds * 1000);
}

int main(int argc, char **argv)
{

  float roll, pitch, yaw;

  auto prevTime = std::chrono::system_clock::now();
  std::chrono::duration<double> duration;
  float sampleTime = 0.02;

  // std::string port = "/dev/serial/by-path/pci-0000:00:14.0-usb-0:1.4:1.0-port0";
  std::string port = "/dev/ttyUSB0";
  imu.connect(port);

  // wait for the imu to fully setup
  for (int i = 1; i <= 6; i += 1)
  {
    delay_ms(1000);
    std::cout << "configuring controller: " << i << " sec" << std::endl;
  }

  // change the reference frame to ENU frame (0 - NWU,  1 - ENU,  2 - NED)
  imu.setRefFrame(1);
  int ref_frame_id;

  // check the refence frame the IMU is working in (0 - NWU,  1 - ENU,  2 - NED)
  imu.getRefFrame(ref_frame_id);
  if (ref_frame_id == 0)
    std::cout << "Reference Frame is North-West-Up (NWU) " << std::endl;
  else if (ref_frame_id == 1)
    std::cout << "Reference Frame is East-North-Up (ENU) " << std::endl;
  else if (ref_frame_id == 2)
    std::cout << "Reference Frame is North-East-Down (NED) " << std::endl;

  // wait for the imu to fully setup
  for (int i = 1; i <= 4; i += 1)
  {
    delay_ms(1000);
    std::cout << "configuring controller: " << i << " sec" << std::endl;
  }

  prevTime = std::chrono::system_clock::now();

  while (true)
  {
    duration = (std::chrono::system_clock::now() - prevTime);
    if (duration.count() > sampleTime)
    {
      try
      {
        imu.getRPY(roll, pitch, yaw); // gets RPY and store value in roll, pitch and yaw variable
      }
      catch (...)
      {
      }

      std::cout << "ROLL: " << roll << std::fixed << std::setprecision(4) << std::endl;
      std::cout << "PITCH: " << pitch << std::fixed << std::setprecision(4) << std::endl;
      std::cout << "YAW: " << yaw << std::fixed << std::setprecision(4) << std::endl;
      std::cout << std::endl;

      prevTime = std::chrono::system_clock::now();
    }
  }
}