#pragma once
#define MATRIX_ROWS 1
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { GP13 }
#define MATRIX_COL_PINS { GP12, GP11, GP10, GP9 }
#define DIODE_DIRECTION COL2ROW
#define NO_USB_STARTUP_CHECK

#define EXTRA_SHORT_COMBOS              // up to 6-key combos; you use <=4
#define COMBO_KEY_BUFFER_LENGTH 6       // keys tracked for combo detection
#define COMBO_BUFFER_LENGTH 4           // simultaneous combos tracked
#define COMBO_TERM 60                   // default is ~50; tune 40–100
#define COMBO_ONLY_FROM_LAYER 0

// Allow combos to match custom keycodes like S_G, S_R, etc.
#define COMBO_ALLOW_ACTION_KEYS

#define SECRET_HOLD_MS 1500
