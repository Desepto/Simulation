class Pompe
{
private :
	int etat;
	// -1 panne / 0 arret / 1 marche
	
public :
	Pompe();
	Pompe(int etat);
	Pompe(const Pompe &p);
	
	Pompe operator = (const Pompe &p);
	
	void panne();
	void marche();
	void arret();
	
	int getEtat();
	void toString();
	
	
	
	~Pompe();
	
};
