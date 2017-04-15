#include<iostream>
#include<stack>
#include<math.h>
using namespace std;

const int MAXSIZE=100;

bool insymbol(char c){  // �����������bool�ж�
	int result = false;
	switch(c){
	case'+':
		result = true;
		break;
	case'-':
		result = true;
		break;
	case'*':
		result = true;
		break;
	case'/':
		result = true;
		break;
	case'(':
		result = true;
		break;
	case')':
		result = true;
		break;
	case'=':
		result = true;
		break;
	}
	return result;
}

char precede(char front, char behind){  // ���ȼ����ж�
	char data[7][7]={'>','>','<','<','<','>','>',
		                     '>','>','<','<','<','>','>',
							 '>','>','>','>','<','>','>',
							 '>','>','>','>','<','>','>',
							 '<','<','<','<','<','=','$',
							 '>','>','>','>','$','>','>',
							 '<','<','<','<','<','$','='};
	int x,y;
	switch(front){
	case'+':
		x=0;
		break;
	case'-':
		x=1;
		break;
	case'*':
		x=2;
		break;
	case'/':
		x=3;
		break;
	case'(':
		x=4;
		break;
	case')':
		x=5;
		break;
	case'=':
		x=6;
		break;
	}
	
	switch(behind){
	case'+':
		y=0;
		break;
	case'-':
		y=1;
		break;
	case'*':
		y=2;
		break;
	case'/':
		y=3;
		break;
	case'(':
		y=4;
		break;
	case')':
		y=5;
		break;
	case'=':
		y=6;
		break;
	}
	return data[x][y];
}

double operate(double a, char theta, double b){ //�Ӽ��˳�������
	double result;
	switch(theta){
	case'+':
		result = a+b;
		break;
	case'-':
		result = a-b;
		break;
	case'*':
		result = a*b;
		break;
	case'/':
		if(b==0){
			cout<<"The denominator ISN'T equal to 0!!!"<<endl;
			cout<<"Have been returned the NUMERATOR!!!"<<endl;
			system("pause");
			result = a;
		}else
			result = a/b;
		break;
	}
	return result;
}



int main(){
	cout<<"Please input a Arithmetic Expression that End with '=' !!!"<<endl;
	cout<<"The important thing which I have to tell you is your numbers can be with fractional part but not be negative !!!"<<endl;

	//����һ���ַ�����Ϊ�������ʽ
	char * expression=new char [MAXSIZE];
	cin>>expression;
	//cout<<expression<<endl;

	int num=0;  //num��ʾ��ȡ���ı��ʽλ��

	//��������ջ �������ջ
	stack<char>OPTR;
	stack<double>OPND;

	//������ʶ������������ջ��
	OPTR.push('=');
	char c = expression[num];
	//cout<<num<<":"<<c<<endl;
	num++;

	//����һ�������ַ��� ������һλ���ϼ�С�����
	char * number = new char [MAXSIZE];
	int digit = 0;  // ������ֲ�������С�����λ��
	int point_num = -1;  // ���С�����λ��
	bool front_is_num = false;  //�ж�֮ǰ������Ƿ�Ϊ����

	//�ж��������ʽ�Ƿ������
	while(c!='=' || OPTR.top()!='='){
		//�ж϶�ȡ���������������
		if(!insymbol(c)){
			//������������ �򽫸��ַ���������������
			//cout<<"if->"<<endl;
			front_is_num = true;

			if(c=='.')
				point_num=digit;

			number[digit] = c;
			digit++;

			c = expression[num];
			//cout<<"c "<<num<<":"<<c<<endl;
			num++;
		}else{
			//���֮ǰ����������� ����жԵ�ǰ��������Ĵ��� ���ó�һ��������ʵ�������double�������� ��������ջ
			if(front_is_num){
				/*
				cout<<"number : ";
				for(int i=0; i<digit; i++)
					cout<<number[i];
				cout<<endl;
				*/
				double figure = 0;  //ʵ������
				double ten_num;   //��һλ������10�ļ��η�
				//����ten_num��ֵ���㷨
				if(point_num==-1)
					ten_num = digit - 1;
				else
					ten_num = point_num - 1;
				//������õ�figure���ۼ��㷨
				for(int i=0; i<digit; i++){
					if(number[i]!='.'){
						//cout<<"figure : "<<figure<<" pow(10,ten_num) : "<<pow(10,ten_num)<<" number["<<i<<"] : "<<number[i]<<" number[i] * pow(10,ten_num) : "<<number[i] * pow(10,ten_num)<<endl;
						figure += (number[i]-48) * pow(10,ten_num);
						ten_num--;
					}
				}
				//cout<<"else--if_front_is_num--"<<endl;
				//cout<<"opnd.push : "<< figure<<endl;
				OPND.push(figure);
				//digit point_num front_is_num �ĳ�ʼ��
				digit = 0;
				point_num = -1;
				front_is_num = false;
			}
			
			//��������ȼ��жϵ��㷨
			switch(precede(OPTR.top(),c)){
			case'<':  // '<'������� ��������������������ջ
				//cout<<"else--<--"<<endl;
				OPTR.push(c);
				//cout<<"optr.push"<<c<<endl;
				c = expression[num];
				//cout<<"else--<--"<<num<<":"<<c<<endl;
				num++;
				break;
			case'=':  // ��=�� ������� pop����һ�������
				//cout<<"else--=--"<<endl;
				//cout<<"optr.pop"<<OPTR.top()<<endl;
				OPTR.pop();
				c = expression[num];
				//cout<<"else--=--"<<num<<":"<<c<<endl;
				num++;
				break;
			case'>':  // '>'������� pop����������� �� �������������� ��������
				//cout<<"else-->--"<<endl;
				char theta = OPTR.top();
				//cout<<"optr.pop"<<OPTR.top()<<endl;
				OPTR.pop();
				double b = OPND.top();
				//cout<<"opnd.pop"<<OPTR.top()<<endl;
				OPND.pop();
				double a = OPND.top();
				//cout<<"opnd.pop"<<OPTR.top()<<endl;
				OPND.pop();
				OPND.push(operate(a,theta,b));
				//cout<<"opnd.push"<<operate(a,theta,b)<<endl;
				break;
			}
		}
	}
	cout<<"the result is "<<OPND.top()<<endl;
	delete expression;
	delete number;
	system("pause");
	return 0;
}