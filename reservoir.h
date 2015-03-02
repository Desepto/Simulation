class Reservoir
{
private :
	bool rempli;
	
public :
	Reservoir();
	Reservoir(bool remplissage);
	Reservoir(const Reservoir &r);
	
	Reservoir operator = (const Reservoir &r);
	
	void vidange();
	void remplir();
	bool getRempli();
	void toString();
	
	
	
	~Reservoir();
	
};

