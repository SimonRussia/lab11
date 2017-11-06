#include <print.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

using namespace boost::filesystem;
using namespace boost::program_options;

int main(int argc, char** argv) {
try {
	std::string text;

    options_description desc{"Options"};
    desc.add_options()
      ("help,h", "Help screen")
      ("output", value<std::string>()/*->notifier(out_func)*/, "Output");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);

    if(exists("/Users/anisim_ovcharov/.config/demo.cfg"))
    	store(parse_config_file<char>( "/Users/anisim_ovcharov/.config/demo.cfg", desc ), vm);

    notify(vm);

    if (vm.count("help")) {
      std::cout << desc << '\n';
    }

    else if (getenv("DEMO_OUTPUT") != nullptr) {
  		std::cout << "ENV" << std::endl;

        std::string _trAddress = getenv("DEMO_OUTPUT");
        std::ofstream out(_trAddress, std::ios_base::app);
        while(std::cin >> text) {
			print(text, out);
			out << std::endl;
		}
        out.close();
  	}

  	else if (vm.count("output")) {
  		std::cout << "Output in >> " << vm["output"].as<std::string>() << '\n';
  		std::ofstream out(vm["output"].as<std::string>(), std::ios_base::app);
		while(std::cin >> text) {
			print(text, out);
			out << std::endl;
		}
		out.close();
  	}

  	else {
  		std::cout << "DEFAULT" << std::endl;

		std::ofstream out("default.log", std::ios_base::app);
		while(std::cin >> text) {
			print(text, out);
			out << std::endl;
		}
		out.close();
  	}

  } catch (const error &ex) {
    std::cerr << ex.what() << '\n';
  }
}
