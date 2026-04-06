# Edge AI Demo with Zephyr RTOS and Edge Impulse

Edge AI is transforming embedded systems, enabling devices to sense, learn, and respond locally without cloud dependency. This comprehensive demo demonstrates how to build a complete Edge AI pipeline from data collection to on-device deployment using Zephyr RTOS, Edge Impulse, and the nRF52840 development kit.

## What You'll Build

By the end of this demo, you'll have working implementations for:

* **Continuous Motion Recognition** - Classify walking, tilt, idle, and shake movements in real-time  
* **Sound Classification** - Distinguish between noise, speech, and specific events  
* **Keyword Spotting** - Recognize voice commands (yes/no/start/stop)

All running entirely on-device with sub-30ms inference latency and minimal power consumption.

## System Architecture

The Edge AI pipeline follows this end-to-end architecture:

1. **Data Collection** - Sensor data streaming via Data Forwarder
2. **Model Training** - Edge Impulse Studio for ML development
3. **Model Deployment** - On-device inference with optimized models

## Hardware Requirements

### Option 1: nRF52840 DK + External Sensor Shield

**Development Board:** Nordic Semiconductor nRF52840 DK
* **MCU**: ARM Cortex-M4F @ 64 MHz  
* **Flash**: 1 MB  
* **RAM**: 256 KB  
* **Connectivity**: Bluetooth 5.0 LE, NFC  
* **Interfaces**: USB, UART, SPI, I2C, GPIO

**Sensor Shield:** X-NUCLEO-IKS01A3
* **LSM6DSO**: 6-axis IMU (accelerometer + gyroscope)  
* **LIS2MDL**: 3-axis magnetometer  
* **LIS2DW12**: Low-power 3-axis accelerometer  
* **HTS221**: Humidity and temperature sensor  
* **LPS22HH**: Pressure sensor

### Option 2: STM32 B-L475E-IOT01A

**Development Board:** STMicroelectronics B-L475E-IOT01A Discovery Kit
* **MCU**: ARM Cortex-M4F @ 80 MHz  
* **Flash**: 1 MB  
* **RAM**: 128 KB  
* **Connectivity**: WiFi, Bluetooth LE, NFC, Sub-GHz  
* **Built-in Sensors:**  
  * **LSM6DSL**: 6-axis IMU  
  * **LIS3MDL**: 3-axis magnetometer  
  * **HTS221**: Humidity and temperature  
  * **LPS22HB**: Pressure sensor  
  * **MP34DT01**: Digital MEMS microphone

## Software Stack Setup

### Prerequisites Installation

#### 1. Install Node.js 22 LTS

**Linux/Ubuntu:**
```bash
curl -sL https://deb.nodesource.com/setup_22.x | sudo -E bash -
sudo apt-get install -y nodejs
node -v  # Verify: v22.x or higher
```

#### 2. Install Zephyr RTOS

Zephyr RTOS Version: v4.4.0

Follow the official guide: [Zephyr Getting Started](https://docs.zephyrproject.org/latest/develop/getting_started/)

Update the `west.yml` of your Zephyr repo adding the lines below for the SDK then call `west update` to download the SDK into your Zephyr repo.

Here are the lines to add the Edge Impulse SDK:

```yaml
   - name: edge-impulse-sdk-zephyr
      path: modules/edge-impulse-sdk-zephyr
      revision: ${EI_SDK_VERSION}
      url: https://github.com/edgeimpulse/edge-impulse-sdk-zephyr
```

#### 3. Install Edge Impulse CLI

```bash
npm install -g edge-impulse-cli --force

# Verify installation
edge-impulse-daemon --version
edge-impulse-data-forwarder --version
edge-impulse-run-impulse --version
```

#### 4. Create Edge Impulse Account

1. Visit [Edge Impulse Studio](https://studio.edgeimpulse.com/signup)  
2. Sign up for a free account  
3. Create a new project (e.g., "nRF52840-Motion-Recognition")

## Project Structure

```tree
edge_ai_demo/
├── README.md                    # This file
├── data_forwarder/              # Data collection application
│   ├── src/main.cpp
│   ├── boards/
│   │   ├── nrf52840dk_nrf52840.conf
│   │   └── disco_l475_iot1.conf
│   ├── CMakeLists.txt
│   └── prj.conf
└── inference_app/               # On-device inference application
    ├── src/main.cpp
    ├── model/                   # Extracted Edge Impulse model
    ├── boards/
    │   ├── nrf52840dk_nrf52840.conf
    │   └── disco_l475_iot1.conf
    ├── CMakeLists.txt
    └── prj.conf
```

## Quick Start

### 1. Data Collection

```bash
cd data_forwarder
# Build for nRF52840 DK
west build -p -b nrf52840dk/nrf52840
west flash

# Connect to Edge Impulse
edge-impulse-data-forwarder
```

### 2. Model Training

1. Open Edge Impulse Studio
2. Collect training data using the data forwarder
3. Create impulse with spectral analysis and neural network
4. Train and evaluate your model

### 3. On-Device Inference

```bash
cd inference_app

# Build and download model
west ei-build -k ei_abc123... -p 12345
west ei-deploy -k ei_abc123... -p 12345
unzip ei_model.zip -d ./model

# Build and flash
west build -p -b nrf52840dk/nrf52840
west flash
```

## Performance Optimization

### Hardware Acceleration

Enable ARM CMSIS-NN for 2-4x faster inference:

```cmake
# Edge Impulse / CMSIS-NN flags
add_definitions(-DEIDSP_USE_CMSIS_DSP=1
               -DEIDSP_LOAD_CMSIS_DSP_SOURCES=1
               -DEI_CLASSIFIER_TFLITE_ENABLE_CMSIS_NN=1
               -DARM_MATH_LOOPUNROLL)
```

### Model Quantization

Use int8 quantization for:
* 4x smaller model size
* 2-3x faster inference
* <2% accuracy loss typically

## Key Benefits

* **Latency**: <30ms for typical models  
* **Privacy**: All processing happens on-device  
* **Offline Operation**: No internet required  
* **Zero Cloud Costs**: One-time deployment  
* **Low Bandwidth**: Only transmit predictions, not raw data

## Support

For detailed step-by-step instructions, see the comprehensive guide: [Edge AI with Zephyr RTOS and Edge Impulse](Edge%20AI%20with%20Zephyr%20RTOS%20and%20Edge%20Impulse.md)
