// COMSC-210 | Lab 19 | Mika Aquino
// IDE used: Visual Studio 2022

/* INSTRUCTIONS:
Lab 18 currently is structured to store and manipulate movie reviews for a single movie title. Abstract this structure by one layer. Automate it such that review comments are read from an external file, and the movie rating is a random double (one decimal place) between 1.0 and 5.0.

Create a Movie class with these private member variables: movie title, a linked list of structs containing the rating and a review comment.

Your main() function needs to feature a container of Movie objects. It'll be your choice of data structures to use for this container: array, vector, linked list.

Your code doesn't need to ask the user to select adding nodes to the head/tail; you can just add nodes to the head to make it easiest.

Exercise your class by writing a driver/demo program that will have at least four Movie objects, each with at least three reviews. */

#include <iostream>
#include <string>
#include <iomanip>	// For displaying doubles
#include <vector>	// For Movie container
#include <cstdlib>	// For random numbers
#include <ctime>	// For seed
#include <fstream>	// For reading files

using namespace std;

struct ReviewNode {
	double rating;
	string comment;
	ReviewNode* next;
};

class Movie {
public:
	// Constructor
	Movie(const string& movieTitle) : title(movieTitle), head(nullptr) {}

	// Destructor
	~Movie() {}

	// Function to add a review
	void addNodeToFront(double newRating, const string& newComment);

	// Function to output a movie's reviews
	void outputReviewsAndAvg() const;

private:
	string title;
	ReviewNode* head;	// Linked list of reviews
};

int main() {
	vector<Movie> movies;						// Vector to hold Movie objects
	srand(static_cast<unsigned int>(time(0)));	// Initialize seed
	const int NUM_REVIEWS = 3;					// Each movie has 3 reviews.
	
	// Create four movie objects and push them to the vector.
	movies.push_back(Movie("The Nightmare Before Christmas"));
	movies.push_back(Movie("Tangled"));
	movies.push_back(Movie("Frozen II"));
	movies.push_back(Movie("Ratatouille"));

	return 0;
}

Movie::~Movie() {
	ReviewNode* current = head;
	while (current) {
		head = current->next;
		delete current;
		current = head;
	}
	head = nullptr;
}

void Movie::addNodeToFront(double newRating, const string& newComment) {
	// Create a new node and make it the head of the linked list
	ReviewNode* newNode = new ReviewNode;
	newNode->rating = newRating;
	newNode->comment = newComment;
	newNode->next = head;
	head = newNode;
}

void Movie::outputReviewsAndAvg() const {
	ReviewNode* current = head;
	double totalRating = 0.0;
	int numReviews = 0;
	double avgRating;
	const int RATING_PRECISION = 1;		// Used for setprecision()
	const int AVG_PRECISION = 5;		// Used for setprecision()

	if (!head) {
		cout << "The list of reviews is empty.\n";
		return;
	}

	cout << "MOVIE: " << title << "\n";
	cout << "Outputting all reviews:\n";

	// Traverse the linked list
	while (current) {
		// Output review
		++numReviews;
		cout << fixed << setprecision(RATING_PRECISION);
		cout << "\t> Review #" << numReviews << ": " << current->rating << ": " << current->comment << "\n";
	
		// Accumulate ratings
		totalRating += current->rating;

		current = current->next;
	}

	// Calculate and output the ratings' average
	avgRating = totalRating / numReviews;
	cout << fixed << setprecision(AVG_PRECISION);
	cout << "\t> Average: " << avgRating << "\n";
}