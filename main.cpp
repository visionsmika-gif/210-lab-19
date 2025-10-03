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
#include <cctype>
#include <iomanip>

using namespace std;

struct ReviewNode {
	float rating;
	string comment;
	ReviewNode* next;
};

// Functions for linked list operations
void addNodeToFront(ReviewNode*& head, float newRating, const string& newComment);
void addNodeToTail(ReviewNode*& head, float newRating, const string& newComment);
void deleteLinkedList(ReviewNode*& head);

// Function for outputting all the reviews and their calculated average
void outputReviewsAndAvg(ReviewNode*& head);

int main() {
	ReviewNode* head = nullptr;
	int modeChoice;
	float rating;
	string comment;
	char reviewChoice;

	// Ask the user which mode they want to use to add nodes
	do {
		cout << "Which linked list method should we use?\n";
		cout << "\t[1] New nodes are added at the head of the linked list\n";
		cout << "\t[2] New nodes are added at the tail of the linked list\n";
		cout << "Choice: ";
		cin >> modeChoice;
		if (modeChoice != 1 && modeChoice != 2) {
			cout << "ERROR: Please enter 1 or 2. Try again.\n";
		}
	} while (modeChoice != 1 && modeChoice != 2);

	// Continuously add new ratings to the linked list until the user doesn't want to anymore
	do {
		// Prompt the user for a rating
		do {
			cout << "Enter review rating 0-5: ";
			cin >> rating;
			if (rating < 0 || rating > 5) {
				cout << "ERROR: Please enter a rating between 0 and 5. Try again.\n";
			}
		} while (rating < 0 || rating > 5);
		cin.ignore();

		// Prompt the user for a comment
		cout << "Enter review comments: ";
		getline(cin, comment);

		// Add a node for the review
		if (modeChoice == 1) {
			addNodeToFront(head, rating, comment);
		}
		else {
			addNodeToTail(head, rating, comment);
		}

		// Ask the user if they want to enter another review
		do {
			cout << "Enter another review? Y/N: ";
			cin >> reviewChoice;
			reviewChoice = tolower(reviewChoice);
			if (reviewChoice != 'y' && reviewChoice != 'n') {
				cout << "ERROR: Please enter Y or N. Try again.\n";
			}
		} while (reviewChoice != 'y' && reviewChoice != 'n');

	} while (reviewChoice == 'y');

	// Display the reviews and average
	outputReviewsAndAvg(head);

	// Deallocate memory
	deleteLinkedList(head);

	return 0;
}

void addNodeToFront(ReviewNode*& head, float newRating, const string& newComment) {
	// Create a new node and make it the head of the linked list
	ReviewNode* newNode = new ReviewNode;
	newNode->rating = newRating;
	newNode->comment = newComment;
	newNode->next = head;
	head = newNode;
}

void addNodeToTail(ReviewNode*& head, float newRating, const string& newComment) {
	// Create a new node
	ReviewNode* newNode = new ReviewNode;
	newNode->rating = newRating;
	newNode->comment = newComment;
	newNode->next = nullptr;

	// Set the new node as the head if the linked list is empty
	if (!head) {
		head = newNode;
		return;
	}

	// If it's not empty, traverse the linked list to the tail and add the node there
	ReviewNode* current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = newNode;
}

void deleteLinkedList(ReviewNode*& head) {
	ReviewNode* current = head;
	while (current) {
		head = current->next;
		delete current;
		current = head;
	}
	head = nullptr;
}

// outputReviewsAndAvg() takes a linked list of ReviewNodes and outputs all of its reviews and the calculated average of the reviews.
// args: head - a pointer to the linked list's head
// returns: void
void outputReviewsAndAvg(ReviewNode*& head) {
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