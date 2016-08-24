#include <bits/stdc++.h>
#include <gmpxx.h>

#define FOR(i,a,b) for(int i=a;i<b;i++)
#define REP(i,b) FOR(i,0,b)
#define MP make_pair
#define PB push_back

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
				return data[i]<rhs.data[i];
		return false;
	}
	inline bool operator>(const BigI& rhs)const{
		if(neg()!=rhs.neg())
			return !neg();
		for(int i=IntegerNum-1;i>=0;i--)
			if(data[i]!=rhs.data[i])
				return data[i]>rhs.data[i];
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
	inline BigI& operator*=(const BigI& rhs){
		return *this=*this*rhs;
	}
	inline const BigI operator*(const BigI& rhs)const{
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

using bint=BigI<640>;

const int Nmax=500000;

vector<int> graph[Nmax];

void AddEdge(int a,int b){
	if(0<=a&&a<Nmax&&0<=b&&b<Nmax){
		graph[a].PB(b);
		graph[b].PB(a);
	}
}

struct Pos{
	int x,y;
	void dbg()const{
		cout<<"x "<<x<<" y "<<y<<endl;
	}
} sites[Nmax];

inline ll Cross(const Pos& a,const Pos& b){
	return ll(a.x)*b.y-ll(a.y)*b.x;
}

inline bool Clockwise(const Pos& a,const Pos& b,const Pos& c){
	return Cross(a,b)+Cross(b,c)+Cross(c,a)<0;
}

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

AccurateCircleUnderLine ComputeAccurateCircleUnderLine(bint ax,bint ay,bint bx,bint by,bint cx,bint cy){
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
	Pos a,b,c;
	AccurateCircleUnderLine GenerateAccurateCircleUnderLine()const{
		return ComputeAccurateCircleUnderLine(a.x,a.y,b.x,b.y,c.x,c.y);
	}
	void Show(){
		ComputeAccurateCircleUnderLine(a.x,a.y,b.x,b.y,c.x,c.y).Show();
	}
	void DoubleShow(){
		cout<<y<<endl;
	}
	void dbg()const{
		cout<<"Point 1";
		a.dbg();
		cout<<"Point 2";
		b.dbg();
		cout<<"Point 3";
		c.dbg();
	}
};

bool operator<(const CircleUnderLine& lhs,const CircleUnderLine& rhs){
	double dif=lhs.y-rhs.y;
	const double errRate=1e-9;
	static int c=0;
	if(abs(dif)<errRate||abs(dif)/max(abs(lhs.y),abs(rhs.y))<errRate){
		if((++c)%1000==0)
			printf("Called %d times\n",c);
		cout<<"Left "<<setprecision(20)<<lhs.y<<endl;
		lhs.dbg();
		cout<<"Right "<<setprecision(20)<<rhs.y<<endl;
		rhs.dbg();
		return lhs.GenerateAccurateCircleUnderLine()<rhs.GenerateAccurateCircleUnderLine();
	}else
		return dif<0;
}

CircleUnderLine ComputeCircleUnderLine(Pos a,Pos b,Pos c){
	double numerX=double(b.y-c.y)*(double(a.x)*a.x+double(a.y)*a.y)+double(c.y-a.y)*(double(b.x)*b.x+double(b.y)*b.y)+double(a.y-b.y)*(double(c.x)*c.x+double(c.y)*c.y);
	double numerY=-(double(b.x-c.x)*(double(a.y)*a.y+double(a.x)*a.x)+double(c.x-a.x)*(double(b.y)*b.y+double(b.x)*b.x)+double(a.x-b.x)*(double(c.y)*c.y+double(c.x)*c.x));
	double denom=(double(a.x)*b.y+double(b.x)*c.y+double(c.x)*a.y-double(a.x)*c.y-double(b.x)*a.y-double(c.x)*b.y)*2;
	numerX/=denom;
	numerY/=denom;
	double rad=(numerX-a.x)*(numerX-a.x)+(numerY-a.y)*(numerY-a.y);
	return CircleUnderLine{numerY-sqrt(rad),a.x,a.y,b.x,b.y,c.x,c.y};
}

struct Node{
	using NP=Node*;
	NP p,l,r,pr,nx;
	Pos pos;
	int id;
	int State(){
		if(p&&p->l==this) return -1;
		if(p&&p->r==this) return 1;
		return 0;
	}
	void Rotate(){
		NP q=p,m;
		if(State()==-1){
			m=r;
			r=q;
			q->l=m;
		}else{
			m=l;
			l=q;
			q->r=m;
		}
		if(m)
			m->p=q;
		p=q->p;
		q->p=this;
		if(p&&p->l==q)
			p->l=this;
		if(p&&p->r==q)
			p->r=this;
	}
	NP Splay(){
		while(p){
			int a=State(),b=p->State();
			if(b&&a==b)
				p->Rotate();
			if(b&&a!=b)
				Rotate();
			Rotate();
		}
		return this;
	}
} nodes[Nmax*3];

using NP=Node*;

using pnn=pair<NP,NP>;

NP newNode(){
	static int i=0;
	nodes[i]=Node{NULL,NULL,NULL,NULL,NULL,Pos{-1,-1},-1};
	return nodes+(i++);
}

void Link(NP a,NP b){
	if(a)
		a->nx=b;
	if(b)
		b->pr=a;
}

void Disconnect(NP a,NP b){
	if(a)
		a->nx=NULL;
	if(b)
		b->pr=NULL;
}

pnn SplitL(NP ptr){
	Disconnect(ptr->pr,ptr);
	pnn ret=MP(ptr->l,ptr);
	if(ptr->l){
		ptr->l->p=NULL;
		ptr->l=NULL;
	}
	return ret;
}

pnn SplitR(NP ptr){
	Disconnect(ptr,ptr->nx);
	pnn ret=MP(ptr,ptr->r);
	if(ptr->r){
		ptr->r->p=NULL;
		ptr->r=NULL;
	}
	return ret;
}

NP MLN(NP ptr){
	if(ptr->l)
		return MLN(ptr->l);
	return ptr->Splay();
}

NP MRN(NP ptr){
	if(ptr->r)
		return MRN(ptr->r);
	return ptr->Splay();
}

NP Merge(NP a,NP b){
	if(!a)return b;
	if(!b)return a;
	a=MRN(a);
	b=MLN(b);
	Link(a,b);
	a->r=b;
	b->p=a;
	return a;
}

using NP=Node::NP;

struct Event{
	CircleUnderLine cul;
	NP ptr;
	bool operator<(const Event& rhs)const{
		return cul<rhs.cul;
	}
};

priority_queue<Event> evs;
NP root;

bool inLeft(Pos a,Pos b,Pos p){
	if(a.y==b.y)
		return p.x*2<=a.x+b.x;
	if(a.y<b.y){
		if(p.x<=a.x)
			return true;
		if(a.y==p.y)
			return p.x<a.x;
	}else{
		if(b.x<=p.x)
			return false;
		if(b.y==p.y)
			return p.x<b.x;
	}
	return (int128(p.x-a.x)*(p.x-a.x)+int128(p.y-a.y)*(p.y-a.y))*(b.y-p.y)
	<=(int128(p.x-b.x)*(p.x-b.x)+int128(p.y-b.y)*(p.y-b.y))*(a.y-p.y);
}

NP FindArc(NP ptr,Pos p){
	if(ptr->l&&inLeft(ptr->pr->pos,ptr->pos,p))
		return FindArc(ptr->l,p);
	if(ptr->r&&!inLeft(ptr->pos,ptr->nx->pos,p))
		return FindArc(ptr->r,p);
	return ptr->Splay();
}

void NewCircleEvent(Pos a,Pos b,Pos c,NP ptr){
	if(Clockwise(a,b,c)){
		evs.push(
			Event{
				ComputeCircleUnderLine(a,b,c),
				ptr
			}
		);
	}
}

void AddArc(Pos pos,int id){
	NP a=FindArc(root,pos);
	AddEdge(id,a->id);
	NP b=newNode(),c=newNode();
	b->pos=pos;
	b->id=id;
	c->pos=a->pos;
	c->id=a->id;
	pnn spl=SplitR(a);
	root=Merge(Merge(spl.first,b),Merge(c,spl.second));
	if(a->pr)
		NewCircleEvent(a->pr->pos,a->pos,b->pos,a);
	NewCircleEvent(a->pos,b->pos,c->pos,b);
	if(c->nx)
		NewCircleEvent(b->pos,c->pos,c->nx->pos,c);
}

void DelArc(NP ptr){
	if(ptr->id==-1)
		return;
	NP a=ptr->pr,b=ptr->nx;
	AddEdge(a->id,b->id);
	ptr->Splay();
	NP u=SplitL(ptr).first;
	NP v=SplitR(ptr).second;
	ptr->id=-1;
	root=Merge(u,v);
	if(a->pr)
		NewCircleEvent(a->pr->pos,a->pos,b->pos,a);
	if(b->nx)
		NewCircleEvent(a->pos,b->pos,b->nx->pos,b);
}

void TreeShow(NP ptr){
	if(ptr->l)
		TreeShow(ptr->l);
	cout<<ptr->id<<" ";
	if(ptr->r)
		TreeShow(ptr->r);
}

void BuildDelauney(int n){
	using pi=pair<Pos,int>;
	vector<pi> tops;
	REP(i,n)
		tops.PB(MP(Pos{sites[i].x,sites[i].y},i));
	sort(tops.begin(),tops.end(),
	[](const pi& lhs,const pi& rhs){
		return lhs.first.y!=rhs.first.y?lhs.first.y>rhs.first.y:lhs.first.x<rhs.first.x;
	});
	root=NULL;
	int idx=0;
	while(idx<n){
		Pos pos=tops[idx].first;
		int id=tops[idx].second;
		if(pos.y!=tops.front().first.y)
			break;
		NP ptr=newNode();
		ptr->pos=pos;
		ptr->id=id;
		ptr->l=root;
		Link(root,ptr);
		if(root){
			root->p=ptr;
			AddEdge(root->id,ptr->id);
		}
		root=ptr;
		idx++;
	}
	while(!evs.empty()||idx<n){
		if(evs.empty()){
			AddArc(tops[idx].first,tops[idx].second);
			idx++;
		}else if(idx==n){
			DelArc(evs.top().ptr);
			evs.pop();
		}else{
			Event e=evs.top();
			int x=tops[idx].first.x,y=tops[idx].first.y;
			if(e.cul<
				CircleUnderLine{
					double(y),
					Pos{x,y},
					Pos{x+1,y+1},
					Pos{x-1,y+1}
				}){
				AddArc(Pos{x,y},tops[idx++].second);
			}else{
				evs.pop();
				DelArc(e.ptr);
			}
		}
	}
}

int main(){
	int n=read();
	REP(i,n){
		sites[i].x=read();
		sites[i].y=read();
	}
	ll ans=LLONG_MAX;
	BuildDelauney(n);
	REP(i,n)
		for(auto j:graph[i])
			ans=min(ans,ll(sites[i].x-sites[j].x)*(sites[i].x-sites[j].x)+ll(sites[i].y-sites[j].y)*(sites[i].y-sites[j].y));
	cout<<ans<<endl;
}