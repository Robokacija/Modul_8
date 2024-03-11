//Upute za izradu prve igrice na uređaju M5Stack
//Sve iza dvije kose crte su komentari i i ne rade ništa u programu.
//Kod programiranja je korisno pisati komentare kako bi vam kasnije lakše znali ćemu služi koji dio programa

#include <M5Stack.h> //Ova naredba uključuje library M5Stack u program

//Ovdje definiramo neke varijable koje se nikada ne mijenjaju - npr. visina i širina ekrana su uvijek iste
#define P_W 5     //Širina igrača
#define P_H 10    //Visina igrača
#define A_H 5     //Veličina jabuke
#define S_H 240   //Visina ekrana
#define S_W 320   //Širina ekrana

//Ovdje definiramo neke varijable koje kasnije možemo promijeniti - npr. bodovi ili timer
int P_time = millis();  //Timer koji koristimo za micanje igrača
int A_time = millis();  //Timer koji koristimo za micanje jabuke

//Ovdje definiramo strukture kako bi spojili sve varijable nekog lika na jedno mjesto
struct Player_struct{ //Deklaracija i ime vrste strukture
  int x;              //Varijable koje definiramo kao dio strukture
}player;              //Ime strukture

struct Apple_struct{
  int x;
  int y;
};

Apple_struct apple;   //Ime strukture vrste Apple_struct - 
//ako želimo dodati nove strukture s istim varijablama, ponovimo onu naredbu i promijenimo ime - npr. umjesto apple upišemo onion

//Ovdje programiramo stvari koje se dogode samo jednom - npr. inicijalizacija pinova 
void setup() {
  M5.begin();
  M5.Power.begin();
  player.x = S_W / 2;             //Stavimo početnu x poziciju igrača
  apple.x = random(0, S_W - A_H); //Stavimo x poziciju jabuke na nasumično mjesto na ekranu
  apple.y = 0;
}

//Ovdje upisujemo naredbe koje želimo da se ponavljaju - kao forever u mblocku
void loop() {
  movement(); //Ovdje pozivamo funkciju movement koju smo sami napravili
  score();    //Ovdje pozivamo funkciju score koju smo sami napravili
}

// Ovdje definiramo funkciju score koja provjerava je li igrač pokupio jabuku
void score(){
  //Ako je y pozicija jabuke veća ili jednaka visini ekrana minus visina igrača minus visina jabuke (jabuka se nalazi pri dnu ekrana)
  if (apple.y >= S_H - P_H - A_H){
    //Ako je x pozicija igrača veća od x pozicije jabuke minus veličina jabuke i ako je x pozicija igrača manja od x pozicije jabuke plus veličina jabuke
    if (player.x >= apple.x - A_H && player.x <= apple.x + A_H){
      M5.Lcd.fillRect(apple.x, apple.y, A_H, A_H, M5.Lcd.color565(0,0,0)); //Brišemo jabuku sa ekrana
      apple.x = random(0, S_W - A_H); //Postavljamo novu nasumičnu x poziciju jabuke
      apple.y = 0; //Resetiramo y poziciju jabuke na vrh ekrana
    }
  }
}

// Ovdje definiramo funkciju movement koja omogućuje kretanje igrača i padanje jabuke
void movement(){
  M5.update(); //Ažuriramo stanje tipki
  if (M5.BtnA.isPressed()){ //Ako je pritisnuta tipka A
    if (millis() - P_time > 10){ //Provjera vremenskog razmaka između dvije akcije
      M5.Lcd.fillRect(player.x, S_H - P_H, P_W, P_H, M5.Lcd.color565(0,0,0)); //Brišemo trenutnu poziciju igrača
      player.x --; //Pomičemo igrača ulijevo
      M5.Lcd.fillRect(player.x, S_H - P_H, P_W, P_H, M5.Lcd.color565(255,255,255)); //Iscrtavamo igrača na novoj poziciji
      P_time = millis(); //Ažuriramo vremenski trenutak posljednje akcije
    }
  }
  if (millis() - A_time > 10){ //Ako je prošlo više od 10 milisekundi od posljednjeg pada jabuke
    if (apple.y > S_H - A_H){ //Ako je jabuka dosegla dno ekrana
      M5.Lcd.fillRect(apple.x, apple.y, A_H, A_H, M5.Lcd.color565(0,0,0)); //Brišemo jabuku sa ekrana
      apple.x = random(0, S_W - A_H); //Postavljamo novu nasumičnu x poziciju jabuke
      apple.y = 0; //Resetiramo y poziciju jabuke na vrh ekrana
    }
    M5.Lcd.fillRect(apple.x, apple.y, A_H, A_H, M5.Lcd.color565(0,0,0)); //Brišemo trenutnu poziciju jabuke
    apple.y ++; //Pomičemo jabuku prema dolje
    M5.Lcd.fillRect(apple.x, apple.y, A_H, A_H, M5.Lcd.color565(255,0,0)); //Iscrtavamo jabuku na novoj poziciji
    A_time = millis(); //Ažuriramo vremenski trenutak posljednjeg pada jabuke
  }
}