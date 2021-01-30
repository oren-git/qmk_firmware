# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes  # Mouse keys
EXTRAKEY_ENABLE = yes  # Audio control and System control
CONSOLE_ENABLE = no   # Console for debug
COMMAND_ENABLE = yes   # Commands for debug and configuration
CUSTOM_MATRIX = yes    # Custom matrix file for the HHKB
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
# SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
# NKRO_ENABLE = yes       # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
# BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
# MIDI_ENABLE = yes       # MIDI controls
# UNICODE_ENABLE = yes    # Unicode
# BLUETOOTH_ENABLE = yes  # Enable Bluetooth with the Adafruit EZ-Key HID


# HHKB_RN42_ENABLE = yes  # Enable support for hasu's BT alt controller -- code borrowed from tmk source tree.

# Either uncomment the HHKB_RN42_ENABLE line above, or run make enabling the
# feature. Be sure to clean any existing build before trying to enable rn42
# support. For example:
#
# make hhkb-keymap-clean
# make hhkb-keymap-dfu HHKB_RN42_ENABLE=yes

# project specific files
SRC = ../../hhkb/ansi/matrix.c

# debug-on: EXTRAFLAGS += -DDEBUG -DDEBUG_ACTION
# debug-on: all

# debug-off: EXTRAFLAGS += -DNO_DEBUG -DNO_PRINT
# debug-off: OPT_DEFS := $(filter-out -DCONSOLE_ENABLE,$(OPT_DEFS))
# debug-off: all

RGBLIGHT_ENABLE = yes
RGBLIGHT_CUSTOM_DRIVER = yes
WS2812_DRIVER_REQUIRED = yes
EXTRAFLAGS += -flto
