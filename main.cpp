#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;

int** generar_matriz(int f, int c)
{
  int **r;
  r = new int*[f];
  for(int i = 0;i<f;i++)
    r[i] = new int[c];

  for(int i=0;i<f;i++)
    for(int j=0;j<c;j++)
      r[i][j] = rand()%10;
  return r;
}

void print(int **a,int f, int c)
{
  for(int i=0;i<f;i++)
  {
    for(int j=0;j<c;j++)
      cout << a[i][j] << " ";
    cout << "\n";
  }
}

int** multiplicacion_matriz(int **a,int fa,int ca, int **b, int fb, int cb)
{
  int **r;
  r = new int*[fa];
  for(int i = 0;i<fa;i++)
  {
    r[i] = new int[cb];
    for(int j=0;j<cb;j++)
      r[i][j] = 0;
  }

  for(int i=0;i<fa;i++)
  {
    for(int j=0;j<cb;j++)
    {
      for(int k=0;k<ca;k++)
      {
          r[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return r;
}

//recibe matrices cuadradas
int** multiplicacion_matriz_bloques(int** a, int** b, int t )
{
	int bloques = t/4;
	int ** r = new int * [t];
	for(int i=0; i<t; i++)
  {
      r[i]=new int [t];
      for(int j=0; j<t; j++)
      {
          r[i][j]=0;
      }
  }

  for(int ii=0; ii<t; ii+=bloques)
  	for(int jj=0; jj<t; jj+=bloques)
  		for(int kk=0; kk<t; kk+=bloques)
  			for(int i=ii; i<ii+bloques; i++)
  				for(int j=jj; j<jj+bloques; j++)
  					for(int k=kk; k<kk+bloques; k++)
  						r[i][j]+=a[i][k]*b[k][j];


  return r;
}




int main()
{
  int **a,**b,**p,**p2,tam;
  tam = 1000;
  cout << "ingrese numero de elementos: ";
  cin >> tam;
  cout << "numero de elementos: " << tam << endl;
  a=generar_matriz(tam,tam);
  b=generar_matriz(tam,tam);

  print(a,tam,tam);
  cout << "\n\n";
  print(b,tam,tam);

  auto start = std::chrono::system_clock::now();
  p=multiplicacion_matriz(a,tam,tam,b,tam,tam);
  auto end = std::chrono::system_clock::now();

  cout << "\n\n";
  print(p,tam,tam);
  cout << "\n\n";
  print(p2,tam,tam);

  auto start2 = std::chrono::system_clock::now();
  p2 = multiplicacion_matriz_bloques(a,b,tam);
  auto end2 = std::chrono::system_clock::now();

   std::chrono::duration<float,std::milli> duration = end - start;
   cout << " \nnormal: " << duration.count()/1000 << " s\n" << endl;

  std::chrono::duration<float,std::milli> duration2 = end2 - start2;
  cout << " \nbloques: " << duration2.count()/1000 << " s\n" << endl;

  // //p=multiplicacion_matriz(a,tam,tam,b,tam,tam);
  // p = multiplicacion_matriz_bloques(a,b,tam);
  return 0;

}
