#include <iostream>
#include <vector>

using namespace std;

//STEP 1
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

//STEP 2
class SoldArtwork: public Artwork {
	string cust_name;
	string cust_addr;
	double sale_amt;
	
//CONSTRUCTORS
public:
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

//STEP 3
class ArtCollection {
	vector<Artwork> my_artwork;
	vector<SoldArtwork> my_sold_artwork;
	
public:		
	//SERVICE FUNCTIONS
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
		if (exists) {
			my_sold_artwork.push_back(artwork_info);
		}
		return exists;
	}
	
	bool operator==(const ArtCollection& new_art) {
		bool are_equal = true;
		if (new_art.my_artwork.size() == my_artwork.size()) {
			for (int i = 0; i < my_artwork.size(); i++) {
				if (my_artwork[i] == new_art.my_artwork[i] && are_equal) {
					are_equal = true;
				} else {
					are_equal = false;
				}
			} 
		} else {
			are_equal = false;
		}
		
		if (new_art.my_sold_artwork.size() == my_sold_artwork.size()) {
			for (int i = 0; i < my_sold_artwork.size(); i++) {
				if (my_sold_artwork[i] == new_art.my_sold_artwork[i] && are_equal) {
					are_equal = true;
				} else {
					are_equal = false;
				}
			}
		} else{
			are_equal = false;
		}
		return are_equal;
	}
		
	friend ArtCollection operator+(const ArtCollection& collection1, const ArtCollection& collection2);
	
	//GETTERS
	int getArtSize() {
		return my_artwork.size();
	}
	int getSoldSize() {
		return my_sold_artwork.size();
	}
};

ArtCollection operator+(const ArtCollection& collection1, const ArtCollection& collection2) {
			ArtCollection new_art;
			new_art.my_artwork = collection1.my_artwork;
			new_art.my_sold_artwork = collection1.my_sold_artwork;
		
			for (int i = 0; i < collection2.my_artwork.size(); i++) {
				new_art.my_artwork.push_back(collection2.my_artwork[i]);
			}
			for (int i = 0; i < collection2.my_sold_artwork.size(); i++) {
				new_art.my_sold_artwork.push_back(collection2.my_sold_artwork[i]);
			}
			return new_art;
		}
		
		
//TEST FUNCTIONS (STEP 5)

//PURPOSE:
	//Do the Artwork class constructors work
	//Can insert_artwork() add items to the art collection
	//Will insert_artwork() prevent the addition of duplicates
	//Does the Artwork "==" operator work
void test_insert_artwork(ArtCollection my_ac) { 
	bool success = false;

	Artwork artworkTest0 = Artwork();
	Artwork artworkTest1 = Artwork("Name One", 1999, "Title One");
	Artwork artworkTest2 = Artwork("Name Two", 2000, "Title Two");
	Artwork artworkTest3 = Artwork("Name Two", 2000, "Title Two");
	
	int artwork_size = my_ac.getArtSize();
	cout << "initial artwork size: " << artwork_size << endl;
	
	my_ac.insert_artwork(artworkTest0);
	artwork_size = my_ac.getArtSize();
	if (artwork_size == 1) {
		cout << "Test successful after adding 1 item" << endl;
	}

	my_ac.insert_artwork(artworkTest1);
	artwork_size = my_ac.getArtSize();
	if (artwork_size == 2) {
		cout << "Test successful after adding 2 items" << endl;
	}

	my_ac.insert_artwork(artworkTest2);
	artwork_size = my_ac.getArtSize();
	if (artwork_size == 3) {
		cout << "Test successful after adding 3 items" << endl;
	}

	my_ac.insert_artwork(artworkTest3);
	artwork_size = my_ac.getArtSize();
	if (artwork_size == 3) {
		success = true;
		cout << "Test successful after adding duplicate item" << endl;
	}
	
	if (artworkTest1 == artworkTest2) {
		success = false;
	}
	
	if (artworkTest2 == artworkTest3) {
		success = true;
	} else {
		success = false;
	}
	
	if (success) {
		cout << "TEST PHASE 1 SUCCESS" << endl << endl;
	}
}

//PURPOSE:
	//Do the SoldArtwork class constructors work
	//Does sell_artwork():
		//a) remove instance from Artwork vector
		//b) add same instance to SoldArtwork vector 
		//c) have no effect if it does not exist in Artwork vector
	//Does the SoldArtwork "==" operator work
void test_sell_artwork(ArtCollection my_ac) {
	bool success = false;
	
	Artwork artworkTest0 = Artwork();
	Artwork artworkTest1 = Artwork("Name One", 1999, "Title One");
	Artwork artworkTest2 = Artwork("Name Two", 2000, "Title Two");
	Artwork artworkTest3 = Artwork("Name Two", 2000, "Title Two");

	SoldArtwork soldArtworkTest0 = SoldArtwork();
	SoldArtwork soldArtworkTest1 = SoldArtwork("Nicholas", "258C Sunview", 12345.69, artworkTest1);
	SoldArtwork soldArtworkTest2 = SoldArtwork("Maura", "3355 White Rd", 6789.08, artworkTest2);
	SoldArtwork soldArtworkTest3 = SoldArtwork("Maura", "3355 White Rd", 6789.08, artworkTest2);
	
	my_ac.insert_artwork(artworkTest0);
	my_ac.insert_artwork(artworkTest1);
	my_ac.insert_artwork(artworkTest2);

	int artwork_size = my_ac.getArtSize();
	cout << "initial artwork size: " << artwork_size << endl;
	int sold_size = my_ac.getSoldSize();
	cout << "initial sold size: " << sold_size << endl;
	
	my_ac.sell_artwork(soldArtworkTest0);
	artwork_size = my_ac.getArtSize();
	sold_size = my_ac.getSoldSize();
	if (artwork_size == 2 && sold_size == 1) {
		cout << "Test successful after selling 1 item" << endl;
	}

	my_ac.sell_artwork(soldArtworkTest1);
	artwork_size = my_ac.getArtSize();
	sold_size = my_ac.getSoldSize();
	if (artwork_size == 1 && sold_size == 2) {
		cout << "Test successful after selling 2 items" << endl;
	}
	
	my_ac.sell_artwork(soldArtworkTest2);
	artwork_size = my_ac.getArtSize();
	sold_size = my_ac.getSoldSize();
	if (artwork_size == 0 && sold_size == 3) {
		cout << "Test successful after selling 3 items" << endl;
		success = true;
	}
	
	my_ac.sell_artwork(soldArtworkTest3);
	artwork_size = my_ac.getArtSize();
	sold_size = my_ac.getSoldSize();
	if (artwork_size == 0 && sold_size == 3) {
		cout << "Test successful after trying to sell duplicate" << endl;
	}
	
	if (soldArtworkTest1 == soldArtworkTest2) {
		success = false;
	}
	if (soldArtworkTest2 == soldArtworkTest3) {
		success = true;
	} else {
		success = false;
	}
	
	if (success) {
		cout << "TEST PHASE 2 SUCCESS" << endl << endl;
	}
}

//PURPOSE:
	//Does the ArtCollection "==" operator work
	//Does the ArtCollection "+" operator work
void test_art_collection(ArtCollection myColl_1, ArtCollection myColl_2, ArtCollection myColl_3) {
	bool success = false;
	
	Artwork artworkTest0 = Artwork();
	Artwork artworkTest1 = Artwork("Name One", 1999, "Title One");
	Artwork artworkTest2 = Artwork("Name Two", 2000, "Title Two");
	Artwork artworkTest3 = Artwork("Name Two", 2000, "Title Two");

	SoldArtwork soldArtworkTest0 = SoldArtwork();
	SoldArtwork soldArtworkTest1 = SoldArtwork("Nicholas", "258C Sunview", 12345.69, artworkTest1);
	SoldArtwork soldArtworkTest2 = SoldArtwork("Maura", "3355 White Rd", 6789.08, artworkTest2);
	SoldArtwork soldArtworkTest3 = SoldArtwork("Maura", "3355 White Rd", 6789.08, artworkTest2);
	
	myColl_1.insert_artwork(artworkTest0);
	myColl_1.insert_artwork(artworkTest1);
	myColl_1.insert_artwork(artworkTest2);
	myColl_1.sell_artwork(soldArtworkTest0);
	myColl_1.sell_artwork(soldArtworkTest1);
	int coll_1_art = myColl_1.getArtSize();
	int coll_1_sold = myColl_1.getSoldSize();
	cout << "collection 1 myartwork size: " << coll_1_art << endl;
	cout << "collection 1 mySoldartwork size: " << coll_1_sold << endl;
	
	myColl_2.insert_artwork(artworkTest0);
	myColl_2.insert_artwork(artworkTest1);
	myColl_2.insert_artwork(artworkTest2);
	myColl_2.sell_artwork(soldArtworkTest0);
	int coll_2_art = myColl_2.getArtSize();
	int coll_2_sold = myColl_2.getSoldSize();
	cout << "collection 2 myartwork size: " << coll_2_art << endl;
	cout << "collection 2 mySoldartwork size: " << coll_2_sold << endl;
			
	myColl_3.insert_artwork(artworkTest0);
	myColl_3.insert_artwork(artworkTest1);
	myColl_3.insert_artwork(artworkTest2);
	myColl_3.sell_artwork(soldArtworkTest0);
	int coll_3_art = myColl_3.getArtSize();
	int coll_3_sold = myColl_3.getSoldSize();
	cout << "collection 3 myartwork size: " << coll_3_art << endl;
	cout << "collection 3 mySoldartwork size: " << coll_3_sold << endl;
		
	//TESTS
	if (myColl_2 == myColl_3) {
		success = true;
		cout << "ArtCollection '==' operator works" << endl;
	}
	
	myColl_1 = myColl_1 + myColl_2;
	int coll_1_art_test = myColl_1.getArtSize();
	int coll_1_sold_test = myColl_1.getSoldSize();
	if (coll_1_art_test == 3 && coll_1_sold_test == 3) {
		success = true;
		cout << "ArtCollection '+' operator works" << endl;	
	}
	
	if (success) {
		cout << "TEST PHASE 3 SUCCESS" << endl;
	}
}

int main() {
	//TEST: Can ArtCollection instances be created
	ArtCollection myArtCollection1;
	ArtCollection myArtCollection2;
	ArtCollection myArtCollection3;
	ArtCollection myArtCollection4;
	
	//Running test functions
	test_insert_artwork(myArtCollection1);
	test_sell_artwork(myArtCollection1);
	test_art_collection(myArtCollection2, myArtCollection3, myArtCollection4);
}

