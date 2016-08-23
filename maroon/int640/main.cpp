#include <bits/stdc++.h>

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

template<int IntrgerSize>
struct BigI{
	static const int IntegerBytes=IntrgerSize/8;
	static const int IntegerNum=IntegerBytes/8;
	ull data[IntegerNum];
	inline void Init(){
		memset(data,0,sizeof(data));
	}
	inline BigI(){
		Init();
	}
	inline BigI& operator=(const int& rhs){
		if(rhs>=0){
			Init();
			data[0]=rhs;
		}else{
			memset(data,0xffffffff,sizeof(data));
			data[0]^=~rhs;
		}
		return *this;
	}
	inline BigI(const int& rhs){
		*this=rhs;
	}
	inline BigI& operator=(const BigI& rhs){
		memcpy(data,rhs.data,sizeof(rhs.data));
		return *this;
	}
	inline BigI(const BigI& rhs){
		*this=rhs;
	}
	inline bool neg() const{
		return data[IntegerNum-1]&(1LL<<63);
	}
	inline bool operator<(const BigI& rhs)const{
		if(neg()!=rhs.neg())
			return neg();
		for(int i=IntegerNum-1;i>=0;i--)
			if(data[i]!=rhs.data[i])
				return neg()^(data[i]<rhs.data[i]);
		return false;
	}
	inline bool operator>(const BigI& rhs)const{
		if(neg()!=rhs.neg())
			return !neg();
		for(int i=IntegerNum-1;i>=0;i--)
			if(data[i]!=rhs.data[i])
				return neg()^(data[i]>rhs.data[i]);
		return false;
	}
	inline bool operator==(const BigI& rhs)const{
		REP(i,IntegerNum)
			if(data[i]!=rhs.data[i])
				return false;
		return true;
	}
	inline BigI& operator+=(const BigI& rhs){
		uint128 last=0;
		REP(i,IntegerNum){
			last+=data[i];
			last+=rhs.data[i];
			data[i]=last&(~0ULL);
			last>>=64;
		}
		return *this;
	}
	inline const BigI operator+(const BigI& rhs)const{
		return BigI(*this)+=rhs;
	}
	inline BigI& operator+=(const int& rhs){
		uint128 last=rhs;
		REP(i,IntegerNum){
			last+=data[i];
			data[i]=last&(~0ULL);
			last>>=64;
		}
		return *this;
	}
	inline const BigI operator+(const int& rhs)const{
		return BigI(*this)+=rhs;
	}
	inline BigI& changeNeg(){
		REP(i,IntegerNum)
			data[i]=~data[i];
		return operator+=(1);
	}
	inline const BigI operator-()const{
		return BigI(*this).changeNeg();
	}
	inline BigI& operator-=(const BigI& rhs){
		BigI tmp=rhs;
		return operator+=(tmp.changeNeg());
	}
	inline const BigI operator-(const BigI& rhs)const{
		return BigI(*this)-=rhs;
	}
	inline BigI& operator-=(const int& rhs){
		BigI tmp=rhs;
		tmp.changeNeg();
		return operator+=(tmp);
	}
	inline const BigI operator-(const int& rhs)const{
		return BigU(*this)-=rhs;
	}
	BigI& operator*=(const BigI& rhs){
		return *this=*this*rhs;
	}
	const BigI operator*(const BigI& rhs)const{
		BigI res;
		REP(i,IntegerNum){
			uint128 last=0,p=rhs.data[i];
			BigI a;
			FOR(j,i,IntegerNum){
				last+=p*data[j-i];
				a.data[j]=last&(~0ULL);
				last>>=64;
			}
			res+=a;
		}
		return res;
	}
};

ostream& operator<<(ostream& os,const uint128& rhs){
	for(int i=3;i>=0;i--)
		printf("%08x",*((uint*)(&rhs)+i));
	return os;
}

template<int IntrgerSize>
ostream& operator<<(ostream& os,const BigI<IntrgerSize>& rhs){
	for(int i=rhs.IntegerNum-1;i>=0;i--)
		printf("%016llx",rhs.data[i]);
	return os;
}

int main(){
	int a=-11,b=-45,c=14,d=8,e=10,f=-89,g=31,h=91,i=-9;
	using uint640=BigI<640>;
	uint640 A=a,C=c,E=e,G=g,I=i;
	cout<<-I*h*G*f*E*d*C*b*A-A*b*C*d*E*f*G*h*I<<endl;
}
