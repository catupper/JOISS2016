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
struct BigU{
	static const int IntegerBytes=IntrgerSize/8;
	static const int IntegerNum=IntegerBytes/8;
	ull data[IntegerNum];
	inline void Init(){
		memset(data,0,sizeof(data));
	}
	inline BigU(){
		Init();
	}
	inline BigU& operator=(const ull& rhs){
		Init();
		data[0]=rhs;
		return *this;
	}
	inline BigU(const ull& rhs){
		*this=rhs;
	}
	inline BigU& operator=(const uint128& rhs){
		Init();
		*((uint128*)data)=rhs;
		return *this;
	}
	inline BigU(const uint128& rhs){
		*this=rhs;
	}
	inline BigU& operator=(const BigU& rhs){
		memcpy(data,rhs.data,sizeof(rhs.data));
		return *this;
	}
	inline BigU(const BigU& rhs){
		*this=rhs;
	}
	bool operator<(const BigU& rhs)const{
		for(int i=IntegerNum-1;i>=0;i--)
			if(data[i]!=rhs.data[i])
				return data[i]<rhs.data[i];
		return false;
	}
	bool operator>(const BigU& rhs)const{
		for(int i=IntegerNum-1;i>=0;i--)
			if(data[i]!=rhs.data[i])
				return data[i]>rhs.data[i];
		return false;
	}
	bool operator==(const BigU& rhs)const{
		REP(i,IntegerNum)
			if(data[i]!=rhs.data[i])
				return false;
		return true;
	}
	BigU& operator+=(const BigU& rhs){
		uint128 last=0;
		REP(i,IntegerNum){
			last+=data[i];
			last+=rhs.data[i];
			data[i]=last&(~0ULL);
			last>>=64;
		}
		return *this;
	}
	const BigU operator+(const BigU& rhs)const{
		return BigU(*this)+=rhs;
	}
	BigU& operator*=(const BigU& rhs){
		return *this=*this*rhs;
	}
	const BigU operator*(const BigU& rhs)const{
		BigU res;
		REP(i,IntegerNum){
			uint128 last=0,p=rhs.data[i];
			BigU a;
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
ostream& operator<<(ostream& os,const BigU<IntrgerSize>& rhs){
	for(int i=rhs.IntegerNum-1;i>=0;i--)
		printf("%016llx",rhs.data[i]);
	return os;
}

int main(){
	uint128 a=0x1001002002002;
	cout<<a<<endl;
	using uint640=BigU<640>;
	uint640 b=a;
	cout<<b*b<<endl;
}
