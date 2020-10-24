#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>



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
		std::string fileName = "MockDataForTesting.txt";

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
			infile.close();
		}

		for (const auto& vector : vectors)
		{
			std::cout << vector.first << "   " << vector.second->ToString() << std::endl;
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



		/******************************************************************************
		 *	Determine the Distance Between the Start Point and a User Selected Point:
		 *	Prompt the user to enter a label or to enter "quit" to end.  If the user
		 *	entered anything other than "quit", attempt to find the label they entered
		 *	in the map. If it was found, report the distance between the point for the
		 *	label they entered and the start point (i.e. the point labeled "AA").
		 *	Otherwise, tell the user that the label they entered is not in the map.
		 *	Repeat these steps until the user enters "quit".
		 ******************************************************************************/

	}
	/******************************************************************************
	 *	Exception Handling:
	 *	Catch any std::exception thrown. Report to the user that a run-time error
	 *	occurred and show what exception was thrown.
	 ******************************************************************************/
	catch (std::exception& ex)  // an exception was thrown
	{
		std::cout << ex.what() << std::endl;
	}
	catch(std::string e)  // an exception was thrown
	{
		std::cout << e;
	}
	catch (...)  // an exception was thrown
	{
		std::cout << "Exception Occured\n";
	}
	// END-OF-PROGRAM

	return 0;
}

