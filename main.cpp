#include <Python.h>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>	// Added to allow for files reading
#include "PrintMenu.h"	// Added to use PrintMenu.cpp

//#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void GetData() {		// I passed the variable by reference for the vectors

	ifstream file;		// Creates input file object
	string fileIn = "frequency.dat";	// Stores file name in a variable for easier coding
	file.open(fileIn);

	if (!file.is_open()) {		// Ensures the file opened properly
		cout << "Could not open file";
		return;
	}

	while (!file.eof()) {		// Runs through the whole file until the end of file(eof)
		string item;
		int quantity;

		file >> item;		// Gets input from the file and assigns it to cities vector

		file >> quantity;			// Gets input from the file and assigns it to temps vector

		cout << item << " " << string(quantity, '*') << endl; // Displays 

	}
	file.close();		// Closes the file so it can be used again later
}

void main()
{
	// Variables to be used throughout main
	int userChoice = 9999;
	bool exitProgram = false;
	string item = "";

	while (!exitProgram){

		PrintMenu();		// Calls a function to print user menu

		if (!(cin >> userChoice)) {		//validates user input to ensur they enter a number and prevents infinte loop
			system("CLS");

			//Notifies the user of a bad selection and clears input stream
			cout << "Bad selection, please choose again." << endl;
			cin.clear();
			cin.ignore();
		}

		// Switch statement to call specific functions based on the user's choice
		switch (userChoice) {
		case 1:
			CallProcedure("ItemCount");		// Calls the python function ItemCount
			cout << endl << "Pressing enter will return you to the main menu." << endl; // Just a notification to the user that they will be returned to the menu
			system("Pause");
			system("CLS");
			break;
		case 2:
			cout << "Please enter an item to check it's frequency." << endl; // Asks user for item to check frequency
			cin >> item;
			// Tells the user the frequency of the item they input and call a python function to get the acutual number of times
			cout << "The frequency of " << item << " is " << callIntFunc("UniqueItemFrequency", item) << " times." << endl;
			cout << endl << "Pressing enter will return you to the main menu." << endl; // Just a notification to the user that they will be returned to the menu
			system("Pause");
			system("CLS");
			break;
		case 3:
			CallProcedure("DisplayHistogram");	// Calls the python function DisplayHistogram
			GetData();	// Calls C++ function to read from a file and display it to the screen in the correct format
			cout << endl << "Pressing enter will return you to the main menu." << endl; // Just a notification to the user that they will be returned to the menu
			system("Pause");
			system("CLS");
			break;
		case 4:
			return; // Exits the program
			break;
		}
	}

	//CallProcedure("printsomething");
	//cout << callIntFunc("PrintMe", "House") << endl;
	//cout << callIntFunc("SquareValue", 2);

}