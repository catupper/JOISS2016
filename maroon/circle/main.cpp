#include <bits/stdc++.h>
#include <gmpxx.h>

#define FOR(i,a,b) for(int i=a;i<b;i++)
#define REP(i,b) FOR(i,0,b)

using namespace std;

int read(){
	int i;
	scanf("%d",&i);
	return i;
}

using uint=unsigned int;
using ll=long long;
using ull=unsigned long long;
//using bint=ll;
using bint=mpz_class;

struct CircleUnderLine{
	bint a,b,c;
	//1/a * (b - sqrt(c))
	void Show(){
		cout<<"1/"<<a<<" * ("<<b<<" - sqrt("<<c<<"))"<<endl;
	}
	void DoubleShow(){
	//	cout<<(long double)(b-sqrt((long double)c))/(long double)a<<endl;
	}
};

inline bool operator<(const CircleUnderLine& lhs,const CircleUnderLine& rhs){
	bint a=lhs.b*rhs.a,b=rhs.c*lhs.a*lhs.a;
	bint c=rhs.b*lhs.a,d=lhs.c*rhs.a*rhs.a;
	bool bias=false;
	if(a<c){
		swap(a,c);
		swap(b,c);
		bias=true;
	}
	a-=c;
	d-=a*a;
	d-=b;
	return bias^(
	d<0?
	false:
	a*a*b*4<d
	);
}

CircleUnderLine ComputeCircle(bint ax,bint ay,bint bx,bint by,bint cx,bint cy){
	bint numerX=(by-cy)*(ax*ax+ay*ay)+(cy-ay)*(bx*bx+by*by)+(ay-by)*(cx*cx+cy*cy);
	bint numerY=-((bx-cx)*(ay*ay+ax*ax)+(cx-ax)*(by*by+bx*bx)+(ax-bx)*(cy*cy+cx*cx));
	bint denom=(ax*by+bx*cy+cx*ay-ax*cy-bx*ay-cx*by)*2;
	if(denom<0){
		numerX=-numerX;
		numerY=-numerY;
		denom=-denom;
	}
	bint rad=(ax*denom-numerX)*(ax*denom-numerX)+(ay*denom-numerY)*(ay*denom-numerY);
	return CircleUnderLine{denom,numerY,rad};
}

int main(){
	srand(clock());
	const int tryCount=100000;
	int tmp=0;
	REP(_,tryCount){
		CircleUnderLine a=ComputeCircle(rand(),rand(),rand(),rand(),rand(),rand());
		CircleUnderLine b=ComputeCircle(rand(),rand(),rand(),rand(),rand(),rand());
		tmp+=(a<b);
	}
	cout<<tmp<<endl;
}
