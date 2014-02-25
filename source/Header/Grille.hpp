#include "Case.hpp"
#include <vector>

class Grille{
	private:
		std::vector<std::vector<Case>> tabGrille;
	public:
		Grille();
		void afficherGrille();
		~Grille();
};
