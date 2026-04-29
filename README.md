# ⚙️ Energy Efficient Automatic Wheel Hoe

An embedded systems project implementing an **energy-efficient automatic wheel hoe** for agricultural use, developed on the **STM32F407VGT6** microcontroller using STM32CubeIDE. The system features progressive speed control via physical switches, current-based energy monitoring, LCD display, LED indicators, exhaust fan switching, and USB/UART communication.

---

## 📌 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware](#hardware)
- [Project Structure](#project-structure)
- [Peripherals & Configuration](#peripherals--configuration)
- [System Operation](#system-operation)
- [Getting Started](#getting-started)
- [Development Tools](#development-tools)
- [License](#license)

---

## 🔍 Overview

The **Energy Efficient Automatic Wheel Hoe** automates the weeding and hoeing process in agricultural fields. A **Master Switch** controls the entire system's ON/OFF state. Two dedicated **Progressive Speed Switches** allow the operator to incrementally increase or decrease the motor speed, with the current speed level shown on a **16×2 LCD display** and indicated visually through **LEDs**. The system continuously monitors motor current consumption via an ADC-connected current sensor and manages an **exhaust fan** based on system load or temperature. All operational data can be logged over UART or USB CDC.

---

## ✨ Features

- 🔘 **Master Switch** — Main ON/OFF control for the entire system
- 🔼🔽 **Progressive Speed Switching** — Two physical switches to incrementally increase or decrease motor speed
- 🖥️ **16×2 LCD Display** — Real-time display of current speed level and system status
- 💡 **LED Speed Indicators** — Visual representation of the active speed level
- 🔋 **Battery Monitoring** — Continuous monitoring of supply/battery voltage via ADC
- 🌀 **Exhaust Fan Switching** — Automatic or manual switching of the exhaust fan based on system conditions
- 📊 **Current Sensing** — ADC1 (12-bit, PA0) monitors motor current for energy efficiency
- 🎛️ **PWM Motor Control** — TIM3 CH1 generates PWM to drive the motor at the selected speed step
- 📡 **UART2 Serial Communication** — Debugging and data logging via serial terminal
- 🔌 **USB Host CDC** — USB-based communication/data logging
- 🕐 **SysTick-based** real-time timing for switch debounce and periodic tasks

---

## 🔧 Hardware

| Component | Details |
|---|---|
| **Microcontroller** | STM32F407VGT6 (LQFP100) |
| **Development Board** | STM32F407G-DISC1 (Discovery) |
| **Current Sensor** | Analog output sensor on PA0 (ADC1 IN0) |
| **Motor Control** | PWM via TIM3 CH1 (PA6) |
| **Master Switch** | Digital input — system ON/OFF |
| **Speed Increase Switch** | Digital input — increments motor speed step |
| **Speed Decrease Switch** | Digital input — decrements motor speed step |
| **16×2 LCD Display** | Connected via I2C or GPIO (displays speed & status) |
| **LED Indicators** | PD12 (Green), PD13 (Orange), PD14 (Red), PD15 (Blue) |
| **Exhaust Fan** | GPIO-controlled output switched based on load/temp |
| **Battery Monitor** | ADC channel — monitors supply voltage level |
| **Communication** | USART2 (PA2/PA3), USB OTG FS CDC Host |
| **Clock** | HSE 8 MHz external oscillator → 168 MHz via PLL |

---

## 📁 Project Structure
Energy_Efficient_Automatic_Wheel_Hoe/
│
├── Core/                        # Main application source & headers
│   └── Src/                     # main.c — master switch, speed logic,
│                                #   LCD, LED, fan, battery monitor
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
| Parameter | Value |
|---|---|
| System Clock | 168 MHz (HSE 8 MHz → PLL: M=8, N=336, Q=7) |
| APB1 | 42 MHz |
| APB2 | 84 MHz |
| USB Clock | 48 MHz (from PLL) |

### ADC1 – Current Sensor & Battery Monitor
| Parameter | Value |
|---|---|
| Channel | IN0 (PA0) |
| Resolution | 12-bit |
| Sampling Time | 3 cycles |
| Usage | Motor current sensing + battery voltage monitoring |

### TIM3 – PWM Motor Control
| Parameter | Value |
|---|---|
| Channel | CH1 (PA6) |
| Prescaler | 83 |
| Period | 100 |
| Effective Frequency | ~1 kHz |
| Speed Steps | Incremented/decremented by progressive switches |

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
| I2C1 | PB6 (SCL), PB9 (SDA) | Audio codec / LCD (if I2C-based) |
| I2C3 | PA8 (SCL), PC9 (SDA) | External sensor / LCD |

### GPIO – Control & Indicators
| Pin | Label | Direction | Function |
|---|---|---|---|
| PD12 | LD4 Green | Output | Speed level / status indicator |
| PD13 | LD3 Orange | Output | Speed level / status indicator |
| PD14 | LD5 Red | Output | Speed level / warning indicator |
| PD15 | LD6 Blue | Output | System ON / master status |
| PC0 | OTG_FS_PowerSwitchOn | Output | USB VBUS enable |
| PE3 | CS_I2C/SPI | Output | SPI CS for MEMS |
| PD4 | Audio_RST | Output | Exhaust fan / peripheral reset |

---

## 🕹️ System Operation

### Master Switch
The master switch serves as the primary ON/OFF control for the entire system. When OFF, the motor stops, the fan is disabled, the LCD shows a standby message, and all LEDs are cleared.

### Progressive Speed Control
Two physical switches control motor speed in discrete steps:

| Switch | Action |
|---|---|
| **Speed UP Switch** | Increments PWM duty cycle by one step (increases motor speed) |
| **Speed DOWN Switch** | Decrements PWM duty cycle by one step (decreases motor speed) |

Speed steps are bounded — the system will not exceed the maximum or drop below the minimum defined speed. Each press updates:
- The **PWM duty cycle** on TIM3 CH1
- The **16×2 LCD** (e.g., `Speed: Level 3/5`)
- The **LED indicators** (each LED represents a speed band)

### Battery Monitoring
The ADC periodically samples the battery/supply voltage. If the voltage drops below a configured threshold, a warning is shown on the LCD and the Red LED is activated.

### Exhaust Fan Switching
The exhaust fan is switched ON/OFF via a GPIO output based on system operating conditions (e.g., high current draw or extended run time).

---

## 🚀 Getting Started

### Prerequisites

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- STM32F4 HAL Firmware Package: `STM32Cube FW_F4 V1.28.3`
- STM32F407G-DISC1 Discovery Board
- ST-Link/V2 debugger (on-board)
- ARM GCC Toolchain (bundled with STM32CubeIDE)

### Build & Flash

1. Clone the repository:
```bash
   git clone https://github.com/AnisMulla9740/Energy_Efficient_Automatic_Wheel_Hoe.git
```
2. Open **STM32CubeIDE** → `File` → `Import` → `Existing Projects into Workspace`
3. Select the cloned folder and import the project
4. Build: `Project` → `Build Project` (`Ctrl+B`)
5. Connect the STM32F407G-DISC1 board via USB
6. Flash & Debug: `Run` → `Debug` (`F11`)

### Serial Monitor

Connect via any serial terminal (e.g., PuTTY, Tera Term) to the USART2 COM port to view real-time speed, current, and battery data.

---

## 🛠️ Development Tools

| Tool | Version / Detail |
|---|---|
| STM32CubeIDE | Eclipse CDT-based IDE |
| STM32CubeMX | v6.14.1 |
| HAL Firmware | STM32Cube FW_F4 V1.28.3 |
| Compiler | ARM GCC (Optimization: -O2) |
| Debug Interface | SWD — SWDIO (PA13), SWCLK (PA14), SWO (PB3) |

---

## 📄 License

**Copyright © 2025 AnisMulla9740. All Rights Reserved.**

This project and all its contents — including but not limited to source code, configuration files, documentation, and hardware designs — are the exclusive intellectual property of the author.

**No part of this project may be reproduced, distributed, modified, sublicensed, or used in any form** — whether for commercial or non-commercial purposes — **without the express prior written permission of the copyright owner.**

Unauthorized use, copying, or distribution of this project, in whole or in part, is strictly prohibited and may be subject to legal action.

For permissions or inquiries, contact the repository owner via GitHub: [@AnisMulla9740](https://github.com/AnisMulla9740)
