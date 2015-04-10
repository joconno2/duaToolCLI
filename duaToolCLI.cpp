#include <iostream>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

int main(int argc, char* argv[]){
	path p(argv[1]);   // p reads clearer than argv[1] in the following code

	try{
		if (exists(p)){    // does p actually exist?
		
			if (is_regular_file(p))        // is p a regular file?   
				std::cout << p << " size is " << file_size(p) << '\n';

			else if (is_directory(p)){      // is p a directory?
				std::cout << p << " is a directory containing:\n";
				std::copy(directory_iterator(p), directory_iterator(),
					std::ostream_iterator<directory_entry>(std::cout, "\n"));	
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
	return 0;
}