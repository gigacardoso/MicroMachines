#include <ctime>
#include "cg/cg.h"
#include "App.h"

int main(int argc, char** argv){

	srand(time(NULL));
	cg::Manager::instance()->runApp(new micro_machines::App(),60,argc,argv);
	return 0;
	
}
