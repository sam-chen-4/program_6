/*
 * Usage of CDK Matrix
 *
 * File:   cdkexample.cc
 * Author: Samuel Chen
 * Email:  sxc144230@utdallas.edu
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
  	BinaryFileHeader *myHeader = new BinaryFileHeader();

	ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

	binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
	//cout << myHeader->magicNumber << endl;
	//cout << myHeader->versionNumber << endl;
	//cout << myHeader->numRecords << endl;
	
	BinaryFileRecord *myRecord = new BinaryFileRecord();
	stringstream ss2;
	char *word;
	string tmp;
	char result4[100];
	char *strlength = "strlen: ";

	for(int i = 2; (unsigned)i<( myHeader->numRecords + 2); i++)
	{
		binInfile.read((char*) myRecord, sizeof(BinaryFileRecord));

		ss2 << strlen(myRecord->stringBuffer);
		tmp = ss2.str();
		strcpy(result4, strlength);
		strcat(result4, const_cast<char*>(tmp.c_str()));
		setCDKMatrixCell(myMatrix, i, 1, result4);
		ss2.str("");
		ss2.clear();

		ss2 << myRecord->stringBuffer << endl;
		tmp = ss2.str();
		word = const_cast<char*>(tmp.c_str());
		setCDKMatrixCell(myMatrix, i, 2, word);
		ss2.str("");
		ss2.clear();
	}

	binInfile.close();

	char result[100];
	char result2[100];
	char result3[100];
	char *magic = "Magic: ";
	char *version = "Version: ";
	char *num = "NumRecords: ";
	
	stringstream ss;
	ss << std::hex << myHeader->magicNumber;
	tmp = ss.str();
	strcpy(result, magic);
	strcat(result, const_cast<char*>(tmp.c_str()));
	setCDKMatrixCell(myMatrix, 1, 1, result);
	ss.str("");
	ss.clear();

	stringstream ss3;
	
	ss3 << myHeader->versionNumber;
	tmp = ss3.str();
	strcpy(result2, version);
	strcat(result2, const_cast<char*>(tmp.c_str()));
	setCDKMatrixCell(myMatrix, 1, 2, result2);
	ss3.str("");
	ss3.clear();

	ss << myHeader->numRecords;
	tmp = ss.str();
	strcpy(result3, num);
	strcat(result3, const_cast<char*>(tmp.c_str()));
	setCDKMatrixCell(myMatrix, 1, 3, result3);
	ss.str("");
	ss.clear();
	
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
