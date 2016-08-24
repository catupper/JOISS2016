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
using int128=__int128;
using uint128=unsigned __int128;

#include "bigI.hpp"

//using bint=mpz_class;
//using bint=ll;
using bint=BigI<640>;
//using bint=long double;

struct AccurateCircleUnderLine{
	bint a,b,c;
	//1/a * (b - sqrt(c))
	void Show(){
		cout<<"1/"<<a<<" * ("<<b<<" - sqrt("<<c<<"))"<<endl;
	}
};

bool operator<(const AccurateCircleUnderLine& lhs,const AccurateCircleUnderLine& rhs){
	bint a=lhs.b*rhs.a,b=rhs.c*lhs.a*lhs.a;
	bint c=rhs.b*lhs.a,d=lhs.c*rhs.a*rhs.a;
	bool bias=false;
	if(a<c){
		swap(a,c);
		swap(b,d);
		bias=true;
	}
	a-=c;
	d-=a*a;
	d-=b;
	return bias^(
	d<0?
	false:
	a*a*b*4<d*d
	);
}

AccurateCircleUnderLine ComputeAccurateCircle(bint ax,bint ay,bint bx,bint by,bint cx,bint cy){
	bint numerX=(by-cy)*(ax*ax+ay*ay)+(cy-ay)*(bx*bx+by*by)+(ay-by)*(cx*cx+cy*cy);
	bint numerY=-((bx-cx)*(ay*ay+ax*ax)+(cx-ax)*(by*by+bx*bx)+(ax-bx)*(cy*cy+cx*cx));
	bint denom=(ax*by+bx*cy+cx*ay-ax*cy-bx*ay-cx*by)*2;
	if(denom<0){
		numerX=-numerX;
		numerY=-numerY;
		denom=-denom;
	}
	bint rad=(denom*ax-numerX)*(denom*ax-numerX)+(denom*ay-numerY)*(denom*ay-numerY);
	return AccurateCircleUnderLine{denom,numerY,rad};
}

struct CircleUnderLine{
	double y;
	int ax,ay,bx,by,cx,cy;
	AccurateCircleUnderLine GenerateAccurateCircle()const{
		return ComputeAccurateCircle(ax,ay,bx,by,cx,cy);
	}
	void Show(){
		ComputeAccurateCircle(ax,ay,bx,by,cx,cy).Show();
	}
	void DoubleShow(){
		cout<<y<<endl;
	}
};

bool operator<(const CircleUnderLine& lhs,const CircleUnderLine& rhs){
	double dif=lhs.y-rhs.y;
	const double errRate=1e-6;
	if(abs(dif)<errRate||abs(dif)/max(abs(lhs.y),abs(rhs.y))<errRate)
		return lhs.GenerateAccurateCircle()<rhs.GenerateAccurateCircle();
	else
		return dif<0;
}

CircleUnderLine ComputeCircle(int ax,int ay,int bx,int by,int cx,int cy){
	double numerX=double(by-cy)*(double(ax)*ax+double(ay)*ay)+double(cy-ay)*(double(bx)*bx+double(by)*by)+double(ay-by)*(double(cx)*cx+double(cy)*cy);
	double numerY=-(double(bx-cx)*(double(ay)*ay+double(ax)*ax)+double(cx-ax)*(double(by)*by+double(bx)*bx)+double(ax-bx)*(double(cy)*cy+double(cx)*cx));
	double denom=(double(ax)*by+double(bx)*cy+double(cx)*ay-double(ax)*cy-double(bx)*ay-double(cx)*by)*2;
	numerX/=denom;
	numerY/=denom;
	double rad=(numerX-ax)*(numerX-ax)+(numerY-ay)*(numerY-ay);
	return CircleUnderLine{numerY-sqrt(rad),ax,ay,bx,by,cx,cy};
}

const int n=100000;
bool ans1[n],ans2[n];
CircleUnderLine cul[n];

int main(){
	//srand(clock());
	REP(i,n)
		cul[i]=ComputeCircle(rand(),rand(),rand(),rand(),rand(),rand());
	sort(cul,cul+n);
	cul[0].Show();
	/*CircleUnderLine a=ComputeCircle(-1,-2,-4,-6,-1,-5);
	CircleUnderLine b=ComputeCircle(48,6,0,48,54,18);
	a.Show();
	a.DoubleShow();
	b.Show();
	b.DoubleShow();
	cout<<(a<b)<<endl;*/
	/*int start=clock();
	REP(i,n)
		cul[i]=ComputeCircle(rand(),rand(),rand(),rand(),rand(),rand());
	REP(i,n-1)
		ans1[i]=cul[i]<cul[i+1];
	cout<<"With Pruning "<<double(clock()-start)/CLOCKS_PER_SEC<<" s"<<endl;
	start=clock();
	REP(i,n-1)
		ans2[i]=cul[i].GenerateAccurateCircle()<cul[i+1].GenerateAccurateCircle();
	cout<<"Without Pruning "<<double(clock()-start)/CLOCKS_PER_SEC<<" s"<<endl;
	REP(i,n)
		if(ans1[i]!=ans2[i]){
			cout<<"Miss "<<i<<" "<<ans1[i]<<" "<<ans2[i]<<endl;
			cul[i].Show();
			cul[i].DoubleShow();
			cul[i+1].Show();
			cul[i+1].DoubleShow();
		}*/
}
