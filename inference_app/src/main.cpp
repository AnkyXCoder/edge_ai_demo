#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"

#define LED0_NODE   DT_ALIAS(led0)
#define GRAVITY_MS2 9.80665f

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];
static size_t feature_ix = 0;

int main(void)
{
    const struct device *accel_dev;
    struct sensor_value accel[3];

    /* Initialize hardware */
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    accel_dev = DEVICE_DT_GET(DT_ALIAS(accel0));

    setvbuf(stdout, NULL, _IONBF, 0);

    printk("\n=== Edge Impulse Inference ===\n");
    printk("Model: %s\n", EI_CLASSIFIER_PROJECT_NAME);
    printk("Classes: %d\n", EI_CLASSIFIER_LABEL_COUNT);
    printk("Window: %d ms\n", EI_CLASSIFIER_SLICE_SIZE);
    printk("\nStarting inference...\n\n");

    const int sample_period_ms = 1000 / EI_CLASSIFIER_FREQUENCY;

    while (1) {
        int64_t start = k_uptime_get();

        /* Sample sensor */
        sensor_sample_fetch(accel_dev);
        sensor_channel_get(accel_dev, SENSOR_CHAN_ACCEL_XYZ, accel);

        /* Fill feature buffer */
        features[feature_ix++] = sensor_value_to_double(&accel[0]) * GRAVITY_MS2;
        features[feature_ix++] = sensor_value_to_double(&accel[1]) * GRAVITY_MS2;
        features[feature_ix++] = sensor_value_to_double(&accel[2]) * GRAVITY_MS2;

        /* Run inference when buffer is full */
        if (feature_ix >= EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
            ei_impulse_result_t result;
            signal_t signal;

            numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);

            EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

            if (res == EI_IMPULSE_OK) {
                /* Print timing */
                printk("Timing: DSP=%d ms, NN=%d ms\n", result.timing.dsp, result.timing.classification);

                /* Find best prediction */
                float max_conf = 0.0f;
                const char *prediction = "";

                printk("Predictions:\n");
                for (size_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
                    printk("  %-12s: %.2f%%\n", result.classification[i].label,
                           result.classification[i].value * 100.0f);

                    if (result.classification[i].value > max_conf) {
                        max_conf = result.classification[i].value;
                        prediction = result.classification[i].label;
                    }
                }

#if EI_CLASSIFIER_HAS_ANOMALY == 1
                printk("  Anomaly: %.3f\n", result.anomaly);
#endif

                printk("\n>>> %s (%.0f%%) <<<\n\n", prediction, max_conf * 100.0f);

                /* LED feedback */
                if (max_conf > 0.8f) {
                    gpio_pin_toggle_dt(&led);
                }
            }

            feature_ix = 0;
        }

        /* Maintain sampling rate */
        k_sleep(K_MSEC(sample_period_ms - (k_uptime_get() - start)));
    }

    return 0;
}
