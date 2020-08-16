#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>//PARA LOS COLORES


void lecturaCaracter(char car);////FUNCION ENCARGADA DE LEER CARACTER POR CARACTER Y DECIDIR QUE HACER Y MANDALO A LA FUNCION EstadosImpresion(). 
void EstadosImpresion();//FUNCION ENCARGADA DE MANDAR LOS MENSAJES DE LOS CARACTERES LEIDOS.
void buscarRESERVADOSID();//FUNCION ENCARGADA DE BUSCAR PALABRAS RESERVADAS EN NUESTRO CODIGO.
void Color(int Background,int Text);//FUNCION ENCARGADA DE CAMBIO DE COLORES EN PANTALLA.

const char *RESERVADOSID[] = {"si","entero","inicio","sino","finsi","repetir","hasta","mientras","leer","imprimir","vacio","cursor","definir","hacer"};
int tamIndicador=sizeof(RESERVADOSID)/sizeof(char *);//Indica el tamaño de nuestras palabras reservadas y el tamaño de memoria de el char
int i;
char identificador[150];
char temp[2];
int estado=0;

enum Colores{
	 BLACK=0,
	 BLUE=1,
	 GREEN=2,
	 CYAN=3,
	 RED=4,
	 MAGENTA=5,
	 BROWN=6,
	 LGREY=7,
	 DGREY=8,
	 YELLOW=14,
	 WHITE=15
 };
int main( )
{
   FILE *archivo ;
   
   Color(WHITE,RED); printf("ANALIZADOR LEXICO C++ \n") ;
   Color(WHITE,GREEN);printf( "Abriendo archivo.....\n" ) ;
   
   archivo = fopen ( "programa.txt", "r" ) ; //ESTE ABRE EL ARCHIVO
   
   char caracter;
      if ( archivo == NULL )//ESTE IF REVISA SI NO EXISTE EL ARCHIVO Y ESTE MANDA UN MSJ
   {
		Color(WHITE,RED);printf ( "Archivo no existe \n" ) ;
     return 1;
   }
    printf( "Leyendo archivo programa.txt**** \n" ) ;
	  Color(WHITE,BLUE);printf( "Archivo Leido \n" ) ;
	
   while (1){//EL ARCHIVO SI EXISTE
	   
	  caracter=fgetc(archivo);//EL fgetch SE ENCARGA DE TOMAR TODO EL TEXTO Y LA VARIABLE caracter SE LE ASIGNA DICHA INFORMACION
	  Color(MAGENTA,WHITE);printf("%c",caracter);//ESTE printf ES EL ENCARGADO DE MANDAR EN PANTALLA TODO EL CODIGO LEIDO EN fopen A TRAVES DE 'r'
	  
	  if(caracter==EOF){
	  break;
	  }
	  while(i==0){//ESTE ES EL INICIO DE MI PROGRAMA CONDICIONANDOLO EN QUE ESTA OBLIGADO A USAR LA PALABRA inicio
		   if(caracter!='i'&&caracter!='n'&&caracter!='i'&&caracter!='c'&&caracter!='i'&&caracter!='o'){
			   Color(WHITE,RED);printf("Debe empezar con inicio");
		   		exit(-1);
			}
		   i=1;
	  }
	  
	  lecturaCaracter(caracter);//LECTURA DE CARACTERES INDIVIDUALES PARA NUESTROS CARACTERES GENERALES
	  switch(caracter){
		  //AQUI SE HACE LA LECTURA DE CARACTERES QUE SON GLOBALES EN NUESTRO CODIGO
		  case '(':Color(BLACK,CYAN);printf("<Token_Parentesis_Abierto>");
		  break;
		  case ')':Color(BLACK,CYAN);printf("<Token_Parentesis_Cerrado>");
		  break;
		  case '{':Color(BLACK,CYAN);printf("<Token_Llave_Abierta>");
		  break;
		  case '}':Color(BLACK,CYAN);printf("<Token_Llave_Cerrada>");
		  break;
		  case ';':Color(BLACK,CYAN);printf("<Token_Punto_Coma>");
		  break;
	  }
	  i++;
   }
   
 
}//FUNCION DE COLORES
void Color(int Background,int Text){
	HANDLE Console=GetStdHandle(STD_OUTPUT_HANDLE);
	int New_Color=Text+(Background*16);
	SetConsoleTextAttribute(Console,New_Color);//Console=Fondo de Consola,New_Color=Color de Texto
}

void buscarRESERVADOSID(){
	for(int i=0;i<tamIndicador;i++){
		if(strcmp(RESERVADOSID[i],identificador)==0){
			//system("pause");//Hay una pausa cada vez que hay una palabra reservada
			Color(BLACK,YELLOW);printf("<TOKENRESERVADO_%s>",RESERVADOSID[i]);//EL printf RECIBE EL TIPO DE TOKEN Y LO CONCATENA USANDO TOKENRESERVADO + %s QUE  RECONOCE LOS RESERVADOSID 
			identificador[0]='\0';
			break;
		}
		//SI SE ESCRIBE UNA PALABRA QUE NO EXISTA EN NUESTRO ANALIZADOR POR EJEMPLO: HOLA EL MANDARA EL MSJ "Error Token_ID"
		if(i==(tamIndicador)-1){
			printf("Error_Token_ID");
			exit(-1);
		}
	}		
}
	
	//FUNCION QUE LEE LOS CARACTERES Y ENCARGADA DE DECIDIR QUE TIPO DE TOKEN ES Y MANDARLO A EJECUTAR A EstadosImpresion
	void lecturaCaracter(char car){
		
		if(car==32||car=='}'||car=='{'||car=='('||car==')'||car==';'){
			EstadosImpresion();
		}
		
		if( car>=65 && car<=90 ){
			if(estado==0){
				estado=1;
			}else if(estado==1||estado==2){
				estado=2;
			}
			else if(estado!=0 && estado!=1 && estado!=2){
				printf("\n error");
				exit(-1);
			}
		}
		
		if(car>=96 && car<=122){
			if(estado==0){
				temp[0]=car; 
				strcat(identificador,temp); 
				estado=3;
			}else if(estado==1||estado==2){
				estado=2;
			}
			else if(estado==3){
				temp[0]=car; 
				strcat(identificador,temp);
				estado=3;}
			else{
				printf("\n error_S"); 
				exit(-1);
			}
		}
		if(car<=57&&car>=48){
			if(estado==0){
				estado=4;
			}else if(estado==4||estado==5){
				estado=5;
			}else if(estado==13||estado==6){
				estado=6;
			}else if(estado==1||estado==2){
				estado=2;
			}else if(estado==7){
				estado=4;
			}else{
				printf("\n ERROR"); 
				exit(-1);
			}
		}
		if(car=='+'){
			if(estado==0){
				estado=8;
			}else if(estado==8){
				estado=17;
			}
		}
		if(car=='.'){
			if((car)<'1' || (car)>='9'){
				estado=19;
			}else{
				if(estado==4||estado==5&&((car)=='1'||(car)=='2'||(car)=='3'||(car)=='4'||(car)=='5'||(car)=='6'||(car)=='7'||(car)=='8'||(car)=='9')){
					estado=20;
				}
				else if(estado!=4 && estado!=5){
					printf("\n ERROR"); 
					exit(-1);
				}
			}
		}
		if(car=='^'){
			if(estado==0){
				estado=18;
			}
			else{
				printf("\n ERROR '^'");
				exit(-1);
			} 
		}
		if(car=='-'){
			if(estado==0){
				estado=7;
			}else if(estado==12){
				estado=10;}
		}	else if(estado==7){
			estado=17;
		}
		
		if(car=='='){
			if(estado==0){
				estado=9;
			}else if(estado==18){
				estado=11;
			}
		}else if(estado==12){
			estado=16;
		}else if(estado==13){
			estado=15;
		}
		
		
		if(car=='/'||car=='*'){
			if(estado==0){
				estado=18;
			}else{
				printf("ERROR");
				//EL exit(-1); CIERRA EL PROGRAMA SI ESTA INCORRECTO
				exit(-1);
			}
		}
		
		if(car=='<'){                
			if(estado==0){
				estado=12;
			}else{
				printf("ERROR '<'");
				exit(-1);
			}
		}
		if(car=='>'){   
			if(estado==0){
				estado=14;
			}else{
				printf("ERROR '>'");
				exit(-1);
			}
		}	
		
		
		if(car=='!'){
			if(estado==0){
				estado=18;
			}else{
				printf("\n ERROR '!'");} 
		}
	}
//ESTA FUNCION RESIVE CARACTER YA LEIDO Y MANDA EL MSJ DE ACUERDO A LO QUE SE LEE
void EstadosImpresion(){
	switch(estado){
			case 1:Color(BLACK,YELLOW);printf("<Token_Variable>"); 
			estado=0;
			break;
			case 2:Color(BLACK,YELLOW);printf("<Token_VariableCompuesta>"); 
			estado=0;
			break;
			case 3:buscarRESERVADOSID(); 
			estado=0;
			break;
			case 4:Color(BLACK,YELLOW);printf("<Token_Numero>"); 
			estado=0;
			break;
			case 5:Color(BLACK,YELLOW);printf("<TOKEN_CONSTANTE_ENTERO>"); 
			estado=0;
			break;
			case 6:Color(BLACK,YELLOW);printf("<TOKEN_CONSTANTE_REAL>"); 
			estado=0;
			break;
			case 7:Color(BLACK,YELLOW);printf("<TOKEN_OPERADOR_NEGATIVO>"); 
			estado=0;
			break;
			case 8:Color(BLACK,YELLOW);printf("<TOKEN_OPERADOR_POSITIVO>"); 
			estado=0;
			break;
			case 9:Color(BLACK,YELLOW);printf("<TOKEN_OPERADOR_IGUAL>"); 
			estado=0;
			break;
			case 10:Color(BLACK,YELLOW);printf("<Token_Asignacion>"); 
			estado=0;
			break;
			case 11:Color(BLACK,YELLOW);printf("<Token_Distinto>"); 
			estado=0;
			break;
			case 12:Color(BLACK,YELLOW);printf("<Token_Menor_Q>"); 
			estado=0;
			break;
			case 14:Color(BLACK,YELLOW);printf("<Token_Mayor_Q>"); 
			estado=0;
			break;
			case 15:Color(BLACK,YELLOW);printf("<Token_Mayor_O_Igual_Q>"); 
			estado=0;
			break;
			case 16:Color(BLACK,YELLOW);printf("<Tkn_Menor_O_Igual_Q>"); 
			estado=0;
			break;
			case 17:Color(BLACK,YELLOW);printf("<Token_Incremento>"); 
			estado=0;
			break;
			case 18:Color(BLACK,YELLOW);printf("<Tkn_Operacional>"); 
			estado=0;
			break;
			case 19:Color(BLACK,YELLOW);printf("<Token_Punto_Decimal>"); 
				estado=0;
			break;
			case 20:Color(BLACK,YELLOW);printf("<Token_Numero_Decimal>"); 
				estado=0;
			break;
			default:
				break;
			}
}
