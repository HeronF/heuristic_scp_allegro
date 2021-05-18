#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>  //função rand
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

using namespace std;

struct Coord{
	int x,y,r;
	};

int main(){
	
	
	srand(time(NULL));	

	ifstream log("Saida_dados.txt",ios::in);

	if (! log){
		cout << "Arquivo saida.txt nao pode ser aberto" << endl;   
		abort();
	}

	float malha_x, malha_y;
	log >> malha_x;   //LIN
	log >> malha_y;		//COL

//lendo a malha		cout << "malha x e malha y é dada por " << malha_x << " e " << malha_y << endl; 



	float xi,xf,yi,yf;

	log >> xi;         //Xi
	log >> xf;			//xf
	log >> yi;			//yi
	log >> yf;			//Yf

//lendo o tamanho do prédio	cout << "O valor de xi xf yi e yf são " << xi << " " << xf << " " << yi << " " << yf << endl;



	int num_cortes;

	log >> num_cortes;	
	cout << "retângulo retirado" << num_cortes << endl;

	vector<float> rxi,rxf,ryi,ryf;

	for(int i=0;i<num_cortes;i++){
	float arxi,arxf,aryi,aryf;
		log >> arxi;
		log >> arxf;
		log >> aryi;
		log >> aryf;

		rxi.push_back(arxi);
		rxf.push_back(arxf);
		ryi.push_back(aryi);
		ryf.push_back(aryf);
	}	
//lendo o tamanho de cortes e inserindo os valores em um vector de floats
//	for(int i=0;i<num_cortes;i++) cout << rxi[i]<< " " << rxf[i] << " "<< i << endl;

	int num_tipo_roteador;
	vector<float> custo_roteador,raio_roteador;
	
	log >> num_tipo_roteador;
	
	for(int i=0;i<num_tipo_roteador;i++){
		float apoio_custo,apoio_raio;
		log >> apoio_custo;
		log >> apoio_raio;
		custo_roteador.push_back(apoio_custo);
		raio_roteador.push_back(apoio_raio);
		cout<< i << " " << apoio_custo << " " << apoio_raio << endl;
		}
	

	vector<Coord> pontos_roteadores;
	int num_roteador;
	log >> num_roteador;
	for(int i=0;i<num_roteador;i++){                      
		Coord apoio;
		log >> apoio.x;
		log >> apoio.y;
		log >> apoio.r;
		

		pontos_roteadores.push_back(apoio);
	}
// lendo numero de roteadores e buscando custos e raios
	//for(int i=0;i<num_roteador;i++) cout << custo_roteador[i]<< " " << raio_roteador[i] << " "<< i << endl;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *imagem = NULL;

	if(!al_init()) {                                         // testa inicialização da biblioteca
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(4*(yf-yi), 4*(xf-xi));                // seta tamanho do display 608,576 = 4*(152,144)

	if(!display) {                                        //testa inicialização do display
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	
	bool primitive =  al_init_primitives_addon();

	if(!primitive) {                                        //testa inicialização do primitive_addon
		fprintf(stderr, "failed to initialize primitives addon!\n");
		return -1;
	}
	bool imag = al_init_image_addon();
	if(!imag) {                                        //testa inicialização do primitive_addon
		fprintf(stderr, "failed to initialize primitives addon!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(255,255,255));               // seta cor de fundo do display em um buffer
	
	ALLEGRO_COLOR cor_preta = al_map_rgb(0,0,0);	
	ALLEGRO_COLOR cor_cinza = al_map_rgb(200,200,200);

	float dx;
	dx = (4*(xf-xi)/(float)(malha_x));
	for(int i=0;i<malha_x;i++){ //desenho da grade de malha no eixo x.
			
		al_draw_line(0,4*(xf-xi)-i*dx,4*(yf-yi),4*(xf-xi)-i*dx,cor_cinza,0);
	}
	float dy;
	dy = 4*(yf-yi)/(float)(malha_y);
	for(int i=0;i<malha_y;i++){ //idem em y.

		al_draw_line(i*dy,0,i*dy,4*(xf-xi),cor_cinza,0);
		for(int j=0;j<malha_x;j++){
			//al_draw_filled_circle(i*dy,j*dx,1,cor_preta);
			
			}
	}



/*	float dx;
	dx = (608/(float)(malha_x-1));
	for(int i=0;i<malha_x;i++){ //desenho da grade de malha no eixo x.
			
		al_draw_line(i*dx,0,i*dx,576,cor_preta,0);	
	}
	float dy;
	dy = 576/(float)(malha_y-1);
	for(int i=0;i<malha_y;i++){ //idem em y.

		al_draw_line(0,i*dy,608,i*dy,cor_preta,0);
	
	}*/

	for(int i=0;i<num_cortes;i++){ // desenhando retângulo dos cortes
		
		al_draw_filled_rectangle(4*ryi[i],4*rxi[i],4*ryf[i],4*rxf[i], al_map_rgb(112,112,112));
	
	}


	ALLEGRO_COLOR cor_roteador[num_roteador];

	for(int i=0; i<num_tipo_roteador;i++){
		
		int x[3];
		for(int j=0;j<3;j++) x[j] = rand()%256;
		cor_roteador[i]=al_map_rgb(x[0],x[1],x[2]);

	}

	
	for (int i= 0; i<num_roteador;i++){
		al_draw_filled_circle(pontos_roteadores[i].y*dy,pontos_roteadores[i].x*dx,min(dx/4,dy/4),cor_roteador[pontos_roteadores[i].r]);

		al_draw_circle(pontos_roteadores[i].y*dy,pontos_roteadores[i].x*dx,4*raio_roteador[pontos_roteadores[i].r],cor_roteador[pontos_roteadores[i].r],2);
		
		//cout << pontos_roteadores[i].r << " " << 4*raio_roteador[pontos_roteadores[i].r] << endl;
	}
	
	
			   
	al_flip_display();                                    //esvazia o buffer

	int a;
	cin >> a ;
//	al_rest(5.0);                                        // espera 10 segundos

	al_destroy_display(display);                           // destroi o display
return(0);
}
