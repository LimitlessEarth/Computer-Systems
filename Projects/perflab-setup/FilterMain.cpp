#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rtdsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    unsigned int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (unsigned int i=0; i < size; i++) {
      for (unsigned int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  unsigned int imageWidth = input -> width;
  unsigned int imageHeight = input -> height;
  unsigned int imgdwth = imageHeight/3;

  unsigned int filtersize = filter -> getSize();
  unsigned int filterdivisor = filter -> getDivisor();
  
  unsigned int localfilter[filtersize][filtersize];
  for ( unsigned char i = 0; i < filtersize; ++i) {
    for ( unsigned char j = 0; j < filtersize; ++j) {
      localfilter[i][j] = filter -> get(i,j);
    }
  }

  int v0, v1 = 0;

  output -> width = imageWidth;
  output -> height = imageHeight;

  --imageHeight;
  --imageWidth;
  
  for(unsigned char plane = 0; plane < 3; ++plane) {
    for(unsigned int row = 1; row < imageHeight ; ++row) {
      for(unsigned int col = 1; col < imageWidth; col += 2) {
 
	v0 = 0;
	v1 = 0;
	

	v0 = v0 
	+ (input -> color[plane][row - 1][col - 1] * localfilter[0][0])
        + (input -> color[plane][row - 1][col    ] * localfilter[0][1])
        + (input -> color[plane][row - 1][col + 1] * localfilter[0][2]);

	v1 = v1 
	+ (input -> color[plane][row - 1][col    ] * localfilter[0][0])
        + (input -> color[plane][row - 1][col + 1] * localfilter[0][1])
        + (input -> color[plane][row - 1][col + 2] * localfilter[0][2]);

	v0 = v0  
	+ (input -> color[plane][row    ][col - 1] * localfilter[1][0])
        + (input -> color[plane][row    ][col    ] * localfilter[1][1])
        + (input -> color[plane][row    ][col + 1] * localfilter[1][2]);

	v1 = v1  
	+ (input -> color[plane][row    ][col    ] * localfilter[1][0])
        + (input -> color[plane][row    ][col + 1] * localfilter[1][1])
        + (input -> color[plane][row    ][col + 2] * localfilter[1][2]);

	v0 = v0  
	+ (input -> color[plane][row + 1][col - 1] * localfilter[2][0])
        + (input -> color[plane][row + 1][col    ] * localfilter[2][1])
        + (input -> color[plane][row + 1][col + 1] * localfilter[2][2]);

	v1 = v1  
	+ (input -> color[plane][row + 1][col    ] * localfilter[2][0])
        + (input -> color[plane][row + 1][col + 1] * localfilter[2][1])
        + (input -> color[plane][row + 1][col + 2] * localfilter[2][2]);



	if ( filterdivisor != 1) {
	v0 = v0 / filterdivisor;
	v1 = v1 / filterdivisor;
	}

	if ( v0  < 0 ) { 
	  v0 = 0; 
	}
	if ( v0  > 255 ) { 
	  v0 = 255;

	}

	if ( v1  < 0 ) { 
	  v1 = 0;
 
	}
	if ( v1  > 255 ) { 
   	  v1 = 255;
 
	}

	    output -> color[plane][row][col] = v0;
	    output -> color[plane][row][col + 1] = v1;	

      }
    }
  }


  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
