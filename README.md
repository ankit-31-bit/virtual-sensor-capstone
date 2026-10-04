# Virtual Sensor Capstone

## Overview

This project implements a virtual temperature sensor as a Linux kernel module.

The kernel driver creates a virtual sensor device at:

/dev/vsensor

A user-space C monitoring application reads the sensor value and displays the temperature.

## Components

### Kernel Driver
- File: driver/vsensor.c
- Kernel module: driver/vsensor.ko
- Device: /dev/vsensor

### User-Space Monitor
- Source: app/monitor.c
- Executable: app/monitor

## Current Output

Temperature: 25°C

## How to Run

Build the driver:

cd driver
make

Load the driver:

sudo insmod vsensor.ko

Run the monitor:

cd ../app
gcc monitor.c -o monitor
sudo ./monitor

## Project Structure

virtual-sensor-capstone/
├── app/
│   ├── monitor.c
│   └── monitor
├── driver/
│   ├── vsensor.c
│   ├── vsensor.ko
│   └── Makefile
└── README.md
