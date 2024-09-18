#include <sstream>
#include <iostream>
#include<unistd.h>

#include <chrono>

#include <iomanip>

#include "eimu.hpp"

EIMU imu;


void delay_ms(unsigned long milliseconds) {
  usleep(milliseconds*1000);
}



int main(int argc, char **argv) {

  float roll, pitch, yaw;

  auto prevTime = std::chrono::system_clock::now();
  std::chrono::duration<double> duration;
  float sampleTime = 0.02;



  // std::string port = "/dev/serial/by-path/pci-0000:00:14.0-usb-0:1.4:1.0-port0";
  std::string port = "/dev/ttyUSB0";
  imu.connect(port);

  // wait for the imu to fully setup
  for (int i=1; i<=10; i+=1){ 
    delay_ms(1000);
    std::cout << "configuring controller: " << i << " sec" << std::endl;
  }

  prevTime = std::chrono::system_clock::now();

  while (true)
  {
    duration = (std::chrono::system_clock::now() - prevTime);
    if (duration.count() > sampleTime)
    {
      try{
        imu.getRPY(roll, pitch, yaw); // gets RPY and store value in roll, pitch and yaw variable
      } catch(...) {}

      std::cout << "ROLL: " << roll << std::fixed << std::setprecision(4) << std::endl;
      std::cout << "PITCH: " << pitch << std::fixed << std::setprecision(4) << std::endl;
      std::cout << "YAW: " << yaw << std::fixed << std::setprecision(4) << std::endl;
      std::cout << std::endl;

      prevTime = std::chrono::system_clock::now();
    }

  }
  
}