#include<iostream>
#include<stack>
#include<math.h>
using namespace std;

const int MAXSIZE=100;

bool insymbol(char c){  // 不是运算符的bool判断
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

char precede(char front, char behind){  // 优先级的判断
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

double operate(double a, char theta, double b){ //加减乘除的运算
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

	//输入一个字符串作为算术表达式
	char * expression=new char [MAXSIZE];
	cin>>expression;
	//cout<<expression<<endl;

	int num=0;  //num表示读取到的表达式位置

	//创建数字栈 和运算符栈
	stack<char>OPTR;
	stack<double>OPND;

	//将结束识别符堆入运算符栈中
	OPTR.push('=');
	char c = expression[num];
	//cout<<num<<":"<<c<<endl;
	num++;

	//创建一个数字字符串 来处理一位以上及小数情况
	char * number = new char [MAXSIZE];
	int digit = 0;  // 标记数字部分连带小数点的位数
	int point_num = -1;  // 标记小数点的位置
	bool front_is_num = false;  //判断之前处理的是否为数字

	//判断算数表达式是否处理完毕
	while(c!='=' || OPTR.top()!='='){
		//判断读取是运算符还是数字
		if(!insymbol(c)){
			//如果不是运算符 则将该字符串堆入数字数组
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
			//如果之前处理的是数字 则进行对当前数字数组的处理 并得出一个具体有实际意义的double类型数字 堆入数字栈
			if(front_is_num){
				/*
				cout<<"number : ";
				for(int i=0; i<digit; i++)
					cout<<number[i];
				cout<<endl;
				*/
				double figure = 0;  //实际数字
				double ten_num;   //第一位数字是10的几次方
				//具体ten_num赋值的算法
				if(point_num==-1)
					ten_num = digit - 1;
				else
					ten_num = point_num - 1;
				//从数组得到figure的累加算法
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
				//digit point_num front_is_num 的初始化
				digit = 0;
				point_num = -1;
				front_is_num = false;
			}
			
			//运算符优先级判断的算法
			switch(precede(OPTR.top(),c)){
			case'<':  // '<'的情况下 继续将运算符堆入运算符栈
				//cout<<"else--<--"<<endl;
				OPTR.push(c);
				//cout<<"optr.push"<<c<<endl;
				c = expression[num];
				//cout<<"else--<--"<<num<<":"<<c<<endl;
				num++;
				break;
			case'=':  // ’=‘ 的情况下 pop出上一个运算符
				//cout<<"else--=--"<<endl;
				//cout<<"optr.pop"<<OPTR.top()<<endl;
				OPTR.pop();
				c = expression[num];
				//cout<<"else--=--"<<num<<":"<<c<<endl;
				num++;
				break;
			case'>':  // '>'的情况下 pop出顶部运算符 和 顶部的两个数字 进行运算
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