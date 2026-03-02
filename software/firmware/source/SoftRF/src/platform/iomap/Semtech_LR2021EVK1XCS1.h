/* Seeed & Semtech LR2021 LoRa Plus™ Evaluation Kit */

/* Peripherals */
#define SOC_GPIO_PIN_CONS_EVK_RX        _PINNUM(1, 8)  // D19, P1.08 +
#define SOC_GPIO_PIN_CONS_EVK_TX        _PINNUM(1, 9)  // D18, P1.09 +

#define SOC_GPIO_PIN_GNSS_EVK_RX        _PINNUM(2, 8)  // D7,  P2.08 +
#define SOC_GPIO_PIN_GNSS_EVK_TX        _PINNUM(2, 7)  // D6,  P2.07 +
#define SOC_GPIO_PIN_GNSS_EVK_PPS       _PINNUM(2, 10) // D13, P2.10 +

/* SPI */
#define SOC_GPIO_PIN_EVK_MOSI           _PINNUM(2, 2)  // D10, P2.02 +
#define SOC_GPIO_PIN_EVK_MISO           _PINNUM(2, 4)  // D9,  P2.04 +
#define SOC_GPIO_PIN_EVK_SCK            _PINNUM(2, 6)  // D8,  P2.06 +
#define SOC_GPIO_PIN_EVK_SS             _PINNUM(1, 7)  // D3,  P1.07 +

/* LR2021 */
#define SOC_GPIO_PIN_EVK_RST            _PINNUM(1, 6)  // D2,  P1.06 +
#define SOC_GPIO_PIN_EVK_DIO7           _PINNUM(2, 7)  // D6,  P2.07 +
#define SOC_GPIO_PIN_EVK_DIO8           _PINNUM(1, 4)  // D0,  P1.04 +
#define SOC_GPIO_PIN_EVK_DIO11          _PINNUM(2, 8)  // D7,  P2.08 +
#define SOC_GPIO_PIN_EVK_BUSY           _PINNUM(1, 5)  // D1,  P1.05 +

/* I2C */
#define SOC_GPIO_PIN_EVK_SDA            _PINNUM(1, 11) // D4,  P1.11 +
#define SOC_GPIO_PIN_EVK_SCL            _PINNUM(1, 12) // D5,  P1.12 +

/* NFC */
#define SOC_GPIO_PIN_NFC_ANT1           _PINNUM(1,  2) // P1.02 +
#define SOC_GPIO_PIN_NFC_ANT2           _PINNUM(1,  3) // P1.03 +

/* antenna switch */
#define SOC_GPIO_PIN_EVK_ANT_SW         _PINNUM(2,  5) // P2.05 +

#define SOC_GPIO_PIN_EVK_STATUS         _PINNUM(2,  0) // D16, P2.00 +
#define SOC_GPIO_PIN_EVK_BUTTON         _PINNUM(0,  0) // D17, P0.00 +
#define SOC_GPIO_PIN_EVK_BUZZER         SOC_UNUSED_PIN
