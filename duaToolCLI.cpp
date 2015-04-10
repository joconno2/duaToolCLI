#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

void list(path,std::ofstream&,int);


int main(int argc, char* argv[]){
	path p(argv[1]);   // p reads clearer than argv[1] in the following code
	const char* filename = "log.txt";
	int indentCount = 0;

	std::ofstream logFile;
	logFile.open(filename);

	list(p,logFile, indentCount);

	logFile.close();
}


void list(path p, std::ofstream& logFile, int indentCount){
	try{
		if (exists(p)){    // does p actually exist?

			if (is_regular_file(p))        // is p a regular file?   
				logFile << p << " size is " << file_size(p) << '\n';

			else if (is_directory(p))      // is p a directory?
			{
				for (int i = 0; i < indentCount; i++)
					logFile << '\t';

				logFile << "<Dir name= " << p << ">\n";

				indentCount++;

				typedef std::vector<path> vec;             // store paths,
				vec v;                                // so we can sort them later

				copy(directory_iterator(p), directory_iterator(), back_inserter(v));
				sort(v.begin(), v.end());

				for (vec::const_iterator it(v.begin()); it != v.end(); ++it)
					if (is_directory(*it))	// Only print size if not a directory, else recurse
						list(*it,logFile,indentCount);
					else{
						for (int i = 0; i < indentCount; i++)
							logFile << '\t';
						logFile << "<File>\n";
						for (int i = 0; i < indentCount; i++)
							logFile << '\t'; 
						logFile << "\t<Path>" << *it << "<\Path>\n";
						for (int i = 0; i < indentCount; i++)
							logFile << '\t'; 
						logFile << "\t<Size>" << file_size(*it) << "<\Size>\n";
					}
			}
			else
				std::cout << p << " exists, but is neither a regular file nor a directory\n";
		}
		else
			std::cout << p << " does not exist\n";
	}

	catch (const filesystem_error& ex){
		std::cout << ex.what() << '\n';
	}
}