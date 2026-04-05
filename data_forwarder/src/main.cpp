#include "zephyr/device.h"
#include "zephyr/devicetree.h"
#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>
#include <stdlib.h>

static int64_t sampling_freq = 104; // in Hz.
static int64_t time_between_samples_us = (1000000 / (sampling_freq - 1));

int main()
{
    // output immediately without buffering
    setvbuf(stdout, NULL, _IONBF, 0);

    // get driver for the accelerometer
    const struct device *accel_dev = DEVICE_DT_GET(DT_ALIAS(accel0));
    if (accel_dev == NULL) {
        printf("Could not get accel: %s device\n", accel_dev->name);
        return 1;
    }

    struct sensor_value accel[3];

    while (1) {
        // start a timer that expires when we need to grab the next value
        struct k_timer next_val_timer;
        k_timer_init(&next_val_timer, NULL, NULL);
        k_timer_start(&next_val_timer, K_USEC(time_between_samples_us), K_NO_WAIT);

        // read data from the sensor
        if (sensor_sample_fetch(accel_dev) < 0) {
            printf("accel_dev Sensor sample update error\n");
            return 1;
        }

        sensor_channel_get(accel_dev, SENSOR_CHAN_ACCEL_XYZ, accel);

        // print over stdout
        printf("%.3f\t%.3f\t%.3f\r\n", sensor_value_to_double(&accel[0]), sensor_value_to_double(&accel[1]),
               sensor_value_to_double(&accel[2]));

        // busy loop until next value should be grabbed
        while (k_timer_status_get(&next_val_timer) <= 0)
            ;
    }
}