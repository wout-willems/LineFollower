# Gebruiksaanwijzing

### opladen / vervangen batterijen
De batterijen kunnen opgeladen worden door de oplaadmodule(3 kabels aan de batterij) in een speciale oplader te bevestigen.

### draadloze communicatie
#### verbinding maken
er is geen draadloze verbinding mogelijk, je kan de robot wel altijd bekabeld verbinden met een laptop en zo de code aanpassen via de Arduino IDE app.

#### commando's
debug [on/off]  
run: de robot start met het parcours  
stop: de robot stopt onmiddelijk
set power [0..200] : hiermee bepaal je de gemiddelde snelheid waarmee de robot het parcours aflegt  
set kp [0-10]  : dit verhoogt/verlaagt de proportionele waarde waarme de ronot fouten zal corrigeren
set ki [0-10]  : dit verhoogt/verlaagt de integrale waarde waarme de ronot fouten zal corrigeren
set kd [0-10]  : dit verhoogt/verlaagt de differentiële waarde waarme de ronot fouten zal corrigeren
calibrate black  : hiermee kalibreer je de standaard zwarte kleur
calibrate white  : hiermee kalibreer je de standaard witte kleur

### kalibratie
via de commando's calibrate black/white kan je de waarden die als zwart of wit worden gerekend fine-tunen. Je hoeft enkel de robot op een volledig zwarte/witte ondergrond te houden en de commando's in te voeren.
Het is aangeraden om dit vrij frequent te doen, zo vermijd je impact van zon, schaduw, lampen...
### settings
Power = 100;
kp = 6.7;
ki = 0;
kd = 4;  

### start/stop button
De rode schakelaar kan gebruikt worden om het programma te starten/stoppen, deze bevindt zich in het midden van de printplaat. De status (start/stop) wordt ook visueel bevestigd door een blauw LED-lampje. Het volledig uitschakelen van de robot kan via de zwarte schakelaar achteraan de robot.
