#include"juego.h"


juego::juego() {

	app = new RenderWindow(VideoMode(800, 600), "TP 1");
	app->setFramerateLimit(60);


	tiempo1 = new Clock;
	regresivo = new Clock;
	temp = 60;

	salto_ok = false;
	gameover = false;

	numeros[0] = rand()%999+1;
	numeros[1] = rand() % 999 + 1;
	numeros[2] = rand() % 999 + 1;
	numeros[3] = rand() % 999 + 1;
	numeros[4] = rand() % 999 + 1;
	numeros[5] = rand() % 999 + 1;
	numeros[6] = rand() % 999 + 1;
	numeros[7] = rand() % 999 + 1;
	numeros[8] = rand() % 999 + 1;
	numeros[9] = rand() % 999 + 1;
	

	pos = NULL;
/////////GRAFICOS

	fondotex = new Texture;
	fondo = new Sprite;

	mariotex = new Texture;
	mario = new Sprite;

	bloquetex = new Texture;
	for (int i = 0; i < 10; i++) { bloque[i] = new Sprite; };



	fondotex->loadFromFile("imagenes/fondo.jpg");
	fondo->setTexture(*fondotex);
	fondo->setScale((float)app->getSize().x / fondotex->getSize().x, (float)app->getSize().y / fondotex->getSize().y);

	mariotex->loadFromFile("imagenes/mario.png");
	mario->setTexture(*mariotex);
	mario->setOrigin(mariotex->getSize().x / 2, mariotex->getSize().y / 2);
	mario->setScale(0.9, 0.9);
	mario->setPosition(50, 495);

	bloquetex->loadFromFile("imagenes/bloque.png");

	int pos = 130;
	for (int i = 0; i < 10; i++) { 
		
	bloque[i]->setTexture(*bloquetex); 
	bloque[i]->setOrigin(bloquetex->getSize().x / 2, bloquetex->getSize().y / 2);
	bloque[i]->setPosition(pos+45, 350);
	pos = pos + 45;
	
	}
	
	



	///////textos

	fuente = new Font;
	texto_tiempo = new Text;
	for (int i = 0; i < 10; i++) { 
		texto_numero[i] = new Text;
		texto_numero[i]->setFont(*fuente);
		texto_numero[i]->setFillColor(Color::Yellow);
		texto_numero[i]->setCharacterSize(40);
		texto_numero[i]->setPosition(bloque[i]->getPosition().x-13, bloque[i]->getPosition().y- 28);
		
		
	}

	fuente->loadFromFile("fuente.ttf");

	texto_tiempo->setFont(*fuente);
	texto_tiempo->setFillColor(Color::Black);
	texto_tiempo->setCharacterSize(50);
	texto_tiempo->setPosition(700, 15);

	


/////////FUNCIONES
	ordenar();
	loop();
}

void juego::loop() {

	while (app->isOpen()) {

		dibujar();
		eventos();



	///////////FUNCIONES DEL JUGADOR


			if (mario->getPosition().y >= 495) {//si el jugador está en el piso salto es falso
				salto_ok = false;
			}
			else {//si el jugador está en el aire, salto es verdadero
				salto_ok = true;
			}

			if (mario->getPosition().y < 495) {//gravedad de mario al saltar
				mario_gravedad();
			}

			colision_bloque();

	///////////TEXTOS
		cuenta_regresiva();
	}
}

void juego::dibujar() {
	
	app->clear();


	app->draw(*fondo);//dibujar fondo

	app->draw(*mario);//dibujar jugador

	app->draw(*texto_tiempo);//dibujar cuenta regresiva

	for (int i = 0; i < 10; i++) { 
		app->draw(*bloque[i]);//dibujar bloques
		texto_numero[i]->setPosition(bloque[i]->getPosition().x - 10, bloque[i]->getPosition().y - 28);//dibujar textos de numeros de los bloques
		app->draw(*texto_numero[i]);
	};

	app->display();

}

void juego::eventos() {

	if (app->pollEvent(evt)) {

		switch (evt.type) {

		case Event::Closed:
			exit(1);

		case Event::KeyPressed:
			if (evt.key.code == Keyboard::Escape) { exit(1); };//al presionar Escape se cierra la aplicacion
			if (evt.key.code == Keyboard::R) { app->close(); new juego; };//reiniciar juego

		}

		if (!gameover) {//si no se perdió o ganó se puede jugar
			if (Keyboard::isKeyPressed(Keyboard::D) == true) { mario_movimiento(1); };//mover a la derecha
			if (Keyboard::isKeyPressed(Keyboard::A) == true) { mario_movimiento(2); };//mover a la izquierda
			if (Keyboard::isKeyPressed(Keyboard::W) == true) {
				if (!salto_ok) {//si el jugador está en el piso, puede saltar
					mario_movimiento(3);
					tiempo1->restart();
				}
			}//salto

			if (Keyboard::isKeyPressed(Keyboard::Right) == true) { mario_movimiento(1); };//mover a la derecha
			if (Keyboard::isKeyPressed(Keyboard::Left) == true) { mario_movimiento(2); };//mover a la izquierda
			if (Keyboard::isKeyPressed(Keyboard::Up) == true) {
				if (!salto_ok) {//si el jugador está en el piso, puede saltar
					mario_movimiento(3);
					tiempo1->restart();
				}
			}//salto
		}
	}



}

void juego::mario_gravedad() {//gravedad de mario
		mario->setPosition(mario->getPosition().x, mario->getPosition().y + 9.81 * tiempo1->getElapsedTime().asSeconds());
}

void juego::mario_movimiento(int dir) {

	switch (dir) {

	case 1:
		if (mario->getPosition().x <= 785) {
			mario->setScale(-0.9, 0.9);
			mario->setPosition(mario->getPosition().x + 5, mario->getPosition().y);
		}
		break;

	case 2:
		if (mario->getPosition().x >= 20) {
			mario->setScale(0.9, 0.9);
			mario->setPosition(mario->getPosition().x - 5, mario->getPosition().y);

		}
		break;

	case 3:
		if (mario->getPosition().y > 450) {
			
			mario->setPosition(mario->getPosition().x, mario->getPosition().y - 125);

	
			if (mario->getPosition().y > 495) {
				mario->setPosition(mario->getPosition().x, 495);
	
			}

		}
		break;


	}
}

void juego::cuenta_regresiva() {

	

	segundos = temp- regresivo->getElapsedTime().asSeconds();//cuenta regresiva de 60 segundos

	char temp[10];

	_itoa_s(segundos, temp, 10);
	texto_tiempo->setString(temp);//escribir tiempo que queda en pantalla
	
	if (segundos <= 0) {//si el timepo llega a 0, se termina la partida
		texto_tiempo->setPosition(300, 200);
		texto_tiempo->setString("Perdiste");
		gameover = true;
	}
	for (int i = 0; i < 10; i++) {//asignar los numeros como texto para los bloques

		char num[10];

		_itoa_s(numeros[i], num, 10);
		texto_numero[i]->setString(num);

	}
	
	if (pos == 10) {
		gameover = true;
		texto_tiempo->setPosition(300, 200);
		texto_tiempo->setString("Ganaste Genix");
	}

}

void juego::colision_bloque() {

	for (int i = 0; i < 10; i++) {
		if (mario->getGlobalBounds().contains(bloque[i]->getPosition())) {//al colisionar contra un bloque
			
				bloque[i]->setPosition(bloque[i]->getPosition().x, 320);
				ordenar();
				
				if (numeros[i] == orden[pos]) {//si el valor de numeros es igual al valor de numero de orden, entonces pintar de verde y subir una posicion
					texto_numero[i]->setFillColor(Color::Green);
					pos++;
				}
				else {//si colisiona con el bloque erroneo, restar 10 segundo al tiempo
				
					temp -= 10;

				}
		}
		else {
			if (!salto_ok) {
				bloque[i]->setPosition(bloque[i]->getPosition().x, 350);//si está en el piso se baja el bloque
			}
		}		
	}
	

}

void juego::ordenar() {

	
	for (int i = 0; i < 10; i++) {//copiar el arreglo numeros en orden
		orden[i] = numeros[i];
	}
	int aux;
	for (int i = 0; i < 10; i++) {//ordenar el arreglo orden
		
		int min = i;
		for (int j = i + 1; j < 10; j++) {
			if (orden[j] < orden[min]) {
				min = j;
			}
			
		}
		aux=orden[i];
		orden[i] = orden[min];
		orden[min] = aux;
	}	
}