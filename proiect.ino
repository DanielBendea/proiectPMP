// variabile care au obiectele folosite
const int buton1 = 2;          // fiecare buton ii va corespunde un bec led galben sau rosu
const int buton2 = 3;         
const int buton3 = 4;          
const int buton4 = 5;    
   
const int bec1 = 7;
const int bec2 = 8;  
const int bec3 = 9;        
const int bec4 = 10;
   
const int buz = 12;           // buzzerul va suna la fiecare apasare de buton/aprindeere de led
const int sunet[4] = {1400, 1600, 1800, 2000};       // sunetul pe care il va face buzzerul la leduri



//// Variabile de debugging
int ok = 0;
int but;

//// Variabile program
int i;

//typedef struct {
  int stareButoane[] = {0, 0, 0, 0};

  int vecSequence[25];
  int nrSequence;
  
  int nLevel;
  int nCurentLevel;

  int becDelay;
  int becTime = 500;
  int speedFactor = 2;
  int speedBase = 150;
  
  int timpAsteptareApasareButon = 300;
  
  int gameOn;
//}GAME_STAT;
//GAME_STAT gameState;

// initializarea variabilelor de mai sus
void setup() {
  // put your setup code here, to run once:
  // variabilele
  nrSequence = 1;
  
  nLevel = 8;
  nCurentLevel = 1;
  
  gameOn = 1;
  
  // butoanele
  pinMode(buton1, INPUT);
  pinMode(buton2, INPUT);
  pinMode(buton3, INPUT);
  pinMode(buton4, INPUT);
  // ledurile
  pinMode(bec1, OUTPUT);
  pinMode(bec2, OUTPUT);
  pinMode(bec3, OUTPUT);
  pinMode(bec4, OUTPUT);
  // buzzerul
  pinMode(buz, OUTPUT);

  randomSeed(analogRead(0));
  
  Serial.begin(9600);
}

void sunetBuzz(int ton, int timp) {
  for(long i = 0; i < timp * 1500L; i = i + ton) {
    digitalWrite(buz, HIGH);
    delayMicroseconds(ton);
    digitalWrite(buz, LOW);
    delayMicroseconds(ton);
  }
}

void refreshGameSequence(int v[], int n) {
  // v este un vector de dimensiune variabila, in care se va memora ordinea ledurilor care vor fi aprinse
  for(i = 0; i < n; i++) {
    v[i] = 0;
    // prea mic
    //int randN = random(1, 100); // luam o valoare aleatorie intre 1 si 100 si in functie de valoarea acesteia asignam un bec
    // 1 - 25 -> bec1
    // 26 - 50 -> bec2
    // 51 - 75 -> bec3
    // 76 - 100 -> bec4
    
    int randN = random(1, 200); // luam o valoare aleatorie intre 1 si 100 si in functie de valoarea acesteia asignam un bec
    // 1 - 50 -> bec1
    // 51 - 100 -> bec2
    // 101 - 150 -> bec3
    // 151 - 200 -> bec4
    
    if(randN <= 50) {
      v[i] = 0;
    }
    else {
      if(randN <= 100) {
        v[i] = 1;
      }
      else {
        if(randN <= 150) {
          v[i] = 2;
        }
        else {
          if(randN <= 200) {
            v[i] = 3;
          }
        }
      }
    }
  }
}

void showSequence() {
  delay (200);
  Serial.print("seq :\n");
  for (i = 0; i < nCurentLevel; i++){
    becDelay = becTime/(1+(speedFactor/nLevel)*(nCurentLevel - 1));
    
    Serial.println(vecSequence[i]);
    Serial.print(" ");
    
    digitalWrite(vecSequence[i]+7, HIGH);
    sunetBuzz(sunet[vecSequence[i]], becDelay);
    digitalWrite(vecSequence[i]+7, LOW);
    
    delay(speedBase/speedFactor);
  }
}

void evaluateSequence() {
  int j = 0;
  int butonApasat = 0;
  while(j < nCurentLevel && gameOn == 1) {
    Serial.println("ButonApasat");
    
    butonApasat = 0;
    for(int i = 0; i < 4; i++) {
      stareButoane[i] = LOW;
    }
    
    while(butonApasat == 0) {
      for(i = 0;i < 4; i++) {
        stareButoane[i] = digitalRead(i+2);
        if(stareButoane[i] > 0) {
          Serial.print(i);
          butonApasat++;
          break;
        }
      }
    }

    Serial.println("ButonApasat_2");
    for(i = 0;i < 4; i++) {
      if(stareButoane[i] == HIGH) {
        digitalWrite(i+7, HIGH);
        sunetBuzz(sunet[vecSequence[i]], becDelay);
        digitalWrite(i+7, LOW);
        Serial.print(i);
        if(vecSequence[j] == i) {
          j++;
        }
        else {
          gameOn = 0;
        }
      }
    }
  }
}

void loadNextLevel() {
  nCurentLevel++;
  speedFactor++;
  becTime = becTime - 25;
  if(nCurentLevel%5 == 0) {
    speedBase = speedBase + 50;
  }
}

void loadLoseSignal() {
  for(i = 0; i < 4; i++) {
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    sunetBuzz(2500, 200);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);

    delay(200);
  }
}

void loadVictorySignal() {
  gameOn = 0;
  delay(500);
  
  int tempoSounds[6] = {100, 100, 200, 200, 300}; 
  
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  sunetBuzz(sunet[0], tempoSounds[0]);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  delay(100);

  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  sunetBuzz(sunet[3], tempoSounds[1]);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  delay(100);

  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  sunetBuzz(sunet[1], tempoSounds[2]);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  delay(200);

  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  sunetBuzz(sunet[2], tempoSounds[3]);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  delay(200);

  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  sunetBuzz(sunet[2], tempoSounds[4]);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  delay(300); 
}

void testWindow() {
  //// test led
  //digitalWrite(6, HIGH);
  //delay(100);
  //digitalWrite(6, LOW);
  //delay(250);
  
  //// test buton
  //but = digitalRead(9);
  //if(but == HIGH) {
  //  digitalWrite(6, HIGH);
  //  delay(100);
  //  digitalWrite(6, LOW);
  //}

  //// test buzzer
  //but = digitalRead(9);
  //if(but == HIGH) {
  //  digitalWrite(buz, HIGH);
  //  delayMicroseconds(2500);
  //  digitalWrite(buz, LOW);
  //}

  //// test sunteBuzz
  //but = digitalRead(9);
  //if(but == HIGH) {
  //  sunetBuzz(1500,200);
  //}

  //// test refreshGameSequence
  if(ok == 0) {
    int v[10];
    int n = 8;
    refreshGameSequence(v, n);
    for(i = 0;i < n; i = i + 1) {
      //Serial.write(v[i]);
      Serial.print(v[i]);
    }
    ok = ok + 1;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // testWindow();
  if(gameOn == 1) {
    refreshGameSequence(vecSequence, nrSequence);
    showSequence();
    evaluateSequence();
    if(gameOn == 1) {
      loadNextLevel();
    }
    else {
      loadLoseSignal();
    }
    if(nLevel == nCurentLevel) {
      loadVictorySignal();
    }
  }
}
