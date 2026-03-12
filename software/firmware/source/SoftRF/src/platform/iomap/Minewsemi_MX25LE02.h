/* Minewsemi MX25LE02 Evaluation Kit */

/* Peripherals */
#define SOC_GPIO_PIN_CONS_MX25_RX       _PINNUM(1,  4) // P1.04
#define SOC_GPIO_PIN_CONS_MX25_TX       _PINNUM(1,  5) // P1.05

#define SOC_GPIO_PIN_GNSS_MX25_RX       _PINNUM(2,  8) // P2.08
#define SOC_GPIO_PIN_GNSS_MX25_TX       _PINNUM(2,  7) // P2.07
#define SOC_GPIO_PIN_GNSS_MX25_PPS      _PINNUM(2, 10) // P2.10

/* SPI */
#define SOC_GPIO_PIN_MX25_MOSI          _PINNUM(2,  2) // P2.02
#define SOC_GPIO_PIN_MX25_MISO          _PINNUM(2,  4) // P2.04
#define SOC_GPIO_PIN_MX25_SCK           _PINNUM(2,  1) // P2.01
#define SOC_GPIO_PIN_MX25_SS            _PINNUM(2,  5) // P2.05

/* SX1262 */
#define SOC_GPIO_PIN_MX25_RST           _PINNUM(2,  0) // P2.00
#define SOC_GPIO_PIN_MX25_DIO1          _PINNUM(0,  0) // P0.00
#define SOC_GPIO_PIN_MX25_BUSY          _PINNUM(0,  1) // P0.01

/* I2C */
#define SOC_GPIO_PIN_MX25_SDA           _PINNUM(1, 10) // P1.10
#define SOC_GPIO_PIN_MX25_SCL           _PINNUM(1, 11) // P1.11

/* LEDs */
#define SOC_GPIO_LED_MX25_GREEN         _PINNUM(0,  3) // P0.03 (Green)
#define SOC_GPIO_LED_MX25_RED           _PINNUM(0,  2) // P0.02 (Red)
#define SOC_GPIO_LED_MX25_BLUE          _PINNUM(0,  4) // P0.04 (Blue)

/* antenna switch */
#define SOC_GPIO_PIN_MX25_ANT_SW2       _PINNUM(2,  3) // P2.03

#define SOC_GPIO_PIN_MX25_STATUS        SOC_GPIO_LED_MX25_GREEN
#define SOC_GPIO_PIN_MX25_BUTTON        _PINNUM(1,  8) // P1.08
#define SOC_GPIO_PIN_MX25_BUZZER        _PINNUM(2,  6) // P2.06
#define SOC_GPIO_PIN_MX25_BATTERY       _PINNUM(1, 14) // P1.14
