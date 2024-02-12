void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);

  randomSeed(analogRead(5));
}

double t0;
void loop() {
  
  //while (Serial.read() != '\n');
  Serial.println("Temps (s)");

  int i;
  t0 = millis()/1000.0;
  for (i=0; i<10; i++){
    // Tour de l'ordinateur
    // choix aleatoire de la led a allumer
    double notes[4] = {523, 659, 784, 880};
    long r = random(10,14); //random nombre entre 10 et 13 inclus
    digitalWrite(r, HIGH);
    tone(8, notes[r-10], 100);
    delay(100);
    digitalWrite(r, LOW);
  
  
    // Tour du joueur
    double t1 = millis()/1000.0 - t0;
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    int photo10 = analogRead(3);
    int photo11 = analogRead(2);
    int photo12 = analogRead(1);
    int photo13 = analogRead(0);

    /*Serial.println(photo10);
    Serial.println(photo11);
    Serial.println(photo12);
    Serial.println(photo13);*/
  
    while (photo10 < 450 && photo11 < 500 && photo12 < 500 && photo13 < 500){
      photo13 = analogRead(0);
      photo12 = analogRead(1);
      photo11 = analogRead(2);
      photo10 = analogRead(3);
    }

    double t2 = millis()/1000.0 - t0;
    int test;
    if (photo10 >= 450){
      digitalWrite(10, HIGH);
      test = 10;
      tone(8, 523, 100);
    }
    else {
      if (photo11 >= 500){
        test = 11;
        digitalWrite(11, HIGH);
        tone(8, 659, 100);
      }
      else {
        if (photo12 >= 500){
          test = 12;
          digitalWrite(12, HIGH);
          tone(8, 784, 100);
        }
        else {
          if (photo13 >= 500){
            test = 13;
            digitalWrite(13, HIGH);
            tone(8, 880, 100);
          }
        }
      }
    }
    delay(100);
  
    // Verification de la LED : si le joueur a appuye sur la mauvaise note, il a perdu
    
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);

    delay(1000);
    if (test != r){
      break;
    }
    Serial.println(t2-t1);
  }

  if (i == 10){
    // victoire !
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    double gDoMaj[8] = {523,587,659,698.5,784,880,988,1046.5};
    for (int j=0; j<8; j++){
      tone(8, gDoMaj[j], 100);
      delay(101);
    }
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  else {
    // perdu !
    double gDoMin[8] = {262,294,311,349,392,415,466,523};
    for (int j=7; j>=0; j--){
      tone(8, gDoMin[j], 100);
      delay(101);
    }
  }
  
}
