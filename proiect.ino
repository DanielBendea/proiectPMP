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
const int sunet[] = {};       // sunetul pe care il va face buzzerul



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
  int speedFactor = 5;
  
  int timpAsteptareApasareButon = 300;
  
  int gameOn;
//}GAME_STAT;
//GAME_STAT gameState;

// initializarea variabilelor de mai sus
void setup() {
  // put your setup code here, to run once:
  // variabilele
  gameState.nrSequence = 1;
  
  gameState.nLevel = 15;
  gameState.nCurentLevel = 1;
  
  gameState.gameOn = 1;
  
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
  for(i = 0; i < n; i=i+1) {
    v[i] = 0;
    int randN = random(1, 100); // luam o valoare aleatorie intre 1 si 100 si in functie de valoarea acesteia asignam un bec
    // 1 - 25 -> bec1
    // 26 - 50 -> bec2
    // 51 - 75 -> bec3
    // 76 - 100 -> bec4
    if(randN <= 25) {
      v[i] = 0;
    }
    else {
      if(randN <= 50) {
        v[i] = 1;
      }
      else {
        if(randN <= 75) {
          v[i] = 2;
        }
        else {
          if(randN <= 100) {
            v[i] = 3;
          }
        }
      }
    }
  }
}

void showSequence() {
  delay (200);
  for (i = 0; i < currentlevel; i= i + 1){
    becDelay = becTime/(1+(speedFactor/nLevel)*(nCurentLevel - 1));
    
    digitalWrite(vecSequence[i]+7, HIGH);
    sunetBuzz(tones[vecSequence[i]], becDelay);
    digitalWrite(vecSequence[i]+7, LOW);
    
    delay(150/speedfactor);
  }
}

void evaluateSequence() {
  int j = 0;
  int butonApasat = 0;
  while(j < nCurentLevel) {
    while(butonApasat == 0) {
      for(i = 0;i < 4; i++) {
        stareButoane[i] = digitalRead(i+2);
        if(stareButoane[i] > 0) {
          butonPasat++;
          break;
        }
      }
    }
  }
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
  testWindow();
}
