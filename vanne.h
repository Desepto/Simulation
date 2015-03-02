class Vanne
{
private :
	bool ouvert;
	
public :
	Vanne();
	Vanne(bool ouverture);
	Vanne(const Vanne &v);
	
	Vanne operator = (const Vanne &r);
	
	void ouvrir();
	void fermer();

	bool getOuvert();
	
    void toString();
	
	~Vanne();
	
};
