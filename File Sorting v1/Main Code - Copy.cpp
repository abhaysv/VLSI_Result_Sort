#include  <iostream>
#include  <string>
#include  <fstream>
#include<conio.h>
#include <stdio.h>
#include <algorithm> 

using namespace std;

FILE *fp1;
char str [80];
float buffer[][5]={0};
float data[255][5],buffer_y[255][5];
float CX[2],CY[2];
char str2[255][20];

int maxrow = 3;

//======================[[-- VARIABLES ANNOTATION  --[[===================//
//	str2 is used to store the label in 1st column
//  data is used to store the column 2 , 3 flot type height , width
//  CX is an array for calculated X ie. CX[0] is u and CX[1] is v
//  Similarly CY is the calculated value for Y
//  Buffer and Buffer_y are the copy of the data array for calc X & Y
//=======================================================================//

void read_file();
void display_array();
void swap(float &, float &);
void calc_x(int);
void compute(int);
void write_file();

//======================[[-- MAIN FUNC  --[[===================//
// read_file() - reads the text file and init data and buffers
// compute(row) - Compuetes row number
// display_array() - displays buffer array fir debug purpose
// write_file() - Write file called Output.txt
//=============================================================//

void main() 
{
	
	printf("Loading file.");
	read_file();

	for(int k=0;k<(maxrow-1);k++)
	{
	compute(k);
	printf("Display Array.\n");
	display_array();
	}
	write_file();
	getch();

}

//======================[[-- CALC X FUNC  --[[===================//
// Takes input row no as index
// X=(x1+x2,min(y1,y2))
// X rep as (u,v) as (CX[0],CX[1])
// Used bufferX for computation leaving data unchanged
//===============================================================//
void calc_x(int index)
{
	cout<<"buffer[index][1]="<<buffer[index][1]<<" buffer[index][2]="<<buffer[index][2]<<endl;
	cout<<"buffer[index+1][1]="<<buffer[index+1][1]<<" buffer[index+1][2]="<<buffer[index+1][2]<<endl;
	CX[0] = buffer[index][1]+buffer[index+1][1];
	CX[1] = min(buffer[index][2],buffer[index+1][2]);
	cout<<"CX[0]="<<CX[0]<<"CX[1]="<<CX[1]<<endl;
	
}
//======================[[-- CALC Y FUNC  --[[===================//
// Takes input row no as index
// X=(min(x1,x2),y1+y2)
// Y rep as (u,v) as (CY[0],CY[1])
// Used buffer_y for computation leaving data unchanged
//===============================================================//


void calc_y(int index)
{
	cout<<"buffer_y[index][1]="<<buffer_y[index][1]<<" buffer_y[index][2]="<<buffer_y[index][2]<<endl;
	cout<<"buffer_y[index+1][1]="<<buffer_y[index+1][1]<<" buffer_y[index+1][2]="<<buffer_y[index+1][2]<<endl;
	CY[0] = min(buffer_y[index][1],buffer_y[index+1][1]);
	CY[1] = buffer_y[index][2]+buffer_y[index+1][2];
	cout<<"CY[0]="<<CY[0]<<"CY[1]="<<CY[1]<<endl;
	
}
void compute(int i)
{	
	
	calc_x(i);
	if(CX[0]>CX[1])
	{
		cout<<"B[0][1]="<<buffer[i][1]<<"B[0][2]="<<buffer[i][2];
		swap(buffer[i][1],buffer[i][2]);
		cout<<"B[0][1]="<<buffer[i][1]<<"B[0][2]="<<buffer[i][2]<<endl;
		calc_x(i);
	}
	else 
	{
		cout<<"B[i+1][1]="<<buffer[i+1][1]<<"B[i+1][2]="<<buffer[i+1][2];
		swap(buffer[i+1][1],buffer[i+1][2]);
		cout<<"B[i+1][1]="<<buffer[i+1][1]<<"B[i+1][2]="<<buffer[i+1][2]<<endl;
		calc_x(i);
	}

	calc_y(i);

	if(CY[0]>CY[1])
	{
		cout<<"BY[0][1]="<<buffer_y[i][1]<<"BY[0][2]="<<buffer_y[i][2];
		swap(buffer_y[i][1],buffer_y[i][2]);
		cout<<"BY[0][1]="<<buffer_y[i][1]<<"BY[0][2]="<<buffer_y[i][2]<<endl;
		calc_y(i);
	}
	else 
	{
		cout<<"BY[i+1][1]="<<buffer_y[i+1][1]<<"BY[i+1][2]="<<buffer_y[i+1][2];
		swap(buffer_y[i+1][1],buffer_y[i+1][2]);
		cout<<"BY[i+1][1]="<<buffer_y[i+1][1]<<"BY[i+1][2]="<<buffer_y[i+1][2]<<endl;
		calc_y(i);
	}
	if((CX[0]*CX[1])<(CY[0]*CY[0]))
	{
		data[i][1] = buffer[i][1];
		data[i][2] = buffer[i][2];
		data[i+1][1] = buffer[i+1][1];
		data[i+1][2] = buffer[i+1][2];

//		IF Min product is X then copy value of buffer_x to buffer_y and update same to data

		buffer_y[i][1] = buffer[i][1];
		buffer_y[i][2] = buffer[i][2];
		buffer_y[i+1][1] = buffer[i+1][1];
		buffer_y[i+1][2] = buffer[i+1][2];
	}
	else 
	{
		data[i][1] = buffer_y[i][1];
		data[i][2] = buffer_y[i][2];
		data[i+1][1] = buffer_y[i+1][1];
		data[i+1][2] = buffer_y[i+1][2];

//		IF Min product is Y then copy value of buffer_Y to buffer_x and update same to data

		buffer[i][1] = buffer_y[i][1];
		buffer[i][2] = buffer_y[i][2];
		buffer[i+1][1] = buffer_y[i+1][1];
		buffer[i+1][2] = buffer_y[i+1][2];
	}
	
}

void read_file()
{
	int i,j;
	fp1 = fopen("Test.txt","r");
	
	for(i=0;i<maxrow;i++) 
	{
		fscanf (fp1, "%s %f %f", str2[i] ,&buffer[i][1],&buffer[i][2]);
		buffer[i][3] = 0;
		data[i][1] = buffer[i][1];
		data[i][2] = buffer[i][2];
		data[i][3] = buffer[i][3];
		buffer_y[i][1] = buffer[i][1];
		buffer_y[i][2] = buffer[i][2];
		buffer_y[i][3] = buffer[i][3];
		printf(".......");

	}

	printf("\n");
	fclose(fp1);
	
}



void write_file()
{
	int i,j;
	fp1 = fopen("Output.txt","w");
	printf("\nWriting to output.txt");
	for(i=0;i<maxrow;i++) 
	{
		fprintf(fp1,"%s", str2[i]);
		fprintf(fp1," ");
		for(j=1;j<4;j++)
		{
			fprintf(fp1,"%f", data[i][j]);
			fprintf(fp1," ");
		}
		fprintf(fp1,"\n");
	}
	printf("\n");
	fclose(fp1);
}
void display_array()
{
	int i,j;
	for(i=0;i<maxrow;i++) 
	{
		for(j=1;j<4;j++)
		{
			printf("%f ",data[i][j]);
		}
		printf("\n");
	}
}



void swap(float &x, float &y) {
   float temp;
   temp = x; 
   x = y;    
   y = temp; 
  
   return;
}
