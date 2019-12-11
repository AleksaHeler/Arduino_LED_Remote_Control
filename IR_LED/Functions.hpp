
enum Mode { NORMAL, FLASH, STROBE, FADE, SMOOTH };
Mode mode = NORMAL;
unsigned long prevTime = 0; // Keeping track of time for animations

int r = 0;              // RGB analog values (0-255)
int g = 0;
int b = 0;
int bright = 255;       // LED brightness
int bright_step = 20;

int clamp(int, int, int);
int setBrightness(int);
void setRandomColor();

void handle_ir(long val){
  mode = NORMAL;
  switch(val){
    case CODE_ON:   setRandomColor();   break;
    case CODE_OFF:  r=0;  g=0;  b=0;    break;
    
    case CODE_INC: bright+=bright_step; break;
    case CODE_DEC: bright-=bright_step; break;
    
    case CODE_R:   r=255; g=0;   b=0;   break;
    case CODE_G:   r=0;   g=255; b=0;   break;
    case CODE_B:   r=0;   g=0;   b=255; break;
    case CODE_W:   r=255; g=255; b=255; break;
  
    case CODE_R1:  r=200; g=0;   b=0;   break;
    case CODE_R2:  r=150; g=0;   b=0;   break;
    case CODE_R3:  r=100; g=0;   b=0;   break;
    case CODE_R4:  r=50;  g=0;   b=0;   break;
  
    case CODE_G1:  r=0;   g=200; b=0;   break;
    case CODE_G2:  r=0;   g=150; b=0;   break;
    case CODE_G3:  r=0;   g=100; b=0;   break;
    case CODE_G4:  r=0;   g=50;  b=0;   break;
  
    case CODE_B1:  r=0;   g=0;   b=200; break;
    case CODE_B2:  r=0;   g=0;   b=150; break;
    case CODE_B3:  r=0;   g=0;   b=100; break;
    case CODE_B4:  r=0;   g=0;   b=50;  break;
  
    case CODE_FLASH:   mode = FLASH;  break;
    case CODE_STROBE:  mode = STROBE; break;
    case CODE_FADE:    mode = FADE;   break;
    case CODE_SMOOTH:  mode = SMOOTH; break;
    
    default: break;
  }
}

void set_led(){
  bright = clamp(bright, 0, 255);
  int tr=0, tg=0, tb=0;

  /// NORMAL MODE
  if(mode == NORMAL){
    tr = setBrightness(r);
    tg = setBrightness(g);
    tb = setBrightness(b);
  }
  /// FLASH MODE
  else if(mode == FLASH){
    unsigned long curTime = millis();
    if(curTime - prevTime < 1000){       // During first second ms turn leds on
      tr = setBrightness(r);
      tg = setBrightness(g);
      tb = setBrightness(b);
    }
    else if(curTime - prevTime < 2000){ // During second second turn leds off
      tr = 0;
      tg = 0;
      tb = 0;
    }else prevTime = curTime;           // Reset timer
  }
  /// STROBE MODE
  else if(mode == STROBE){
    unsigned long curTime = millis();
    if(curTime - prevTime < 1000){
      tr = setBrightness(r);
      tg = setBrightness(g);
      tb = setBrightness(b);
    }else {
      // Every 1000 ms change color
      setRandomColor();
      prevTime = curTime;
    }
  }

  // Clamp values and apply
  tr = clamp(tr, 0, 255);
  tg = clamp(tg, 0, 255);
  tb = clamp(tb, 0, 255);
  analogWrite(R_PIN, tr);
  analogWrite(G_PIN, tg);
  analogWrite(B_PIN, tb);
}

int clamp(int val, int min, int max){
  if(val < min){
    val = min;
  }
  if(val > max){
    val = max;
  }
  return val;
}

int setBrightness(int val){
  float x = 1.0*val*bright/255.0;
  int temp = clamp((int)x,0,255);
  return temp;
}

void setRandomColor(){
  r = clamp(random(0,255), 0, 255);
  g = clamp(random(0,255), 0, 255);
  b = clamp(random(0,255), 0, 255);
}

  
