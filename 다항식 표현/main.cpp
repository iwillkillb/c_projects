#include <iostream>
#define MaxDegree 20
using namespace std;
/*
class Polynomial{
	private:
		int degree; //0이 아닌 항 중 제일 큰 지수 
		float *coef;
		
		Term *termArray;
		int capacity;
		int terms;
	public:
		Polynomial(int d);
		Polynomial Add(Polynomial poly);
		Polynomial Mult(Polynomial poly);
		void NewTerm(const float c, const int e);
		
		float Eval(float f);
};
class Polynomial;
class Term{
	friend Polynomial;
	private:
		float coef;
		int exp;
};



Polynomial::Polynomial(int d){
	degree = d;
	coef = new float[degree + 1];
}

Polynomial Polynomial::Add(Polynomial b){
	Polynomial c;
	int aPos = 0, bPos = 0;
	while((aPos < terms) && (bPos < b.terms)){
		if(termArray[aPos].exp == b.termArray[bPos].exp){
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if(termArray[aPos].exp < b.termArray[bPos].exp){
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	for( ; aPos < terms ; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for( ; bPos < b.terms ; aPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}

void Polynomial::NewTerm(const float the Coeff, const int theExp){
	if(terms == capacity){
		capacity *= 2;
		term *temp = new term[capacity];
		copy(termArray, termArray + terms, temp);
		delete [] termArray;
		termArray = temp;
	}
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}
*/
class Polynomial{
	private:
		int degree;
		float *coef;
	public:
		Polynomial(int d);
		Polynomial Add(Polynomial b);
		void PrintCoef();
};

Polynomial::Polynomial(int d){
	degree = d;
	coef = new float[degree+1];
	for(int a=0 ; a<degree ; a++){
		cout << a+1 << "번째 계수 : ";
		cin >> coef[a];
	}
	cout << "계수 입력 완료." << endl << endl;
}

Polynomial Polynomial::Add(Polynomial b){
	if(this->degree > b.degree){
		for(int a=0 ; a<this->degree ; a++)
			this->coef[a] += b.coef[a];
		return (*this);
	}
	else {
		for(int a=0 ; a<b.degree ; a++)
			b.coef[a] += this->coef[a];
		return b;
	}
}

void Polynomial::PrintCoef(){
	for(int a=0 ; a<degree ; a++)
		cout << a+1 << "번째 계수 : " << coef[a] << endl;
	cout << "계수 출력 완료." << endl << endl;
}

int main(){
	int degree1, degree2;
	
	cout << "첫번째 다항식의 차수 : ";
	cin >> degree1;	Polynomial a(degree1);
	cout << "두번째 다항식의 차수 : ";
	cin >> degree2;	Polynomial b(degree2);
	
	a = a.Add(b);
	a.PrintCoef();
	b.PrintCoef();
	
	return 0;
}
