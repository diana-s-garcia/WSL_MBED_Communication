# WSL_MBED_Communication
ECE 4180 Final Project
By Diana Garcia & Ritarka Samanta

## Project Idea

## Instructions

[https://learn.microsoft.com/en-us/windows/wsl/connect-usb](Connecting USB device to WSL)
Requirements:
- Windows 11
- Machine with x64/x86 processor
- Linux installed
- Linux set to WSL 2
- Linux kernel 5.10.60.1 or later

Steps:
1. Download mbed program and compile in Keil Studio.
2. Upload to MED
3. Download latest [https://github.com/dorssel/usbipd-win/releases](usbipd-win.msi)
4. Run msi file
5. Open Ubuntu
6. Run following command
      sudo apt install linux-tools-generic hwdata
      sudo update-alternatives --install /usr/local/bin/usbip usbip /usr/lib/linux-tools/*-generic/usbip 20
7. Connect MED to device with USB cable
8. Open Powershell
9. Run following command
     usbipd wsl list
10. Note down the busid the mbed is connected to
11. Run the following command and edit "<busid>" to be the busid you recieved in the previous step
      usbipd wsl attach --busid <busid>
12. Open Ubuntu
    
13. 

## Hardware Setups
1. Connect MED to device with USB cable
