import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;
import java.awt.Toolkit;

void CopyToClipboard(String s) {
  Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
  StringSelection data = new StringSelection(s);
  clipboard.setContents(data, data);
}

void setup(){
 size(250,250);
 }
float x=125;
float y=115;
int r=0;
int g=0;
int b=0;
int check=1;
String rgb;

void draw(){
  background(255);
  textSize(25);
  fill(0);
  text("Color Maker",60,20);
  textSize(13);
  text("pls press & release mouse or M key",30,40);
  fill(r,g,b);
  textSize(18);
  text("RGB :  "+r+" , "+g+" , "+b,50,210);
  
  if(check==1){
    textSize(15);
    text("copy :  press C key",65,240);
  }else if(check==0){
    textSize(15);
    text("copied!",105,240);
  }
  
  noStroke();
  rgb=r+","+g+","+b;

  ellipse(x,y,100,100);
  
  if(mousePressed){
    check=1;
    r=int(random(0,256));
    g=int(random(0,256));
    b=int(random(0,256));
  }else if(keyPressed){
   if(key=='m'||key=='M') {
    check=1;
    r=int(random(0,256));
    g=int(random(0,256));
    b=int(random(0,256));
   }
  }
}

void keyPressed(){
  if(key=='c'||key=='C'){
  CopyToClipboard("//"+rgb);
  check=0;
  }
}
