/*  Proyecto final _ control de distancia delantera de carrito*/


/*  --------------------------  ENTRADA   --------------------------  */
// Configuración del sensor ultrasónico
const int Trigger = 2;   //Pin digital 2 para el Trigger del sensor
const int Echo = 3;   //Pin digital 3 para el echo del sensor
long t; //timepo que demora en llegar el eco
long d; //distancia en centimetros


int posDes = 20;     //Posición deseada
double posAct = 0;       //Posición Actual
double error = 0;   //ERROR

//Límites de ENTRADA (basado en error)
// ERROR NEGATIVO
int en0 = -20 ;   int en1 = 0 ;
double erN1 ;   double erN3;  double erN4 ;
double FEN ;
//ERROR MEDIO (CASI NULO)
int em0 = -15;     int em1 = 15 ;
double em2 = (em0 + em1) / 2 ;
double erM1 ;  double erM2 ;  double erM3;  double erM4 ;
double FEM ;
//ERROR POSITIVO
int ep0 = 0 ;    int ep1 = 20;
double erP1 ;  double erP2 ;  double erP4 ;
double FEP ;


/*  --------------------------  SALIDA   --------------------------  */
//Voltaje NEGATIVO
double SVN[] = {1, 0.8, 0.6, 0.4, 0.2, 0, 0, 0, 0};
//Voltaje MEDIO
double SVM[] = {0,0,0.3,0.6,1,0.6,0.3,0,0} ;
//Voltaje POSITIVO
double SVP[] = {0,0,0,0,0.2,0.4,0.6,0.8,1};

//Vector de salida
double y[] = { -5,-3,-2,-1,0,1,2,3,5};

// *****************    Datos de salida, ACTIVACIÓN DE PUENTE H ************************
int adelante = 9 ;
int atras = 10 ;

/*  --------------------------  CENTROIDE   --------------------------  */
double R1[9];    double R2[9];    double R3[9];
double C0 = 0; double C1 = 0; double C2 = 0;
double C3 = 0; double C4 = 0; double C5 = 0;
double C6 = 0; double C7 = 0; double C8 = 0;

double sumaMult;   double sumaCE;
double salidaFisica;


void setup() {
  Serial.begin(9600);
  pinMode(adelante, OUTPUT);
  pinMode(atras, OUTPUT);
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  Serial.print("Esperamos unos segunditos para comenzar: ");
  delay(5000);
}

void loop() {

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  erN1 = 0; erN3 = 0; erN4 = 0;
  erM1 = 0; erM2 = 0; erM3 = 0; erM4 = 0;
  erP1 = 0; erP2 = 0; erP4 = 0;
  //error = posDes - map(d, 0, 1024, -90, 90);
  error = posDes - d;
  //Error = PosiciónDeseada - PosiciónActual
  //error = (posAct*100)/1023.0;

  //Funcipon de membresia (ERROR NEGATIVO)
  if (error <= en0)    {    erN1 = 1;  }
  if ( en0 < error && error <= en1 )    {    erN3 = (en1 - error) / (en1 - en0);  }
  if ( error >= en1 )    {    erN4 = 0;  }
  FEN = (erN1 + erN3 + erN4);

  //Funcion de membresia (ERROR MEDIO)
  if (error <= em0)    {    erM1 = 0;  }
  if ( em0 < error && error <= em2 )    {    erM2 = (error - em0) / (em2 - em0);  }
  if ( em2 < error && error <= em1 )    {    erM3 = (em1 - error) / (em1 - em2);  }
  if ( error >= em1 )    {    erM4 = 0;  }
  FEM = (erM1 + erM2 + erM3 + erM4);

  //Funcipon de membresia (ERROR POSITIVO)
  if (error <= ep0)    {    erP1 = 0;  }
  if ( ep0 < error && error <= ep1 )    {    erP2 = (error - ep0) / (ep1 - ep0);}  
  if ( ep1 < error )    {    erP4 = 1;  }
  FEP = (erP1 + erP2 + erP4);

  /*Serial.print("ErrNeg: ");   Serial.println(FEN);
    Serial.print("ErrMed: ");   Serial.println(FEM);
    Serial.print("ErrPos: ");   Serial.println(FEP);*/
  /*Serial.print(adelante);    Serial.print(",");
  Serial.print(atras);    Serial.print(",");    
  Serial.print(salidaFisica);   Serial.print(",");    */
  Serial.println(d); 
  REGLAS();
  DEFUZZ();

  //delay(10);
}


void REGLAS() {
  R1[0] = min(FEN, SVP[0]);
  R2[0] = min(FEM, SVM[0]);
  R3[0] = min(FEP, SVN[0]);
  C0 = max(R1[0], max(R2[0], R3[0]));
  R1[1] = min(FEN, SVP[1]);
  R2[1] = min(FEM, SVM[1]);
  R3[1] = min(FEP, SVN[1]);
  C1 = max(R1[1], max(R2[1], R3[1]));
  R1[2] = min(FEN, SVP[2]);
  R2[2] = min(FEM, SVM[2]);
  R3[2] = min(FEP, SVN[2]);
  C2 = max(R1[2], max(R2[2], R3[2]));
  R1[3]=min(FEN,SVP[3]);
  R2[3]=min(FEM,SVM[3]);
  R3[3]=min(FEP,SVN[3]);
  C3=max(R1[3],max(R2[3],R3[3]));
  R1[4]=min(FEN,SVP[4]);
  R2[4]=min(FEM,SVM[4]);
  R3[4]=min(FEP,SVN[4]);
  C4=max(R1[4],max(R2[4],R3[4]));
  R1[5]=min(FEN,SVP[5]);
  R2[5]=min(FEM,SVM[5]);
  R3[5]=min(FEP,SVN[5]);
  C5=max(R1[5],max(R2[5],R3[5]));
  R1[6]=min(FEN,SVP[6]);
  R2[6]=min(FEM,SVM[6]);
  R3[6]=min(FEP,SVN[6]);
  C6=max(R1[6],max(R2[6],R3[6]));
  R1[7]=min(FEN,SVP[7]);
  R2[7]=min(FEM,SVM[7]);
  R3[7]=min(FEP,SVN[7]);
  C7=max(R1[7],max(R2[7],R3[7]));
  R1[8]=min(FEN,SVP[8]);
  R2[8]=min(FEM,SVM[8]);
  R3[8]=min(FEP,SVN[8]);
  C8=max(R1[8],max(R2[8],R3[8]));
  
  sumaMult = (C0*y[0] + C1*y[1] + C2*y[2] + C3*y[3]+C4*y[4]+C5*y[5]+C6*y[6]+C7*y[7]+C8*y[8]);
  sumaCE = C0+C1+C2+C3+C4+C5+C6+C7+C8;

}

void DEFUZZ() {
  salidaFisica = sumaMult / sumaCE;
  
  if (salidaFisica < 0)   {digitalWrite(adelante, HIGH);}
  else if (salidaFisica > 0)   {digitalWrite(atras, HIGH);}
  //if (salidaFisica == 0)   {digitalWrite(atras, LOW); digitalWrite(adelante, LOW);}
  
  else {digitalWrite(adelante, LOW); digitalWrite(atras, LOW);}
  
}