# Inference Application Example (Zephyr)

This application demonstrates on-device machine learning inference using Edge Impulse models deployed on Zephyr RTOS. It supports real-time classification of sensor data with sub-30ms latency on the nRF52840 and STM32 B-L475E-IOT01A development boards.

## Overview

The inference application runs trained machine learning models locally on the microcontroller, providing:

* **Real-time inference** - Process sensor data and output predictions instantly
* **Low power consumption** - Optimized for battery-powered devices
* **Privacy-preserving** - All processing happens on-device
* **Offline operation** - No internet connectivity required

## Prerequisites

### Edge Impulse SDK Integration

Update the `west.yml` of your Zephyr repo adding the lines below for the SDK then call `west update` to download the SDK into your Zephyr repo.

Here are the lines to add the Edge Impulse SDK:

```yaml
   - name: edge-impulse-sdk-zephyr
      path: modules/edge-impulse-sdk-zephyr
      revision: ${EI_SDK_VERSION}
      west-commands: west/west-commands.yml
      url: https://github.com/edgeimpulse/edge-impulse-sdk-zephyr
```

## Model Building and Deployment

### 1. Configure and Train Edge Impulse Model




### 2. Build Edge Impulse Model

Use `west ei-build` to trigger a new build of your Edge Impulse model deployment in Studio:

```bash
# Build the latest model configuration from your Edge Impulse project
west ei-build -k ei_abc123... -p 12345

# With optional parameters
west ei-build -k ei_abc123... -p 12345 -e tflite-eon -t int8 -i 1
```

**Required arguments:**

* `-k, --api-key` - Your Edge Impulse API key  
* `-p, --project` - Your Edge Impulse project ID (integer)

**Optional arguments:**

* `-i, --impulseid` - Specific impulse ID to build (default: 1)  
* `-e, --engine` - Build engine: `tflite` or `tflite-eon` (default: `tflite-eon`)  
* `-t, --modeltype` - Model type: `int8` or `float32` (default: `int8`)

### 2. Download Edge Impulse Model

Use `west ei-deploy` to download your pre-built Edge Impulse model deployment:

```bash
# Download the latest built model from your Edge Impulse project
west ei-deploy -k ei_abc123... -p 12345

# With optional parameters
west ei-deploy -k ei_abc123... -p 12345 -e tflite-eon -t int8 -i 1

# The zip file is downloaded as ei_model.zip
# Extract it to the model/ directory
unzip ei_model.zip -d ./model
```

**Required arguments:**

* `-k, --api-key` - Your Edge Impulse API key  
* `-p, --project` - Your Edge Impulse project ID (integer)

**Optional arguments:**

* `-i, --impulseid` - Specific impulse ID to download (default: 1)  
* `-e, --engine` - Build engine: `tflite` or `tflite-eon` (default: `tflite-eon`)  
* `-t, --modeltype` - Model type: `int8` or `float32` (default: `int8`)

### 3. Extract Model

```bash
unzip ei_model.zip -d ./model
```

## How to Build

### For nRF52840 DK

```bash
cd inference_app
west build -p -b nrf52840dk/nrf52840
west flash
# or
west flash -r jlink
```

### For STM32 B-L475E-IOT01A

```bash
cd inference_app
west build -p -b disco_l475_iot01
west flash
```

## Expected Output

When the application starts, you'll see output similar to:

```bash
[00:00:00.384,948] <dbg> LIS2DW12: lis2dw12_power_up: power-mode is 0
[00:00:00.384,948] <dbg> LIS2DW12: lis2dw12_set_power_mode: Apply default Power Mode
[00:00:00.385,406] <dbg> LIS2DW12: lis2dw12_power_up: low noise is 0
[00:00:00.388,397] <dbg> LIS2DW12: lis2dw12_power_up: range is 2
[00:00:00.389,434] <dbg> LIS2DW12: lis2dw12_power_up: bandwidth filter is 0
[00:00:00.390,441] <dbg> LIS2DW12: lis2dw12_power_up: high pass reference mode is 0
[00:00:00.391,448] <dbg> LIS2DW12: lis2dw12_power_up: high pass filter path is 0
[00:00:00.395,477] <inf> LSM6DSO: Initialize device lsm6dso@6b
[00:00:00.396,484] <inf> LSM6DSO: chip id 0x6c
[00:00:00.401,000] <dbg> LSM6DSO: lsm6dso_init_chip: accel pm is 0
[00:00:00.402,923] <dbg> LSM6DSO: lsm6dso_init_chip: accel range is 0
[00:00:00.403,900] <dbg> LSM6DSO: lsm6dso_init_chip: accel odr is 0
[00:00:00.406,280] <dbg> LSM6DSO: lsm6dso_init_chip: gyro pm is 0
[00:00:00.407,257] <dbg> LSM6DSO: lsm6dso_init_chip: gyro range is 0
[00:00:00.408,203] <dbg> LSM6DSO: lsm6dso_init_chip: gyro odr is 0
*** Booting Zephyr OS build v4.4.0-rc2-41-g149c8b1758a8 ***

=== Edge Impulse Inference ===
Model: Motion Classification - Continuous motion recognition                                   
Classes: 4                                                                                     
Window: 31 ms                                                                                  
                                                                                                
Starting inference...                                                                          

Timing: DSP=12 ms, NN=0 ms
Predictions:
idle        : 99.22%
snake       : 0.78%
updown      : 0.00%
wave        : 0.00%

>>> idle (99%) <<<

Timing: DSP=12 ms, NN=1 ms
Predictions:
idle        : 0.00%
snake       : 0.00%
updown      : 99.61%
wave        : 0.00%

>>> updown (100%) <<<

Timing: DSP=12 ms, NN=0 ms
Predictions:
idle        : 0.00%
snake       : 0.00%
updown      : 0.00%
wave        : 99.61%

>>> wave (100%) <<<

Timing: DSP=12 ms, NN=1 ms
Predictions:
idle        : 0.00%
snake       : 0.00%
updown      : 0.00%
wave        : 99.61%

>>> wave (100%) <<<

Timing: DSP=11 ms, NN=1 ms
Predictions:
idle        : 0.00%
snake       : 55.86%
updown      : 44.14%
wave        : 0.00%

>>> snake (56%) <<<

Timing: DSP=12 ms, NN=1 ms
Predictions:
idle        : 0.00%
snake       : 50.00%
updown      : 50.00%
wave        : 0.00%

>>> snake (50%) <<<

Timing: DSP=12 ms, NN=0 ms
Predictions:
idle        : 0.00%
snake       : 3.12%
updown      : 96.88%
wave        : 0.00%

>>> updown (97%) <<<
```

## Project Structure

```tree
inference_app/
├── src/main.cpp
├── model/                   # Extracted model
├── boards/
│   ├── nrf52840dk_nrf52840.conf
│   └── disco_l475_iot1.conf
├── CMakeLists.txt
└── prj.conf
```

## Performance Optimization

### Hardware Acceleration

Enable ARM CMSIS-NN for 2-4x faster inference:

Add to `CMakeLists.txt`:

```cmake
# Edge Impulse / CMSIS-NN flags (apply to app instead of unknown target)
add_definitions(-DEIDSP_USE_CMSIS_DSP=1
               -DEIDSP_LOAD_CMSIS_DSP_SOURCES=1
               -DEI_CLASSIFIER_TFLITE_ENABLE_CMSIS_NN=1
               -DARM_MATH_LOOPUNROLL)
```

**Performance Improvement:**

* 2-4x faster inference  
* 30-50% lower power consumption

### Model Quantization

**int8 Quantization** reduces model size and speeds up inference:

In Edge Impulse → EON Tuner:

* Enable int8 quantization  
* Calibrate with representative dataset  
* Rebuild model

**Benefits:**

* 4x smaller model size (Flash savings)  
* 2-3x faster inference  
* <2% accuracy loss typically

**Results:**

Before quantization:  

* Model size: 112 KB  
* Inference: 25 ms  
* RAM: 35 KB

After int8 quantization:  

* Model size: 28 KB  
* Inference: 12 ms  
* RAM: 20 KB

## Configuration

### Board-Specific Settings

The application includes board-specific configuration files:

* `boards/nrf52840dk_nrf52840.conf` - Settings for nRF52840 DK
* `boards/disco_l475_iot1.conf` - Settings for STM32 B-L475E-IOT01A

### Model Configuration

The application automatically loads the model from the `model/` directory. Ensure the extracted model files are present before building.

## Troubleshooting

### Common Issues

1. **Model not found**
   * Ensure `ei_model.zip` was extracted to `model/` directory
   * Check that model files exist and are readable

2. **Memory issues**
   * Enable model quantization to reduce memory usage
   * Reduce input window size if needed

3. **Slow inference**
   * Enable CMSIS-NN acceleration
   * Use int8 quantization

### Debug Output

Enable debug output by modifying `prj.conf`:

```kconfig
CONFIG_LOG=y
CONFIG_LOG_LEVEL=4
```

## Supported Model Types

The inference application supports various model types:

* **Motion Recognition** - Continuous classification of movement patterns

## Integration with Data Collection

This inference application is designed to work with models trained using the [data_forwarder application](../data_forwarder/README.md). The complete workflow is:

1. Collect training data using data_forwarder
2. Train models in Edge Impulse Studio
3. Deploy models to inference_app
4. Run real-time inference on-device

## Next Steps

* Add support for Model Types:
  * **Sound Classification** - Audio event detection
  * **Keyword Spotting** - Voice command recognition
  * **Anomaly Detection** - Unusual pattern detection
* Experiment with different model architectures
* Optimize for your specific use case
* Implement custom post-processing logic
* Add wireless connectivity for result transmission
