#define BOOTMAGIC_ROW 1
#define BOOTMAGIC_COLUMN 0
#define BOOTMAGIC_ROW_RIGHT 6
#define BOOTMAGIC_COLUMN_RIGHT 5

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define MASTER_LEFT

// Tap/hold timing to match ZMK
// https://zmk.dev/docs/keymaps/behaviors/hold-tap?examples=home_row_mods

#define TAPPING_TERM 280          // tapping-term-ms = 280
#define QUICK_TAP_TERM 175        // quick-tap-ms   = 175

// "balanced" in ZMK ≈ QMK Permissive Hold
#define PERMISSIVE_HOLD           // hold when the other key is pressed+released

// ZMK require-prior-idle-ms = 150 → QMK Flow Tap
#define FLOW_TAP_TERM 150         // disables holds during fast typing

// ZMK positional hold-tap (opposite-hand lists) → QMK Chordal Hold
#define CHORDAL_HOLD              // same-hand chords stay tap; opposite-hand can hold
