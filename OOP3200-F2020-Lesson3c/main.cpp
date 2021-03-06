/*
 * Nick Sturch-Flint 100303769
 * October 25, 2020
 * main.cpp
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <Windows.h>


#include "Vector2D.h"



int main()
{
	try
	{
		/************************
		 *	DECLARATIONS
		 ************************/
		//map
		std::map<std::string, Vector2D<float>*> vectors;
		//ifstream
		std::ifstream infile;
		std::string fileName = "PointData.dat";
		std::string exit = "q";
		std::string userInput = "";


		/******************************************************************************
		 *	Reading Labels/Points into the Map:
		 *	Attempt to open the data file.  If the data file opens, read a label,
		 *	followed by a point and insert them into the map using the label as the key.
		 *	Repeat until all the data is read and close the file. If the data file did
		 *	not open, tell the user and remind them to check that the file exists. If
		 *	the file opened but the map is empty after the input loop, report that to
		 *	the user and remind them to check that the file contains valid data in
		 *	the correct format. Only continue processing if the file was opened and the
		 *	map is not empty.
		 ******************************************************************************/
		 //attempt to open the file
		infile.open(fileName.c_str());

		//after file is opened
		if (infile.is_open())
		{
			//declarations
			std::string name;
			float x, y;
			//read the data until there's no data left
			while (!infile.fail())
			{
				//retrieve the data
				infile >> name;
				infile.ignore(1, ' ');
				infile.ignore(1, '(');
				infile >> x;
				infile.ignore(1, ',');
				infile.ignore(1, ' ');
				infile >> y;
				infile.ignore(1, ')');
				//store the data in a map
				auto* tempVector = new Vector2D<float>(x, y);
				vectors[name] = tempVector;
			}
			infile.close(); //close the file when done
		}
		else
		{ //if the fail fails to open
			std::cerr << "\n---------------------------------------------------------\n" <<
				fileName << " could not be opened for input. Check that the file exists."
				<< "\n---------------------------------------------------------\n\n"
				<< std::endl;
			system("pause");
			return 0;
		}
		//if the map is empty, do not continue
		if (vectors.empty())
		{
			std::cerr << "\n--------------------------------------------------------------------------------------------\n" <<
						 "The map is empty. Check that the file contains valid data, or that the file name is correct."
			<< std::endl << "--------------------------------------------------------------------------------------------\n\n";
			system("pause");
			return 0;
		}
		else //if everything works
		{
			std::cout << "\n================================================================================================================\n";
			for (auto& vector : vectors)
			{
				std::cout << vector.first << "   " << vector.second->ToString() << std::endl;
			}
			std::cout << "\n================================================================================================================\n\n";
		}
		/******************************************************************************
		 *	Determine the Total Distance Between All Points in Order:
		 *	Use an iterator and a loop to traverse each label/point in the map. For
		 *	each label/point, determine the distance from that point to the previous
		 *	point (or next point depending on how you implement this) and add that
		 *	distance to a total.  Note that the Vector2D class includes a static
		 *	distance function to determine the distance between two Vector2D
		 *	objects, so you should not need to use any complicated math here.  Report
		 *	to the user how many points the map contains and what the total distance is.
		 ******************************************************************************/
		const auto map_iter = vectors.begin();
		Vector2D<float>* tempVector = map_iter->second; //new Vector2D<float>(0.0f, 0.0f);

		std::cout << "\n================================================================================================================\n";
		for (auto& vector : vectors)
		{
			auto distance = Vector2D<float>::Distance(*tempVector, *vector.second);

			std::cout << vector.first << " is located at " << vector.second->ToString() << " and is " << distance << " from " << tempVector->ToString() << std::endl;

			tempVector = vector.second;
		}
		std::cout << "\n================================================================================================================\n\n";
		std::cout << "\n================================================================================================================\n";
		//print the number of stored vectors
		std::cout << "\nThe total number of Vectors the map contains is " << vectors.size() << std::endl;
		std::cout << "\n================================================================================================================\n\n";
		/******************************************************************************
		 *	Determine the Distance Between the Start Point and a User Selected Point:
		 *	Prompt the user to enter a label or to enter "quit" to end.  If the user
		 *	entered anything other than "quit", attempt to find the label they entered
		 *	in the map. If it was found, report the distance between the point for the
		 *	label they entered and the start point (i.e. the point labeled "AA").
		 *	Otherwise, tell the user that the label they entered is not in the map.
		 *	Repeat these steps until the user enters "quit".
		 ******************************************************************************/
		std::cout << "\n================================================================================================================\n";
		std::cout << "\nPlease enter the label of the point you wish to go to or type 'q' to exit.\n";
		//user can input as many labels as they like until inputting q
		while (userInput != exit)
		{
			//Get the label
			std::cout << "Label: ";
			//user input
			std::cin >> userInput;

			//if the label exists
			if (vectors.find(userInput) != vectors.end())
			{
				auto distance = Vector2D<float>::Distance(*vectors[userInput], *vectors.begin()->second);

				std::cout << "Found! The Label " << userInput << " holds a value of" << *vectors[userInput] << std::endl
				<< "It is a total distance of " << distance << " from " << *vectors.begin()->second << std::endl;
			} //if the user wants to quit
			else if (userInput == "q")
			{
				std::cout << "Thank you for using our app, have a nice day!\n";
			}
			else //if the label doesn't exist
			{
				std::cout << "Label not found, try again!" << std::endl;
			}
			std::cout << "\n================================================================================================================\n";
		}
	}
	/******************************************************************************
	 *	Exception Handling:
	 *	Catch any std::exception thrown. Report to the user that a run-time error
	 *	occurred and show what exception was thrown.
	 ******************************************************************************/
	catch(std::ios_base::failure e)  // an exception was thrown
	{
		std::cerr << e.what();
	}
	catch (std::exception& ex)  // an exception was thrown
	{
		std::cerr << ex.what() << std::endl;
	}
	catch (...)  // an exception was thrown
	{
		std::cerr << "Exception Occured\n";
	}
	// END-OF-PROGRAM

	return 0;
}

