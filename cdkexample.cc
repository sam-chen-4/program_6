/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string>
#include <sstream>
using namespace std;

class BinaryFileHeader
{
	public:
       		uint32_t magicNumber;
		uint32_t versionNumber;
		uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
	public:
		uint8_t strLength;
		char stringBuffer[maxRecordStringLength];
};

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Binary File Contents"

int main()
{
  	BinaryFileHeader *myHeader = new BinaryFileHeader();

	ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

	binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
	cout << myHeader->magicNumber << endl;
	cout << myHeader->versionNumber << endl;
	cout << myHeader->numRecords << endl;

	binInfile.close();

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
 // setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
	stringstream ss;
	ss << std::hex << myHeader->magicNumber;
	char *magNum;
	string tmp = ss.str();
	magNum = const_cast<char*>(tmp.c_str());
	setCDKMatrixCell(myMatrix, 1, 1, magNum);
	ss.str("");
	ss.clear();
	
	ss << myHeader->versionNumber;
	char *verNum;
	tmp = ss.str();
	verNum = const_cast<char*>(tmp.c_str());
	setCDKMatrixCell(myMatrix, 1, 2, verNum);
	ss.str("");
	ss.clear();

	ss << myHeader->numRecords;
	char *numRec;
	tmp = ss.str();
	numRec = const_cast<char*>(tmp.c_str());
	setCDKMatrixCell(myMatrix, 1, 3, numRec);
	
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
