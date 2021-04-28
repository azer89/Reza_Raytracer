
#include <iostream>
#include <fstream> // ofstream

#include "Vec3.h"

int main()
{
	using namespace std;

	const int img_width = 256;
	const int img_height = 256;

	// Render
	ofstream my_file;
	my_file.open("image.ppm");

	my_file << "P3\n" << img_width << ' ' << img_height << "\n255\n";

	for(int y = img_height - 1; y >= 0; y--)
	{
		for (int x = 0; x < img_width; x++)
		{
			auto r = double(x) / (img_width - 1);
			auto g = double(y) / (img_height - 1);
			auto b = 0.25;

			int ir = static_cast<int>(255.0 * r);
			int ig = static_cast<int>(255.0 * g);
			int ib = static_cast<int>(255.0 * b);

			my_file << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	
	my_file.close();
	
	//cout << "Hello World\n";

	/*ofstream myfile;
	myfile.open("example.txt");
	myfile << "Writing this to a file.\n";
	myfile << "Writing this to a file.\n";
	myfile << "Writing this to a file.\n";
	myfile << "Writing this to a file.\n";
	myfile.close();*/

	return 0;
	
	return 0;
}