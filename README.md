# Virtual Sensor Capstone

A Linux kernel-module project that implements a virtual temperature sensor as a character device.

The project demonstrates communication between a user-space C application and a Linux kernel module through the virtual device `/dev/vsensor`.

---

## Overview

The project consists of two main components:

- **Kernel Module** — Implements the virtual temperature sensor.
- **C Monitor Application** — Reads the temperature from the virtual sensor and displays it in the terminal.

The virtual sensor is exposed to user space through:

```text
/dev/vsensor
```

---

## Project Architecture

```text
                    USER / TERMINAL
                           |
                           |
              Write temperature (45°C)
                           |
                           v
                  +----------------+
                  |  /dev/vsensor  |
                  | Virtual Device |
                  +-------+--------+
                          |
                          v
              +-----------------------+
              |   Linux Kernel        |
              |   Module              |
              |                       |
              |     vsensor.c         |
              |                       |
              |  - Device registration|
              |  - Read operation     |
              |  - Write operation    |
              |  - Temperature storage|
              +----------+------------+
                         |
                         | Read temperature
                         v
              +-----------------------+
              |   C Monitor           |
              |   Application         |
              |                       |
              |     monitor.c         |
              +----------+------------+
                         |
                         v
                  +--------------+
                  | Temperature  |
                  |    45°C      |
                  +--------------+
```

### Data Flow

1. The user writes a temperature value to `/dev/vsensor`.
2. The virtual sensor kernel module receives the value.
3. The driver stores the temperature value.
4. The C monitor application reads the value from `/dev/vsensor`.
5. The temperature is displayed in the terminal.

---

## Project Structure

```text
virtual-sensor-capstone/
│
├── app/
│   └── monitor.c
│
├── driver/
│   ├── Makefile
│   └── vsensor.c
│
├── .gitignore
└── README.md
```

### File Description

| File | Description |
|------|-------------|
| `driver/vsensor.c` | Linux kernel module implementing the virtual sensor |
| `driver/Makefile` | Builds the kernel module |
| `app/monitor.c` | User-space C application that reads and displays the temperature |
| `.gitignore` | Specifies files ignored by Git |
| `README.md` | Project documentation |

---

## Requirements

- Ubuntu/Linux
- GCC
- Make
- Linux kernel headers
- Root privileges for loading and accessing the kernel module

---

## Build the Kernel Module

Navigate to the driver directory:

```bash
cd driver
```

Build the kernel module:

```bash
make
```

This generates:

```text
vsensor.ko
```

---

## Load the Driver

From the project root, load the kernel module:

```bash
sudo insmod driver/vsensor.ko
```

Verify that the module is loaded:

```bash
lsmod | grep vsensor
```

---

## Verify the Virtual Device

Check that the device file exists:

```bash
ls -l /dev/vsensor
```

Expected device:

```text
/dev/vsensor
```

---

## Build the Monitor Application

Navigate to the application directory:

```bash
cd app
```

Compile the monitor:

```bash
gcc monitor.c -o monitor
```

---

## Run the Monitor

Run:

```bash
sudo ./monitor
```

Example output:

```text
Virtual Sensor Monitor
=======================
Temperature: 45°C
```

---

## Change the Sensor Temperature

A new temperature can be written to the virtual sensor using:

```bash
echo 45 | sudo tee /dev/vsensor
```

Then run the monitor:

```bash
sudo ./monitor
```

Example output:

```text
Virtual Sensor Monitor
=======================
Temperature: 45°C
```

You can change the value:

```bash
echo 30 | sudo tee /dev/vsensor
```

Then:

```bash
sudo ./monitor
```

Output:

```text
Virtual Sensor Monitor
=======================
Temperature: 30°C
```

---

## Kernel Module Management

Check whether the module is loaded:

```bash
lsmod | grep vsensor
```

Remove the module:

```bash
sudo rmmod vsensor
```

After removing the module, `/dev/vsensor` will no longer be available until the module is loaded again.

---

## Complete Workflow

```bash
# Build the kernel module
cd driver
make

# Return to project root
cd ..

# Load the kernel module
sudo insmod driver/vsensor.ko

# Verify the module
lsmod | grep vsensor

# Verify the device
ls -l /dev/vsensor

# Build the monitor application
cd app
gcc monitor.c -o monitor

# Set the temperature
echo 45 | sudo tee /dev/vsensor

# Run the monitor
sudo ./monitor
```

---

## Expected Output

```text
Virtual Sensor Monitor
=======================
Temperature: 45°C
```

---

## Technologies Used

- C
- Linux Kernel Modules
- Linux Character Devices
- GCC
- Make
- Ubuntu/Linux

---

## Key Concepts Demonstrated

- Linux kernel module development
- Character device drivers
- Kernel-space and user-space communication
- Device file interaction
- Read and write operations
- Linux device management
- Kernel module compilation and loading
- C system programming

---

## Author

**ankit-31-bit**

GitHub Repository:

https://github.com/ankit-31-bit/virtual-sensor-capstone
