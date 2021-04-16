#include <pgmspace.h>

const char clearSkyDay[] PROGMEM = { //01d
    0x00, 0x00, 0x80, 0x80, 0xE0, 0xF0, 0xF8, 0xF8, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0010 (16) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00,   // 0x0020 (32) pixels
    0xE0, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0030 (48) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,   // 0x0040 (64) pixels
    0x03, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0050 (80) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x3F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF,   // 0x0070 (112) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char clearSkyNight[] PROGMEM = { //01n
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x3F,   // 0x0010 (16) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0030 (48) pixels
    0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC,   // 0x0040 (64) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0050 (80) pixels
    0x80, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0xF0, 0xF8, 0xFE,   // 0x0070 (112) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char fewCloudsDay [] PROGMEM = { //02d
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80,   // 0x0010 (16) pixels
    0x00, 0x00, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0030 (48) pixels
    0xFF, 0xFE, 0xF8, 0xE3, 0xF7, 0xF7, 0xE7, 0xEF, 0xCF, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,   // 0x0040 (64) pixels
    0x00, 0x3E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0050 (80) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFC, 0x79, 0x03, 0x01,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,   // 0x0070 (112) pixels
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char fewCloudsNight [] PROGMEM = { //02n
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80,   // 0x0010 (16) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x30, 0x70, 0x70, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0030 (48) pixels
    0xFF, 0xFE, 0xF8, 0xE0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x00, 0x01, 0xC3, 0xFF, 0xFF, 0xFF, 0xFE,   // 0x0040 (64) pixels
    0x00, 0x3E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0050 (80) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFC, 0x79, 0x03, 0x01,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,   // 0x0070 (112) pixels
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char scatteredCloudsDay[] PROGMEM = { //03d
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0,   // 0x0010 (16) pixels
    0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x00, 0xC0, 0xC0, 0xE0, 0xE0, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0030 (48) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0040 (64) pixels
    0x00, 0x1C, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0050 (80) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x7C,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,   // 0x0070 (112) pixels
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char scatteredCloudsNight[] PROGMEM = { //03n
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0,   // 0x0010 (16) pixels
    0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x00, 0xC0, 0xC0, 0xE0, 0xE0, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0030 (48) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0040 (64) pixels
    0x00, 0x1C, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0050 (80) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x7C,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,   // 0x0070 (112) pixels
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char brokenCloudsDay[] PROGMEM = { //04d
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0010 (16) pixels
    0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC,   // 0x0030 (48) pixels
    0xF9, 0xE3, 0xCF, 0xEF, 0xCF, 0xCF, 0x3F, 0x7E, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8, 0xE0, 0xE0, 0xC0,   // 0x0040 (64) pixels
    0x00, 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0050 (80) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xF9, 0x63, 0x0F, 0x0F, 0x0F, 0x07,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,   // 0x0070 (112) pixels
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char brokenCloudsNight[] PROGMEM = { //04n
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0010 (16) pixels
    0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC,   // 0x0030 (48) pixels
    0xF9, 0xE3, 0xCF, 0xEF, 0xCF, 0xCF, 0x3F, 0x7E, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8, 0xE0, 0xE0, 0xC0,   // 0x0040 (64) pixels
    0x00, 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0050 (80) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xF9, 0x63, 0x0F, 0x0F, 0x0F, 0x07,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,   // 0x0070 (112) pixels
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char showerRainDay[] PROGMEM = { //09d
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0,   // 0x0010 (16) pixels
    0x98, 0x3C, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00,   // 0x0020 (32) pixels
    0x00, 0x80, 0xE0, 0xF0, 0xF8, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0030 (48) pixels
    0xFF, 0xFC, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8, 0xE1, 0xCF, 0xDF, 0x9F, 0x3F, 0x7F, 0xFC, 0x7C, 0x7C,   // 0x0040 (64) pixels
    0x00, 0x01, 0x0F, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x3F, 0x2F, 0x1F, 0x1F, 0x9F, 0x1F, 0x1F,   // 0x0050 (80) pixels
    0x1F, 0x9F, 0x9F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x02, 0x00, 0x00, 0x00, 0x00,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x00, 0x00, 0x10, 0x13, 0x03, 0x01, 0x00,   // 0x0070 (112) pixels
    0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char showerRainNight[] PROGMEM = { //09n
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0,   // 0x0010 (16) pixels
    0x98, 0x3C, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00,   // 0x0020 (32) pixels
    0x00, 0x80, 0xE0, 0xF0, 0xF8, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0030 (48) pixels
    0xFF, 0xFC, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8, 0xE1, 0xCF, 0xDF, 0x9F, 0x3F, 0x7F, 0xFC, 0x7C, 0x7C,   // 0x0040 (64) pixels
    0x00, 0x01, 0x0F, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x3F, 0x2F, 0x1F, 0x1F, 0x9F, 0x1F, 0x1F,   // 0x0050 (80) pixels
    0x1F, 0x9F, 0x9F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x02, 0x00, 0x00, 0x00, 0x00,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x00, 0x00, 0x10, 0x13, 0x03, 0x01, 0x00,   // 0x0070 (112) pixels
    0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char rainDay[] PROGMEM = { //10d
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,   // 0x0010 (16) pixels
    0xF0, 0xE0, 0x8C, 0x3C, 0x7E, 0x7E, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xE0,   // 0x0020 (32) pixels
    0x00, 0xE0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0030 (48) pixels
    0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xE1, 0xEF, 0xEF, 0xCF, 0x9F, 0x3F, 0x1F,   // 0x0040 (64) pixels
    0x00, 0x03, 0x0F, 0x0F, 0x1F, 0x1F, 0x9F, 0xDF, 0x5F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F,   // 0x0050 (80) pixels
    0x0F, 0x1F, 0x1F, 0x1F, 0xDF, 0x3F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x00, 0x00,   // 0x0060 (96) pixels
    0x00, 0xC0, 0xC0, 0x00, 0x1C, 0x00, 0x01, 0x00, 0x00, 0x80, 0x40, 0x00, 0x0C, 0x02, 0x00, 0x00,   // 0x0070 (112) pixels
    0xC0, 0x30, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char rainNight[] PROGMEM = { //10n
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,   // 0x0010 (16) pixels
    0xF0, 0xE0, 0x80, 0x00, 0x02, 0x02, 0x03, 0x07, 0x0F, 0x1F, 0x7E, 0xFE, 0xFC, 0xFC, 0xF8, 0xE0,   // 0x0020 (32) pixels
    0x00, 0xE0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x0030 (48) pixels
    0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xE0, 0xE8, 0xEF, 0xCF, 0x9F, 0x3F, 0x1F,   // 0x0040 (64) pixels
    0x00, 0x03, 0x0F, 0x0F, 0x1F, 0x1F, 0x9F, 0xDF, 0x5F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F,   // 0x0050 (80) pixels
    0x0F, 0x1F, 0x1F, 0x1F, 0xDF, 0x3F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x00, 0x00,   // 0x0060 (96) pixels
    0x00, 0xC0, 0xC0, 0x00, 0x1C, 0x00, 0x01, 0x00, 0x00, 0x80, 0x40, 0x00, 0x0C, 0x02, 0x00, 0x00,   // 0x0070 (112) pixels
    0xC0, 0x30, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char thunderstormDay[] PROGMEM = { //11d
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xF0,   // 0x0010 (16) pixels
    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0020 (32) pixels
    0x00, 0x80, 0xC0, 0xC0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC,   // 0x0030 (48) pixels
    0xF9, 0xC3, 0xCF, 0xEF, 0xEF, 0xEF, 0x8F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xF8, 0xF8, 0xF8, 0xF0,   // 0x0040 (64) pixels
    0x00, 0x1F, 0x3F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0x1F, 0x03, 0x03, 0xC3, 0xC3, 0xFF, 0xFF,   // 0x0050 (80) pixels
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x38, 0x3B, 0x13, 0x03, 0x03, 0x03, 0x01,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00,   // 0x0070 (112) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char thunderstormNight[] PROGMEM = { //11n
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF0,   // 0x0010 (16) pixels
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xE0, 0xE0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0020 (32) pixels
    0x00, 0x80, 0x40, 0x40, 0x30, 0x30, 0x30, 0x3F, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,   // 0x0030 (48) pixels
    0x0F, 0x0F, 0x0C, 0x0C, 0x08, 0x08, 0x70, 0x70, 0xC0, 0x80, 0x80, 0x07, 0x08, 0x08, 0x08, 0xF0,   // 0x0040 (64) pixels
    0x00, 0x1F, 0x20, 0x20, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xE0, 0xFC, 0xFC, 0xFC, 0xFC, 0xC0, 0xC0,   // 0x0050 (80) pixels
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0x21, 0x21, 0x1E, 0x02, 0x02, 0x02, 0x01,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00,   // 0x0070 (112) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char snowDay[] PROGMEM = { //13d
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x20, 0xF0, 0xE0, 0x80, 0x0C, 0x1C, 0x3C, 0x78, 0xF7,   // 0x0010 (16) pixels
    0xFF, 0xFF, 0x70, 0x78, 0x78, 0x3C, 0x00, 0x00, 0xE0, 0xF0, 0x70, 0x00, 0x80, 0x80, 0x80, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x20, 0x31, 0x33, 0x3B, 0x3F, 0x3E, 0x3F, 0x1F, 0x3F, 0x38, 0xF8, 0xF0, 0xF0, 0x3F,   // 0x0030 (48) pixels
    0x3F, 0x3F, 0x38, 0xF8, 0xF0, 0xF0, 0x3C, 0x3F, 0x1F, 0x3F, 0x3E, 0x3F, 0x3B, 0x33, 0x33, 0x20,   // 0x0040 (64) pixels
    0x00, 0x00, 0x02, 0xC6, 0xEE, 0xEE, 0x7E, 0x7E, 0xFE, 0xFC, 0xFC, 0x0E, 0x0F, 0x07, 0x0F, 0xFE,   // 0x0050 (80) pixels
    0xFE, 0xFC, 0x0E, 0x0F, 0x07, 0x0F, 0x1E, 0x7E, 0xFC, 0xFE, 0x7E, 0x7E, 0xEE, 0xEE, 0xC6, 0x06,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x07, 0x00, 0x18, 0x1C, 0x1E, 0x0F, 0x7F,   // 0x0070 (112) pixels
    0xFF, 0xFF, 0x0F, 0x0F, 0x1E, 0x1C, 0x10, 0x00, 0x03, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char snowNight[] PROGMEM = { //13n
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x20, 0xF0, 0xE0, 0x80, 0x0C, 0x1C, 0x3C, 0x78, 0xF7,   // 0x0010 (16) pixels
    0xFF, 0xFF, 0x70, 0x78, 0x78, 0x3C, 0x00, 0x00, 0xE0, 0xF0, 0x70, 0x00, 0x80, 0x80, 0x80, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x20, 0x31, 0x33, 0x3B, 0x3F, 0x3E, 0x3F, 0x1F, 0x3F, 0x38, 0xF8, 0xF0, 0xF0, 0x3F,   // 0x0030 (48) pixels
    0x3F, 0x3F, 0x38, 0xF8, 0xF0, 0xF0, 0x3C, 0x3F, 0x1F, 0x3F, 0x3E, 0x3F, 0x3B, 0x33, 0x33, 0x20,   // 0x0040 (64) pixels
    0x00, 0x00, 0x02, 0xC6, 0xEE, 0xEE, 0x7E, 0x7E, 0xFE, 0xFC, 0xFC, 0x0E, 0x0F, 0x07, 0x0F, 0xFE,   // 0x0050 (80) pixels
    0xFE, 0xFC, 0x0E, 0x0F, 0x07, 0x0F, 0x1E, 0x7E, 0xFC, 0xFE, 0x7E, 0x7E, 0xEE, 0xEE, 0xC6, 0x06,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x07, 0x00, 0x18, 0x1C, 0x1E, 0x0F, 0x7F,   // 0x0070 (112) pixels
    0xFF, 0xFF, 0x0F, 0x0F, 0x1E, 0x1C, 0x10, 0x00, 0x03, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char mistDay[] PROGMEM = { //50d
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,   // 0x0010 (16) pixels
    0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C,   // 0x0030 (48) pixels
    0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,   // 0x0040 (64) pixels
    0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32,   // 0x0050 (80) pixels
    0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x30, 0x30, 0x30, 0x30, 0x20, 0x00, 0x00, 0x00,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,   // 0x0070 (112) pixels
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };

const char mistNight[] PROGMEM = { //50n
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,   // 0x0010 (16) pixels
    0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0020 (32) pixels
    0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C,   // 0x0030 (48) pixels
    0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,   // 0x0040 (64) pixels
    0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32,   // 0x0050 (80) pixels
    0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x30, 0x30, 0x30, 0x30, 0x20, 0x00, 0x00, 0x00,   // 0x0060 (96) pixels
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,   // 0x0070 (112) pixels
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // 0x0080 (128) pixels
    };
