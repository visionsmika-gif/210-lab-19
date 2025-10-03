// COMSC-210 | Lab 19 | Mika Aquino
// IDE used: Visual Studio 2022

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
	~Movie();

	// Function to add a review
	void addNodeToFront(double newRating, const string& newComment);

	// Function to output a movie's reviews
	void outputReviewsAndAvg() const;

private:
	string title;
	ReviewNode* head; // Linked list of reviews
};

int main() {
	vector<Movie> movies;						// Vector to hold Movie objects
	srand(static_cast<unsigned int>(time(0)));	// Initialize seed
	const int NUM_REVIEWS = 3;					// Each movie has 3 reviews.
	const string FILE_NAME = "comments.txt";	// File to read comments from
	
	// Create four movie objects and push them to the vector.
	movies.push_back(Movie("The Nightmare Before Christmas"));
	movies.push_back(Movie("Tangled"));
	movies.push_back(Movie("Frozen II"));
	movies.push_back(Movie("Ratatouille"));

	// Check that the comments file is open.
	ifstream commentsFile(FILE_NAME);
	if (!commentsFile) {
		cout << "ERROR: Unable to open " << FILE_NAME << ".\n";
		return 1;
	}

	// The loop goes through each movie in the vector and populates it with reviews.
	for (int i = 0; i < movies.size(); ++i) {
		for (int j = 0; j < NUM_REVIEWS; ++j) {
			string comment;
			getline(commentsFile, comment);									// Read a comment from the file.
			double rating = (static_cast<double>(rand()) / RAND_MAX) * 5.0;	// Generate a random rating from 0-5.
			(movies.at(i)).addNodeToFront(rating, comment);					// Add the review to the linked list.
		}
	}

	commentsFile.close();

	// The loop outputs each movie in the vector and its corresponding reviews.
	for (int i = 0; i < movies.size(); ++i) {
		(movies.at(i)).outputReviewsAndAvg();
	}

	return 0;
}

// Movie destructor to clean up linked list
Movie::~Movie() {
	ReviewNode* current = head;
	while (current) {
		head = current->next;
		delete current;
		current = head;
	}
	head = nullptr;
}

// Movie member function to add a review
void Movie::addNodeToFront(double newRating, const string& newComment) {
	// Create a new node and make it the head of the linked list
	ReviewNode* newNode = new ReviewNode;
	newNode->rating = newRating;
	newNode->comment = newComment;
	newNode->next = head;
	head = newNode;
}

// Movie member function to output reviews
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