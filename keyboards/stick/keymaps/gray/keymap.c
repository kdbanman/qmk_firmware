// keymaps/gray/keymap.c
// Lookup-only: define layout + strings, then include the shared module.

#define SECRET_LAYOUT LAYOUT( S_G, S_R, S_A, S_Y )

// Single-key holds: NAME, "string ", tap-keycode
#define SINGLE_LIST(X) \
  X(G, "goose ",   KC_G) \
  X(R, "hamster ", KC_R) \
  X(A, "chicken ", KC_A) \
  X(Y, "pencil ",  KC_Y)

// Multi-key holds (use S_* names, not KC_*)
#define COMBO_LIST(X) \
  X(GR,   "flops ",            S_G, S_R) \
  X(GA,   "jumps ",            S_G, S_A) \
  X(GY,   "toots ",            S_G, S_Y) \
  X(RA,   "explodes ",         S_R, S_A) \
  X(RY,   "grows ",            S_R, S_Y) \
  X(AY,   "hammers ",          S_A, S_Y) \
  X(GRA,  "its wings ",        S_G, S_R, S_A) \
  X(GRY,  "into a cloud ",     S_G, S_R, S_Y) \
  X(GAY,  "on a bus ",         S_G, S_A, S_Y) \
  X(RAY,  "through a window ", S_R, S_A, S_Y) \
  X(GRAY, "a toilet ",         S_G, S_R, S_A, S_Y)

#include "../../secrets.h"
