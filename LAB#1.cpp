#include <iostream>
#include <vector>

using namespace std;

class Artwork {
  string name;
  unsigned int year;
  string title;
  
  public: 
  	//CONSTRUCTORS
  	Artwork() : name(""), year(0), title("") {	//empty/default constructor
	}
  	Artwork	(string new_name, unsigned int new_year, string new_title) : name(new_name), year(new_year), title(new_title) {	//parametric constructor
	}
	
	//SERVICE FUNCTIONS
	bool operator ==(const Artwork& new_art) {
		bool are_equal = true;
		are_equal = are_equal && (name == new_art.name);
		are_equal = are_equal && (year == new_art.year);
		are_equal = are_equal && (title == new_art.title);
		return are_equal;
	}
};

class SoldArtwork: public Artwork {
	string cust_name;
	string cust_addr;
	double sale_amt;
	
	//CONSTRUCTORS
	SoldArtwork () : cust_name(""), cust_addr(""), sale_amt(0.0) {	//empty/default constructor
	}
	SoldArtwork (string new_cust_name, string new_cust_addr, double new_sale_amt, Artwork new_art_info)  : cust_name(new_cust_name), 
		cust_addr(new_cust_addr), sale_amt(new_sale_amt), Artwork(new_art_info) {	//parametric constructor
	}
	
	//SERVICE FUNCTIONS
	bool operator ==(const SoldArtwork& new_art){
		bool are_equal = true;
		are_equal = are_equal && (cust_name == new_art.cust_name);
		are_equal = are_equal && (cust_addr == new_art.cust_addr);
		are_equal = are_equal && (sale_amt == new_art.sale_amt);
		return are_equal;
	}
};

class ArtCollection {
	vector<Artwork> my_artwork;
	vector<SoldArtwork> my_sold_artwork;
	
	public:
		//METHODS
		bool insert_artwork(const Artwork&artwork_info) {
			bool is_unique = true;
			for (int index = 0; index < my_artwork.size() && is_unique; ++index) {
				if (my_artwork[index] == artwork_info) {
					is_unique = false;
				}
			}
			if (is_unique) {
				my_artwork.push_back(artwork_info);
			}
			return is_unique;
		}
		
		bool sell_artwork(const SoldArtwork&artwork_info) {
			bool exists = false;
			static_cast<Artwork>(artwork_info);
			for (int index = 0; index < my_artwork.size(); ++index) {
				if (my_artwork[index] == artwork_info){
					my_artwork.erase(my_artwork.begin() + index);
					exists = true;
				}
			}
			my_sold_artwork.push_back(artwork_info);
			return exists;
		}
		
		/*bool operator==(const ArtCollection& new_art) {
			bool are_equal = true;
			are_equal = are_equal && (my_artwork == new_art.my_artwork);
			are_equal = are_equal && (my_sold_artwork == new_art.my_sold_artwork);
			return are_equal;
		}
		bool operator+(const ArtCollection& ) {
			
		}*/
};


