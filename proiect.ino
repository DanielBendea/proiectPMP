// variabile care au obiectele folosite
const int buton1 = 2;          // fiecare buton ii va corespunde un bec led galben sau rosu
const int buton2 = 3;         
const int buton3 = 4;          
const int buton4 = 5;       
const int bec1 = 6;
const int bec2 = 7;  
const int bec3 = 8;        
const int bec4 = 9;
   
const int buz = 10;           // buzzerul va suna la fiecare apasare de buton/aprindeere de led
const int sunet[] = {};       // sunetul pe care il va face buzzerul

// initializarea variabilelor de mai sus
void setup() {
  // put your setup code here, to run once:
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


//// Variabile de debugging
int ok = 0;
int but;

//// Variabile program
int becAprins = 300;
int timpAsteptareApasareButon = 300;
int i;

int stareButoane[] = {0, 0, 0, 0};

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

void testWindow() {
  // put your main code here, to run repeatedly:
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
  testWindow();
}
