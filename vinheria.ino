// Aqui são definidas variáveis correspondentes às portas do Arduino,
// onde cada componente está conectado.

int ldr = A0;      // Pino analógico conectado ao LDR (Sensor de Luz)
int valorldr = 0;  // Variável para armazenar o valor lido pelo LDR
int som = 8;       // Pino digital conectado ao buzzer (alto-falante)
int red = 6;       // Pino digital conectado ao LED vermelho
int yellow = 3;    // Pino digital conectado ao LED amarelo
int green = 5;     // Pino digital conectado ao LED verde

// Configuração inicial do Arduino
void setup()
{
  pinMode(ldr, INPUT);       // Define o pino LDR como entrada (para leitura analógica)
  pinMode(som, OUTPUT);      // Define o pino do som como saída
  pinMode(green, OUTPUT);    // Define o pino do LED verde como saída
  pinMode(yellow, OUTPUT);   // Define o pino do LED amarelo como saída
  pinMode(red, OUTPUT);      // Define o pino do LED vermelho como saída
  Serial.begin(9600);        // Inicializa a comunicação serial a 9600 bps
}

// Loop principal do programa
void loop()
{
  valorldr = analogRead(ldr); // Lê o valor analógico do sensor de luz (LDR)
  Serial.print("Valor lido pelo LDR = ");
  Serial.println(valorldr);  // Envia o valor lido para a porta serial

  // Verifica as condições do valor lido pelo LDR e realiza ações com base nele
  // Aqui o sistema ao ligar, inicia com a luz verde
  if (valorldr < 840) {
    noTone(som);              // Desliga o som (buzzer)
    digitalWrite(yellow, LOW);  // Desliga o LED amarelo
    digitalWrite(red, LOW);     // Desliga o LED vermelho
    digitalWrite(green, HIGH);  // Liga o LED verde
    digitalWrite(som, LOW);     // Desliga o som
  }
  // Aqui o sistema ao notar uma mudança na luz desliga o led verde
  // Liga o led amarelo e toca uma buzina que dura 3 segundos
  if (valorldr > 900 && valorldr < 950) {
    digitalWrite(green, LOW);     // Desliga o LED verde
    digitalWrite(red, LOW);       // Desliga o LED vermelho
    digitalWrite(yellow, HIGH);   // Liga o LED amarelo
    tone(som, 261);                // Gera um tom no buzzer a 261 Hz
    digitalWrite(som, HIGH);       // Liga o buzzer
    delay(3000);                   // Aguarda 3 segundos
    noTone(som);                   // Desliga o som (buzzer)
    digitalWrite(som, LOW);        // Desliga o buzzer
    delay(3000);                   // Aguarda mais 3 segundos
  }
  
  // Aqui o sistema ao notar uma mudança drastica na luz desliga o led verde  e o amarelo
  // Liga o led amarelo e toca uma buzina permanete  até que a falha seja corrijida
  if (valorldr > 950) {
    digitalWrite(yellow, LOW);     // Desliga o LED amarelo
    digitalWrite(green, LOW);      // Desliga o LED verde
    digitalWrite(red, HIGH);       // Liga o LED vermelho
    tone(som, 261);                // Gera um tom no buzzer a 261 Hz
    digitalWrite(som, HIGH);       // Liga o buzzer
  }
}