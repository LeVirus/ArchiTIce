#include <iostream>
#include "include/jBiblAudio.h"
#include <Ice/Ice.h>
#include <IceStorm/IceStorm.h>
//#include <Printer.h>

using namespace std;
//using namespace Demo;

int main(int argc, char* argv[])
{
    //basculer le tout dans le constructeur de jBibl
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
	ic = Ice::initialize(argc, argv);
	Ice::ObjectAdapterPtr adapter =
	    ic->createObjectAdapterWithEndpoints("BiblAudioAdapter", "default -p 10000");
	Ice::ObjectPtr object = new BiblAudio;
	adapter->add(object, ic->stringToIdentity("BiblAudio"));
	adapter->activate();

	ic->waitForShutdown();
    } catch (const Ice::Exception& e) {
	cerr << e << endl;
	status = 1;
    } catch (const char* msg) {
	cerr << msg << endl;
	status = 1;
    }
    if (ic) {
	try {
	    ic->destroy();
	} catch (const Ice::Exception& e) {
	    cerr << e << endl;
	    status = 1;
	}
    }
    return status;
}
