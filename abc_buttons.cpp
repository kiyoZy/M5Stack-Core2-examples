#include <M5Unified.h>

enum ButtonState {
  NONE,
  A_PRESSED,
  B_PRESSED,
  C_PRESSED
};

ButtonState state = NONE;

// 柔らかい色（RGB565）
uint16_t softRed   = M5.Display.color565(220, 80, 80);
uint16_t softYellow= M5.Display.color565(240, 210, 80);
uint16_t softBlue  = M5.Display.color565(80, 120, 220);

void drawBaseUI() {
  M5.Display.fillScreen(BLACK);

  // 下部の A B C 表示
  M5.Display.setTextSize(3);
  M5.Display.setTextColor(WHITE);

  int y = 220;  // Core2 の下部に合わせる
  M5.Display.setCursor(40,  y); M5.Display.print("A");
  M5.Display.setCursor(140, y); M5.Display.print("B");
  M5.Display.setCursor(240, y); M5.Display.print("C");
}

void drawBox(ButtonState s) {
  // 画面中央に少し小さめの四角
  int margin = 20;
  int x1 = margin;
  int y1 = margin;
  int x2 = M5.Display.width()  - margin;
  int y2 = 200 - margin;  // 下の ABC を隠さない

  uint16_t color = BLACK;

  switch (s) {
    case A_PRESSED: color = softRed; break;
    case B_PRESSED: color = softYellow; break;
    case C_PRESSED: color = softBlue; break;
    default: return;
  }

  M5.Display.fillRect(x1, y1, x2 - x1, y2 - y1, color);

  // 中央に文字（黒で抜くイメージ）
  M5.Display.setTextColor(BLACK);
  M5.Display.setTextSize(6);
  M5.Display.setCursor((x1 + x2) / 2 - 15, (y1 + y2) / 2 - 20);

  if (s == A_PRESSED) M5.Display.print("A");
  if (s == B_PRESSED) M5.Display.print("B");
  if (s == C_PRESSED) M5.Display.print("C");
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  drawBaseUI();
}

void loop() {
  M5.update();

  ButtonState newState = NONE;

  if (M5.BtnA.wasPressed()) newState = A_PRESSED;
  if (M5.BtnB.wasPressed()) newState = B_PRESSED;
  if (M5.BtnC.wasPressed()) newState = C_PRESSED;

  if (newState != NONE) {
    drawBaseUI();   // 下の ABC を残す
    drawBox(newState);
  }

  delay(10);
}
