#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BUTTON_PIN A4

#define Glyph_Width 5
#define Glyph_Height 8
#define ScreenTileNumX 16

struct Glyph {
  uint8_t val[8]; // index is row, bit is column
};

// row major!
struct GlyphImage {
  uint8_t pixels[Glyph_Height][Glyph_Width];
  uint8_t GetPixel(const int x, const int y) {
    return pixels[y][x];
  }
  void SetPixel(const int x, const int y, const uint8_t val) {
    pixels[y][x] = val;
  }
};

Glyph g_fullGlyph = Glyph{0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xf0};

// image[row][column]
static inline Glyph GenerateGlyph(GlyphImage image) {
  Glyph result = {};
  for(int y = 0; y < Glyph_Height; y++) {
    for(int x = 0; x < Glyph_Width; x++) {
      if(image.GetPixel(x,y) != 0) {
        result.val[y] |= 1 << (Glyph_Width-1 - x);
      }
    }
  }
  return result;
}

#define TileIndex_Flat 0
#define TileIndex_Full 1
#define TileIndex_UpRampHigh 2
#define TileIndex_UpRampLow 3
#define TileIndex_DownRampHigh 4
#define TileIndex_DownRampLow 5

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  lcd.begin();
  lcd.backlight();

  // generate glyps
  {
    Glyph GlyphTable[6] = {};


    GlyphTable[TileIndex_Flat] = GenerateGlyph(GlyphImage{{
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
      }});

    GlyphTable[TileIndex_Full] = GenerateGlyph(GlyphImage{{
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
      }});
      
    GlyphTable[TileIndex_UpRampHigh] = GenerateGlyph(GlyphImage{{
        {0,0,0,0,1},
        {0,0,0,1,1},
        {0,0,1,1,1},
        {0,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
      }});
     
    GlyphTable[TileIndex_UpRampLow] = GenerateGlyph(GlyphImage{{
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,1},
        {0,0,0,1,1},
        {0,0,1,1,1},
        {0,1,1,1,1},
      }});
 
    GlyphTable[TileIndex_DownRampHigh] = GenerateGlyph(GlyphImage{{
        {1,0,0,0,0},
        {1,1,0,0,0},
        {1,1,1,0,0},
        {1,1,1,1,0},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
      }});
  
    GlyphTable[TileIndex_DownRampLow] = GenerateGlyph(GlyphImage{{
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {1,0,0,0,0},
        {1,1,0,0,0},
        {1,1,1,0,0},
        {1,1,1,1,0},
      }});

    lcd.createChar(TileIndex_Flat, GlyphTable[TileIndex_Flat].val);
    lcd.createChar(TileIndex_Full, GlyphTable[TileIndex_Full].val);
    lcd.createChar(TileIndex_UpRampHigh, GlyphTable[TileIndex_UpRampHigh].val);
    lcd.createChar(TileIndex_UpRampLow,  GlyphTable[TileIndex_UpRampLow].val);
    lcd.createChar(TileIndex_DownRampHigh, GlyphTable[TileIndex_DownRampHigh].val);
    lcd.createChar(TileIndex_DownRampLow,  GlyphTable[TileIndex_DownRampLow].val);
  }

  lcd.home();

  // init random()
  randomSeed(analogRead(0));
}

int clamp(int x, int low, int high) {
  if(x < low) return low;
  if(x > high) return high;
  return x;
}

void loop() {
  lcd.clear();
  lcd.home();

  static int TileRingBuf[ScreenTileNumX] = {}; // stores TileIndex
  static int TileRingBufIndex = 0;
  TileRingBufIndex++;

  // map generator
  {
    static int GeneratorHeight = 0;
    const int offset = random(0, 10) - 5;
    const int prev_GeneratorHeight = GeneratorHeight;
    GeneratorHeight += offset;
    GeneratorHeight = clamp(GeneratorHeight, 0, 3);
    int index = 0;
    if(offset > 0) index = TileIndex_Full;
    TileRingBuf[(TileRingBufIndex - 1) % ScreenTileNumX] = TileIndex_Full;
  }
  

  TileRingBuf[0] = TileIndex_UpRampLow;
  TileRingBuf[1] = TileIndex_UpRampHigh;
  TileRingBuf[2] = TileIndex_Full;
  TileRingBuf[3] = TileIndex_DownRampHigh;
  TileRingBuf[4] = TileIndex_DownRampLow;
  

  // handle button input
  const int button_val = 0; //digitalRead(BUTTON_PIN);
  static bool button_down = false;
  const bool prev_button_down = button_down;
  button_down = button_val == HIGH ? false : true;
  const bool button_pressed = !prev_button_down && button_down;

  float mil = millis();

  lcd.setCursor(0, 0);
  for(int i = 0; i < 16; i++) {
    lcd.write(TileRingBuf[(TileRingBufIndex + i) % ScreenTileNumX]);
  }

  lcd.setCursor(0, 1);
  // lcd.print("hello");
  for(int i = 0; i < 16; i++) lcd.write((i-2) % 6);


  delay(200);
}
