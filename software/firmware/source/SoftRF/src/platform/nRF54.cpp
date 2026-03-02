/*
 * Platform_nRF54.cpp
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

#include <SPI.h>
#include <Wire.h>

//#include <ArduinoJson.h>

#include "../system/SoC.h"
#include "../driver/RF.h"
#include "../driver/EEPROM.h"
#include "../driver/GNSS.h"
#include "../driver/Baro.h"
#include "../driver/LED.h"
#include "../driver/Bluetooth.h"
#include "../driver/EPD.h"
#include "../driver/Battery.h"
#include "../driver/Sound.h"
#include "../protocol/data/NMEA.h"
#include "../protocol/data/GDL90.h"
#include "../protocol/data/D1090.h"
//#include "../protocol/data/JSON.h"
#include "../system/Time.h"

#if defined(USE_OLED)
#include "../driver/OLED.h"
#endif /* USE_OLED */

// RFM95W pin mapping
lmic_pinmap lmic_pins = {
    .nss = LMIC_UNUSED_PIN,
    .txe = LMIC_UNUSED_PIN,
    .rxe = LMIC_UNUSED_PIN,
    .rst = LMIC_UNUSED_PIN,
    .dio = {LMIC_UNUSED_PIN, LMIC_UNUSED_PIN, LMIC_UNUSED_PIN},
    .busy = LMIC_UNUSED_PIN,
    .tcxo = LMIC_UNUSED_PIN,
};

static struct rst_info reset_info = {
  .reason = REASON_DEFAULT_RST,
};

static uint32_t bootCount __attribute__ ((section (".noinit")));

static nRF54_board_id nRF54_board = NRF54_LR2021EVK1XCS1; /* default */

const char *nRF54_Device_Manufacturer = SOFTRF_IDENT;
const char *nRF54_Device_Model = "Academy Edition";

#if defined(EXCLUDE_EEPROM)
eeprom_t eeprom_block;
settings_t *settings = &eeprom_block.field.settings;
#endif /* EXCLUDE_EEPROM */

#if defined(EXCLUDE_WIFI)
char UDPpacketBuffer[256]; // Dummy definition to satisfy build sequence
#endif /* EXCLUDE_WIFI */

char *dtostrf_workaround(double number, signed char width, unsigned char prec, char *s) {
    bool negative = false;

    if (isnan(number)) {
        strcpy(s, "nan");
        return s;
    }
    if (isinf(number)) {
        strcpy(s, "inf");
        return s;
    }

    char* out = s;

    int fillme = width; // how many cells to fill for the integer part
    if (prec > 0) {
        fillme -= (prec+1);
    }

    // Handle negative numbers
    if (number < 0.0) {
        negative = true;
        fillme--;
        number = -number;
    }

    // Round correctly so that print(1.999, 2) prints as "2.00"
    // I optimized out most of the divisions
    double rounding = 2.0;
    for (uint8_t i = 0; i < prec; ++i)
        rounding *= 10.0;
    rounding = 1.0 / rounding;

    number += rounding;

    // Figure out how big our number really is
    double tenpow = 1.0;
    int digitcount = 1;
    while (number >= 10.0 * tenpow) {
        tenpow *= 10.0;
        digitcount++;
    }

    number /= tenpow;
    fillme -= digitcount;

    // Pad unused cells with spaces
    while (fillme-- > 0) {
        *out++ = ' ';
    }

    // Handle negative sign
    if (negative) *out++ = '-';

    // Print the digits, and if necessary, the decimal point
    digitcount += prec;
    int8_t digit = 0;
    while (digitcount-- > 0) {
        digit = (int8_t)number;
        if (digit > 9) digit = 9; // insurance
        *out++ = (char)('0' | digit);
        if ((digitcount == prec) && (prec > 0)) {
            *out++ = '.';
        }
        number -= digit;
        number *= 10.0;
    }

    // make sure the string is terminated
    *out = 0;
    return s;
}

static void nRF54_setup()
{
  switch (nRF54_board)
  {
    case NRF54_LR2021EVK1XCS1:
    default:
      lmic_pins.nss  = SOC_GPIO_PIN_EVK_SS;
      lmic_pins.rst  = SOC_GPIO_PIN_EVK_RST;
      lmic_pins.busy = SOC_GPIO_PIN_EVK_BUSY;
#if defined(USE_RADIOLIB)
      lmic_pins.dio[0] = SOC_GPIO_PIN_EVK_DIO8;
#endif /* USE_RADIOLIB */
      break;
  }
}

static void nRF54_post_init()
{

}

static void nRF54_loop()
{

}

static void nRF54_fini(int reason)
{

}

static void nRF54_reset()
{

}

static uint32_t nRF54_getChipId()
{
  return 0;
}

static void* nRF54_getResetInfoPtr()
{
  return (void *) &reset_info;
}

static String nRF54_getResetInfo()
{
  switch (reset_info.reason)
  {
    default                     : return F("No reset information available");
  }
}

static String nRF54_getResetReason()
{
  switch (reset_info.reason)
  {
    case REASON_DEFAULT_RST       : return F("DEFAULT");
    case REASON_WDT_RST           : return F("WDT");
    case REASON_EXCEPTION_RST     : return F("EXCEPTION");
    case REASON_SOFT_WDT_RST      : return F("SOFT_WDT");
    case REASON_SOFT_RESTART      : return F("SOFT_RESTART");
    case REASON_DEEP_SLEEP_AWAKE  : return F("DEEP_SLEEP_AWAKE");
    case REASON_EXT_SYS_RST       : return F("EXT_SYS");
    default                       : return F("NO_MEAN");
  }
}

static uint32_t nRF54_getFreeHeap()
{
  return 0; /* TBD */
}

static long nRF54_random(long howsmall, long howBig)
{
  return random(howsmall, howBig);
}


static void nRF54_Sound_test(int var)
{

}

static void nRF54_Sound_tone(int hz, uint8_t volume)
{

}

static void nRF54_WiFi_set_param(int ndx, int value)
{
  /* NONE */
}

static void nRF54_WiFi_transmit_UDP(int port, byte *buf, size_t size)
{
  /* NONE */
}

static bool nRF54_EEPROM_begin(size_t size)
{
#if !defined(EXCLUDE_EEPROM)
  if (size > EEPROM.length()) {
    return false;
  }

  EEPROM.begin();
#endif /* EXCLUDE_EEPROM */

  return true;
}

static void nRF54_EEPROM_extension(int cmd)
{

}

static void nRF54_SPI_begin()
{
  switch (nRF54_board)
  {
    case NRF54_LR2021EVK1XCS1:
    default:
      SPI.begin(SOC_GPIO_PIN_EVK_SS);
      break;
  }
}

static void nRF54_swSer_begin(unsigned long baud)
{
  Serial_GNSS_In.begin(baud);
}

static void nRF54_swSer_enableRx(boolean arg)
{
  /* NONE */
}

static byte nRF54_Display_setup()
{
  byte rval = DISPLAY_NONE;

  if (nRF54_board == NRF54_LR2021EVK1XCS1) {
#if defined(USE_OLED)
    rval = OLED_setup();
#endif /* USE_OLED */
  }

  return rval;
}

static void nRF54_Display_loop()
{
  switch (hw_info.display)
  {
#if defined(USE_OLED)
  case DISPLAY_OLED_1_3:
  case DISPLAY_OLED_TTGO:
  case DISPLAY_OLED_HELTEC:
    OLED_loop();
    break;
#endif /* USE_OLED */

  case DISPLAY_NONE:
  default:
    break;
  }
}

static void nRF54_Display_fini(int reason)
{
  switch (hw_info.display)
  {
#if defined(USE_OLED)
  case DISPLAY_OLED_1_3:
  case DISPLAY_OLED_TTGO:
  case DISPLAY_OLED_HELTEC:
    OLED_fini(reason);
    break;
#endif /* USE_OLED */

  case DISPLAY_NONE:
  default:
    break;
  }
}

static void nRF54_Battery_setup()
{

}

static float nRF54_Battery_param(uint8_t param)
{
  float rval = 0;

  return rval;
}

void nRF54_GNSS_PPS_Interrupt_handler() {
  PPS_TimeMarker = millis();
}

static unsigned long nRF54_get_PPS_TimeMarker() {
  return PPS_TimeMarker;
}

static bool nRF54_Baro_setup() {
  return false;
}

static void nRF54_UATSerial_begin(unsigned long baud)
{

}

static void nRF54_UATModule_restart()
{

}

static void nRF54_WDT_setup()
{

}

static void nRF54_WDT_fini()
{

}

static void nRF54_Button_setup()
{

}

static void nRF54_Button_loop()
{

}

static void nRF54_Button_fini()
{

}

static bool nRF54_ADB_setup()
{
  return false;
}

static bool nRF54_ADB_fini()
{
  return false;
}

/*
 * One aircraft CDB (20000+ records) query takes:
 * 1)     FOUND : 5-7 milliseconds
 * 2) NOT FOUND :   3 milliseconds
 */
static bool nRF54_ADB_query(uint8_t type, uint32_t id, char *buf, size_t size)
{
  return false;
}

DB_ops_t nRF54_ADB_ops = {
  nRF54_ADB_setup,
  nRF54_ADB_fini,
  nRF54_ADB_query
};

const SoC_ops_t nRF54_ops = {
  SOC_NRF54,
  "nRF54",
  nRF54_setup,
  nRF54_post_init,
  nRF54_loop,
  nRF54_fini,
  nRF54_reset,
  nRF54_getChipId,
  nRF54_getResetInfoPtr,
  nRF54_getResetInfo,
  nRF54_getResetReason,
  nRF54_getFreeHeap,
  nRF54_random,
  nRF54_Sound_test,
  nRF54_Sound_tone,
  NULL,
  nRF54_WiFi_set_param,
  nRF54_WiFi_transmit_UDP,
  NULL,
  NULL,
  NULL,
  nRF54_EEPROM_begin,
  nRF54_EEPROM_extension,
  nRF54_SPI_begin,
  nRF54_swSer_begin,
  nRF54_swSer_enableRx,
  NULL,
  NULL,
  NULL,
  nRF54_Display_setup,
  nRF54_Display_loop,
  nRF54_Display_fini,
  nRF54_Battery_setup,
  nRF54_Battery_param,
  nRF54_GNSS_PPS_Interrupt_handler,
  nRF54_get_PPS_TimeMarker,
  nRF54_Baro_setup,
  nRF54_UATSerial_begin,
  nRF54_UATModule_restart,
  nRF54_WDT_setup,
  nRF54_WDT_fini,
  nRF54_Button_setup,
  nRF54_Button_loop,
  nRF54_Button_fini,
  &nRF54_ADB_ops
};

#endif /* ARDUINO_ARCH_NRF54L15CLEAN */
