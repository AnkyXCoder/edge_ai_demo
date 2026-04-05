# Inference Applixcation example (Zephyr)


## How to build

1. Build Edge Impulse Model:

    ```bash
    west ei-build -k ei_3e58e2... -p 12345 -e tflite-eon -t int8 -i 1
    ```

1. Download and deploy Edge Impulse Model:

    ```bash
    west ei-deploy -k ei_3e58e2... -p 12345 -e tflite-eon -t int8 -i 1
    ```

1. Extract model:

    ```bash
    unzip ei_model.zip -d ./model
    ```

1. Build and flash this application:

    ```bash
    cd data_forwarder
    west build -p -b nrf52840dk/nrf52840
    west flash
    # or
    west flash -r jlink
    ```

1. Example output:

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
