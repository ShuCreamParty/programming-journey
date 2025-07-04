int groupChoice1, groupChoice2, groupChoice3, groupChoice4, groupChoice5;//サイコロの目
int[] count = {0, 0, 0, 0, 0, 0};
boolean[] yaku = {false, false, false, false, false, false, false, false, false, false, false, false};//1,2,3,4,5,6,チョイス,4ダイス,フルハウス,sスト,bスト,ヨット

void draw() {
}

//仮
void mousePressed() {
  mazemaze();
  print(str(groupChoice1)+str(groupChoice2)+str(groupChoice3)+str(groupChoice4)+str(groupChoice5));
  counter();
  hantei();
}

//サイコロ振るやつ　不要
void mazemaze() {
  for (int i=0; i < 6; i++) {
    count[i]=0;
  }
  for (int i = 0; i < yaku.length; i++) {
    yaku[i] = false;
  }
  groupChoice1 = int(random(6));
  groupChoice2 = int(random(6));
  groupChoice3 = int(random(6));
  groupChoice4 = int(random(6));
  groupChoice5 = int(random(6));
}

//サイコロの目カウント
void counter() {
  for (int i = 0; i<6; i++) {
    if (groupChoice1 == i) {
      count[i] += 1;
    }
    if (groupChoice2 == i) {
      count[i] += 1;
    }
    if (groupChoice3 == i) {
      count[i] += 1;
    }
    if (groupChoice4 == i) {
      count[i] += 1;
    }
    if (groupChoice5 == i) {
      count[i] += 1;
    }
  }
}

//まとめたかっただけ
void hantei() {
  number();
  four();
  full();
  ryanmen();
  piano();
  yot();
}

//以下判定用
void number() {
  for (int i = 0; i<6; i++) {
    if (count[i] != 0) {
      yaku[i]=true;
    }
  }
}

void four() {
  for (int i = 0; i<6; i++) {
    if (count[i] >= 4) {
      yaku[7]=true;
    }
  }
}

void full() {
  boolean hasThree = false;
  boolean hasTwo = false;

  for (int i = 0; i < 6; i++) {
    if (count[i] == 3) hasThree = true;
    if (count[i] == 2) hasTwo = true;
  }

  if (hasThree && hasTwo) {
    yaku[8] = true;
  }
}

void ryanmen() {
  if ((count[0] != 0 && count[1] != 0 && count[2] != 0 && count[3] != 0) || (count[1] != 0 && count[2] != 0 && count[3] != 0 && count[4] != 0) || (count[2] != 0 && count[3] != 0 && count[4] != 0 && count[5] != 0)) {
    yaku[9]=true;
  }
}

void piano() {
  if ((count[0] != 0 && count[1] != 0 && count[2] != 0 && count[3] != 0 &&count[4] != 0)||(count[1] != 0 && count[2] != 0 && count[3] != 0 && count[4] != 0 &&count[5] != 0)) {
    yaku[10]=true;
  }
}

void yot() {
  if (count[0] == 5 || count[1] == 5 || count[2] == 5 || count[3] == 5 || count[4] == 5 || count[5] == 5) {
    yaku[11]=true;
    return;
  }
}
