// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include <cmath>

  double solve( string s) { // разбор строки
	 int i = 0,j=0;
	 double temp, x, d, tx;
	 lexem arr[1000];
	 
	 if(s[i] == '-') {
		
		 arr[j++]= -1;
		 arr[j++]="*";
		 i++;
	 }
	 while (s[i]!='\0' ) {		 
	
		
		 if((s[i] >= '0') && (s[i]<='9')) {
			 x = 0;
			 d= 10;
			 
			 while ((s[i] >= '0') && (s[i]<='9'))
			 {
				 temp = (double)(s[i] - '0');
				
				 x=x*10 + temp;
				 i++;
				 				
			 }
			 if (s[i]=='.') {
				 i++;				
				 
				 while ((s[i] >= '0') && (s[i]<='9'))
				 {
					 if ((s[i] >= '0') && (s[i]<='9')) {
						 temp = (double)(s[i] - '0');
						 
						 x=x + temp/d;
						 i++;
						 d=d*10;
					 }
				 }
			 }
			  
			 
			 arr[j] = x;

			 j++;
			 
		 }
		 
		 else if((s[i] == 's')&&(s[i+1]=='i')&&(s[i+2]=='n')) {
			 arr[j++]="sin";
			  i=i+3;
		 }
		 else if((s[i] == 'c')&&(s[i+1]=='o')&&(s[i+2]=='s')) {
			 arr[j++]="cos";
			  i=i+3;
		 }
		 else  if((s[i] == 'l')&&(s[i+1] == 'n')) {
			 arr[j++]="ln";
			  i=i+2;
		 }
		 else  if((s[i] == 'e')&&(s[i+1]=='x')&&(s[i+2]=='p')) {
			 arr[j++]="exp";
			 i=i+3;
		 }
		 else if(s[i]=='x'&& ((s[i+1] >= '1') && (s[i+1]<='9'))) {
			 cout<<"Ведите  x"<<s[i+1]<<endl;
			 cin>> tx;
			 arr[j++]= tx;
			 i=i+2;
		 }
		 else  if(s[i] == '+') {
			
			 arr[j] = "+";
			 j++;
			 i++;
		 }

		 else  if(s[i] == '*') {
			 
			 arr[j] = "*";
			 j++;
			 i++;
		 }

		 else  if(s[i] == '/') {
			 
			 arr[j] = "/";
			 j++;
			 i++;
		 }

		 else if(s[i] == '-') {
			 if(arr[j-1].isop()&&arr[j-1].getop()!=")") {
				 
					 arr[j++]=-1;
					 arr[j++]="*";
					 i++;
				 
			 } else {
			 arr[j] = "-";
			 j++;
			 i++;
			 }
			 
		 }

		 else if(s[i] == '(') {
			 
			 arr[j] = "(";
			 j++;
			 i++;
		 }

		 else if(s[i] == ')') {
			 
			 arr[j] = ")";
			 j++;
			 i++;
		 }		 
		 else {cout<<"Недопустимый символ "<< s[i]<<endl;
		 return 0;
		 }		
	 }	 	
	 //массив лексем
	 
	 
	 
	 switch (proverka(arr, j)) { //проверка
	 case 0: { 
		 cout << "Проверка успешно пройдена" << endl;
		 break;}
	 case 1: {
		 cout << "После числа  стоит не бинарный оператор или )" << endl;
		 return 0;}
	 case 2: {
		 cout << "После ( стоит не номер или (" << endl;
		return 0;}
	 case 3: {
		 cout << "После )  стоит не  бинарный  оператор или )" << endl;
		 return 0;}
	 case 4: {
		 cout << "После оператора стоит не  число или (" << endl;
		 return 0;}
	 case 5: {
		 cout << ") стоит раньше чем (" << endl;
		 return 0;}
	 case 6: {
		 cout << "Количество ( и ) не совпадает" << endl;
		 return 0;}
	 case 7: {
		 cout << "Недопустимый знак в конце выражения" << endl;
		 return 0;}
	 }
	 

	
	 lexem *arr2; // перевод в ОПЗ
	  arr2 = new lexem[j];
	  stack<lexem> t;
	  int l=0 ;
	  
	  for (int k= 0; k < j; k++) {
		   
		  if(arr[k].isnum()) {		
			 
			  arr2[l] = arr[k];
			  
			  l++;
			  
		  }  else  {
			  
			  if(t.isempty()) {
				  
				  t.push(arr[k]);
				  
			  }  else  {
				  if(arr[k].getprior() == 1) {
					  t.push(arr[k]);
				  } else {

					  while (!(t.isempty()) && (arr[k].getprior() <= t.show().getprior())) {
						  if(t.show().getprior() == 1) {
							  t.pop();
							  break;
						  } else {
							  arr2[l]=t.pop();
							  l++;	
						  }
					  }	
					  if (arr[k].getprior() != 0) {
					  t.push(arr[k]);
					  }
				  }
			  }
			 
			  
		  }
		   
	  }
	     
	   while(!(t.isempty())){
		   
		arr2[l]=t.pop();
		l++;
	   }
		
	
	  return calculate (arr2 ,  l); //вычисление
 }
 
 
 int proverka (lexem* arr, int n) {	 
	 int j=0;
	 for(int i = 0; i < n; i++) {
		 if(arr[i].isnum()){
			if(i!=n-1){
			 if(( arr[i+1].getop() == "+")&&(arr[i+1].getop() == "-")&&(arr[i+1].getop() == "*")&&(arr[i+1].getop() == "/")&&(arr[i+1].getop() == ")")) {return 1;}		
			}
		 } else {
			 
			 if(arr[i].getop()=="(") {	
				 j++;
				 if(i==n-1) {return 7;}
				 if ((arr[i+1].isop()) && (arr[i+1].getop() !="(")) {return 2;}				
			 }
			 else if(arr[i].getop()==")") {
				 j--;
				 if(i!=n-1){
					 if ((arr[i+1].isnum()) || ((arr[i+1].getop() != "+")&&(arr[i+1].getop() != "-")&&(arr[i+1].getop() != "*")&&(arr[i+1].getop() != "/")&&(arr[i+1].getop() != ")"))) {return 3;} 
				 }
			 }			 
			 else {
				 if(i==n-1) {return 7;}
				 else if ((arr[i+1].isop()) && ((arr[i+1].getop() !="(") && (arr[i+1].getop() !="cos")&& (arr[i+1].getop() !="sin")&& (arr[i+1].getop() !="ln")&& (arr[i+1].getop() !="exp"))) {return 4;}
			 }
			 if (j<0){return 5;}
		 }
		 
	 }
	 if(j!=0){return 6;}
	 return 0;} 

 double calculate (lexem* arr , int l) {
	 stack<lexem> s;
	 lexem t;
	 double x1, x2;
	 for(int i = 0; i < l; i++) {
		
		 if (arr[i].isnum()) {
			 
			 s.push(arr[i]);
		
		 }
		 else {
			  
			 
			 if(arr[i].getop() == "+"){ 
				 x2 = (s.pop()).getnum();
				 x1 = (s.pop()).getnum();
				 t = x1 + x2;}
			 if(arr[i].getop() == "-"){ 
				 x2 = (s.pop()).getnum();
				 x1 = (s.pop()).getnum();
				 t = x1 - x2;}
			 if(arr[i].getop() == "*"){ 
				 x2 = (s.pop()).getnum();
				 x1 = (s.pop()).getnum();
				 t = x1 * x2;}
			 if(arr[i].getop() == "/"){ 
				 x2 = (s.pop()).getnum();
				 x1 = (s.pop()).getnum();
				 t = x1 / x2;}

			 if(arr[i].getop() == "sin"){ 
				 x2 = (s.pop()).getnum();
				 t =  sin(x2);}
			 if(arr[i].getop() == "cos"){ 
				 x2 = (s.pop()).getnum();
				 t = cos(x2);}
			 if(arr[i].getop() == "ln"){ 
				 x2 = (s.pop()).getnum();
				 t = log(x2);}
			 if(arr[i].getop() == "exp"){ 
				 x2 = (s.pop()).getnum();
				 t = exp(x2);}
			 s.push(t);				
		 }
	 }
	 return (s.pop()).getnum();
 }

 