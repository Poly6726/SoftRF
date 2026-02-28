/*
 * Platform_nRF54.h
 * Copyright (C) 2026 Linar Yusupov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#if defined(ARDUINO_ARCH_NRF54L15CLEAN)

#ifndef PLATFORM_NRF54_H
#define PLATFORM_NRF54_H

//#include <avr/dtostrf.h>

/* Maximum of tracked flying objects is now SoC-specific constant */
#define MAX_TRACKING_OBJECTS    8

#define DEFAULT_SOFTRF_MODEL    SOFTRF_MODEL_ACADEMY

#define isValidFix()            isValidGNSSFix()

#define uni_begin()             strip.begin()
#define uni_show()              strip.show()
#define uni_setPixelColor(i, c) strip.setPixelColor(i, c)
#define uni_numPixels()         strip.numPixels()
#define uni_Color(r,g,b)        strip.Color(r,g,b)
#define color_t                 uint32_t

//#define PROGMEM
//#define PGM_P                   const char *
//#define PGM_VOID_P              const void *

//#define PSTR(s)                 (s)

//#define pgm_read_byte(addr)     (*(const unsigned char *)(addr))
//#define pgm_read_word(addr)     (*(const unsigned short *)(addr))

extern char *dtostrf_workaround(double, signed char, unsigned char, char *);
#define dtostrf                 dtostrf_workaround

#define snprintf_P              snprintf
#define EEPROM_commit()         {}

// State when LED is litted
#define LED_STATE_ON            LOW

#define SerialOutput            Serial
#define Serial_GNSS_In          Serial1
#define Serial_GNSS_Out         Serial_GNSS_In

enum rst_reason {
  REASON_DEFAULT_RST      = 0,  /* normal startup by power on */
  REASON_WDT_RST          = 1,  /* hardware watch dog reset */
  REASON_EXCEPTION_RST    = 2,  /* exception reset, GPIO status won't change */
  REASON_SOFT_WDT_RST     = 3,  /* software watch dog reset, GPIO status won't change */
  REASON_SOFT_RESTART     = 4,  /* software restart ,system_restart , GPIO status won't change */
  REASON_DEEP_SLEEP_AWAKE = 5,  /* wake up from deep-sleep */
  REASON_EXT_SYS_RST      = 6   /* external system reset */
};

enum nRF54_board_id {
  NRF54_SEEED_XIAO,
};

struct rst_info {
  uint32_t reason;
  uint32_t exccause;
  uint32_t epc1;
  uint32_t epc2;
  uint32_t epc3;
  uint32_t excvaddr;
  uint32_t depc;
};

#if !defined(_PINNUM)
#define _PINNUM(port, pin)    ((port)*32 + (pin))
#endif

/* Peripherals */
#define SOC_GPIO_PIN_CONS_RX            _PINNUM(1, 8)  // D19, P1.08 +
#define SOC_GPIO_PIN_CONS_TX            _PINNUM(1, 9)  // D18, P1.09 +

#define SOC_GPIO_PIN_GNSS_RX            _PINNUM(2, 8)  // D7,  P2.08 +
#define SOC_GPIO_PIN_GNSS_TX            _PINNUM(2, 7)  // D6,  P2.07 +
#define SOC_GPIO_PIN_GNSS_PPS           _PINNUM(2, 10) // D13, P2.10 +

/* SPI */
#define SOC_GPIO_PIN_MOSI               _PINNUM(2, 2)  // D10, P2.02 +
#define SOC_GPIO_PIN_MISO               _PINNUM(2, 4)  // D9,  P2.04 +
#define SOC_GPIO_PIN_SCK                _PINNUM(2, 6)  // D8,  P2.06 +
#define SOC_GPIO_PIN_SS                 _PINNUM(1, 7)  // D3,  P1.07 +

/* LR2021 */
#define SOC_GPIO_PIN_RST                _PINNUM(1, 6)  // D2,  P1.06 +
#define SOC_GPIO_PIN_DIO7               _PINNUM(2, 7)  // D6,  P2.07 +
#define SOC_GPIO_PIN_DIO8               _PINNUM(1, 4)  // D0,  P1.04 +
#define SOC_GPIO_PIN_DIO11              _PINNUM(2, 8)  // D7,  P2.08 +
#define SOC_GPIO_PIN_BUSY               _PINNUM(1, 5)  // D1,  P1.05 +

/* I2C */
#define SOC_GPIO_PIN_SDA                _PINNUM(1, 11) // D4,  P1.11 +
#define SOC_GPIO_PIN_SCL                _PINNUM(1, 12) // D5,  P1.12 +

/* NFC */
#define SOC_GPIO_PIN_NFC_ANT1           _PINNUM(1,  2) // P1.02 +
#define SOC_GPIO_PIN_NFC_ANT2           _PINNUM(1,  3) // P1.03 +

/* antenna switch */
#define SOC_GPIO_PIN_ANT_SW             _PINNUM(2,  5) // P2.05 +

#define SOC_GPIO_PIN_STATUS             _PINNUM(2,  0) // D16, P2.00 +
#define SOC_GPIO_PIN_BUTTON             _PINNUM(0,  0) // D17, P0.00 +
#define SOC_GPIO_PIN_BUZZER             SOC_UNUSED_PIN

#define EXCLUDE_EEPROM
#define EXCLUDE_WIFI
#define EXCLUDE_ETHERNET

#define EXCLUDE_CC13XX
#define EXCLUDE_TEST_MODE
#define EXCLUDE_SOFTRF_HEARTBEAT
#define EXCLUDE_LK8EX1

//#define EXCLUDE_GNSS_UBLOX
#define EXCLUDE_GNSS_SONY
#define EXCLUDE_GNSS_MTK
#define EXCLUDE_GNSS_GOKE     /* 'Air530' GK9501 GPS/GLO/BDS (GAL inop.) */
#define EXCLUDE_GNSS_AT65     /* Quectel L76K */
#define EXCLUDE_GNSS_UC65
#define EXCLUDE_GNSS_AG33

/* Component                         Cost */
/* -------------------------------------- */
//#define USE_NMEALIB            //  +  8 kb
#define USE_NMEA_CFG             //  +    kb
//#define USE_SKYVIEW_CFG        //  +    kb
#define EXCLUDE_BMP180           //  -    kb
//#define EXCLUDE_BMP280         //  -    kb
#define EXCLUDE_BME680           //  -    kb
#define EXCLUDE_BME280AUX        //  -    kb
#define EXCLUDE_MPL3115A2        //  -    kb
#define EXCLUDE_NRF905           //  -    kb
#define EXCLUDE_MAVLINK          //  -    kb
#define EXCLUDE_UATM             //  -    kb
#define EXCLUDE_EGM96            //  - 16 kb
#define EXCLUDE_LED_RING         //  -    kb

#define USE_BASICMAC
//#define EXCLUDE_SX1276         //  -  3 kb

#define USE_TIME_SLOTS

/* Experimental */
//#define USE_WEBUSB_SERIAL
//#define USE_WEBUSB_SETTINGS
//#define USE_USB_MIDI
//#define USE_PWM_SOUND
//#define USE_GDL90_MSL
//#define USE_IBEACON
#define EXCLUDE_NUS
#define EXCLUDE_IMU
#define USE_OGN_ENCRYPTION
#define ENABLE_ADSL
#define ENABLE_PROL

#define USE_RADIOLIB
#define EXCLUDE_LR11XX
//#define EXCLUDE_LR20XX
#define EXCLUDE_CC1101
#define EXCLUDE_SI443X
#define EXCLUDE_SI446X
#define EXCLUDE_SX1231
#define EXCLUDE_SX1280
//#define ENABLE_RECORDER
//#define EXCLUDE_BLUETOOTH
#define EXCLUDE_BHI260

/* FTD-012 data port protocol version 8 and 9 */
#define PFLAA_EXT1_FMT  ",%d,%d,%d"
#define PFLAA_EXT1_ARGS ,Container[i].no_track,data_source,Container[i].rssi

#endif /* PLATFORM_NRF54_H */
#endif /* ARDUINO_ARCH_NRF54L15CLEAN */
