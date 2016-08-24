#include <bits/stdc++.h>

using namespace std;

namespace GenJS{
	struct Color{
		int r,g,b;
	};

	const Color Black=Color{0,0,0};
	const Color Red=Color{255,0,0};
	const Color Green=Color{0,255,0};
	const Color Blue=Color{0,0,255};
	const Color Yellow=Color{255,255,0};
	
	#define STRINGFY(...) #__VA_ARGS__

	string firstHalf=
	#include "firstHalf.txt"
	;
	//Arguments
	const string width_undefined="width_undefined";
	const string height_undefined="height_undefined";
	const string font_size_undefined="font_size_undefined";
	
	string secondHalf=
	#include "secondHalf.txt"
	;
	
	void Find_Replace(string& dst,const string& from,const string& to){
		auto f=dst.find(from);
		if(f==string::npos){
			cerr<<from<<" was now found in "<<dst<<endl;
		}else
			dst.replace(f,from.length(),to);
	}
	
	double TransX(double x,double width){
		return width/2+x;
	}

	double TransY(double y,double height){
		return height/2-y;
	}
	
	string d_str(const double d){
		ostringstream ss;
		ss<<setprecision(0)<<fixed<<d;
		return ss.str();
	}
	
	class Vis{
		double width,height,magnif;
		ofstream dst;
		
		public:
		Vis(string filename,double w,double h,double mg=1,double fontSize=15){
			width=w*mg;
			height=h*mg;
			magnif=mg;
			
			Find_Replace(firstHalf,width_undefined,d_str(width));
			Find_Replace(firstHalf,height_undefined,d_str(height));
			Find_Replace(firstHalf,font_size_undefined,d_str(fontSize));
			
			dst.open(filename);
			dst<<firstHalf<<endl;
			
			DrawLine(-w/2,0,w/2,0,3,Color{0,0,0});
			DrawLine(0,-h/2,0,h/2,3,Color{0,0,0});
		}
		~Vis(){
			dst<<secondHalf<<endl;
		}
		
		void DrawLine(double fx,double fy,double tx,double ty,double w=3,Color col=Color{0,0,0}){
			fx*=magnif;
			fy*=magnif;
			tx*=magnif;
			ty*=magnif;
			fx=TransX(fx,width);
			fy=TransY(fy,height);
			tx=TransX(tx,width);
			ty=TransY(ty,height);
			dst<<"DrawLine("<<fx<<","<<fy<<","<<tx<<","<<ty<<","<<w
			<<",\"rgb("<<col.r<<","<<col.g<<","<<col.b<<")\");"<<endl;
		}
		void DrawCircle(double x,double y,double r,Color col=Color{0,0,0}){
			x*=magnif;
			y*=magnif;
			r*=magnif;
			x=TransX(x,width);
			y=TransY(y,height);
			dst<<"DrawCircle("<<x<<","<<y<<","<<r
			<<",\"rgb("<<col.r<<","<<col.g<<","<<col.b<<")\");"<<endl;
		}
		void DrawCircleLine(double x,double y,double r,double w=3,Color col=Color{0,0,0}){
			x*=magnif;
			y*=magnif;
			r*=magnif;
			x=TransX(x,width);
			y=TransY(y,height);
			dst<<"DrawCircleLine("<<x<<","<<y<<","<<r<<","<<w
			<<",\"rgb("<<col.r<<","<<col.g<<","<<col.b<<")\");"<<endl;
		}
		void DrawText(double val,double x,double y,Color col=Color{0,0,0}){
			DrawText(d_str(val),x,y,col);
		}
		void DrawText(string txt,double x,double y,Color col=Color{0,0,0}){
			x*=magnif;
			y*=magnif;
			x=TransX(x,width);
			y=TransY(y,height);
			dst<<"DrawText(\""<<txt<<"\","<<x<<","<<y
			<<",\"rgb("<<col.r<<","<<col.g<<","<<col.b<<")\");"<<endl;
		}
	};
}
