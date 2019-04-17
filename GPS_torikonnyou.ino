
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial mySerial(10, 11); // RX, TX
//TinyGPSCustom magneticVariation(gps, "GPRMC", 10);

float a, b, x, y, s, t;
int m = 41;
int i;
float Kiken [41][2];
float Kyori [41];
void setup() {
  delay(500);
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  Kiken[0][0] = 136.255295;
  Kiken[0][1] = 35.296029;
  Kiken[1][0] = 136.255242;
  Kiken[1][1] = 35.296309;
  Kiken[2][0] = 136.255199;
  Kiken[2][1] = 35.296581;
  Kiken[3][0] = 136.255134;
  Kiken[3][1] = 35.296861;
  Kiken[4][0] = 136.255081;
  Kiken[4][1] = 35.297133;
  Kiken[5][0] = 136.255016;
  Kiken[5][1] = 35.297386;
  Kiken[6][0] = 136.254941;
  Kiken[6][1] = 35.297658;
  Kiken[7][0] = 136.254845;
  Kiken[7][1] = 35.297929;
  Kiken[8][0] = 136.254748;
  Kiken[8][1] = 35.298183;
  Kiken[9][0] = 136.254630;
  Kiken[9][1] = 35.298429;
  Kiken[10][0] = 136.254491;
  Kiken[10][1] = 35.298674;
  Kiken[11][0] = 136.254373;
  Kiken[11][1] = 35.298919;
  Kiken[12][0] = 136.254233;
  Kiken[12][1] = 35.299147;
  Kiken[13][0] = 136.254083;
  Kiken[13][1] = 35.299400;
  Kiken[14][0] = 136.253911;
  Kiken[14][1] = 35.299637;
  Kiken[15][0] = 136.253750;
  Kiken[15][1] = 35.299865;
  Kiken[16][0] = 136.253579;
  Kiken[16][1] = 35.300092;
  Kiken[17][0] = 136.253396;
  Kiken[17][1] = 35.300311;
  Kiken[18][0] = 136.253675;
  Kiken[18][1] = 35.300477;
  Kiken[19][0] = 136.253943;
  Kiken[19][1] = 35.300688;
  Kiken[20][0] = 136.253976;
  Kiken[20][1] = 35.300977;
  Kiken[21][0] = 136.254244;
  Kiken[21][1] = 35.301169;
  Kiken[22][0] = 136.254501;
  Kiken[22][1] = 35.301344;
  Kiken[23][0] = 136.254727;
  Kiken[23][1] = 35.301563;
  Kiken[24][0] = 136.254941;
  Kiken[24][1] = 35.301773;
  Kiken[25][0] = 136.255124;
  Kiken[25][1] = 35.302010;
  Kiken[26][0] = 136.255263;
  Kiken[26][1] = 35.302264;
  Kiken[27][0] = 136.255349;
  Kiken[27][1] = 35.302544;
  Kiken[28][0] = 136.255606;
  Kiken[28][1] = 35.302719;
  Kiken[29][0] = 136.255842;
  Kiken[29][1] = 35.302903;
  Kiken[30][0] = 136.256046;
  Kiken[30][1] = 35.303104;
  Kiken[31][0] = 136.256261;
  Kiken[31][1] = 35.303306;
  Kiken[32][0] = 136.256475;
  Kiken[32][1] = 35.303516;
  Kiken[33][0] = 136.256679;
  Kiken[33][1] = 35.303735;
  Kiken[34][0] = 136.256883;
  Kiken[34][1] = 35.303962;
  Kiken[35][0] = 136.257087;
  Kiken[35][1] = 35.304164;
  Kiken[36][0] = 136.257280;
  Kiken[36][1] = 35.304356;
  Kiken[37][0] = 136.257505;
  Kiken[37][1] = 35.304575;
  Kiken[38][0] = 136.257709;
  Kiken[38][1] = 35.304820;
  Kiken[39][0] = 136.257945;
  Kiken[39][1] = 35.305057;
  Kiken[40][0] = 136.258138;
  Kiken[40][1] = 35.305276;
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Goodnight moon!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() { // run over and over
  float u = 300;
  while (mySerial.available() > 0) {
    char c = mySerial.read();
    //Serial.print(c);
    gps.encode(c);
    if (gps.location.isUpdated()) {
      y = gps.location.lat();
      x = gps.location.lng();
      Serial.print("緯度："); Serial.println(gps.location.lat(), 6);
      Serial.print("経度："); Serial.println(gps.location.lng(), 6);
      //Serial.print("海抜："); Serial.println(gps.altitude.meters());

      for (i = 0; i < m; i++) {
        a = x - Kiken[i][0];
        b = y - Kiken[i][1];
        //Serial.println(a,9);
        //Serial.println(b,8);
        s = a * 90850.92404;
        t = b * 110942.97;
        //Serial.println(s,6);
        //Serial.println(t,6);
        Kyori[i] = pow((pow(s, 2) + pow(t, 2)), 0.5);
        //Serial.println(Kyori[i],6);
      }
      for (i = 0; i < m; i++) {
        if (u > Kyori[i]) {
          u = Kyori[i];
        }
      }
      Serial.print("距離:");
      Serial.println(u);
      if (u <= 10) {
        Serial.println("危ない！！");
      }
    }
  }
}
