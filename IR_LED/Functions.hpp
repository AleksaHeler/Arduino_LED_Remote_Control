
int r = 0;              // RGB analog values (0-255)
int g = 0;
int b = 0;
int bright = 255;       // LED brightness
int bright_step = 20;

void handle_ir(long val){
  switch(val){
    case CODE_ON:   r=0;  g=0;  b=0;    break;
    case CODE_OFF:  r=0;  g=0;  b=0;    break;
    
    case CODE_INC: bright+=bright_step; break;
    case CODE_DEC: bright-=bright_step; break;
    
    case CODE_R:   r=255; g=0;   b=0;   break;
    case CODE_G:   r=0;   g=255; b=0;   break;
    case CODE_B:   r=0;   g=0;   b=255; break;
    case CODE_W:   r=255; g=255; b=255; break;
  
    //All colors
  
    //Different modes
    
    default: break;
  }
}

void set_led(){
  if(brightness < 0){ brightness = 0; }
  if(brightness > 255){ brightness = 255; }
  
  if(on){
    int t_r = r - (255-brightness);
    int t_g = g - (255-brightness);
    int t_b = b - (255-brightness);
    if(t_r < 0){ t_r = 0; }
    if(t_r > 255){ t_r = 255; }
    if(t_g < 0){ t_g = 0; }
    if(t_g > 255){ t_g = 255; }
    if(t_b < 0){ t_b = 0; }
    if(t_b > 255){ t_b = 255; }
    analogWrite(R_PIN, t_r);
    analogWrite(G_PIN, t_g);
    analogWrite(B_PIN, t_b);
  } else {
    digitalWrite(R_PIN, LOW);
    digitalWrite(G_PIN, LOW);
    digitalWrite(B_PIN, LOW);
  }
}
