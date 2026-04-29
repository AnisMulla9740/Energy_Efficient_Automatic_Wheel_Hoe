# ⚙️ Energy Efficient Automatic Wheel Hoe

An embedded systems project implementing an **energy-efficient automatic wheel hoe** for agricultural use, developed on the **STM32F407VGT6** microcontroller using STM32CubeIDE. The system uses current sensing, PWM motor control, USB communication, and UART to automate and optimize the wheel hoe operation while minimizing energy consumption.

---

## 📌 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware](#hardware)
- [Project Structure](#project-structure)
- [Peripherals & Configuration](#peripherals--configuration)
- [Getting Started](#getting-started)
- [Development Tools](#development-tools)
- [License](#license)

---

## 🔍 Overview

The **Energy Efficient Automatic Wheel Hoe** is designed to automate the weeding/hoeing process in agricultural fields. The system continuously monitors motor current consumption via an ADC-connected current sensor and uses PWM-based motor control to regulate speed and energy usage. Data can be logged or monitored over UART or USB (CDC) communication.

---

## ✨ Features

- 🔋 **Energy-efficient motor control** via PWM (TIM3 – 1 kHz PWM, 12-bit resolution)
- 📊 **Current sensing** using ADC1 (12-bit, Channel 0 – PA0)
- 🔌 **USB Host CDC** for real-time data logging or command input
- 📡 **UART2** for serial communication/debugging
- 💡 **LED status indicators** (Green, Orange, Red, Blue – PD12–PD15)
- 🕐 **SysTick-based** real-time timing
- I2C (I2C1 & I2C3) interfaces for peripherals/sensors
- I2S3 audio interface support (CS43L22 codec)
- SPI1 interface (LIS302DL MEMS accelerometer)
- External oscillator (HSE 8 MHz → PLL → 168 MHz system clock)

---

## 🔧 Hardware

| Component | Details |
|---|---|
| **Microcontroller** | STM32F407VGT6 (LQFP100) |
| **Development Board** | STM32F407G-DISC1 (Discovery) |
| **Current Sensor** | Analog output sensor on PA0 (ADC1 IN0) |
| **Motor Control** | PWM via TIM3 CH1 (PA6) |
| **Communication** | USART2 (PA2/PA3), USB OTG FS (CDC Host) |
| **Indicators** | LEDs on PD12, PD13, PD14, PD15 |
| **Clock** | HSE 8 MHz external oscillator → 168 MHz via PLL |

---

## 📁 Project Structure

Energy_Efficient_Automatic_Wheel_Hoe/
│
├── Core/                        # Main application source & headers
│   └── Src/                     # main.c, system init, peripheral drivers
│
├── Drivers/                     # STM32 HAL & BSP drivers
│
├── Middlewares/
│   └── ST/STM32_USB_Host_Library/   # USB Host middleware (CDC class)
│
├── USB_HOST/                    # USB Host application layer
│
├── Debug/                       # Build output (debug binaries)
│
├── Current_Sensor.ioc           # STM32CubeMX project configuration
├── STM32F407VGTX_FLASH.ld       # Linker script (Flash)
├── STM32F407VGTX_RAM.ld         # Linker script (RAM)
├── .cproject                    # Eclipse/STM32CubeIDE project file
└── .project                     # Eclipse project descriptor

---
## ⚡ Peripherals & Configuration

### Clock
- **System Clock:** 168 MHz (HSE 8 MHz → PLL: M=8, N=336, Q=7)
- **APB1:** 42 MHz | **APB2:** 84 MHz
- **USB 48 MHz** clock derived from PLL

### ADC1 – Current Sensor
| Parameter | Value |
|---|---|
| Channel | IN0 (PA0) |
| Resolution | 12-bit |
| Sampling Time | 3 cycles |
| Conversions | 1 |

### TIM3 – PWM Motor Control
| Parameter | Value |
|---|---|
| Channel | CH1 (PA6) |
| Prescaler | 83 |
| Period | 100 |
| Effective Frequency | ~1 kHz |

### USART2 – Serial Communication
| Parameter | Value |
|---|---|
| Mode | Asynchronous |
| TX | PA2 |
| RX | PA3 |

### USB OTG FS – USB Host (CDC)
| Parameter | Value |
|---|---|
| Mode | Host Only |
| PHY | Embedded |
| Class | CDC (Virtual COM Port) |
| VBUS Control | PC0 (Active High) |

### I2C
| Interface | Pins | Usage |
|---|---|---|
| I2C1 | PB6 (SCL), PB9 (SDA) | Audio codec (CS43L22) |
| I2C3 | PA8 (SCL), PC9 (SDA) | External sensor |

---

## 🚀 Getting Started

### Prerequisites

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) (v1.x or later)
- STM32CubeMX (optional, for viewing/modifying `.ioc`)
- STM32F4 HAL Firmware Package: `STM32Cube FW_F4 V1.28.3`
- ST-Link/V2 debugger (on-board on Discovery kit)
- ARM GCC Toolchain (bundled with STM32CubeIDE)

### Build & Flash

1. Clone the repository:
```bash
   git clone https://github.com/AnisMulla9740/Energy_Efficient_Automatic_Wheel_Hoe.git
```
2. Open **STM32CubeIDE** → `File` → `Import` → `Existing Projects into Workspace`
3. Select the cloned folder and import the project
4. Build: `Project` → `Build Project` (or `Ctrl+B`)
5. Flash: `Run` → `Debug` (or press `F11`) with the STM32F407G-DISC1 connected via USB

### Serial Monitor

Connect via any serial terminal (e.g., PuTTY, Tera Term) to the USART2 port. Default baud rate is configured in `main.c`.

---

## 🛠️ Development Tools

| Tool | Version |
|---|---|
| STM32CubeIDE | Based on Eclipse CDT |
| STM32CubeMX | v6.14.1 |
| HAL Firmware | STM32Cube FW_F4 V1.28.3 |
| Compiler | ARM GCC (Optimization: -O2) |
| Debug Interface | SWD (SWDIO – PA13, SWCLK – PA14, SWO – PB3) |

---

## 📄 License

**Copyright © 2025 AnisMulla9740. All Rights Reserved.**

This project and all its contents — including but not limited to source code, configuration files, documentation, and hardware designs — are the exclusive intellectual property of the author.

**No part of this project may be reproduced, distributed, modified, sublicensed, or used in any form** — whether for commercial or non-commercial purposes — **without the express prior written permission of the copyright owner.**

Unauthorized use, copying, or distribution of this project, in whole or in part, is strictly prohibited and may be subject to legal action.

For permissions or inquiries, contact the repository owner via GitHub: [@AnisMulla9740](https://github.com/AnisMulla9740)

---

## 📁 Project Structure
