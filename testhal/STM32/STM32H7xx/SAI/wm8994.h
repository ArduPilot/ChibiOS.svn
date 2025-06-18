/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    wm8994.h
 * @brief   WM8994 interface module header.
 *
 * @author  Edoardo Lombardi
 *
 * @addtogroup WM8994
 * @ingroup AUDIO
 * @{
 */

#ifndef WM8994_H
#define WM8994_H

/******************************************************************************/
/***************************  Codec User defines ******************************/
/******************************************************************************/
/* Codec output DEVICE */
#define OUTPUT_DEVICE_SPEAKER                 ((uint16_t)0x0001)
#define OUTPUT_DEVICE_HEADPHONE               ((uint16_t)0x0002)
#define OUTPUT_DEVICE_BOTH                    ((uint16_t)0x0003)
#define OUTPUT_DEVICE_AUTO                    ((uint16_t)0x0004)
#define INPUT_DEVICE_DIGITAL_MICROPHONE_1     ((uint16_t)0x0100)
#define INPUT_DEVICE_DIGITAL_MICROPHONE_2     ((uint16_t)0x0200)
#define INPUT_DEVICE_INPUT_LINE_1             ((uint16_t)0x0300)
#define INPUT_DEVICE_INPUT_LINE_2             ((uint16_t)0x0400)
#define INPUT_DEVICE_DIGITAL_MIC1_MIC2        ((uint16_t)0x0800)

/* Volume Levels values */
#define DEFAULT_VOLMIN                0x00
#define DEFAULT_VOLMAX                0xFF
#define DEFAULT_VOLSTEP               0x04

#define AUDIO_PAUSE                   0
#define AUDIO_RESUME                  1

/* Codec POWER DOWN modes */
#define CODEC_PDWN_HW                 1
#define CODEC_PDWN_SW                 2

/* MUTE commands */
#define AUDIO_MUTE_ON                 1
#define AUDIO_MUTE_OFF                0

/* AUDIO FREQUENCY */
#define AUDIO_FREQUENCY_192K          ((uint32_t)192000)
#define AUDIO_FREQUENCY_96K           ((uint32_t)96000)
#define AUDIO_FREQUENCY_48K           ((uint32_t)48000)
#define AUDIO_FREQUENCY_44K           ((uint32_t)44100)
#define AUDIO_FREQUENCY_32K           ((uint32_t)32000)
#define AUDIO_FREQUENCY_22K           ((uint32_t)22050)
#define AUDIO_FREQUENCY_16K           ((uint32_t)16000)
#define AUDIO_FREQUENCY_11K           ((uint32_t)11025)
#define AUDIO_FREQUENCY_8K            ((uint32_t)8000)

#define VOLUME_CONVERT(Volume)        (((Volume) > 100)? 100:((uint8_t)(((Volume) * 63) / 100)))
#define VOLUME_IN_CONVERT(Volume)     (((Volume) >= 100)? 239:((uint8_t)(((Volume) * 240) / 100)))

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/
#define WM8994_ADDR                   0x1A

/* SW Reset */
#define WM8994_SW_RESET               (uint16_t)0x0000

/* Power Management */
#define WM8994_PWR_MANAGEMENT_1       (uint16_t)0x0001
#define WM8994_PWR_MANAGEMENT_2       (uint16_t)0x0002
#define WM8994_PWR_MANAGEMENT_3       (uint16_t)0x0003
#define WM8994_PWR_MANAGEMENT_4       (uint16_t)0x0004
#define WM8994_PWR_MANAGEMENT_5       (uint16_t)0x0005
#define WM8994_PWR_MANAGEMENT_6       (uint16_t)0x0006

/* Input mixer */
#define WM8994_INPUT_MIXER_1          (uint16_t)0x0015

/* Input volume */
#define WM8994_LEFT_LINE_IN12_VOL     (uint16_t)0x0018
#define WM8994_LEFT_LINE_IN34_VOL     (uint16_t)0x0019
#define WM8994_RIGHT_LINE_IN12_VOL    (uint16_t)0x001A
#define WM8994_RIGHT_LINE_IN34_VOL    (uint16_t)0x001B

/* L/R Output volumes */
#define WM8994_LEFT_OUTPUT_VOL        (uint16_t)0x001C
#define WM8994_RIGHT_OUTPUT_VOL       (uint16_t)0x001D
#define WM8994_LINE_OUTPUT_VOL        (uint16_t)0x001E
#define WM8994_OUTPUT2_VOL            (uint16_t)0x001F

/* L/R OPGA volumes */
#define WM8994_LEFT_OPGA_VOL          (uint16_t)0x0020
#define WM8994_RIGHT_OPGA_VOL         (uint16_t)0x0021

/* SPKMIXL/R Attenuation */
#define WM8994_SPKMIXL_ATT            (uint16_t)0x0022
#define WM8994_SPKMIXR_ATT            (uint16_t)0x0023
#define WM8994_OUTPUT_MIXER           (uint16_t)0x0024
#define WM8994_CLASS_D                (uint16_t)0x0025
/* L/R Speakers volumes */
#define WM8994_SPK_LEFT_VOL           (uint16_t)0x0026
#define WM8994_SPK_RIGHT_VOL          (uint16_t)0x0027

/* Input mixer */
#define WM8994_INPUT_MIXER_2          (uint16_t)0x0028
#define WM8994_INPUT_MIXER_3          (uint16_t)0x0029
#define WM8994_INPUT_MIXER_4          (uint16_t)0x002A
#define WM8994_INPUT_MIXER_5          (uint16_t)0x002B
#define WM8994_INPUT_MIXER_6          (uint16_t)0x002C

/* Output mixer */
#define WM8994_OUTPUT_MIXER_1         (uint16_t)0x002D
#define WM8994_OUTPUT_MIXER_2         (uint16_t)0x002E
#define WM8994_OUTPUT_MIXER_3         (uint16_t)0x002F
#define WM8994_OUTPUT_MIXER_4         (uint16_t)0x0030
#define WM8994_OUTPUT_MIXER_5         (uint16_t)0x0031
#define WM8994_OUTPUT_MIXER_6         (uint16_t)0x0032
#define WM8994_OUTPUT2_MIXER          (uint16_t)0x0033
#define WM8994_LINE_MIXER_1           (uint16_t)0x0034
#define WM8994_LINE_MIXER_2           (uint16_t)0x0035
#define WM8994_SPEAKER_MIXER          (uint16_t)0x0036
#define WM8994_ADD_CONTROL            (uint16_t)0x0037

/* Antipop */
#define WM8994_ANTIPOP1               (uint16_t)0x0038
#define WM8994_ANTIPOP2               (uint16_t)0x0039
#define WM8994_MICBIAS                (uint16_t)0x003A
#define WM8994_LDO1                   (uint16_t)0x003B
#define WM8994_LDO2                   (uint16_t)0x003C

/* Charge pump */
#define WM8994_CHARGE_PUMP1           (uint16_t)0x004C
#define WM8994_CHARGE_PUMP2           (uint16_t)0x004D

#define WM8994_CLASS_W                (uint16_t)0x0051

#define WM8994_DC_SERVO1              (uint16_t)0x0054
#define WM8994_DC_SERVO2              (uint16_t)0x0055
#define WM8994_DC_SERVO_READBACK      (uint16_t)0x0058
#define WM8994_DC_SERVO_WRITEVAL      (uint16_t)0x0059

/* Analog HP */
#define WM8994_ANALOG_HP              (uint16_t)0x0060

#define WM8994_CHIP_REVISION          (uint16_t)0x0100
#define WM8994_CONTROL_INTERFACE      (uint16_t)0x0101
#define WM8994_WRITE_SEQ_CTRL1        (uint16_t)0x0110
#define WM8994_WRITE_SEQ_CTRL2        (uint16_t)0x0111

/* WM8994 clocking */
#define WM8994_AIF1_CLOCKING1         (uint16_t)0x0200
#define WM8994_AIF1_CLOCKING2         (uint16_t)0x0201
#define WM8994_AIF2_CLOCKING1         (uint16_t)0x0204
#define WM8994_AIF2_CLOCKING2         (uint16_t)0x0205
#define WM8994_CLOCKING1              (uint16_t)0x0208
#define WM8994_CLOCKING2              (uint16_t)0x0209
#define WM8994_AIF1_RATE              (uint16_t)0x0210
#define WM8994_AIF2_RATE              (uint16_t)0x0211
#define WM8994_RATE_STATUS            (uint16_t)0x0212

/* FLL1 Control */
#define WM8994_FLL1_CONTROL1          (uint16_t)0x0220
#define WM8994_FLL1_CONTROL2          (uint16_t)0x0221
#define WM8994_FLL1_CONTROL3          (uint16_t)0x0222
#define WM8994_FLL1_CONTROL4          (uint16_t)0x0223
#define WM8994_FLL1_CONTROL5          (uint16_t)0x0224

/* FLL2 Control */
#define WM8994_FLL2_CONTROL1          (uint16_t)0x0240
#define WM8994_FLL2_CONTROL2          (uint16_t)0x0241
#define WM8994_FLL2_CONTROL3          (uint16_t)0x0242
#define WM8994_FLL2_CONTROL4          (uint16_t)0x0243
#define WM8994_FLL2_CONTROL5          (uint16_t)0x0244

/* AIF1 control */
#define WM8994_AIF1_CONTROL1          (uint16_t)0x0300
#define WM8994_AIF1_CONTROL2          (uint16_t)0x0301
#define WM8994_AIF1_MASTER_SLAVE      (uint16_t)0x0302
#define WM8994_AIF1_BCLK              (uint16_t)0x0303
#define WM8994_AIF1_ADC_LRCLK         (uint16_t)0x0304
#define WM8994_AIF1_DAC_LRCLK         (uint16_t)0x0305
#define WM8994_AIF1_DAC_DELTA         (uint16_t)0x0306
#define WM8994_AIF1_ADC_DELTA         (uint16_t)0x0307

/* AIF2 control */
#define WM8994_AIF2_CONTROL1          (uint16_t)0x0310
#define WM8994_AIF2_CONTROL2          (uint16_t)0x0311
#define WM8994_AIF2_MASTER_SLAVE      (uint16_t)0x0312
#define WM8994_AIF2_BCLK              (uint16_t)0x0313
#define WM8994_AIF2_ADC_LRCLK         (uint16_t)0x0314
#define WM8994_AIF2_DAC_LRCLK         (uint16_t)0x0315
#define WM8994_AIF2_DAC_DELTA         (uint16_t)0x0316
#define WM8994_AIF2_ADC_DELTA         (uint16_t)0x0317

/* AIF1 ADC/DAC LR volumes */
#define WM8994_AIF1_ADC1_LEFT_VOL     (uint16_t)0x0400
#define WM8994_AIF1_ADC1_RIGHT_VOL    (uint16_t)0x0401
#define WM8994_AIF1_DAC1_LEFT_VOL     (uint16_t)0x0402
#define WM8994_AIF1_DAC1_RIGHT_VOL    (uint16_t)0x0403
#define WM8994_AIF1_ADC2_LEFT_VOL     (uint16_t)0x0404
#define WM8994_AIF1_ADC2_RIGHT_VOL    (uint16_t)0x0405
#define WM8994_AIF1_DAC2_LEFT_VOL     (uint16_t)0x0406
#define WM8994_AIF1_DAC2_RIGHT_VOL    (uint16_t)0x0407

/* AIF1 ADC/DAC filters */
#define WM8994_AIF1_ADC1_FILTERS      (uint16_t)0x0410
#define WM8994_AIF1_ADC2_FILTERS      (uint16_t)0x0411
#define WM8994_AIF1_DAC1_FILTER1      (uint16_t)0x0420
#define WM8994_AIF1_DAC1_FILTER2      (uint16_t)0x0421
#define WM8994_AIF1_DAC2_FILTER1      (uint16_t)0x0422
#define WM8994_AIF1_DAC2_FILTER2      (uint16_t)0x0423

/* AIF1 DRC1 registers */
#define WM8994_AIF1_DRC1              (uint16_t)0x0440
#define WM8994_AIF1_DRC1_1            (uint16_t)0x0441
#define WM8994_AIF1_DRC1_2            (uint16_t)0x0442
#define WM8994_AIF1_DRC1_3            (uint16_t)0x0443
#define WM8994_AIF1_DRC1_4            (uint16_t)0x0444

/* AIF1 DRC2 registers */
#define WM8994_AIF1_DRC2              (uint16_t)0x0450
#define WM8994_AIF1_DRC2_1            (uint16_t)0x0451
#define WM8994_AIF1_DRC2_2            (uint16_t)0x0452
#define WM8994_AIF1_DRC2_3            (uint16_t)0x0453
#define WM8994_AIF1_DRC2_4            (uint16_t)0x0454

/* AIF1 DAC1 EQ Gains Bands */
#define WM8994_AIF1_DAC1_EQG_1        (uint16_t)0x0480
#define WM8994_AIF1_DAC1_EQG_2        (uint16_t)0x0481
#define WM8994_AIF1_DAC1_EQG_1A       (uint16_t)0x0482
#define WM8994_AIF1_DAC1_EQG_1B       (uint16_t)0x0483
#define WM8994_AIF1_DAC1_EQG_1PG      (uint16_t)0x0484
#define WM8994_AIF1_DAC1_EQG_2A       (uint16_t)0x0485
#define WM8994_AIF1_DAC1_EQG_2B       (uint16_t)0x0486
#define WM8994_AIF1_DAC1_EQG_2C       (uint16_t)0x0487
#define WM8994_AIF1_DAC1_EQG_2PG      (uint16_t)0x0488
#define WM8994_AIF1_DAC1_EQG_3A       (uint16_t)0x0489
#define WM8994_AIF1_DAC1_EQG_3B       (uint16_t)0x048A
#define WM8994_AIF1_DAC1_EQG_3C       (uint16_t)0x048B
#define WM8994_AIF1_DAC1_EQG_3PG      (uint16_t)0x048C
#define WM8994_AIF1_DAC1_EQG_4A       (uint16_t)0x048D
#define WM8994_AIF1_DAC1_EQG_4B       (uint16_t)0x048E
#define WM8994_AIF1_DAC1_EQG_4C       (uint16_t)0x048F
#define WM8994_AIF1_DAC1_EQG_4PG      (uint16_t)0x0490
#define WM8994_AIF1_DAC1_EQG_5A       (uint16_t)0x0491
#define WM8994_AIF1_DAC1_EQG_5B       (uint16_t)0x0492
#define WM8994_AIF1_DAC1_EQG_5PG      (uint16_t)0x0493

/* AIF1 DAC2 EQ Gains/bands */
#define WM8994_AIF1_DAC2_EQG_1        (uint16_t)0x04A0
#define WM8994_AIF1_DAC2_EQG_2        (uint16_t)0x04A1
#define WM8994_AIF1_DAC2_EQG_1A       (uint16_t)0x04A2
#define WM8994_AIF1_DAC2_EQG_1B       (uint16_t)0x04A3
#define WM8994_AIF1_DAC2_EQG_1PG      (uint16_t)0x04A4
#define WM8994_AIF1_DAC2_EQG_2A       (uint16_t)0x04A5
#define WM8994_AIF1_DAC2_EQG_2B       (uint16_t)0x04A6
#define WM8994_AIF1_DAC2_EQG_2C       (uint16_t)0x04A7
#define WM8994_AIF1_DAC2_EQG_2PG      (uint16_t)0x04A8
#define WM8994_AIF1_DAC2_EQG_3A       (uint16_t)0x04A9
#define WM8994_AIF1_DAC2_EQG_3B       (uint16_t)0x04AA
#define WM8994_AIF1_DAC2_EQG_3C       (uint16_t)0x04AB
#define WM8994_AIF1_DAC2_EQG_3PG      (uint16_t)0x04AC
#define WM8994_AIF1_DAC2_EQG_4A       (uint16_t)0x04AD
#define WM8994_AIF1_DAC2_EQG_4B       (uint16_t)0x04AE
#define WM8994_AIF1_DAC2_EQG_4C       (uint16_t)0x04AF
#define WM8994_AIF1_DAC2_EQG_4PG      (uint16_t)0x04B0
#define WM8994_AIF1_DAC2_EQG_5A       (uint16_t)0x04B1
#define WM8994_AIF1_DAC2_EQG_5B       (uint16_t)0x04B2
#define WM8994_AIF1_DAC2_EQG_5PG      (uint16_t)0x04B3

/* AIF2 ADC/DAC LR volumes */
#define WM8994_AIF2_ADC_LEFT_VOL      (uint16_t)0x0500
#define WM8994_AIF2_ADC_RIGHT_VOL     (uint16_t)0x0501
#define WM8994_AIF2_DAC_LEFT_VOL      (uint16_t)0x0502
#define WM8994_AIF2_DAC_RIGHT_VOL     (uint16_t)0x0503

/* AIF2 ADC/DAC filters */
#define WM8994_AIF2_ADC_FILTERS       (uint16_t)0x0510
#define WM8994_AIF2_DAC_FILTER_1      (uint16_t)0x0520
#define WM8994_AIF2_DAC_FILTER_2      (uint16_t)0x0521

/* AIF2 DRC registers */
#define WM8994_AIF2_DRC_1             (uint16_t)0x0540
#define WM8994_AIF2_DRC_2             (uint16_t)0x0541
#define WM8994_AIF2_DRC_3             (uint16_t)0x0542
#define WM8994_AIF2_DRC_4             (uint16_t)0x0543
#define WM8994_AIF2_DRC_5             (uint16_t)0x0544

/* AIF2 EQ Gains/bands */
#define WM8994_AIF2_EQG_1             (uint16_t)0x0580
#define WM8994_AIF2_EQG_2             (uint16_t)0x0581
#define WM8994_AIF2_EQG_1A            (uint16_t)0x0582
#define WM8994_AIF2_EQG_1B            (uint16_t)0x0583
#define WM8994_AIF2_EQG_1PG           (uint16_t)0x0584
#define WM8994_AIF2_EQG_2A            (uint16_t)0x0585
#define WM8994_AIF2_EQG_2B            (uint16_t)0x0586
#define WM8994_AIF2_EQG_2C            (uint16_t)0x0587
#define WM8994_AIF2_EQG_2PG           (uint16_t)0x0588
#define WM8994_AIF2_EQG_3A            (uint16_t)0x0589
#define WM8994_AIF2_EQG_3B            (uint16_t)0x058A
#define WM8994_AIF2_EQG_3C            (uint16_t)0x058B
#define WM8994_AIF2_EQG_3PG           (uint16_t)0x058C
#define WM8994_AIF2_EQG_4A            (uint16_t)0x058D
#define WM8994_AIF2_EQG_4B            (uint16_t)0x058E
#define WM8994_AIF2_EQG_4C            (uint16_t)0x058F
#define WM8994_AIF2_EQG_4PG           (uint16_t)0x0590
#define WM8994_AIF2_EQG_5A            (uint16_t)0x0591
#define WM8994_AIF2_EQG_5B            (uint16_t)0x0592
#define WM8994_AIF2_EQG_5PG           (uint16_t)0x0593

/* AIF1 DAC1 Mixer volume */
#define WM8994_DAC1_MIXER_VOL         (uint16_t)0x0600
/* AIF1 DAC1 Left Mixer Routing */
#define WM8994_AIF1_DAC1_LMR          (uint16_t)0x0601
/* AIF1 DAC1 Righ Mixer Routing */
#define WM8994_AIF1_DAC1_RMR          (uint16_t)0x0602
/* AIF1 DAC2 Mixer volume */
#define WM8994_DAC2_MIXER_VOL         (uint16_t)0x0603
/* AIF1 DAC2 Left Mixer Routing */
#define WM8994_AIF1_DAC2_LMR          (uint16_t)0x0604
/* AIF1 DAC2 Righ Mixer Routing */
#define WM8994_AIF1_DAC2_RMR          (uint16_t)0x0605
/* AIF1 ADC1 Left Mixer Routing */
#define WM8994_AIF1_ADC1_LMR          (uint16_t)0x0606
/* AIF1 ADC1 Righ Mixer Routing */
#define WM8994_AIF1_ADC1_RMR          (uint16_t)0x0607
/* AIF1 ADC2 Left Mixer Routing */
#define WM8994_AIF1_ADC2_LMR          (uint16_t)0x0608
/* AIF1 ADC2 Righ Mixer Routing */
#define WM8994_AIF1_ADC2_RMR          (uint16_t)0x0609

/* Volume control */
#define WM8994_DAC1_LEFT_VOL          (uint16_t)0x0610
#define WM8994_DAC1_RIGHT_VOL         (uint16_t)0x0611
#define WM8994_DAC2_LEFT_VOL          (uint16_t)0x0612
#define WM8994_DAC2_RIGHT_VOL         (uint16_t)0x0613
#define WM8994_DAC_SOFTMUTE           (uint16_t)0x0614

#define WM8994_OVERSAMPLING           (uint16_t)0x0620
#define WM8994_SIDETONE               (uint16_t)0x0621

/* GPIO */
#define WM8994_GPIO1                  (uint16_t)0x0700
#define WM8994_GPIO2                  (uint16_t)0x0701
#define WM8994_GPIO3                  (uint16_t)0x0702
#define WM8994_GPIO4                  (uint16_t)0x0703
#define WM8994_GPIO5                  (uint16_t)0x0704
#define WM8994_GPIO6                  (uint16_t)0x0705
#define WM8994_GPIO7                  (uint16_t)0x0706
#define WM8994_GPIO8                  (uint16_t)0x0707
#define WM8994_GPIO9                  (uint16_t)0x0708
#define WM8994_GPIO10                 (uint16_t)0x0709
#define WM8994_GPIO11                 (uint16_t)0x070A

/* Pull Contol */
#define WM8994_PULL_CONTROL_1         (uint16_t)0x0720
#define WM8994_PULL_CONTROL_2         (uint16_t)0x0721

/* WM8994 Interrupts */
#define WM8994_INT_STATUS_1           (uint16_t)0x0730
#define WM8994_INT_STATUS_2           (uint16_t)0x0731
#define WM8994_INT_RAW_STATUS_2       (uint16_t)0x0732
#define WM8994_INT_STATUS1_MASK       (uint16_t)0x0738
#define WM8994_INT_STATUS2_MASK       (uint16_t)0x0739
#define WM8994_INT_CONTROL            (uint16_t)0x0740
#define WM8994_IRQ_DEBOUNCE           (uint16_t)0x0748

/* Write Sequencer registers from 0 to 511 */
#define WM8994_WRITE_SEQUENCER0       (uint16_t)0x3000
#define WM8994_WRITE_SEQUENCER1       (uint16_t)0x3001
#define WM8994_WRITE_SEQUENCER2       (uint16_t)0x3002
#define WM8994_WRITE_SEQUENCER3       (uint16_t)0x3003

#define WM8994_WRITE_SEQUENCER4       (uint16_t)0x3508
#define WM8994_WRITE_SEQUENCER5       (uint16_t)0x3509
#define WM8994_WRITE_SEQUENCER6       (uint16_t)0x3510
#define WM8994_WRITE_SEQUENCER7       (uint16_t)0x3511

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
msg_t wm8994Init (I2CDriver *i2cp);
#ifdef __cplusplus
}
#endif

#endif  /* WM8994_H */

/** @} */
