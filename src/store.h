
/**
 * @file store.h
 * @author Adam Page (adam.page@ambiq.com)
 * @brief Act as central store for app
 * @version 1.0
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __APP_STORE_H
#define __APP_STORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <arm_math.h>
// Modules
#include "tio_usb.h"
// neuralSPOT
#include "ns_ambiqsuite_harness.h"
#include "ns_i2c.h"
#include "ns_peripherals_button.h"
#include "ns_peripherals_power.h"
// PhysioKit
#include "pk_ppg.h"
#include "pk_hrv.h"
#include "pk_ecg.h"
// Locals
#include "constants.h"
#include "sensor.h"
#include "metrics.h"
#include "ringbuffer.h"

enum HeartRhythm { HeartRhythmNormal, HeartRhythmAfib, HeartRhythmAfut };
typedef enum HeartRhythm HeartRhythm;

enum HeartBeat { HeartBeatNormal, HeartBeatPac, HeartBeatPvc, HeartBeatNoise };
typedef enum HeartBeat HeartBeat;

enum HeartRate { HeartRateNormal, HeartRateTachycardia, HeartRateBradycardia };
typedef enum HeartRate HeartRate;

enum HeartSegment { HeartSegmentNormal, HeartSegmentPWave, HeartSegmentQrs, HeartSegmentTWave };
typedef enum HeartSegment HeartSegment;

enum DenoiseMode { DenoiseModeOff, DenoiseModeDsp, DenoiseModeAi };
typedef enum DenoiseMode DenoiseMode;

enum SegmentationMode { SegmentationModeOff, SegmentationModeDsp, SegmentationModeAi };
typedef enum SegmentationMode SegmentationMode;

enum ArrhythmiaMode { ArrhythmiaModeOff, ArrhythmiaModeDsp, ArrhythmiaModeAi };
typedef enum ArrhythmiaMode ArrhythmiaMode;


typedef struct {
    uint8_t inputSource;
    uint8_t bwNoiseLevel; // 0-100
    uint8_t maNoiseLevel; // 0-100
    uint8_t emNoiseLevel; // 0-100
    uint8_t speedMode;  // 0-1
    uint8_t denoiseMode; // 0-2
    uint8_t segMode;  // 0-2
    uint8_t arrMode;  // 0-2
} app_state_t;

///////////////////////////////////////////////////////////////////////////////
// EVB Configuration
///////////////////////////////////////////////////////////////////////////////

extern ns_power_config_t nsPwrCfg;
extern ns_core_config_t nsCoreCfg;
extern ns_i2c_config_t nsI2cCfg;
extern ns_button_config_t nsBtnCfg;


///////////////////////////////////////////////////////////////////////////////
// Sensor Configuration
///////////////////////////////////////////////////////////////////////////////

extern sensor_context_t sensorCtx;
extern rb_config_t rbEcgSensor;


///////////////////////////////////////////////////////////////////////////////
// Preprocess Configuration
///////////////////////////////////////////////////////////////////////////////

extern arm_biquad_casd_df1_inst_f32 ecgFilterCtx;


///////////////////////////////////////////////////////////////////////////////
// ECG Denoise Configuration
///////////////////////////////////////////////////////////////////////////////

extern float32_t ecgDenScratch[ECG_DEN_WINDOW_LEN];
extern float32_t ecgDenInout[ECG_DEN_WINDOW_LEN];
extern float32_t ecgDenNoise[ECG_DEN_WINDOW_LEN];
extern rb_config_t rbEcgDen;


///////////////////////////////////////////////////////////////////////////////
// ECG Arrhythmia Configuration
///////////////////////////////////////////////////////////////////////////////

extern float32_t ecgArrScratch[ECG_ARR_WINDOW_LEN];
extern float32_t ecgArrInout[ECG_ARR_WINDOW_LEN];

///////////////////////////////////////////////////////////////////////////////
// ECG Segmentation Configuration
///////////////////////////////////////////////////////////////////////////////

extern float32_t ecgSegScratch[ECG_SEG_WINDOW_LEN];
extern float32_t ecgSegInout[ECG_SEG_WINDOW_LEN];
extern uint16_t ecgSegMask[ECG_SEG_WINDOW_LEN];
extern rb_config_t rbEcgRawSeg;
extern rb_config_t rbEcgSeg;
extern ecg_peak_f32_t ecgPkPeakCtx;


///////////////////////////////////////////////////////////////////////////////
// Shared Metrics Configuration
///////////////////////////////////////////////////////////////////////////////

extern metrics_config_t metricsCfg;
extern uint32_t peaksMetrics[MAX_RR_PEAKS];
extern uint32_t rriMetrics[MAX_RR_PEAKS];
extern uint8_t rriMask[MAX_RR_PEAKS];


///////////////////////////////////////////////////////////////////////////////
// ECG Metrics Configuration
///////////////////////////////////////////////////////////////////////////////

extern rb_config_t rbEcgMet;
extern rb_config_t rbEcgMaskMet;

extern float32_t ecgMetData[ECG_MET_WINDOW_LEN];
extern uint16_t ecgMaskMetData[ECG_MET_WINDOW_LEN];

extern hrv_td_metrics_t ecgHrvMetrics;

extern metrics_app_results_t appMetResults;


///////////////////////////////////////////////////////////////////////////////
// TILEIO Configuration
///////////////////////////////////////////////////////////////////////////////

extern rb_config_t rbEcgRawTx;
extern rb_config_t rbEcgDenTx;
extern uint16_t ecgMaskTxBuffer[ECG_TX_BUF_LEN];
extern rb_config_t rbEcgMaskTx;

///////////////////////////////////////////////////////////////////////////////
// APP Configuration
///////////////////////////////////////////////////////////////////////////////

// extern uint8_t LED_COLORS[10][4];
extern ns_timer_config_t timerCfg;
extern ns_timer_config_t timer2Cfg;
extern app_state_t appState;

#ifdef __cplusplus
}
#endif

#endif // __APP_STORE_H
