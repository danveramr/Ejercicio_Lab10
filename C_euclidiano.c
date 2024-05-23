#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void estratificacion(int columna, int fila, char arr[columna][fila][100]);

int main()
{
	FILE *archivo;
	int i=0,j=0,k=0;
	char nom_archivo[50];

	printf("\n\tEjecicio de Lab. 9");
	printf("\n\tIntroduce el nombre del archivo: ");
	scanf("%s",nom_archivo);
	
	archivo = fopen(nom_archivo,"r");
	if(archivo == NULL)
		printf("\n\tError en la apertura del archivo");

	int c,fila=1,coma=0,columna;
	while ((c = fgetc(archivo)) != EOF) 
	{
		if(c == '\n')
		{
			fila++;
		}
		else if(c == ',')
		{	
			coma++;
		}
    	}
	//printf("\n\tFila : %d",fila);
	//printf("\n\tComas : %d",coma);
	columna = (coma/fila) + 1;
	//printf("\n\tColumnas : %d",columna);
	fseek(archivo,0,SEEK_SET);

	char line[1024];
	char arr[columna][fila][100];
	
	
    	while(fgets(line, sizeof(line), archivo) != NULL) 
	{
        	char *token = strtok(line, ",");
        	while (token != NULL) 
		{
			//printf("\t%s\n", token);
			if (strchr(token, '\n') != NULL) 
			{
            			token[strcspn(token, "\n")] = '\0';
        		}
			strcpy(arr[i][j], token);
           		token = strtok(NULL, ",");
			i++;
        	}
		j++;
		i=0;
	}	

	estratificacion(columna,fila,arr);
	fclose(archivo);
	return 0;
}

void estratificacion(int columna, int fila, char arr[columna][fila][100])
{
	int i,j,k;
	int num_clase=0;
    	char clases[100][100] = {0}; 
	int clase = columna - 1;
	int flag;
   	char elementos[100] = {0};

	float valor_f[columna][fila];
	float aux[columna][fila];

	//printf("\n\tClases:\n\t");
    	for(i=0;i<fila;i++) 
	{
        	if(strlen(arr[clase][i])>0) 
		{
            		flag = 1;
            		for(j=0;j<num_clase;j++) 
			{
                		if(strcmp(clases[j], arr[clase][i]) == 0) 
				{
                	 		flag = 0;
					elementos[j]++;
                    			break;
                		}
            		}
            		if(flag) 
			{
                		//printf("%s\n\t", arr[clase][i]);
                		strcpy(clases[num_clase], arr[clase][i]);
				elementos[num_clase]++;
                		num_clase++;
            		}
		}
    	}
	int l=0,r;
	int max;
	int min=0;
	int vf[fila];
	

	for(i=0;i<fila;i++)
	{
		vf[i] = -1;
	}
	srand(time(NULL));
	flag=0;
	for(k=0;k<num_clase;k++)
	{ 
		max = elementos[l]+min; 
		
		for(i=min;i<max;i++)
		{
			while(flag == 0)
			{
				r = min + rand() % (max - min);
    				//printf("\n\tNumero aleatorio entre %d y %d: %d\n", min, max, r);
				for(j=min;j<max;j++)
				{	
					//printf("\n\tR vale: %d",r);
					//printf("\n\tvf[%d] vale: %d",j,vf[j]);
					if(r == vf[j])
					{
						flag=0;
						break;
					}
					else
						flag=1;
				}
			}
			vf[i] = r;
			flag=0;
		}

		//printf("\n\n\tColumna %d:\n\t",k+1);
		//printf("\n\tMin vale: %d\n",min);
		//printf("\n\tMax vale: %d\n",max);
		for(i=min;i<max;i++) 
		{	
			//printf("[");	
      			for(j=0;j<clase;j++) 
			{
					//printf("%s,",arr[j][i-1]);
					valor_f[j][i] = atof(arr[j][i]);
					//printf("\n\tAtof vale: %.2f\n",atof(arr[j][i-1]));
        		}
			//printf("]\n\t");
			/*printf("\n\t[");	
			for(j=0;j<clase;j++)
			{
				printf("%.2f,",valor_f[j][i]);
			}
			printf("]\t");*/
    		}

		//Arreglo ordenado aleatoriamente
		//printf("\n\n\tColumna %d orden aleatorio:\n",k+1);
		for(i=min;i<max;i++) 
		{	
			//printf("\n\t[");
      			for(j=0;j<clase;j++) 
			{
				aux[j][i] = valor_f[j][vf[i]];
				//printf("%.2f,",aux[j][i]);
        		}
			//printf("]\t");
		}

		min = max;
		l++;
	}

	
	
	float h70[100]={0},h30[100]={0};
	int fila70=0,fila30=0;
	printf("\n\n\tNumero de valores para cada clase:\n");
   	for(i=0;i<num_clase;i++) 
	{
        	printf("\n\tClase %s: %d", clases[i], elementos[i]);
		h70[i] = elementos[i] * 0.7;
		h70[i] = round(h70[i]);
		h30[i] = elementos[i] - h70[i];
		//printf("\n\tH70 vale: %.0f",h70[i]);
		//printf("\n\tH30 vale: %.0f\n",h30[i]);
		fila70 = h70[i] + fila70;
		fila30 = h30[i] + fila30;
    	}
	//printf("\n\tFila70 vale: %d",fila70);
	//printf("\n\tFila30 vale: %d",fila30);
	float aux70[columna][fila70];
	float aux30[columna][fila30];

	//printf("\n\n\n\tNuevo arreglo 70p:\n\t");
	min = 0;
	l = 0;
	for(k=0;k<num_clase;k++) 
	{
		max = h70[k] + min;
		//printf("\n\tMin vale: %d",min);
		//printf("\n\tMax vale: %d",max);

		for(i=min;i<max;i++) 
		{	
			//printf("\n\tValor float:\n\t[");	
      			for(j=0;j<clase;j++) 
			{
				aux70[j][l] = aux[j][i];
				//printf("%.2f,",aux70[j][l]);
        		}
			//printf("]\n\n\t");
			l++;	
    		}
		min = max + h30[k];
	}

	printf("\n\n\tConjunto E:\n\t");
	printf("Total de elementos: %d\n",fila70);
	for(i=0;i<fila70;i++) 
	{	
		printf("\n\t[");
      		for(j=0;j<clase;j++) 
		{
			printf("%.2f,",aux70[j][i]);
        	}
		printf("]\t");
	}

	//printf("\n\n\n\tNuevo arreglo 30p:\n\t");
	min = h70[0];
	l = 0;
	for(k=0;k<num_clase;k++) 
	{
		max = h30[k] + min;
		//printf("\n\tMin vale: %d",min);
		//printf("\n\tMax vale: %d",max);

		for(i=min;i<max;i++) 
		{	
			//printf("\n\tValor float:\n\t[");	
      			for(j=0;j<clase;j++) 
			{
				aux30[j][l] = aux[j][i];
				//printf("%.2f,",aux30[j][l]);
        		}
			//printf("]\n\n\t");
			l++;	
    		}
		min = max + h70[k+1];
	}

	printf("\n\n\tConjunto P:\n\t");
	printf("Total de elementos: %d\n",fila30);
	for(i=0;i<fila30;i++) 
	{	
		printf("\n\t[");
      		for(j=0;j<clase;j++) 
		{
			printf("%.2f,",aux30[j][i]);
        	}
		printf("]\t");
	}
	printf("\n");

	//Para calcular los centroides
	float prom70[clase][num_clase];
	float suma70[clase];
	float min70=0;

	for(k=0;k<num_clase;k++)
	{
		printf("\n\tMin70 vale: %.0f",min70);
		printf("\n\tMax70 vale: %.0f",min70+h70[k]);
		for(i=0;i<clase;i++) 
		{
			suma70[i] = 0;	
			
			for(j=min70;j<min70+h70[k];j++)
			{
				suma70[i] = suma70[i] + aux70[i][j];
				//printf("\n\tH70 vale: %.0f",h70[i]);
				//printf("\n\tH30 vale: %.0f\n",h30[i]);
			}
			prom70[i][k] = suma70[i] / h70[k];
			//printf("\n\th70[%d] vale: %.2f",i,h70[k]);
			printf("\n\tSuma70[%d] vale: %.2f",i,suma70[i]);
			printf("\n\tProm70[%d][%d] vale: %.2f\n",i,k,prom70[i][k]);
	    	}
		min70 = min70 + h70[k];
	}
	printf("\n\tCoordenadas de los centroides:\n");
	for(k=0;k<num_clase;k++) 
	{
		printf("\n\t[");
		for(i=0;i<clase;i++)
		{
			printf("%.2f,",prom70[i][k]);

		}
		printf("]");
	}
	printf("\n");

	//Calcular distancia euclidiana de cada elemento
	float dist_euclid[fila70][num_clase];
	float sumatoria_euclid[fila70];
	for(k=0;k<num_clase;k++)
	{
		for(i=0;i<fila70;i++)
		{
			sumatoria_euclid[i] = 0;
			for(j=0;j<clase;j++) 
			{
				//printf("\n\tAux70[%d][%d] vale: %.2f",j,i,aux70[j][i]);
				//printf("\n\tprom70[%d][%d] vale: %.2f",j,i,prom70[j][k]);
				//printf("\n\tValor absoluto resta: %.2f", fabs(aux70[j][i] - prom70[j][k]) );
				
				sumatoria_euclid[i] = sumatoria_euclid[i] + pow(fabs(aux70[j][i] - prom70[j][k]), 2);
				//printf("\n\tSumatoria euclidiana en %d vale: %.2f",j,sumatoria_euclid[i]);
        		}
			
			dist_euclid[i][k] = pow(sumatoria_euclid[i],0.5);
			printf("\n\tDistancia euclidiana[%d][%d]: %.2f",i,k,dist_euclid[i][k]);
		}
		printf("\n");
	}

	//Obtener el menor numero y definir la clase a la que pertenece cada elemento
	float menor_num[fila70];
	float menor;
	int p_clase[fila70];
	j=0;
	for(i=0;i<fila70;i++)
	{
		p_clase[i] = 0;
		menor = dist_euclid[i][0];
		for(k=1;k<num_clase;k++)
		{
			if(dist_euclid[i][k] < menor)
			{
				//printf("\n\nEntro en el if");
				menor = dist_euclid[i][k]; 
				p_clase[i]++;
			}
			menor_num[i] = menor;
		}
		//printf("\n\tP_clase vale: %d",p_clase[i]);
		//printf("\n\tMenor de %d: %.2f",i,menor_num[i]);
		printf("\n\tEl elemento no. %d pertenece a la clase %s",i,clases[p_clase[i]]);
	}

}