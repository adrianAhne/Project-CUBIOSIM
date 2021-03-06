/***************

Project cuBIOSIM
Polytech Paris UPMC

authors:
	Liliane Kissita
	Elise Grojean
	Adrian Ahne
	Lucas Gaudelet

****************/

// standard C++
#include <fstream>
#include <iostream>
#include <vector>

// ODE solver
#include <boost/numeric/odeint.hpp>

// repressilator class
#include <repressilator.hh>

// command line parser and timer
#include <chCommandLine.h>
#include <chTimer.hpp>


// namespaces
using namespace std;
using namespace boost::numeric::odeint;


// Constants
const static int DEFAULT_N = 3;

const static double Ktl = 1e-2;	// Translation rate
const static double Ktr = 1e-3;	// Transcription rate
const static double KR = 1e-2;  // Strength of repressors
const static double nR = 2;	// Hills coefficient of repressors
const static double dprot = 1e-3;	// Protein degradation rate
const static double dmRNA = 1e-2;	// mRNA degradation rate


// function prototypes
void write_ODE_result( const vector<double> &Y, const double t );
void print_help(char* argv);


// main
int main(int argc, char **argv) {

	// print help
	bool      help = chCommandLineGetBool("h", argc, argv);
	if(!help) help = chCommandLineGetBool("help", argc, argv);
	if(help)  print_help(argv[0]);

	// repressilator size
	int n = -1;
	chCommandLineGet<int>(&n, "n", argc, argv);
	chCommandLineGet<int>(&n, "repressor-number", argc, argv);
	n = (n!=-1)? n:DEFAULT_N;
	
	if( n%2==0 ) {
		cout << "n must be an odd interger" << endl;
		exit(-1);
	}
	else {
		cout << "repressors : " << n 
			<< "\tspecies: " << 2*(n+1)
			<< "\treactions: " << 2*n+1 << endl;
	}

	// repressilator initialisation
	Repressilator_ODE repr(n, dprot, dmRNA, Ktl, Ktr, KR, nR);
	//repr.check();

	// initial point
	vector<double> Y0(2*(n+1),0.0);	Y0[0] = 1;

	// compute
cout << "call integrate...\t" << flush;
	integrate( repr , Y0 , 0.0 , 100000.0 , 1e-2 , write_ODE_result );
cout << "done" << endl;

	return 0;

}


// utility functions
void write_ODE_result( const vector<double> &Y, const double t )
{
	ofstream file;
	file.open ("bin/Result.csv",ios::app); // write at the end of file
	
	file << t;
	for( double d : Y) {
		file << ";" << d;	
	}
	file << "\n";
	
	file.close();
}

void print_help( char* argv) {

	cout	<< "Help:" << endl
		<< "  Usage: " << endl
		<< "  " << argv << " [options][-n <repressor-number> ]" << endl
		<< endl
		<< "  -n|--repressor-number" << endl
		<< "      number of repressors to be used, must be an odd integer" << endl
		<< endl;

}



