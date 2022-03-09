
#include "UI.h"
#include "..\PartOpsUI\PartsUtilsUI.h"
#include "..\FeatureOpsUI\MakeWidgetFeature.h"
#include "..\AppPartOps\PartOps.h"
#include "..\Journaling\Journaling.h"
#include "..\Core\LibraryLoad.h"
#include "..\Core\CoreSession.h"
#include "..\Core\Observer.h"

UI::UI()
{

}


void UI::Init()
{
	CoreSession::GetInstance().SetupDefaultObservers();


}

void UI::StartGUILoop()
{

	Observer* observer4;
	Observer* observer5;

	CoreSession::GetInstance().CreateMessage("Hello World! :D");
	CoreSession::GetInstance().CreateMessage("The weather is hot today! :p");
	observer4 = new Observer(CoreSession::GetInstance(), Observer::ClosePart);
	observer5 = new Observer(CoreSession::GetInstance(), Observer::SavePart);
	CoreSession::GetInstance().CreateMessage("My new car is great! ;)");


	// This is just mimic'ing a simple CAD workflow.
	// We are going to pretend the user makes  part, makes a widget feature, saves the part,
	// and then exits.  And this will stop the GUI loop and lead to exit on main

	//Setup Journaling File
	SetJournalingLangauge(JournalingLanguage::CPP);
	StartJournaling("C:\\Users\\jpbro\\Documents\\develop\\SoftwareArch\\repositories\\SoftwareArchitectureCLassApplication\\JournaledCPPFileProject\\SampleJournal.txt");


	PartFile * partFile = MakePartUI("d:\\workdir\\someDir\\SomeName.part");
	AddWidgetFeatureToPartUI(partFile, true, 10);
	SavePartUI(partFile);

	PartFile* partFile2 = OpenPartUI("C:\\Users\\jpbro\\Documents\\develop\\SoftwareArch\\repositories\\SoftwareArchitectureCLassApplication\\SampleVersionUp.prt");

	SavePartUI(partFile2);

	//End Journaling
	EndJournaling();

	std::cout << "Before Loaded Library"<<std::endl;
	HINSTANCE handle = LoadLibrary("COOLDEMANDLOADEDLIBRARY.dll");
	std::cout << "After Loaded Library"<<std::endl;
	UnloadLibrary(handle);
	std::cout << "After UnLoaded Library"<<std::endl;

	observer4->RemoveMeFromTheList();
	observer5->RemoveMeFromTheList();
	

}