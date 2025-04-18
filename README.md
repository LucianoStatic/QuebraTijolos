# QuebraTijolos
🧱 Quebra-Tijolos com Arduino + OLED + Joystick


Este é um mini game estilo "Brick Breaker" desenvolvido com Arduino Uno, display OLED, joystick analógico e buzzer.
Um projetinho divertido para quem está aprendendo programação com Arduino e quer aplicar lógica de jogos em projetos físicos!

-----------------------------------------------------------------------------------------------------------------------------
🕹️ Componentes Utilizados
Arduino Uno

Display OLED 128x64 (I2C)

Joystick analógico

Buzzer passivo

Jumpers macho-macho

Protoboard (opcional)

----------------------------------------------------------------------------------------------------------------------------

⚙️ Funcionamento
Use o joystick para mover a raquete na parte inferior da tela.

Rebata a bolinha para destruir os tijolos na parte superior.

Ao acertar um tijolo, ele desaparece e a pontuação aumenta.

O jogo termina se a bola passar da raquete (Game Over).

Efeitos sonoros são tocados pelo buzzer em eventos como colisões e fim de jogo.

----------------------------------------------------------------------------------------------------------------------------

📌 Ligações

Componente	Conexão com Arduino
OLED VCC	5V
OLED GND	GND
OLED SCL	A5
OLED SDA	A4
Joystick GND	GND
Joystick VCC	5V
Joystick VRx	A0
Buzzer VCC	Pino Digital 3
Buzzer GND	GND
💡 O eixo Y do joystick não é utilizado neste projeto.

----------------------------------------------------------------------------------------------------------------------------

🚀 Como Usar
Instale as bibliotecas Adafruit GFX e Adafruit SSD1306 pela IDE do Arduino.

Faça as conexões conforme o esquema.

Carregue o código no seu Arduino.

Divirta-se jogando!

📢 Créditos
Este projeto foi desenvolvido por @Luciano Drop com o intuito de compartilhar conhecimento com a comunidade maker.
Sinta-se livre para adaptar e melhorar!
