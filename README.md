# Algorithm #1
Write a Python 3 program that does the following:
Ask the user for a range (e.g., 1 to 100) instead of hardcoding it.
* For multiples of three, print "Ross."
* For multiples of five, print "Robotics."
* For multiples of both three and five, print "Ross Robotics."
* For multiples of seven, print "Lucky."
* For multiples of both three and seven, print "Ross Lucky."
* For multiples of both five and seven, print "Robotics Lucky."
* For multiples of three, five, and seven, print "Jackpot!"
* For prime numbers, print "Prime."
* For all other numbers, print the number itself.

# Algorithm #2
In C++, implement the RANSAC algorithm to robustly estimate a line from noisy 2d points.
Tools: can use STL, boost, and C++ using a modern C++ compiler (up to C++ 11).
Input :
* A set of 2d points with unknown uncertainties, and any required algorithm parameters.
A file containing a set of test points is provided inside the supporting files folder
Outputs :
* The line parameterized as two points, and which input points are inliers.
Consider how the code might be organised to be easy to test, for others to read, and to improve
later. Emphasis will be placed on a correct and well-engineered solution.
Use of the internet is encouraged to become familiar with details of the algorithm and its variants.
The Wikipedia page should be treated with particular scepticism.
Comments can be useful to explain design/implementation choices; there will also be an opportunity
to explain these verbally.
Any reasonable extensions to the basic RANSAC algorithm would be welcome but please note in
comments where these are made, and provide any relevant citations.
We have provided a simple command-line harness (inside the supporting files folder), including codeto read and write the output.

Please feel free to remove the boost command line parser if you do not have access to boost.

sample_points.csv is provided as input test data file, and display_points.py is provided to visualise

the results output by the test program inside the folder
software_engineering_test_algorithm_2_supporting_file.

# Algorithm #3
Design a C++ class that simulates a deck of playing cards. Your class should not only shuffle and deal
cards but also have some extra bells and whistles.
Core Features:
* Shuffle 'Em Up: Implement a method to shuffle the deck.
* Single Draw: Create a function to deal a single card from the deck.
* Multi-Draw: Why stop at one? Add a function to deal multiple cards at once.
* Card Count: Include a method to check how many cards are left in the deck.

Bonus Features:
* Joker's Wild: Add a method to insert a Joker into the deck.
* Prime Time: (Optional) Add a special function that identifies if a card is a prime number (only
for numbered cards, of course).
Demonstrate the awesomeness of your card deck class by writing a small program that deals out the
entire deck, one card at a time.
Don't forget to write a unit test to make sure your deck is up to snuff. Validate all the core and bonus
features you've implemented.
