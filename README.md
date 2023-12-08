# WSL_MBED_Communication
ECE 4180 Final Project
By Diana Garcia & Ritarka Samanta

## Project Idea
It would be quite convenient if we could interact with the mbed as another pluggable piece of hardware.
To this end, we attempted to create an interface for an user to quickly write commands on a WSL terminal and see the changes taking place in the mbed.
This can abstract some of the underlying complexity of the mbed.

## Instructions

[Connecting USB device to WSL](https://learn.microsoft.com/en-us/windows/wsl/connect-usb)

Requirements:
- Windows 11
- Machine with x64/x86 processor
- Linux installed
- Linux set to WSL 2
- Linux kernel 5.10.60.1 or later

Steps:
1. Download mbed program and compile in Keil Studio.
2. Upload to MED
3. Download latest [usbipd-win.msi](https://github.com/dorssel/usbipd-win/releases)
4. Run msi file
5. Open Ubuntu
6. Run following command
```
      sudo apt install linux-tools-generic hwdata
      sudo update-alternatives --install /usr/local/bin/usbip usbip /usr/lib/linux-tools/*-generic/usbip 20
```
8. Connect MED to device with USB cable
9. Open Powershell as Admin
10. Run following command
```
     usbipd wsl list
```
12. Note down the busid the mbed is connected to
13. Run the following command and edit "<busid>" to be the busid you recieved in the previous step
```
      usbipd wsl attach --busid <busid>
```
15. Open Ubuntu  
16. Compile program using g++ and run
17. Watch youtube video linked below for example commands

## Hardware Setups
1. Connect MED to PC with USB cable

## Youtube Video
[Link](https://www.youtube.com/watch?v=D3uV4TH-VVE)
