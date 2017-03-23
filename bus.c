#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cell{
	int o;
	int f;
	int n;
	int b;
};
typedef struct cell cel; 

void todos(cel **x,int px,int py){
	int o,u;
	for(o=-1;o<=1;o++){
		for(u=-1;u<=1;u++){
			if(x[px-o][py-u].n == 0 && x[px-o][py-u].o == 1){
				 x[px-o][py-u].o = 0;
				 todos(x,px-o,py-u);
			}else{
				if(x[px-o][py-u].o==1 && x[px-o][py-u].b==0){
					x[px-o][py-u].o=0;
				}
			}
		}
	}
}

 int ganar(int tam, cel **x,int tam2){
	int i,j;
	for(i = 1;i<=tam;i++){
		for(j=0;j<tam2;j++){
			if(x[i][j].o==1){
				return 0;
			}
		}
	}
	printf("\nGANASTE!!\n");
	return 1;
}

void dibujar (cel **x,int tam,int tam2){
	int i,j;
	printf("   ");
	for(i=1;i<=tam2;i++){
		printf("%i ",i);
	}
	printf("\n");
	for(i = 1;i<=tam;i++){
		printf("%i ",i);
		for(j=0;j<tam2;j++){
			if(x[i][j].o == 0){
				if(x[i][j].f==1){
					printf("|f");
					continue;
				}
				if(x[i][j].b==1){
					printf("|&");
				}else{
					printf("|%i",x[i][j].n);
				}
			}else{
				if(x[i][j].f == 0){
					printf("| ");
				}else{
					printf("|f");
				}
			}
		}
		printf("|\n");
	}
}
void dibujarR (cel **x,int tam,int tam2){
	int i,j;
	for(i = 1;i<=tam;i++){
		for(j=0;j<tam2;j++){
				if(x[i][j].b==0){
					printf("|%i|",x[i][j].n);
				}else{
					printf("|&|");
				}
			}
		printf("\n");
	}
}

int revisar(int tam, cel **x,int tam2,int pxr, int pyr,int px, int py){
	int o,u;
	for(o=-1;o<=1;o++){
		for(u=-1;u<=1;u++){
			if(px-o ==pxr && py-u ==pyr){
				return 0;
			}
		}
	}
	return 1;
}

void bombas(int tam, cel **x,int tam2,int n,int pxr, int pyr,int pasa){
	int i;
	srand(time(NULL));
	int px,py,a1;
	if(tam*tam2 <= n){
		n = (tam*tam2)-2;
	}
	for(i=0;i<n;i++){
		do{
			do{
			px = rand()%tam+1;
			py = rand()%tam2;
			a1=1;
			if(pasa!=1){
				a1=revisar(tam,x,tam2,pxr,pyr,px,py);
			}
			}while(a1==0);
		}while(x[px][py].b==1 || px == 0);
		x[px][py].b=1;//nueve es casilla con bomba
	}
}

void numeross(int tam, cel **x,int tam2){
	int i=1,j=0;
	i=j+1;
	for(i=1;i<=tam;i++){
		for(j=0;j<tam2;j++){
			if(x[i][j].b==1){
				continue;
			}
			int o,u,cont=0;
			for(o=-1;o<=1;o++){
				for(u=-1;u<=1;u++){
					if(x[i-o][j-u].b==1){
				 		cont +=1;
					}
				}
			}
	 		x[i][j].n=cont;//10-1 10 de la señalacoion y -1 del mas en el contador
		}
	}
}

int juego(int tam,cel **x,int px,int py,char orden,int tam2){
	if(orden!='n'){
		py -=1;
		if(x[px][py].o == 0){
				return 0;
			}
		if(orden == 'o' && x[px][py].o==1){
			x[px][py].o = 0;
			if(x[px][py].n==0){
				todos(x,px,py);
			}
			if(x[px][py].b == 1){
				int i,j;
				for(i = 1;i<=tam;i++){
					for(j=0;j<tam2;j++){
						x[i][j].o = 0;
					}	
				}
				printf("\nPERDISTE!\n");
				return 1;	
			}
		}
		if(orden=='f' && x[px][py].o==1){
			x[px][py].f = 1;
			x[px][py].o = 0;
		}
		return 0;
	}
}
void main(int argc,char *argv[]){
	printf("Escribe las ordenes en orden de: open(o) flat(f)  ,  fila  ,  columna \n");
	int tam=atoi(argv[1]),tam2=atoi(argv[2]);
	int bom=atoi(argv[3]);
	int i,j,v=0;
	cel **x=(cel**)malloc((tam+2)*sizeof(cel));
	for(i=0;i<=tam+2;i++){
		x[i]=(cel*)malloc((tam2+1)*sizeof(cel));
		for(j=0;j<tam2;j++){
			x[i][j].o=1;
			x[i][j].f=0;
			x[i][j].n=1;
			x[i][j].b=0;
		}
	}
	int pasa =0;
	int px,py;
	char orden;
	dibujar(x,tam,tam2);
	scanf("%c %i %i",&orden,&px,&py);
	if(tam*tam<bom+9){
		pasa=1;
	}

	bombas(tam,x,tam2,bom,px,py-1,pasa);
	numeross(tam,x,tam2);
	//dibujarR(x,tam,tam2);
	juego(tam,x,px,py,orden,tam2);
	while (1){
		dibujar(x,tam,tam2);
		scanf("%c %i %i",&orden,&px,&py);
		if(px <= tam && py <= tam2){
			v = juego(tam,x,px,py,orden,tam2);
			if(v==0){
				v = ganar(tam,x,tam2);
			}
			if(v==1){
				dibujar(x,tam,tam2);
				break;
			}
		}
		printf("------------------------------------------------\n");
	}


}

