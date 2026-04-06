# Data Forwarder Example (Zephyr)

An example firmware for the Nordic Semiconductor nRF52840 DK showing how to use the [Edge Impulse Data Forwarder](https://docs.edgeimpulse.com/docs/cli-data-forwarder) to capture data from an IMU sensor at 104Hz and send it to Edge Impulse. This application should be easily adaptable to other Zephyr-supported development boards or sensors.

## Overview

The Data Forwarder is a Zephyr application that streams sensor data to Edge Impulse via serial connection. It handles:

* Real-time sensor sampling at precise frequencies  
* Data formatting (CSV/tab-delimited)  
* Serial transmission  
* Automatic frequency detection by Edge Impulse CLI

## Hardware Setup

### nRF52840 DK Assembly

1. Align X-NUCLEO-IKS01A3 shield with Arduino headers  
2. Carefully press the shield onto the headers. Ensure the shield doesn't touch the center pins  
3. Connect micro-USB cable to the SHORT side of the board  
4. Set power switch to ON  
5. Verify JLINK drive appears in your file system

### STM32 Setup

1. Connect micro-USB cable  
2. Board mounts as DIS_L4IOT drive  
3. All sensors are ready to use immediately

## Prerequisites

1. Install the [Edge Impulse CLI](https://docs.edgeimpulse.com/docs/cli-installation)
2. Install and configure your Zephyr toolchain.
3. Clone this repository:

```bash
git clone git@github.com:AnkyXCoder/edge_ai_demo.git
```

## How to Build

### For nRF52840 DK

```bash
cd data_forwarder
west build -p -b nrf52840dk/nrf52840
west flash
# or
west flash -r jlink
```

### For STM32 B-L475E-IOT01A

```bash
cd data_forwarder
west build -p -b disco_l475_iot01
west flash
```

## Data Collection Workflow

### 1. Connect Device to Edge Impulse

```bash
edge-impulse-data-forwarder
```

Follow the prompts:

* Login credentials
* Project selection
* Axes naming: accX, accY, accZ
* Device name

Example output:

```bash
Edge Impulse data forwarder v1.37.3
? What is your user name or e-mail address (edgeimpulse.com)? <your e-mail address>
? What is your password? [hidden]
Endpoints:
    Websocket: wss://remote-mgmt.edgeimpulse.com
    API:       https://studio.edgeimpulse.com
    Ingestion: https://ingestion.edgeimpulse.com

[SER] Connecting to /dev/ttyACM0
[SER] Serial is connected (00:06:83:94:40:08)
[WS ] Connecting to wss://remote-mgmt.edgeimpulse.com
[WS ] Connected to wss://remote-mgmt.edgeimpulse.com

[SER] Detecting data frequency...
[SER] Detected data frequency: 102Hz
? 3 sensor axes detected (example values: [-0.431,-0.134,9.418]). What do you want to call them? Separate the names with ',': accX,accY,accZ
[WS ] Device "test_device" is now connected to project "AnkyXCoder-project-1". To connect to another project, run `edge-impulse-data-forwarder --clean`.
[WS ] Go to https://studio.edgeimpulse.com/studio/123064/acquisition/training to build your machine learning model!
```

### 2. Collect Training Data

In Edge Impulse Studio → Data Acquisition:

* Set label (e.g., "square")  
* Sample length: 10000 ms  
* Click "Start sampling"  
* Perform continuous motion for 10 seconds  
* Repeat 10-15 times per class

### Best Practices

* Collect 3+ minutes per class  
* Vary speed (slow/fast movements)  
* Test different orientations  
* Include edge cases  
* Maintain continuous motion during recording  
* Balanced dataset (equal samples per class)

## Project Structure

```tree
data_forwarder/
├── src/main.cpp
├── boards/
│   ├── nrf52840dk_nrf52840.conf
│   └── disco_l475_iot1.conf
├── CMakeLists.txt
└── prj.conf
```

## Configuration

### Board-Specific Settings

The application includes board-specific configuration files:

* `boards/nrf52840dk_nrf52840.conf` - Settings for nRF52840 DK
* `boards/disco_l475_iot1.conf` - Settings for STM32 B-L475E-IOT01A

### Sensor Configuration

The application is configured to work with the following sensors:

* **LSM6DSO**: 6-axis IMU (accelerometer + gyroscope) on X-NUCLEO-IKS01A3
* **LSM6DSL**: 6-axis IMU on STM32 B-L475E-IOT01A

Sample rate is set to 104Hz for optimal motion recognition performance.

## Troubleshooting

### Common Issues

1. **Device not detected**
   * Check USB connection
   * Verify power switch is ON
   * Check device manager for JLINK/DIS_L4IOT drive

2. **Serial connection errors**
   * Verify device appears as /dev/ttyACM0 or similar
   * Check permissions on serial device
   * Try different USB port

3. **Data frequency detection issues**
   * Ensure sensor is properly connected
   * Check sensor configuration in board files
   * Verify sampling rate settings

### Debug Output

Enable debug output by modifying `prj.conf`:

```kconfig
CONFIG_LOG=y
CONFIG_LOG_LEVEL=4
```

## Next Steps

Once you have collected training data:

1. Open Edge Impulse Studio
2. Create impulse with spectral analysis and neural network
3. Train and evaluate your model
4. Deploy to the inference application

See the [inference_app README](../inference_app/README.md) for deployment instructions.
