#pragma once
#include "singletonBase.h"

class dataManager:public singletonBase<dataManager>
{
private:
	
	int p;
	int n;
	
	
	float px;
	float py;
	float cx;
	float cy;
	float nx;
	float ny;
	float cox;
	float coy;
	
	
	RECT prc;



	bool d;
	bool bd;
	bool bod;
	bool nd;
	bool cd;

public:
	
	void setPX(float X) {px= X; }
	void setPY(float Y) { py = Y; }
	void setPRC(RECT PRC) { prc = PRC; }
	void setN(int N) { n = N; }
	void setP(int P) { p = P; }
	void setD(bool D) { d = D; }
	void setCX(float CX) { cx = CX; }
	void setCY(float CY) { cy = CY; }
	void setNX(float NX){nx=NX;}
	void setNY(float NY){ny=NY;}
	void setND(bool ND) { nd = ND; }
	void setCOX(float COX){cox=COX;}
	void setCOY(float COY){coy=COY;}
	void setCD(bool CD) { cd = CD; }
	void setBD(bool BD) { bd = BD; }
	void setBOD(bool BOD) { bod = BOD; }
	
	

	dataManager();
	~dataManager();
	HRESULT init();
	void release();

	float getPX() { return px; }
	float getPY() { return py; }
	float getCX(){return cx;}
	float getCY(){return cy;}
	float getNX(){return nx;}
	float getNY(){return ny;}
	bool getND() { return nd; }
	RECT getPRC() { return prc; }
	int getN() { return n; }
	int getP() { return p; }
	bool getD() { return d; }
	bool getBD() { return bd; }
	bool getBOD() { return bod; }
	float getCOX(){return cox;}
	float getCOY(){return coy;}
	float getCD(){return cd;}
};

