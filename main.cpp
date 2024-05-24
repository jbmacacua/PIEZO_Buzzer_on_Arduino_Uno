#define NOTE_G4 392
#define NOTE_F4 349
#define NOTE_E4 330
#define NOTE_A4 440
#define NOTE_D4 294
#define NOTE_B4 494
#define NOTE_C5 523

const int buzzerPin = 9;
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 10};

float melody[] = {
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4, 
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_F4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4, 
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4,
  NOTE_A4, NOTE_A4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_C5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C5
};

int noteDurations[] = {
  4, 4, 4, 4, 4, 3,
  4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 3,
  4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 3,
  4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 3,
  4, 4, 4, 4, 4, 2
};

void setup() {
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  playSong(1.0);
  runningLights(1.0);

  playSong(0.75);
  runningLights(0.75);

  while (true); // Stop the loop after playing the song and lights
}

void playSong(float speed) {
  int numNotes = sizeof(melody) / sizeof(melody[0]);
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    int duration = noteDuration * speed;
    tone(buzzerPin, melody[thisNote], duration);

    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    noTone(buzzerPin);
    runningLightsDuringSong();
  }
}

void runningLights(float speed) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(100 * speed);
    digitalWrite(ledPins[i], LOW);
  }

  for (int i = 6; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(100 * speed);
    digitalWrite(ledPins[i], LOW);
  }
}

void runningLightsDuringSong() {
  static int ledIndex = 0;
  digitalWrite(ledPins[ledIndex], HIGH);
  delay(50);
  digitalWrite(ledPins[ledIndex], LOW);

  ledIndex++;
  if (ledIndex >= 8) {
    ledIndex = 0;
  }
}
