#ifndef PORTAL_HEADER
#define PORTAL_HEADER

class Portal{

public:
	int id_destino;
	Portal* prox;
	bool verificaDuplicada(Portal* nova);
	void adPortal(Portal* prox);
	Portal(int id);
	~Portal();

};

#endif