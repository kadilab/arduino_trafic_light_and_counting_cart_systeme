// Déclaration des broches pour les feux de signalisation
const int feuRougeVoie1 = 4;
const int feuOrangeVoie1 = 3;
const int feuVertVoie1 = 2;
const int feuRougeVoie2 = 7;
const int feuOrangeVoie2 = 6;
const int feuVertVoie2 = 5;

// Déclaration des broches pour les capteurs ultrasoniques
const int trigPin1 = 8;
const int echoPin1 = 9;
const int trigPin2 = 10;
const int echoPin2 = 11;

// Variables pour le contrôle des feux de signalisation
unsigned long tempsDepart;
unsigned long delaiFeuVert = 5000;
unsigned long delaiFeuOrange = 2000;

// Variables pour le comptage des voitures
int compteurVoie1 = 0;
int compteurVoie2 = 0;
//condition 
static bool estAuDessusDe10 = false; // Variable pour suivre l'état précédent
static bool estAuDessusDe20 = false; // Variable pour suivre l'état précédent


void setup() {
  // Configuration des broches comme des sorties
  pinMode(feuRougeVoie1, OUTPUT);
  pinMode(feuOrangeVoie1, OUTPUT);
  pinMode(feuVertVoie1, OUTPUT);
  pinMode(feuRougeVoie2, OUTPUT);
  pinMode(feuOrangeVoie2, OUTPUT);
  pinMode(feuVertVoie2, OUTPUT);
  // Configuration des broches comme des sorties ou des entrées
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Initialisation du moniteur série
  Serial.begin(9600);

  // Mémorisation du temps de départ
  tempsDepart = millis();
}

void loop() {
  // Mesure de la distance avec le capteur 1
  float distanceCapteur1 = mesurerDistanceCapteur1();
  // Mesure de la distance avec le capteur 2
  float distanceCapteur2 = mesurerDistanceCapteur2();

  // Contrôle des feux de signalisation
  // Vérification si une voiture est passée à moins de 10 cm des capteurs
//    if (distanceCapteur1 < 10) {
//        compteurVoie1++;
//          envoyerNombreVoitures();
//
//    }
//
//    if (distanceCapteur2 < 10) {
//        compteurVoie2++;
//          envoyerNombreVoitures();
//
//    }

if (distanceCapteur1 > 20 && !estAuDessusDe10) {
    // La valeur est montée au-dessus de 10
    estAuDessusDe10 = true;
    delay(500);
} else if (distanceCapteur1 < 10 && estAuDessusDe10) {
    // La valeur est redescendue en dessous de 10
    estAuDessusDe10 = false;
    compteurVoie1++; // Incrémentation du compteur
    envoyerNombreVoitures();
}
  
if (distanceCapteur2 > 20 && !estAuDessusDe20) {
    // La valeur est montée au-dessus de 10
    estAuDessusDe20 = true;
    delay(500);
} else if (distanceCapteur2 < 10 && estAuDessusDe20) {
    // La valeur est redescendue en dessous de 10
    estAuDessusDe20 = false;
    compteurVoie2++; // Incrémentation du compteur
    envoyerNombreVoitures();
}
  
  unsigned long tempsEcoule = millis() - tempsDepart;

  if (tempsEcoule < delaiFeuVert) {
    // Voie 1 - Feu vert, voie 2 - Feu rouge
    digitalWrite(feuVertVoie1, HIGH);
    digitalWrite(feuRougeVoie1, LOW);
    digitalWrite(feuOrangeVoie1, LOW);
    digitalWrite(feuVertVoie2, LOW);
    digitalWrite(feuRougeVoie2, HIGH);
    digitalWrite(feuOrangeVoie2, LOW);
  } else if (tempsEcoule < (delaiFeuVert + delaiFeuOrange)) {
    // Voie 1 - Feu orange
    digitalWrite(feuVertVoie1, LOW);
    digitalWrite(feuRougeVoie1, LOW);
    digitalWrite(feuOrangeVoie1, HIGH);
  } else if (tempsEcoule < (2 * delaiFeuVert + delaiFeuOrange)) {
    // Voie 1 - Feu rouge, voie 2 - Feu vert
    digitalWrite(feuVertVoie1, LOW);
    digitalWrite(feuRougeVoie1, HIGH);
    digitalWrite(feuOrangeVoie1, LOW);
    digitalWrite(feuVertVoie2, HIGH);
    digitalWrite(feuRougeVoie2, LOW);
    digitalWrite(feuOrangeVoie2, LOW);
  } else if (tempsEcoule < (2 * delaiFeuVert + 2 * delaiFeuOrange)) {
    // Voie 2 - Feu orange
    digitalWrite(feuVertVoie2, LOW);
    digitalWrite(feuRougeVoie2, LOW);
    digitalWrite(feuOrangeVoie2, HIGH);
  } else {
    // Réinitialisation du temps de départ
    tempsDepart = millis();

  }
}

float mesurerDistanceCapteur1() {
  // Envoi d'une impulsion ultrasonique pour le capteur 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Lecture de la durée de l'impulsion écho pour le capteur 1
  long duration = pulseIn(echoPin1, HIGH);

  // Calcul de la distance pour le capteur 1
  float distance = (duration * 0.0343) / 2;

  return distance;
}

float mesurerDistanceCapteur2() {
  // Envoi d'une impulsion ultrasonique pour le capteur 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  // Lecture de la durée de l'impulsion écho pour le capteur 2
  long duration = pulseIn(echoPin2, HIGH);

  // Calcul de la distance pour le capteur 2
  float distance = (duration * 0.0343) / 2;

  return distance;
}

void envoyerNombreVoitures() {
  // Envoi du nombre de voitures via la voie série
//  Serial.print("Voitures nombre : ");
  Serial.println(compteurVoie1+compteurVoie2);

}
