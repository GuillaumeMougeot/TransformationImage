#ifndef MATRICE_HPP
#define MATRICE_HPP

#include <vector>
#include <iostream>
#include <fstream>

/* DECLARATION */
template <class T>
class Matrice
{
public:
	// Constructeurs et destructeurs
	Matrice(int ligne, int colonne);
	Matrice(T nombre, int ligne, int colonne);
	Matrice(std::vector<std::vector<T> > const& matrice);
	Matrice(Matrice<T> const& matrice);
	~Matrice();
	
	// Accesseurs
	int getLigne() const {return m_ligne;}
	int getColonne() const {return m_colonne;}
	std::vector<T>& operator[](std::size_t indice) {return m_matrice[indice];}
	
	// Surcharge d'operateurs
	Matrice<T>& operator=(Matrice<T> const& matrice);
	Matrice<T>& operator*=(Matrice<T> const& matrice);
	Matrice<T>& operator+=(Matrice<T> const& matrice);
	
	// Surcharge de l'operateur particulier <<
	// Cf site : http://web.mst.edu/~nmjxv3/articles/templates.html
	template <class U>
	friend std::ostream& operator<<(std::ostream& flux, Matrice<U> const& matrice);
	
	// Utile
	// Transforme la matrice en matrice identité si celle-ci est carrée
	void identite();
	// Renvoie une matrice identité
	static Matrice<T> identite(int taille);
	
private:
	int m_ligne;
	int m_colonne;
	std::vector<std::vector <T> > m_matrice;
	
	// Affichage
	void afficher(std::ostream& out) const;
};

template <class T>
Matrice<T> operator*(Matrice<T> const& A, Matrice<T> const& B);

template <class T>
Matrice<T> operator+(Matrice<T> const& A, Matrice<T> const& B);

/* IMPLEMENTATION */
template <class T>
Matrice<T>::Matrice(int ligne, int colonne)
{
	m_ligne = ligne;
	m_colonne = colonne;
	// On initialise la matrice de base à l'identité
	for(int i = 0; i < m_ligne; i++)
	{
		m_matrice.push_back(std::vector<T>());
		for(int j = 0; j < m_colonne; j++)
		{
			if (i==j)
			{
				m_matrice.back().push_back(1);
			}
			else
			{
				m_matrice.back().push_back(0);
			}
		}
	}
}

template <class T>
Matrice<T>::Matrice(T nombre, int ligne, int colonne)
{
	m_ligne = ligne;
	m_colonne = colonne;
	for(int i = 0; i < m_ligne; i++)
	{
		m_matrice.push_back(std::vector<T>());
		for(int j = 0; j < m_colonne; j++)
		{
			m_matrice.back().push_back(nombre);
		}
	}
}

template <class T>
Matrice<T>::Matrice(std::vector< std::vector<T> > const& matrice)
{
	std::vector<T> vect_crt;
	m_ligne = matrice.size();
	if (matrice.empty())
	{
		std::cout << "[Erreur] La matrice donnee en entree est vide. Initialisation echouee." << std::endl;
	}
	else
	{
		m_colonne = matrice[0].size();
		
		for(int i = 0; i < matrice.size(); i++)
		{
			vect_crt.clear();
			if (matrice[i].size() != m_colonne)
			{
				std::cout << "[Erreur] La matrice donnee en entree n'est pas de ligne conforme. Initialisation echouee." << std::endl;
				break;
			}
			else
			{
				for(int j = 0; j < m_colonne; j++)
				{
					vect_crt.push_back(matrice[i][j]);
				}
				m_matrice.push_back(vect_crt);
			}
		}
	}
}

template <class T>
Matrice<T>::Matrice(Matrice<T> const& matrice)
{
	m_ligne = matrice.m_ligne;
	m_colonne = matrice.m_colonne;
	m_matrice = matrice.m_matrice;
}

template <class T>
Matrice<T>::~Matrice()
{
	for(int i = 0; i < m_matrice.size(); i++)
	{
		m_matrice[i].clear();
	}
}

template <class T>
Matrice<T>& Matrice<T>::operator=(Matrice<T> const& matrice)
{
	m_ligne = matrice.m_ligne;
	m_colonne = matrice.m_colonne;
	m_matrice = matrice.m_matrice;
	return *this;
}

template <class T>
Matrice<T>& Matrice<T>::operator*=(Matrice<T> const& matrice)
{
	if (m_colonne != matrice.m_ligne)
	{
		std::cout << "[Erreur] Les dimensions des matrices ne correspondent pas. Multipliation echouee." << std::endl;
	}
	else
	{
		Matrice<T> resultat(m_ligne, matrice.m_colonne);
		T element_crt;
		
		for(int i = 0; i < m_ligne; i++)
		{
			for(int j = 0; j < matrice.m_colonne; j++)
			{
				element_crt = 0;
				for(int k = 0; k < m_colonne; k++)
				{
					element_crt += m_matrice[i][k] * matrice.m_matrice[k][j];
				}
				resultat.m_matrice[i][j] = element_crt;
			}
		}
		*this = resultat;
	}
	
	return *this;
}

template <class T>
Matrice<T> operator*(Matrice<T> const& A, Matrice<T> const& B)
{
	Matrice<T> resultat(A.getLigne(), A.getColonne());
	resultat = A;
	resultat *= B;
	return resultat;
}

template <class T>
Matrice<T>& Matrice<T>::operator+=(Matrice<T> const& matrice)
{
	if (m_colonne != matrice.m_colonne && m_ligne != matrice.m_ligne)
	{
		std::cout << "[Erreur] Les dimensions des matrices ne correspondent pas. Multipliation echouee." << std::endl;
	}
	else
	{
		Matrice<T> resultat(m_ligne, m_colonne);
		
		for(int i = 0; i < m_ligne; i++)
		{
			for(int j = 0; j < matrice.m_colonne; j++)
			{
				resultat.m_matrice[i][j] = m_matrice[i][j] + matrice.m_matrice[i][j];
			}
		}
		*this = resultat;
	}
	return *this;
}

template <class T>
Matrice<T> operator+(Matrice<T> const& A, Matrice<T> const& B)
{
	Matrice<T> resultat(A);
	resultat += B;
	return resultat;
}


template <class T>
void Matrice<T>::afficher(std::ostream& out) const
{
	out << '[';
	for(int i = 0; i < m_ligne; i++)
	{
		out << '[' << '\t';
		for(int j = 0; j < m_colonne; j++)
		{
			out << m_matrice[i][j] << '\t';
		}
		if (i != m_ligne-1)
		{
			out << ']' << std::endl;
		}
		else
		{
		out << "]]" << std::endl;
		}
	}
}

template <class T>
std::ostream& operator<<(std::ostream& flux, Matrice<T> const& matrice)
{
	matrice.afficher(flux);
	return flux;
}

template <class T>
void Matrice<T>::identite()
{
	if(m_ligne != m_colonne)
	{
		std::cout << "[Erreur] La matrice n'est pas carree. Abandon." << std::endl;
	}
	else
	{
		for(int i = 0; i < m_ligne; i++)
		{
			for(int j = 0; j < m_colonne; j++)
			{
				if (i==j)
				{
					m_matrice[i][j] = 1;
				}
				else
				{
					m_matrice[i][j] = 0;
				}
			}
		}
	}
}

template <class T>
Matrice<T> Matrice<T>::identite(int taille)
{
	Matrice<T> resultat(taille, taille);
	resultat.identite();
	return resultat;
}


#endif






