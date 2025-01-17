/**
 * @file sensor.h
 * @author Adam Page (adam.page@ambiq.com)
 * @brief Initializes and collects sensor data from MAX86150
 * @version 1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __SENSOR_H
#define __SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <arm_math.h>
// Locals
#include "max86150_addons.h"
#include "ns_max86150_driver.h"

/**
 * @brief Sensor context structure
 *
 */
typedef struct {
    max86150_context_t *maxCtx;
    max86150_config_t *maxCfg;
    uint32_t *buffer;
    uint8_t initialized;
    uint8_t inputSource;
} sensor_context_t;

/**
 * @brief Initialize sensor frontend
 * @param ctx Sensor context
 * @return uint32_t
 */
uint32_t
sensor_init(sensor_context_t *ctx);

/**
 * @brief Enable sensor frontend
 *
 * @param ctx Sensor context
 */
void
sensor_start(sensor_context_t *ctx);

/**
 * @brief Capture sensor data from FIFO
 *
 * @param ctx Sensor context
 * @return uint32_t
 */
uint32_t
sensor_capture_data(sensor_context_t *ctx);

/**
 * @brief Capture stored data
 *
 * @param ctx
 * @param reqSamples  Number of samples to capture
 * @return uint32_t
 */
uint32_t
sensor_dummy_data(sensor_context_t *ctx, uint32_t reqSamples);

/**
 * @brief Disable sensor frontend
 *
 * @param ctx Sensor context
 */
void
sensor_stop(sensor_context_t *ctx);

#ifdef __cplusplus
}
#endif

#endif // __SENSOR_H
