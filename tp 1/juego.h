#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;

class juego {

private:
	
///////////VARIABLES
	RenderWindow * app;
	Event evt;

	Clock  *tiempo1;
	Clock *regresivo;

	Time *suma_tiempo;

	bool salto_ok;
	bool gameover;


	float segundos;
	float temp;

	int numeros[10];
	int orden[10];
	int pos;
///////////GRAFICOS

	Texture *fondotex;
	Sprite  *fondo;

	Texture *mariotex;
	Sprite *mario;

	Texture *bloquetex;
	Sprite *bloque[11];


/////////TEXTOS

	Font *fuente;
	Text *texto_tiempo;
	Text *texto_numero[10];
public:
	juego();
	void loop();//bucle del juego
	void dibujar();//dibujar en pantalla
	void eventos();//detenccion de teclas en le juego
	void mario_gravedad();//gravedad del personaje al saltar
	void mario_movimiento(int dir);//movimiento del personaje en X e Y
	void cuenta_regresiva();
	void colision_bloque();
	void ordenar();
};