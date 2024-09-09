#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <Arduino.h>

// #define SERVO_DEBUG  // uncomment for manual servo control
// #define FFT_WHITE_NOISE_CAL  // uncomment for white noise calibration
// #define CONFIG_ARDUINO_LOOP_STACK_SIZE 8192 * 4;
// Path to skdconfig.h: .platformio\packages\framework-arduinoespressif32@3.10006.210326\tools\sdk\include\config\sdkconfig.h

// Strings
const char* const APP_NAME = "Audiobox XL";
const char* const MDNS_DOMAIN_NAME = "audiobox";

// Keys for Preferences dictionary
const char* const PREFS_WIFI_SSID_KEY = "wifi_ssid";
const char* const PREFS_WIFI_PASS_KEY = "wifi_pass";
const char* const PREFS_SPOTIFY_CLIENT_ID_KEY = "sp_cli_id";
const char* const PREFS_SPOTIFY_CLIENT_SECRET_KEY = "sp_cli_sec";
const char* const PREFS_SPOTIFY_AUTH_B64_KEY = "sp_auth_b64";
const char* const PREFS_SPOTIFY_REFRESH_TOKEN_KEY = "sp_ref_tok";
const char* const PREFS_SPOTIFY_USER_NAME_KEY = "sp_user";

// Networking
const uint8_t WIFI_LOCAL_IP[4] = { 192, 168, 3, 147 };
const uint8_t WIFI_GATEWAY[4] = { 192, 168, 1, 1 };
const uint8_t WIFI_SUBNET[4] = { 255, 255, 0, 0 };
const uint8_t WIFI_DNS1[4] = { 8, 8, 8, 8 };
const uint8_t WIFI_DNS2[4] = { 8, 8, 4, 4 };

// Event Handler
#define MAX_EVENTHANDLER_TASKS 32
#define MAX_EVENTHANDLER_EVENTS 32

// Maximum string lengths
#define HTTP_MAX_CHARS 512   // max number of chars for http processing
#define CLI_MAX_CHARS 256    // max number of chars for CLI input
#define MAX_CLI_MENU_ITEMS 9 // max items per level of CLI
#define MAX_CLI_MENU_TEXT 64 // max text length for CLI menu items

// Hardware pins
#define PIN_LED_CONTROL 12           // LED strip control GPIO
#define PIN_LED_STATUS 2             // Status LED on ESP32 Hiletgo board
#define PIN_BUTTON_MODE 14           // Physical mode button 1 (upper)
#define PIN_BUTTON2_MODE 22          // Physical Mode button 2 (lower)
#define PIN_BUTTON_LED 27            // Illuminated button LED
#define PIN_I2S_BCK 5                // I2S for microphone
#define PIN_I2S_DIN 17               // I2S for microphone
#define PIN_I2S_WS 16                // I2S for microphone
#define PIN_SERVO 18                 // I2S for microphone
#define PIN_POWER_SWITCH GPIO_NUM_13 // GPIO number used as wakeup source. Only GPIOs which are have RTC
                                     // functionality can be used: 0,2,4,12-15,25-27,32-39.

// LED
#define MAX_BRIGHT 50 // sets max brightness for LEDs, 100 = ~3A at full white, 60 = ~1.8A
#define GRID_H 16     // LED panel height
#define GRID_W 16     // LED panel width
#define NUM_LEDS GRID_H* GRID_W
#define FPS 60 // LED refresh rate

// Gamma to use for color channels (see: https://drive.google.com/file/d/1v7AEu2hqfFiiNiP1ngT0oPzDP944fT0s/view?usp=sharing)
#define LED_GAMMA_R 3.0
#define LED_GAMMA_G 3.3
#define LED_GAMMA_B 4.0
#define JPG_GAMMA 2.2 // used to undo gamma encoding during JPG decode

// Audio
#define I2S_PORT I2S_NUM_0                                      // I2S port
#define I2S_SAMPLE_RATE 44100                                   // audio sampling rate (per Nyquist, FFT will provide up frequency information up to sample_rate / 2)
#define I2S_MIC_BIT_DEPTH 18                                    // SPH0645 bit depth, per datasheet (18-bit 2's complement in 24-bit container)
#define FFT_SAMPLES 1024                                        // Number of audio samples to collect per FFT invocation. FFT result will have FFT_SAMPLES / 2 data points.
#define FFTS_PER_SEC int(double(I2S_SAMPLE_RATE) / FFT_SAMPLES) // number of FFTs computed each sec

// Timeouts and delays
#define DURATION_MS_ART 10000      // how long to display the album art before switching modes
#define DURATION_MS_AUDIO 600000   // how long to display audio visualization before switching modes
#define SPOTIFY_CYCLE_TIME_MS 1000 // how often to run the Spotify task
#define SERVO_CYCLE_TIME_MS 50     // how often to run the servo task
#define WIFI_TIMEOUT_MS 10000      // how long to wait on wifi connect before bailing out

// Mean cut
#define MEAN_CUT_DEPTH 4                      // recursive depth for mean cut algorithm (results in 2^MEAN_CUT_DEPTH colors)
#define PALETTE_ENTRIES (1 << MEAN_CUT_DEPTH) // number of color palette entries

// Servo
#define SERVO_MIN_US 700  // minimum servo PWM setting in microseconds
#define SERVO_MAX_US 2400 // maximum servo PWM setting in microseconds
#define SERVO_MAX_POS 170 // maximum servo angular position (0 to 180)
#define SERVO_MIN_POS 20  // minimum servo angular position (0 to 180)

// Servo positions
// larger number = sharper image, LED panel closer to front of box
// smaller number = blurrier image, LED panel further from front of box
#define SERVO_POS_NOISE 30 // position for lava / noise display mode
#define SERVO_POS_ART 110  // position for album art mode
#define SERVO_POS_BARS 160 // position for vertical column visualizer
#define SERVO_POS_GRID 30  // position for diffuse visualizer mode

// Modes
enum MainMode {
    MODE_MAIN_ART,
    MODE_MAIN_AUDIO,
    MODE_MAIN_IMAGE,
    MODE_MAIN_MODES_MAX,
};
enum ArtSubMode {
    MODE_ART_WITHOUT_ELAPSED,
    MODE_ART_WITH_ELAPSED,
    MODE_ART_WITH_PALETTE,
    MODE_ART_SUBMODE_MAX,
};
enum AudioSubMode {
    MODE_AUDIO_NOISE,
    MODE_AUDIO_SNAKE_GRID,
    MODE_AUDIO_BARS,
    MODE_AUDIO_CENTER_BARS,
    MODE_AUDIO_WATERFALL,
    MODE_AUDIO_MODES_MAX,
    MODE_AUDIO_SCROLLING,
    MODE_AUDIO_OUTRUN_BARS,
    MODE_AUDIO_SUBMODE_MAX,
};

// Audio volume control
#define VOL_FACTOR 10                       // empirically found that RMS of signal needs x10 to match RMS of FFT
#define VOL_MULT 0.4 * 256 / FFT_SAMPLES    // multiplier to go from volume to FFT max value, scaled by FFT_SAMPLES because more samples = less energy per bin
#define VOL_PEAK_FACTOR 1.5                 // factor above avg for finding peaks
#define VOL_AVG_SCALE 0.01 * 30 / FPS       // exponential moving averaging scale factor for calculating running avg of volume
#define VOL_THRESH_DB -65                   // threshold below which we shouldn't update LEDs as FFT data may not be reliable
#define FFT_FIXED_MAX_VAL 0.0014 * VOL_MULT // value to use when not volume scaling

// Audio bands for vertical bar visualizations
#define LOWEST_BASS_FREQ 60
#define HIGHEST_BASS_FREQ 130
#define LOWEST_FREQ_BAND 60
#define HIGHEST_FREQ_BAND I2S_SAMPLE_RATE / 2
#define NUM_AUDIO_BANDS 16

// Audio LED settings
#define BRIGHT_LEVELS 255                    // number of levels of brightness to use
#define MIN_BRIGHT_FADE 0                    // Cut-off as we fade (this is a 5 in the gamma table)
#define MIN_BRIGHT_UPDATE 32                 // Cut-off for new values (this is a 5 in the gamma table)
#define FADE BRIGHT_LEVELS / 32 * 30 / FPS   // Rate at which LEDs will fade out (remember, gamma will be applied so fall off will seem faster).                                                           // Scale by FPS so that the fade speed is always the same.
#define LED_SMOOTHING 0.75 * 30 / FPS        // smoothing factor for updating LEDs
#define FFT_SCALE_POWER 1.5                  // power by which to scale the FFT for LED intensity
#define PALETTE_CHANGE_RATE 24               // default from https://gist.github.com/kriegsman/1f7ccbbfa492a73c015e
#define PEAK_DECAY_RATE int(round(FPS / 16)) // rate at which peak decays on vertical bar visualization

// Scrolling grid art
#define SCROLL_AVG_FACTOR int(4 * 60 / FPS) // number of frames to average to create a single vertical slice that scrolls

// Macros
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
#define TIME_THIS(A)                           \
    {                                          \
        unsigned long last_micros = micros();  \
        A;                                     \
        print("%d\n", micros() - last_micros); \
    }

#define FASTLED_ALLOW_INTERRUPTS 0      // TODO: check if we still need this
#define FASTLED_INTERRUPT_RETRY_COUNT 1 // TODO: check if we still need this

// Gamma curve for perceptual brightness (looks like this is close to gamma=2.8)
const uint8_t PROGMEM GAMMA8[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
    2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,
    5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
    115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
    144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
    177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
    215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

// Audio gamma
const uint16_t GAMMA16_FFT[] = {
    0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 54, 56, 58, 60, 62, 64, 66, 68, 69, 71, 73, 75, 77, 79, 81, 82, 84, 86, 88, 90, 91, 93, 95, 97, 99, 101, 102, 104, 106, 108, 109, 111, 113, 115, 116, 118, 120, 122, 123, 125, 127, 129, 130, 132, 134, 136, 137, 139, 141, 142, 144, 146, 147, 149, 151, 153, 154, 156, 158, 159, 161, 162, 164, 166, 167, 169, 171, 172, 174, 176, 177, 179, 180, 182, 184, 185, 187, 188, 190, 192, 193, 195, 196, 198, 199, 201, 203, 204, 206, 207, 209, 210, 212, 213, 215, 216, 218, 219, 221, 222, 224, 225, 227, 228, 230, 231, 233, 234, 236, 237, 239, 240, 242, 243, 245, 246, 247, 249, 250, 252, 253, 255, 256, 257, 259, 260, 262, 263, 264, 266, 267, 269, 270, 271, 273, 274, 275, 277, 278, 279, 281, 282, 283, 285, 286, 287, 289, 290, 291, 293, 294, 295, 297, 298, 299, 300, 302, 303, 304, 306, 307, 308, 309, 311, 312, 313, 314, 316, 317, 318, 319, 321, 322, 323, 324, 325, 327, 328, 329, 330, 331, 333, 334, 335, 336, 337, 338, 340, 341, 342, 343, 344, 345, 346, 348, 349, 350, 351, 352, 353, 354, 355, 356, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 407, 408, 409, 410, 411, 412, 413, 414, 415, 415, 416, 417, 418, 419, 420, 421, 421, 422, 423, 424, 425, 426, 426, 427, 428, 429, 430, 430, 431, 432, 433, 434, 434, 435, 436, 437, 437, 438, 439, 440, 440, 441, 442, 443, 443, 444, 445, 445, 446, 447, 448, 448, 449, 450, 450, 451, 452, 452, 453, 454, 454, 455, 456, 456, 457, 458, 458, 459, 460, 460, 461, 462, 462, 463, 463, 464, 465, 465, 466, 466, 467, 468, 468, 469, 469, 470, 470, 471, 472, 472, 473, 473, 474, 474, 475, 475, 476, 476, 477, 477, 478, 478, 479, 479, 480, 480, 481, 481, 482, 482, 483, 483, 484, 484, 485, 485, 486, 486, 486, 487, 487, 488, 488, 489, 489, 489, 490, 490, 491, 491, 491, 492, 492, 493, 493, 493, 494, 494, 494, 495, 495, 495, 496, 496, 497, 497, 497, 498, 498, 498, 498, 499, 499, 499, 500, 500, 500, 501, 501, 501, 501, 502, 502, 502, 502, 503, 503, 503, 503, 504, 504, 504, 504, 505, 505, 505, 505, 506, 506, 506, 506, 506, 506, 507, 507, 507, 507, 507, 508, 508, 508, 508, 508, 508, 508, 509, 509, 509, 509, 509, 509, 509, 509, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 510, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511, 511
};

// FFT equalization

// This is the base "noise" levels to remove from the FFT output (determined empirically)
// For analog mic (sparkfun)
// const uint8_t fft_remove[FFT_SAMPLES / 2] = {63, 45, 30, 29, 28, 27, 27, 26, 24, 23, 24, 24, 23, 23, 24, 24, 24, 25, 24, 23, 25, 25, 25, 24, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24, 25, 24, 24, 23, 24, 24, 25, 24, 24, 23, 25, 25, 24, 25, 23, 25, 26, 25, 26, 25, 24, 26, 26, 25, 26, 27, 27, 27, 26, 25, 25, 25, 26, 26, 25, 26, 25, 25, 26, 25, 23, 25, 25, 25, 25, 25, 25, 24, 26, 25, 24, 24, 24, 25, 24, 23, 23, 23, 24, 24, 24, 22, 23, 23, 25, 24, 24, 23, 23, 24, 24, 24, 23, 23, 23, 24, 24, 25, 25, 24, 24, 24, 24, 25, 25, 24, 22, 24, 25, 25, 23, 24, 24, 25};
// For digital mic (adafruit SPH0645)
// const uint16_t FFT_REMOVE[FFT_SAMPLES / 2] = {0}; //{1212, 2329, 1601, 246, 172, 150, 154, 184, 188, 119, 105, 120, 166, 90, 76, 69, 73, 63, 60, 58, 58, 60, 58, 52, 53, 58, 52, 49, 52, 50, 49, 52, 52, 44, 48, 48, 48, 50, 46, 45, 43, 44, 47, 45, 43, 43, 43, 46, 43, 40, 41, 45, 45, 46, 44, 46, 47, 43, 44, 41, 41, 38, 38, 39, 37, 35, 35, 33, 35, 33, 36, 39, 35, 34, 35, 33, 33, 31, 29, 29, 28, 29, 29, 29, 28, 29, 28, 26, 25, 24, 23, 25, 26, 25, 24, 25, 23, 21, 21, 22, 20, 20, 19, 19, 17, 16, 16, 16, 14, 14, 14, 13, 13, 12, 12, 12, 11, 9, 9, 9, 9, 8, 7, 7, 7, 6, 6, 6};
const float FFT_REMOVE[FFT_SAMPLES / 2] = { 0.0002852002216969, 0.0002224564728489, 0.0001436876642791, 0.0000984009431185, 0.0000337695707588, 0.0000459380792433, 0.0000572257670553, 0.0000664587567891, 0.0000407142696791, 0.0000230581882923, 0.0000188005489170, 0.0000293643826288, 0.0000318876960332, 0.0000350216969309, 0.0000188616501029, 0.0000141881992671, 0.0000166980064803, 0.0000229776447733, 0.0000245268009686, 0.0000165288966595, 0.0000093196630847, 0.0000128196289942, 0.0000174583557444, 0.0000182192286827, 0.0000163852018724, 0.0000085946585224, 0.0000092097000431, 0.0000114346514855, 0.0000144596116018, 0.0000154523106955, 0.0000089255130596, 0.0000072218765946, 0.0000095928179056, 0.0000121745906816, 0.0000134651943751, 0.0000086521403903, 0.0000067556095635, 0.0000078519687382, 0.0000091218965963, 0.0000117493195505, 0.0000073797472899, 0.0000063803223611, 0.0000062753573015, 0.0000066175613094, 0.0000098204869313, 0.0000083406832557, 0.0000075864168788, 0.0000050075230027, 0.0000078692551142, 0.0000086036649074, 0.0000085107358570, 0.0000060758200756, 0.0000063869396009, 0.0000056791583834, 0.0000074872729751, 0.0000068477512351, 0.0000062728571655, 0.0000059254128116, 0.0000051127978103, 0.0000065782747478, 0.0000070127176904, 0.0000066582920714, 0.0000064481105012, 0.0000052847367767, 0.0000056660514279, 0.0000061042629146, 0.0000068241923746, 0.0000059570548793, 0.0000053631969682, 0.0000053768191524, 0.0000047543177532, 0.0000062444819703, 0.0000064903008803, 0.0000035220017318, 0.0000041090642152, 0.0000059445499931, 0.0000059264271905, 0.0000044853517401, 0.0000041110567963, 0.0000032136482966, 0.0000048149259848, 0.0000055557955290, 0.0000055168305185, 0.0000048724592554, 0.0000046687031922, 0.0000046228141985, 0.0000051256861785, 0.0000051642589857, 0.0000040518494708, 0.0000031193124853, 0.0000040780557161, 0.0000043530873849, 0.0000045605567039, 0.0000057643630303, 0.0000035711158018, 0.0000036942249153, 0.0000041894955010, 0.0000041606379487, 0.0000039431701972, 0.0000038806758441, 0.0000038078016230, 0.0000038272139591, 0.0000036963187995, 0.0000031711684382, 0.0000031954663281, 0.0000035365869410, 0.0000038668722888, 0.0000047006738311, 0.0000036746090148, 0.0000036171746923, 0.0000026085825441, 0.0000033575344267, 0.0000044473249951, 0.0000040017799685, 0.0000043962857360, 0.0000037534074084, 0.0000049383654316, 0.0000047381545625, 0.0000038675001243, 0.0000030777452317, 0.0000030583429732, 0.0000034373003765, 0.0000039165029031, 0.0000035692661088, 0.0000035321452125, 0.0000023153221313, 0.0000035388546037, 0.0000036364037734, 0.0000034078232066, 0.0000046245542568, 0.0000026288496429, 0.0000037366825641, 0.0000033810651010, 0.0000038386903855, 0.0000046457488777, 0.0000031374639085, 0.0000035317242870, 0.0000041288308077, 0.0000030589504953, 0.0000029191056764, 0.0000032995477081, 0.0000030485429322, 0.0000032266024326, 0.0000037616765261, 0.0000036266443918, 0.0000032108235603, 0.0000028557727205, 0.0000021449364697, 0.0000040428684461, 0.0000035764293216, 0.0000027651418415, 0.0000027262708337, 0.0000029357407324, 0.0000030519667738, 0.0000039138174251, 0.0000037238679299, 0.0000039271282373, 0.0000028778211864, 0.0000026400230208, 0.0000030015384596, 0.0000040822203736, 0.0000027795827171, 0.0000024283450638, 0.0000039663189000, 0.0000049275484701, 0.0000040998088074, 0.0000039509594509, 0.0000023185134361, 0.0000027694699643, 0.0000023211919224, 0.0000028913520477, 0.0000017186077019, 0.0000013132952219, 0.0000024688077036, 0.0000028287945010, 0.0000029471702224, 0.0000029527886909, 0.0000028494581232, 0.0000024926960184, 0.0000025195713533, 0.0000045868795756, 0.0000029583184471, 0.0000017730030615, 0.0000026075911543, 0.0000025995699389, 0.0000036568489707, 0.0000032092964375, 0.0000030402994997, 0.0000028297023554, 0.0000038197724247, 0.0000033866902283, 0.0000043535029590, 0.0000030784059391, 0.0000033328065001, 0.0000022754125918, 0.0000039706918804, 0.0000042991189438, 0.0000039188629281, 0.0000020241749651, 0.0000026239095925, 0.0000022115520843, 0.0000027217367428, 0.0000034819476013, 0.0000030856277168, 0.0000028891170578, 0.0000019192239863, 0.0000030556162837, 0.0000035795292206, 0.0000034937067669, 0.0000024051594291, 0.0000033742091676, 0.0000025188896952, 0.0000030893177235, 0.0000027901135452, 0.0000030165076136, 0.0000031762260002, 0.0000030637449819, 0.0000032915391850, 0.0000028948319206, 0.0000026993515852, 0.0000022311840553, 0.0000024816763796, 0.0000019906253864, 0.0000029795165233, 0.0000021888323139, 0.0000020732151630, 0.0000036814260592, 0.0000023230110336, 0.0000028623443963, 0.0000036507892186, 0.0000021703291558, 0.0000019740315582, 0.0000031675732868, 0.0000020972187258, 0.0000031506367171, 0.0000031384188495, 0.0000022639120678, 0.0000025811206439, 0.0000024370488713, 0.0000024277452927, 0.0000023590105229, 0.0000018545456929, 0.0000019472411249, 0.0000029629787507, 0.0000023388417064, 0.0000029057401808, 0.0000018661635376, 0.0000026747754061, 0.0000026064212437, 0.0000019040763846, 0.0000021712807227, 0.0000017147875805, 0.0000024512432739, 0.0000032609331616, 0.0000024965250012, 0.0000026255591235, 0.0000025321957569, 0.0000029397346160, 0.0000038373744441, 0.0000020499682673, 0.0000031391825165, 0.0000017274859009, 0.0000019834443736, 0.0000023490508007, 0.0000027553968006, 0.0000025204118970, 0.0000023071310287, 0.0000024896696199, 0.0000023469452961, 0.0000026991465022, 0.0000024659024283, 0.0000016933170254, 0.0000018304590331, 0.0000020013108123, 0.0000027281653274, 0.0000022215566722, 0.0000031401070016, 0.0000024715368292, 0.0000023657691242, 0.0000021919697539, 0.0000029739685812, 0.0000029074933212, 0.0000024157366170, 0.0000011851446280, 0.0000021215895133, 0.0000029655811561, 0.0000023783489951, 0.0000026939618871, 0.0000051384453010, 0.0000069267051523, 0.0000072157912915, 0.0000046715651284, 0.0000024434861855, 0.0000026657114022, 0.0000030310248462, 0.0000030643563248, 0.0000025807290313, 0.0000032913801695, 0.0000030045518348, 0.0000026941162495, 0.0000031017754704, 0.0000064238228593, 0.0000036173464651, 0.0000021617425513, 0.0000025916078649, 0.0000022165222455, 0.0000033816309042, 0.0000036974514452, 0.0000033256600643, 0.0000035941230700, 0.0000031804930326, 0.0000022869622610, 0.0000033878868635, 0.0000032129940531, 0.0000025980957941, 0.0000020477687518, 0.0000018003856021, 0.0000034865514635, 0.0000034959517653, 0.0000023881281582, 0.0000025429112124, 0.0000032055869497, 0.0000031285476812, 0.0000035021248225, 0.0000068058484430, 0.0000047221570542, 0.0000035039509579, 0.0000025196424198, 0.0000027453645950, 0.0000020937258520, 0.0000025842364510, 0.0000034458629606, 0.0000029704116693, 0.0000035827633269, 0.0000033122310339, 0.0000021106218396, 0.0000019505192240, 0.0000024755957254, 0.0000028173387169, 0.0000038903387381, 0.0000031871634617, 0.0000027128322212, 0.0000025493853692, 0.0000027000518230, 0.0000020920912708, 0.0000020156072001, 0.0000021778697601, 0.0000030439226586, 0.0000021510365481, 0.0000021276409581, 0.0000035578497497, 0.0000023009450193, 0.0000023299212038, 0.0000020368838583, 0.0000024805336969, 0.0000019589104617, 0.0000019873697852, 0.0000024095224944, 0.0000020371181060, 0.0000015485830147, 0.0000010883578848, 0.0000013973846324, 0.0000019889992992, 0.0000014614894894, 0.0000015932536103, 0.0000021446896556, 0.0000017260376158, 0.0000018882848565, 0.0000010222010555, 0.0000016474380037, 0.0000016626805908, 0.0000019304128175, 0.0000016831576691, 0.0000018410914160, 0.0000017097121534, 0.0000013558122792, 0.0000013543360069, 0.0000021477338257, 0.0000013011264173, 0.0000013917903792, 0.0000018165505773, 0.0000020883963348, 0.0000013974799141, 0.0000009938473470, 0.0000014854012420, 0.0000018481276730, 0.0000008918819471, 0.0000022547712827, 0.0000012140164602, 0.0000018646175834, 0.0000016079651297, 0.0000014787644359, 0.0000019570733554, 0.0000018338241919, 0.0000020530742566, 0.0000020324866503, 0.0000016238689925, 0.0000014424795966, 0.0000013932740087, 0.0000013391706619, 0.0000015730386979, 0.0000015268607773, 0.0000016182938428, 0.0000015429065538, 0.0000015495276387, 0.0000015680380240, 0.0000011502665903, 0.0000009679064295, 0.0000010121938487, 0.0000011445533253, 0.0000017498510942, 0.0000013048228738, 0.0000008176334271, 0.0000015165343581, 0.0000017762605872, 0.0000013444429742, 0.0000018346950859, 0.0000018305586228, 0.0000009895896410, 0.0000012410448542, 0.0000011720138998, 0.0000013984168195, 0.0000016754005401, 0.0000010176177260, 0.0000018501731834, 0.0000018768699184, 0.0000014051164377, 0.0000010735260280, 0.0000018551493578, 0.0000014398917512, 0.0000016384127873, 0.0000008827645144, 0.0000014171534336, 0.0000016519840520, 0.0000012565740966, 0.0000013179741489, 0.0000015448789554, 0.0000009945257570, 0.0000014446204740, 0.0000010328946262, 0.0000014437134053, 0.0000009804413383, 0.0000010751055381, 0.0000014324666121, 0.0000011051648861, 0.0000014787712774, 0.0000009275775231, 0.0000014996436164, 0.0000012288147023, 0.0000014074353812, 0.0000014170864152, 0.0000010638615972, 0.0000011580921568, 0.0000014055732760, 0.0000013667814471, 0.0000011610916480, 0.0000011849350423, 0.0000009982367918, 0.0000009759724924, 0.0000014116458748, 0.0000015028515788, 0.0000011191157755, 0.0000007650395162, 0.0000012343472398, 0.0000010477918997, 0.0000013846240604, 0.0000010816184123, 0.0000008718264317, 0.0000010444877115, 0.0000010829397265, 0.0000009351081108, 0.0000012600178983, 0.0000007418749947, 0.0000011691355805, 0.0000010597448019, 0.0000009127512044, 0.0000013389904398, 0.0000010269594749, 0.0000009182809850, 0.0000009165120705, 0.0000010724902008, 0.0000012039512650, 0.0000011317659495, 0.0000010082072330, 0.0000010203200418, 0.0000008750866739, 0.0000010492258866, 0.0000009811551089, 0.0000010167552788, 0.0000010922644407, 0.0000009942707168, 0.0000011873216092, 0.0000011111935143, 0.0000008543064272, 0.0000010162262620, 0.0000008507704397, 0.0000009545273960, 0.0000011173750595, 0.0000011864940258, 0.0000010417450288, 0.0000010140492057, 0.0000009352272993, 0.0000010097618548, 0.0000010237932620, 0.0000010948131818, 0.0000008178784339, 0.0000009218119520, 0.0000011314492911, 0.0000011482175637, 0.0000010458279170, 0.0000009182569392, 0.0000000000000000 };

// This is the EQ to apply to get a "flat" response. Determined empirically using white noise through speakers. 255 divided by the values here determines the gain for that freq band.
// For analog mic (sparkfun)
// const uint8_t fft_eq[FFT_SAMPLES / 2] = {87, 199, 255, 219, 189, 171, 153, 141, 151, 173, 129, 132, 133, 131, 108, 76, 76, 72, 82, 94, 110, 111, 111, 98, 94, 97, 89, 97, 92, 85, 95, 107, 102, 98, 101, 98, 93, 93, 102, 101, 100, 93, 89, 96, 93, 87, 71, 72, 72, 73, 75, 76, 80, 65, 85, 100, 97, 122, 125, 136, 139, 139, 130, 126, 123, 118, 106, 94, 97, 94, 92, 84, 79, 81, 80, 82, 73, 73, 65, 66, 73, 68, 66, 64, 61, 59, 58, 63, 59, 60, 65, 68, 58, 53, 52, 55, 47, 47, 40, 40, 38, 36, 37, 40, 38, 42, 44, 43, 41, 36, 33, 31, 31, 28, 27, 28, 29, 29, 30, 35, 37, 35, 33, 32, 32, 35, 33, 33};
// For digital mic (adafruit SPH0645)
const uint8_t FFT_EQ[FFT_SAMPLES / 2] = { 44, 72, 85, 101, 101, 101, 101, 104, 110, 116, 116, 107, 98, 91, 107, 123, 116, 120, 120, 107, 104, 107, 98, 88, 82, 85, 85, 88, 82, 69, 60, 57, 57, 63, 69, 82, 91, 101, 113, 101, 94, 91, 94, 94, 91, 88, 91, 98, 98, 101, 101, 91, 94, 101, 110, 110, 110, 120, 120, 107, 110, 110, 123, 132, 129, 132, 132, 142, 139, 132, 129, 123, 132, 135, 132, 132, 135, 135, 139, 135, 139, 151, 151, 151, 157, 161, 154, 157, 167, 176, 186, 195, 198, 192, 198, 205, 211, 224, 230, 227, 224, 217, 214, 230, 227, 224, 233, 239, 255, 255, 227, 205, 189, 176, 161, 151, 151, 164, 157, 164, 164, 161, 154, 154, 148, 139, 126, 116, 104, 94, 94, 85, 82, 82, 85, 79, 66, 57, 54, 47, 47, 47, 47, 50, 50, 47, 44, 44, 41, 44, 44, 47, 50, 50, 50, 47, 57, 63, 60, 57, 63, 69, 76, 76, 79, 76, 85, 88, 98, 98, 101, 107, 110, 110, 116, 120, 126, 135, 139, 132, 139, 148, 148, 157, 161, 151, 154, 167, 167, 151, 142, 154, 157, 142, 135, 129, 132, 132, 129, 132, 135, 135, 129, 129, 123, 120, 120, 120, 113, 110, 104, 94, 88, 82, 79, 69, 57, 47, 38, 38, 31, 38, 44, 54, 60, 69, 82, 88, 98, 107, 104, 107, 113, 123, 126, 120, 116, 113, 116, 123, 120, 120, 123, 120, 123, 126, 135, 148, 145, 145, 142, 135, 142, 142, 142, 145, 142, 139, 151, 151, 148, 148, 148, 154, 154, 154, 151, 154, 148, 142, 139, 148, 145, 145, 135, 135, 139, 132, 132, 129, 126, 126, 132, 129, 129, 126, 126, 132, 135, 145, 157, 157, 148, 148, 161, 164, 173, 167, 167, 176, 176, 167, 164, 173, 176, 173, 179, 170, 176, 173, 170, 173, 183, 192, 176, 167, 170, 170, 173, 167, 164, 157, 161, 164, 151, 161, 161, 154, 151, 145, 139, 142, 145, 135, 135, 139, 145, 145, 139, 139, 145, 145, 148, 148, 151, 151, 151, 154, 154, 154, 148, 142, 148, 148, 142, 142, 145, 148, 139, 139, 129, 129, 135, 129, 132, 129, 123, 116, 110, 113, 113, 113, 113, 113, 107, 101, 101, 98, 91, 85, 88, 85, 79, 79, 79, 79, 82, 76, 79, 82, 82, 79, 79, 79, 79, 79, 76, 79, 79, 72, 69, 69, 69, 69, 63, 50, 28, 19, 16, 16, 13, 13, 13, 13, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 6, 9, 6, 9, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }; //{98, 197, 255, 238, 195, 186, 168, 162, 179, 201, 154, 174, 160, 148, 143, 122, 91, 73, 84, 111, 138, 132, 128, 126, 106, 107, 116, 113, 131, 119, 129, 134, 133, 139, 152, 128, 113, 115, 113, 130, 135, 132, 119, 112, 99, 103, 108, 108, 92, 87, 93, 87, 84, 81, 90, 93, 92, 101, 105, 101, 97, 96, 89, 88, 96, 101, 97, 91, 92, 90, 97, 100, 93, 92, 96, 95, 106, 105, 102, 98, 85, 95, 97, 95, 88, 85, 94, 89, 87, 80, 80, 73, 60, 60, 51, 47, 43, 44, 44, 46, 48, 46, 43, 42, 40, 36, 34, 32, 31, 27, 25, 23, 22, 19, 18, 17, 16, 15, 13, 12, 12, 10, 8, 7, 6, 4, 3, 2};

// Divide these values by 255 to create the a-weighting gain
// const uint8_t a_weighting[FFT_SAMPLES / 2] = {0, 18, 49, 78, 103, 125, 144, 159, 172, 183, 192, 199, 205, 211, 215, 219, 222, 224, 226, 228, 230, 231, 232, 233, 233, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 233, 233, 232, 232, 231, 231, 230, 229, 229, 228, 227, 226, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 216, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 199, 198, 197, 196, 195, 194, 193, 191, 190, 189, 188, 187, 186, 185, 183, 182, 181, 180, 179, 178, 177, 175, 174, 173, 172, 171, 170, 169, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140};
// Shifted over by one so we get some low end
const uint8_t A_WEIGHTING[FFT_SAMPLES / 2] = { 0 }; //{18, 49, 78, 103, 125, 144, 159, 172, 183, 192, 199, 205, 211, 215, 219, 222, 224, 226, 228, 230, 231, 232, 233, 233, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 233, 233, 232, 232, 231, 231, 230, 229, 229, 228, 227, 226, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 216, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 199, 198, 197, 196, 195, 194, 193, 191, 190, 189, 188, 187, 186, 185, 183, 182, 181, 180, 179, 178, 177, 175, 174, 173, 172, 171, 170, 169, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 140};

#endif //_CONSTANTS_H
