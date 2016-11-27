/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++}
{						OPENGL APP 3D PTP VERSION 1.0					    }
{       Writen by P7C SARL, June 2016.							}
{	  	contact: info@p7c-sarl,com											}
{																			}
{       																	}
{																			}
{        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND		}
{++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*==========================================================================
BACKGROUND TO CODE

This code is C syntax rather than C++ or C# code and contains no objects
or sophisticated elements. That is not because those techniques don't have
merit or a place but simply because this code is targetted as a learning
tool to the widest audience. Anyone proficient in C++ or C# could easily
convert this code to those formats.

==========================================================================*/

#define _WIN32_WINNT 0x0500
#include <windows.h>		// Standard windows headers
#include <tchar.h>			// Unicode support	.. we will use TCHAR rather than char	
#include <commctrl.h>		// Common controls dialogs unit
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library


#include <stdio.h>
#include <strsafe.h>

#define  argsused  warning(disable:4100)

#define SIZE_OF_PTP 6000
// This is the lazy adding libraries via #pragma rather than in linker includes
// If you are not on visual studio you will need to add the librarys via your linker
#pragma comment(lib,"ComCtl32.lib")
#pragma comment(lib,"OpenGl32.lib")
#pragma comment(lib,"GLU32.lib")

GLfloat X = -60.0f; // Translate screen to x direction (left or right)
GLfloat Y = -10.0f; // Translate screen to y direction (up or down)
GLfloat Z = -20.0f; // Translate screen to z direction (zoom in or out)

GLfloat rotLx = 0.0f; // Translate screen by using the glulookAt function (left or right)
GLfloat rotLy = 0.0f; // Translate screen by using the glulookAt function (up or down)
GLfloat rotLz = 0.0f; // Translate screen by using the glulookAt function (zoom in or out)

GLfloat minLimit_X = 0.0;
GLfloat maxLimit_X = 6000.0;
GLfloat Scala_X = 10.0;

GLfloat minLimit_Y = -150.0;
GLfloat maxLimit_Y = 1650.0;
GLfloat Scala_Y = 10.0;

GLfloat minLimit_Z = 0.0;
GLfloat maxLimit_Z = 15.0;
GLfloat Scala_Z = 1.0;

GLfloat LineWidth_X = 2;
GLfloat LineWidth_Y = 2;
GLfloat LineWidth_Z = 2;

HWND hWndEdit_XMin;
HWND hWndEdit_XMax;
HWND hWndEdit_XScala;
HWND hWndEdit_YMin;
HWND hWndEdit_YMax;
HWND hWndEdit_YScala;
HWND hWndEdit_ZMin;
HWND hWndEdit_ZMax;
HWND hWndEdit_ZScala;

HWND hWndCoord_X_MINUS;
HWND hWndCoord_Y_MINUS;
HWND hWndCoord_Z_MINUS;

HWND hWndCoord_X_PLUS;
HWND hWndCoord_Y_PLUS;
HWND hWndCoord_Z_PLUS;
//HWND hWndEdit;


HWND hWndCoord_BandWidtTitel;
HWND hWndCoord_BandWidtValue;

HWND hWndBtn_DisplayBand;
HWND hWndBtn_DisplayPlane;
HWND hWndBtn_DisplayLine;

GLfloat BandWidth = 0.5;

// Data structure of a line from ptp file.
typedef struct
{
	GLfloat Time;
	GLfloat P1;
	GLfloat P2;
	GLfloat P3;
	GLfloat P4;
	GLfloat P5;
	GLfloat P6;
	GLfloat P7;
	GLfloat P8;
	GLfloat P9;
	GLfloat P10;
	GLfloat P11;
	GLfloat P12;
	GLfloat P13;
	GLfloat P14;
	GLfloat P15;
	GLfloat P16;
	GLfloat P17;
	GLfloat P18;
	GLfloat P19;
	GLfloat P20;
	GLfloat P21;
} PTPData;
PTPData	 ListOfPTPData[SIZE_OF_PTP] = { 0 };

//number of line read from a ptp file
int numLines = 0;

GLfloat ProfileDistance = 1.0f;

GLfloat ProfileWidth = 1.0;

BOOL DisplayBackground = 0;

BOOL DisplayProfil_1 = 1;
BOOL DisplayProfil_2 = 1;
BOOL DisplayProfil_3 = 1;
BOOL DisplayProfil_4 = 1;
BOOL DisplayProfil_5 = 1;
BOOL DisplayProfil_6 = 1;
BOOL DisplayProfil_7 = 1;
BOOL DisplayProfil_8 = 1;
BOOL DisplayProfil_9 = 1;
BOOL DisplayProfil_10 = 1;
BOOL DisplayProfil_11 = 1;
BOOL DisplayProfil_12 = 1;
BOOL DisplayProfil_13 = 1;
BOOL DisplayProfil_14 = 1;
BOOL DisplayProfil_15 = 1;
BOOL DisplayProfil_16 = 1;
BOOL DisplayProfil_17 = 1;
BOOL DisplayProfil_18 = 1;
BOOL DisplayProfil_19 = 1;
BOOL DisplayProfil_20 = 1;
BOOL DisplayProfil_21 = 1;

BOOL DataProfil_1 = 0;
BOOL DataProfil_2 = 0;
BOOL DataProfil_3 = 0;
BOOL DataProfil_4 = 0;
BOOL DataProfil_5 = 0;
BOOL DataProfil_6 = 0;
BOOL DataProfil_7 = 0;
BOOL DataProfil_8 = 0;
BOOL DataProfil_9 = 0;
BOOL DataProfil_10 = 0;
BOOL DataProfil_11 = 0;
BOOL DataProfil_12 = 0;
BOOL DataProfil_13 = 0;
BOOL DataProfil_14 = 0;
BOOL DataProfil_15 = 0;
BOOL DataProfil_16 = 0;
BOOL DataProfil_17 = 0;
BOOL DataProfil_18 = 0;
BOOL DataProfil_19 = 0;
BOOL DataProfil_20 = 0;
BOOL DataProfil_21 = 0;

BOOL DisplayUnit_X = 1;
BOOL DisplayUnit_Y = 1;
BOOL DisplayUnit_Z = 0;

BOOL IncreaseProfileWidth = 1;

BOOL DisplayPlane = TRUE;
BOOL DisplayProfile = TRUE;
BOOL DisplayBand = FALSE;

char s[30];

int DrawBackGround(BOOL draw, GLfloat MaxLimit);

void drawAxis_X(GLfloat minLimit, GLfloat maxLimit, GLfloat LineWidth, GLfloat unit);

void drawAxis_Y(GLfloat minLimit, GLfloat maxLimit, GLfloat LineWidth, GLfloat unit);

void drawAxis_Z(GLfloat minLimit, GLfloat maxLimit, GLfloat LineWidth, GLfloat unit);

void ReadPTPDataFromPTPFile(TCHAR* FileName);

void ReadFilePTP(TCHAR* FileName);

BOOL LoadFileAndRetrieveProfile(HWND hEdit, LPCTSTR pszFileName);

INT ReadSensorFile_PTP(LPTSTR lpFile);

void ReadCoordinates();


/***************************************************************************
APP SPECIFIC INTERNAL CONSTANTS
***************************************************************************/

/*--------------------------------------------------------------------------}
;{                   MAIN MENU COMMAND VALUE CONSTANTS			            }
;{-------------------------------------------------------------------------*/

#define IDC_PTPLOAD 101									// App menu to load PTP File
#define IDC_EXIT 102									// App menu command to exit application
#define IDC_TIMERSTART 201								// App menu to start timer
#define IDC_TIMERSTOP 202								// App menu to stop timer
#define IDC_BUTTONPLUS 50								// Button Increment 
#define IDC_BUTTONMINUS 51								// Button Decrement 
#define IDC_PROFILEDISTANCE 52							// EDITBUTTON PROFILEDISTANCE 
#define IDC_PROFILEDISTANCE_PLUS 53						// EDITBUTTON PROFILEDISTANCE Increse 
#define IDC_PROFILEDISTANCE_MINUS 54					// EDITBUTTON PROFILEDISTANCE decrese
#define IDC_PROFILEWIDTH 55								// EDITBUTTON PROFILE WIDTH
#define IDC_PROFILESCALE 56								// EDITBUTTON PROFILE SCALE
#define IDC_DISPLAYBAND 57
#define IDC_DISPLAYPLANE 58
#define IDC_DISPLAYPROFILE 59

#define IDC_PROFILE_1_DISPLAY 301							// DISPLAY PROFILE 1
#define IDC_PROFILE_2_DISPLAY 302							// DISPLAY PROFILE 2
#define IDC_PROFILE_3_DISPLAY 303							// DISPLAY PROFILE 3
#define IDC_PROFILE_4_DISPLAY 304							// DISPLAY PROFILE 1
#define IDC_PROFILE_5_DISPLAY 305							// DISPLAY PROFILE 2
#define IDC_PROFILE_6_DISPLAY 306							// DISPLAY PROFILE 3
#define IDC_PROFILE_7_DISPLAY 307							// DISPLAY PROFILE 1
#define IDC_PROFILE_8_DISPLAY 308							// DISPLAY PROFILE 2
#define IDC_PROFILE_9_DISPLAY 309							// DISPLAY PROFILE 3

#define IDC_BACKGROUND_DISPLAY 350							// DISPLAY BACKGROUND 3
#define BUF_SIZE 40			
#define MAX_PATH  260
#define MAX_CHANNELS  22 

#define IDC_CORRD_X_MINUS 700
#define IDC_CORRD_Y_MINUS 701
#define IDC_CORRD_Z_MINUS 702
#define IDC_CORRD_X_PLUS 703
#define IDC_CORRD_Y_PLUS 704
#define IDC_CORRD_Z_PLUS 705




//------------Begin Read PTP File--------Open Dialog-------------
#define BUFFERSIZE 528000
DWORD g_BytesTransferred = 0;
VOID CALLBACK FileIOCompletionRoutine(__in  DWORD dwErrorCode, __in  DWORD dwNumberOfBytesTransfered,	__in  LPOVERLAPPED lpOverlapped);

#pragma argsused
VOID CALLBACK FileIOCompletionRoutine(__in  DWORD dwErrorCode, __in  DWORD dwNumberOfBytesTransfered,	__in  LPOVERLAPPED lpOverlapped)
{
	_tprintf(TEXT("Error code:\t%x\n"), dwErrorCode);
	_tprintf(TEXT("Number of bytes:\t%x\n"), dwNumberOfBytesTransfered);
	g_BytesTransferred = dwNumberOfBytesTransfered;
}

#pragma argsused
VOID CALLBACK readComplete(DWORD err, DWORD bytes, LPOVERLAPPED ovlp)
{
}
//-------------End Read PTP File----------------------------------


/*--------------------------------------------------------------------------}
;{                      APPLICATION STRING CONSTANTS			            }
;{-------------------------------------------------------------------------*/
const TCHAR* AppClassName = _T("OPENGL_DEMO_APP");
static const TCHAR* DATABASE_PROPERTY = _T("OurDataStructure");

/*---------------------------------------------------------------------------
OUR OPENGL DATA RECORD DEFINITION
---------------------------------------------------------------------------*/
typedef struct OpenGLData {
	HGLRC Rc;											// Our render context ** Always Needed
	GLuint glTexture;									// Our texture to draw
	GLfloat	xrot;										// Rotate screen on x axis 
	GLfloat	yrot;										// Rotate screen on y axis 
	GLfloat zrot;										// Rotate screen on z axis 
} GLDATABASE;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
COMMON DIALOG CALL ROUTINES
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*--------------------------------------------------------------------------
This uses file open common control from windows to select a file.
--------------------------------------------------------------------------*/
int OpenFileDialog(TCHAR* Name, unsigned short NameBufSize, TCHAR* String, TCHAR* Ext, TCHAR* Title, HWND Wnd) {
	int i;
	TCHAR FileName[256], DefExt[256], Filter[400];
	OPENFILENAME OpenFN;

	InitCommonControls();											// Initialize common dialogs
	Name[0] = 0;													// Preset name clear
	_tcscpy_s(&FileName[0], _countof(FileName), _T("_R7."));			// Tranfer "*."
	_tcscat_s(&FileName[0], _countof(FileName), Ext);				// Create "*.xxx" extension
	_tcscpy_s(Filter, _countof(Filter), String);					// Tranfer string
	i = _tcslen(Filter);											// Fetch that string length in TCHAR
	_tcscpy_s(&Filter[i + 1], _countof(Filter) - i - 1, &FileName[0]);	// Transfer "*.ext"
	i += (_tcslen(&FileName[0]) + 1);								// Advance to beyond end
	_tcscpy_s(&Filter[i + 1], _countof(Filter) - i - 1, _T("\0"));	// Must end with two 0 entries
	_tcscpy_s(&Filter[i + 2], _countof(Filter) - i - 2, _T("\0"));	// Must end with two 0 entries
	_tcscpy_s(DefExt, _countof(DefExt), Ext);						// Default ext name
	memset((void*)&OpenFN, 0, sizeof(OpenFN));					    // Zero unused fields
	OpenFN.lStructSize = sizeof(OPENFILENAME);					    // Size of structure
	OpenFN.hInstance = GetModuleHandle(NULL);						// Pointer to instance
	OpenFN.hwndOwner = Wnd;											// Owner window
	OpenFN.lpstrFilter = &Filter[0];								// Filter
	OpenFN.nFilterIndex = 1;										// 1st Filter String
	OpenFN.lpstrFile = &FileName[0];								// Return result
	OpenFN.nMaxFile = _countof(FileName);							// Max name length
	OpenFN.lpstrDefExt = Ext;										// Default extension
	OpenFN.lpstrFileTitle = &FileName[0];							// Default file title
	OpenFN.nMaxFileTitle = _countof(FileName);						// Max size of file title
	OpenFN.lpstrTitle = Title;	                     			    // Window title
	OpenFN.lpfnHook = NULL;											// No hook handler
	OpenFN.Flags = OFN_FILEMUSTEXIST | OFN_LONGNAMES;               // Set flag masks
	if (GetOpenFileName(&OpenFN) != 0) {
		_tcscpy_s(Name, NameBufSize, FileName);						// Return the name
		return OpenFN.nFilterIndex;									// Return filter type
	}
	else return 0;												// Dialog cancelled
};




/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
OPENGL ROUTINES
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*-[ InitGL ]---------------------------------------------------------------

Initializes the OpenGL system for the provided window handle, this is a one
time call made for the window and the function returns the created Render
context for the window. The responsibility to delete the render context when
completed is placed on the caller. In this demo initialization will be called
from WM_CREATE from the application window. Failure of initialization will
return a render context handle equal to zero.

June 2016 P7C.Sarl
--------------------------------------------------------------------------*/
static HGLRC InitGL(HWND Wnd) {
	HGLRC ourOpenGLRC = 0;											// Preset render context to zero

																	//  We need to make sure the window create in a suitable DC format
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
		PFD_TYPE_RGBA,												// The kind of framebuffer. RGBA or palette.
		32,															// Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,															// Number of bits for the depthbuffer
		8,															// Number of bits for the stencilbuffer
		0,															// Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC ourWindowHandleToDeviceContext = GetDC(Wnd);				// Get a DC for our window
	int letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd); // Let windows select an appropriate pixel format
	if (SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd)) { // Try to set that pixel format
		ourOpenGLRC = wglCreateContext(ourWindowHandleToDeviceContext);
		if (ourOpenGLRC != 0) {
			wglMakeCurrent(ourWindowHandleToDeviceContext, ourOpenGLRC); // Make our render context current
			glEnable(GL_TEXTURE_2D);								// Enable Texture Mapping
			glShadeModel(GL_SMOOTH);								// Enable Smooth Shading
		    glClearColor(1.0, 1.0, 1.0, 1.0);						// Paint scene to white
			//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// Black Background
			glClearDepth(1.0f);										// Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);								// Enables Depth Testing
			glDepthFunc(GL_LEQUAL);									// The Type Of Depth Testing To Do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		// Really Nice Perspective Calculations
		}
	}
	ReleaseDC(Wnd, ourWindowHandleToDeviceContext);					// Release the window device context we are done
	return (ourOpenGLRC);											// Return the render context
}


/*-[ ReSizeGLScene ]--------------------------------------------------------

Rescales the OpenGL system for a given size of screen, called at anytime
the Application resizes the window . It will call once after InitGL and
in this demo it is called from WM_WINDOWPOSCHANGED from the application
main window.

June 2016 P7C.Sarl
--------------------------------------------------------------------------*/
static void ReSizeGLScene(HWND Wnd) {
	GLDATABASE* db = (GLDATABASE*)GetProp(Wnd, DATABASE_PROPERTY);  // Fetch the data base
	if (db == 0) return;											// Cant resize .. no render context
	HDC Dc = GetWindowDC(Wnd);										// Get the window DC
	RECT r;
	GetWindowRect(Wnd, &r);											// Fetch the window size
	int Width = r.right - r.left;									// Window width
	int Height = r.bottom - r.top;									// Window height
	if (Height == 0) Height = 1;									// Stop divid by zero
	wglMakeCurrent(Dc, db->Rc);										// Make our render context current
	glViewport(0, 0, Width, Height);								// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);									// Select The Projection Matrix
	glLoadIdentity();												// Reset The Projection Matrix																
	//gluPerspective(45.0f, 	2.0 *(GLfloat)Width / (GLfloat)Height ,							// Calculate The Aspect Ratio Of The Window
	//		5.1f, 	100.0f);		
	gluPerspective(45.0f, 5.0, 5.1f, 100.0f);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	//glOrtho(0.0, 0.0, 0.0, 0.0, 1, 1);
	glMatrixMode(GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity();												// Reset The Modelview Matrix
	ReleaseDC(Wnd, Dc);												// Release the window DC
}


/*-[ DrawGLScene ]----------------------------------------------------------

This is where all the OpenGL drawing is done for each frame. In this application
it will be called from WM_PAINT messages to the window

June 2016 P7C.Sarl
--------------------------------------------------------------------------*/
void DrawGLScene(GLDATABASE* db, HDC Dc) {
	//if ((db == 0) || (db->glTexture == 0)) return;					// Cant draw .. no render context
	//wglMakeCurrent(Dc, db->Rc);										// Make our render context current

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear The Screen And The Depth Buffer
	glPushMatrix();													// Push matrix before calling
	glMatrixMode(GL_MODELVIEW);										//select the model view matrix.
	glLoadIdentity();												// Reset The View

	//Position and orientation of camera.
	gluLookAt(1.0, 2.0, 20.0,										// Camera position
		0, 0, 0,													// Camera orientation
		0, 1, 0);													// Camera direction	
	
	ReadCoordinates();												// Read parameters for system coordinate

	// Translates the screen left or right, 
	// up or down or zoom in zoom out
	// Draw the positive side of the lines x,y,z
	glTranslatef(X, Y, Z);

	glRotatef(db->yrot, 0.0f, 1.0f, 0.0f);

	// Draw Axis x, y and z
	drawAxis_X(minLimit_X, maxLimit_X, LineWidth_X, 10);
	drawAxis_Y(minLimit_Y, maxLimit_Y, LineWidth_Y, 10);
	drawAxis_Z( minLimit_Z, maxLimit_Z, LineWidth_Z, 10);
	
	DrawBackGround(DisplayBackground,20.0f);
	

	//Draw the profiles from list of PTP Data
	ProfileDistance = Scala_Z;

	
		glLineWidth(ProfileWidth);
		for (int i = 0; i < numLines; i++)
		{
			GLfloat time = ListOfPTPData[i].Time / Scala_X;
			GLfloat timePlus1 = ListOfPTPData[i + 1].Time / Scala_X;
			GLfloat tempP = 0.0;
			if (timePlus1 > 0)
			{
				if (DisplayPlane)
				{
					glBegin(GL_QUADS);
					tempP = ListOfPTPData[i].P1 / 160;
					glColor3f(tempP, 0.0f, 1 - tempP);
					glVertex3f(time, ListOfPTPData[i].P1 / Scala_Y, ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P1 / Scala_Y, ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P2 / Scala_Y, 2 * ProfileDistance);
					glVertex3f(time, ListOfPTPData[i].P2 / Scala_Y, 2 * ProfileDistance);
					glEnd();

					glBegin(GL_QUADS);
					tempP = ListOfPTPData[i].P2 / 160;
					glColor3f(tempP, 0.0f, 1 - tempP);
					glVertex3f(time, ListOfPTPData[i].P2 / Scala_Y, 2 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P2 / Scala_Y, 2 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P3 / Scala_Y, 3 * ProfileDistance);
					glVertex3f(time, ListOfPTPData[i].P3 / Scala_Y, 3 * ProfileDistance);
					glEnd();

					glBegin(GL_QUADS);
					tempP = ListOfPTPData[i].P3 / 160;
					glColor3f(tempP, 0.0f, 1 - tempP);
					glVertex3f(time, ListOfPTPData[i].P3 / Scala_Y, 3 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P3 / Scala_Y, 3 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P4 / Scala_Y, 4 * ProfileDistance);
					glVertex3f(time, ListOfPTPData[i].P4 / Scala_Y, 4 * ProfileDistance);
					glEnd();

					glBegin(GL_QUADS);
					tempP = ListOfPTPData[i].P4 / 160;
					glColor3f(tempP, 0.0f, 1 - tempP);
					glVertex3f(time, ListOfPTPData[i].P4 / Scala_Y, 4 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P4 / Scala_Y, 4 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P5 / Scala_Y, 5 * ProfileDistance);
					glVertex3f(time, ListOfPTPData[i].P5 / Scala_Y, 5 * ProfileDistance);
					glEnd();

					glBegin(GL_QUADS);
					tempP = ListOfPTPData[i].P5 / 160;
					glColor3f(tempP, 0.0f, 1 - tempP);
					glVertex3f(time, ListOfPTPData[i].P5 / Scala_Y, 5 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P5 / Scala_Y, 5 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P6 / Scala_Y, 6 * ProfileDistance);
					glVertex3f(time, ListOfPTPData[i].P6 / Scala_Y, 6 * ProfileDistance);
					glEnd();

					glBegin(GL_QUADS);
					tempP = ListOfPTPData[i].P6 / 160;
					glColor3f(tempP, 0.0f, 1 - tempP);
					glVertex3f(time, ListOfPTPData[i].P6 / Scala_Y, 6 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P6 / Scala_Y, 6 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P7 / Scala_Y, 7 * ProfileDistance);
					glVertex3f(time, ListOfPTPData[i].P7 / Scala_Y, 7 * ProfileDistance);
					glEnd();

					glBegin(GL_QUADS);
					tempP = ListOfPTPData[i].P7 / 160;
					glColor3f(tempP, 0.0f, 1 - tempP);
					glVertex3f(time, ListOfPTPData[i].P7 / Scala_Y, 7 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P7 / Scala_Y, 7 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P8 / Scala_Y, 8 * ProfileDistance);
					glVertex3f(time, ListOfPTPData[i].P8 / Scala_Y, 8 * ProfileDistance);
					glEnd();

					glBegin(GL_QUADS);
					tempP = ListOfPTPData[i].P8 / 160;
					glColor3f(tempP, 0.0f, 1 - tempP);
					glVertex3f(time, ListOfPTPData[i].P8 / Scala_Y, 8 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P8 / Scala_Y, 8 * ProfileDistance);
					glVertex3f(timePlus1, ListOfPTPData[i + 1].P9 / Scala_Y, 9 * ProfileDistance);
					glVertex3f(time, ListOfPTPData[i].P9 / Scala_Y, 9 * ProfileDistance);
					glEnd();
				}
				
				if(DisplayProfile)
				{
					if (DisplayProfil_1 && DataProfil_1)
					{
						//Profil 1
						glBegin(GL_LINES);
						glColor3f(1.0f, 1.0f, 0.0f);
						glVertex3f(time, ListOfPTPData[i].P1 / Scala_Y, ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P1 / Scala_Y, ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P1 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);

							glVertex3f(time, ListOfPTPData[i].P1 / Scala_Y, ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P1 / Scala_Y, ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P1 / Scala_Y, ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P1 / Scala_Y, ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_2 && DataProfil_2)
					{
						//Profi	2
						glBegin(GL_LINES);
						glColor3f(1.0f, 1.0f, 0.4f);
						glVertex3f(time, ListOfPTPData[i].P2 / Scala_Y, 2 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P2 / Scala_Y, 2 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P2 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);

							glVertex3f(time, ListOfPTPData[i].P2 / Scala_Y, 2 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P2 / Scala_Y, 2 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P2 / Scala_Y, 2 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P2 / Scala_Y, 2 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_3 && DataProfil_3)
					{
						//Profi	3
						glBegin(GL_LINES);
						glColor3f(1.0f, 0.7f, 0.0f);
						glVertex3f(time, ListOfPTPData[i].P3 / Scala_Y, 3 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P3 / Scala_Y, 3 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P3 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P3 / Scala_Y, 3 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P3 / Scala_Y, 3 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P3 / Scala_Y, 3 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P3 / Scala_Y, 3 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_4 && DataProfil_4)
					{

						//Profi	4
						glBegin(GL_LINES);
						glColor3f(1.0f, 1.0f, 0.0f);
						glVertex3f(time, ListOfPTPData[i].P4 / Scala_Y, 4 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P4 / Scala_Y, 4 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P4 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P4 / Scala_Y, 4 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P4 / Scala_Y, 4 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P4 / Scala_Y, 4 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P4 / Scala_Y, 4 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_5 && DataProfil_5)
					{
						//Profi	5
						glBegin(GL_LINES);
						glColor3f(1.0f, 0.0f, 4.0f);
						glVertex3f(time, ListOfPTPData[i].P5 / Scala_Y, 5 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P5 / Scala_Y, 5 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P5 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P5 / Scala_Y, 5 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P5 / Scala_Y, 5 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P5 / Scala_Y, 5 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P5 / Scala_Y, 5 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_6  && DataProfil_6)
					{
						//Profi	6
						glBegin(GL_LINES);
						glColor3f(1.0f, 0.0f, 7.0f);
						glVertex3f(time, ListOfPTPData[i].P6 / Scala_Y, 6 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P6 / Scala_Y, 6 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P6 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P6 / Scala_Y, 6 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P6 / Scala_Y, 6 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P6 / Scala_Y, 6 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P6 / Scala_Y, 6 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_7 && DataProfil_7)
					{
						//Profi	7
						glBegin(GL_LINES);
						glColor3f(1.0f, 0.0f, 0.0f);
						glVertex3f(time, ListOfPTPData[i].P7 / Scala_Y, 7 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P7 / Scala_Y, 7 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P7 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P7 / Scala_Y, 7 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P7 / Scala_Y, 7 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P7 / Scala_Y, 7 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P7 / Scala_Y, 7 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_8 && DataProfil_8)
					{
						//Profi	8
						glBegin(GL_LINES);
						glColor3f(0.0f, 0.0f, 0.4f);
						glVertex3f(time, ListOfPTPData[i].P8 / Scala_Y, 8 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P8 / Scala_Y, 8 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P8 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P8 / Scala_Y, 8 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P8 / Scala_Y, 8 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P8 / Scala_Y, 8 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P8 / Scala_Y, 8 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_9 && DataProfil_9)
					{
						//Profi	9
						glBegin(GL_LINES);
						glColor3f(0.0f, 0.0f, 0.7f);
						glVertex3f(time, ListOfPTPData[i].P9 / Scala_Y, 9 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P9 / Scala_Y, 9 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P9 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P9 / Scala_Y, 9 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P9 / Scala_Y, 9 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P9 / Scala_Y, 9 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P9 / Scala_Y, 9 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_10 && DataProfil_10)
					{
						//Profi	10
						glBegin(GL_LINES);
						glColor3f(0.0f, 0.0f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P10 / Scala_Y, 10 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P10 / Scala_Y, 10 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P10 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P10 / Scala_Y, 10 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P10 / Scala_Y, 10 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P10 / Scala_Y, 10 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P10 / Scala_Y, 10 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_11 && DataProfil_11)
					{
						//Profi	11
						glBegin(GL_LINES);
						glColor3f(0.0f, 0.4f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P11 / Scala_Y, 11 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P11 / Scala_Y, 11 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P11 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P11 / Scala_Y, 11 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P11 / Scala_Y, 11 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P11 / Scala_Y, 11 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P11 / Scala_Y, 11 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_12 && DataProfil_12)
					{
						//Profi	12
						glBegin(GL_LINES);
						glColor3f(0.0f, 0.7f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P12 / Scala_Y, 12 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P12 / Scala_Y, 12 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P12 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P12 / Scala_Y, 12 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P12 / Scala_Y, 12 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P12 / Scala_Y, 12 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P12 / Scala_Y, 12 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_13 && DataProfil_13)
					{
						//Profi	13
						glBegin(GL_LINES);
						glColor3f(0.4f, 1.0f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P13 / Scala_Y, 13 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P13 / Scala_Y, 13 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P13 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P13 / Scala_Y, 13 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P13 / Scala_Y, 13 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P13 / Scala_Y, 13 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P13 / Scala_Y, 13 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_14 && DataProfil_14)
					{
						//Profi	14
						glBegin(GL_LINES);
						glColor3f(0.7f, 1.0f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P14 / Scala_Y, 14 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P14 / Scala_Y, 14 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P14 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P14 / Scala_Y, 14 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P14 / Scala_Y, 14 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P14 / Scala_Y, 14 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P14 / Scala_Y, 14 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_15 && DataProfil_15)
					{
						//Profi	15
						glBegin(GL_LINES);
						glColor3f(1.0f, 1.0f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P15 / Scala_Y, 15 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P15 / Scala_Y, 15 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P15 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P15 / Scala_Y, 15 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P15 / Scala_Y, 15 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P15 / Scala_Y, 15 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P15 / Scala_Y, 15 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_16 && DataProfil_16)
					{
						//Profi	16
						glBegin(GL_LINES);
						glColor3f(0.4f, 1.0f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P16 / Scala_Y, 16 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P16 / Scala_Y, 16 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P16 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P16 / Scala_Y, 16 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P16 / Scala_Y, 16 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P16 / Scala_Y, 16 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P16 / Scala_Y, 16 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_17 && DataProfil_17)
					{
						//Profi	17
						glBegin(GL_LINES);
						glColor3f(0.7f, 1.0f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P17 / Scala_Y, 17 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P17 / Scala_Y, 17 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P17 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P17 / Scala_Y, 17 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P17 / Scala_Y, 17 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P17 / Scala_Y, 17 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P17 / Scala_Y, 17 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_18 && DataProfil_18)
					{
						//Profi	18
						glBegin(GL_LINES);
						glColor3f(1.0f, 1.0f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P18 / Scala_Y, 18 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P18 / Scala_Y, 18 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P18 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P18 / Scala_Y, 18 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P18 / Scala_Y, 18 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P18 / Scala_Y, 18 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P18 / Scala_Y, 18 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_19 && DataProfil_19)
					{
						//Profi	19
						glBegin(GL_LINES);
						glColor3f(0.7f, 1.0f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P19 / Scala_Y, 19 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P19 / Scala_Y, 19 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P19 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P19 / Scala_Y, 19 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P19 / Scala_Y, 19 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P19 / Scala_Y, 19 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P19 / Scala_Y, 19 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_20 && DataProfil_20)
					{
						//Profi	20
						glBegin(GL_LINES);
						glColor3f(1.0f, 1.0f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P20 / Scala_Y, 20 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P20 / Scala_Y, 20 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P20 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P20 / Scala_Y, 20 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P20 / Scala_Y, 20 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P20 / Scala_Y, 20 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P20 / Scala_Y, 20 * ProfileDistance - BandWidth);
							glEnd();
						}
					}

					if (DisplayProfil_21 && DataProfil_21)
					{
						//Profi	21
						glBegin(GL_LINES);
						glColor3f(1.0f, 1.0f, 1.0f);
						glVertex3f(time, ListOfPTPData[i].P21 / Scala_Y, 21 * ProfileDistance);
						glVertex3f(timePlus1, ListOfPTPData[i + 1].P21 / Scala_Y, 21 * ProfileDistance);
						glEnd();

						if (DisplayBand)
						{
							glBegin(GL_QUADS);
							tempP = ListOfPTPData[i].P21 / 255;
							glColor3f(tempP, 0.0f, 1 - tempP);
							glVertex3f(time, ListOfPTPData[i].P21 / Scala_Y, 21 * ProfileDistance - BandWidth);
							glVertex3f(time, ListOfPTPData[i].P21 / Scala_Y, 21 * ProfileDistance + BandWidth);

							glVertex3f(timePlus1, ListOfPTPData[i + 1].P21 / Scala_Y, 21 * ProfileDistance + BandWidth);
							glVertex3f(timePlus1, ListOfPTPData[i + 1].P21 / Scala_Y, 21 * ProfileDistance - BandWidth);
							glEnd();
						}
					}
				}
			}
		}
	glPopMatrix(); 													// Don't forget to pop the Matrix
}


/*-[ BMP2GLTexture ]--------------------------------------------------------

This converts a bitmap file from the filename path and converts it to an
OpenGL texture. If the filename is invalid of the file not a bitmap the
routine will return a GLuint of zero.

June 2016 P7C.Sarl
--------------------------------------------------------------------------*/
GLuint BMP2GLTexture(TCHAR* fileName, HWND Wnd, GLDATABASE* db) {
	HBITMAP hBMP;                                                   // Handle Of The Bitmap
	BITMAP  BMP;                                                    // Bitmap Structure

	HDC Dc = GetWindowDC(Wnd);										// Fetch the window DC
	if ((db != 0) && (db->Rc != 0)) wglMakeCurrent(Dc, db->Rc);		// Make our render context current

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), fileName,
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);	// Load the bitmap from file
	if (!hBMP) return (0);											// If bitmap does not exist return false
	GetObject(hBMP, sizeof(BMP), &BMP);								// Get The bitmap details
	int P2Width = (BMP.bmWidth) >> 2;								// Divid width by 4
	if ((P2Width << 2) < (BMP.bmWidth)) P2Width++;					// Inc by 1 if width x 4 is less than original
	P2Width = P2Width << 2;											// Power of two width
	long imageSize = (long)P2Width * (long)BMP.bmHeight * sizeof(RGBQUAD);
	BYTE* lpPixels = (BYTE*)malloc(imageSize);						// Create the pixel buffer					

																	// Create and fill BITMAPINFO structure to pass to GetDIBits
	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = BMP.bmWidth;
	bmi.bmiHeader.biHeight = BMP.bmHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = 0;
	bmi.bmiHeader.biSizeImage = imageSize;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biClrImportant = 0;

	// Put DIBBits into memory buffer
	GetDIBits(Dc, hBMP, 0, BMP.bmHeight, lpPixels, &bmi, DIB_RGB_COLORS);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);							// Pixel Storage Mode (Word Alignment / 4 Bytes)
	GLuint texture;
	glGenTextures(1, &texture);										// Create a GL texture

																	// Create Nearest Filtered Texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, lpPixels);

	free(lpPixels);													// Free allocated pixel memory
	ReleaseDC(Wnd, Dc);												// Release the window DC
	DeleteObject(hBMP);												// Delete The Object
	return (texture);												// Return the texture
}



/*-[ drawAxis_X ]--------------------------------------------------------

This function draw and dimension x axis.
argument @unit define the calibration of dimension. By default it's equals 10.

June 2016 P7C.Sarl
--------------------------------------------------------------------------*/
void drawAxis_X(GLfloat minLimit, GLfloat maxLimit, GLfloat LineWidth, GLfloat unit)
{
	//Draw x axis
	glColor3f(0.0, 0.0, 0.0); // black for x axis
	glLineWidth(LineWidth);
	glBegin(GL_LINES);
	glVertex3f(minLimit, 0, 0);
	glVertex3f(maxLimit, 0, 0);
	glEnd();
	
	//Dimensioning x axis throw +
	for (GLfloat u = 0.0; u <= maxLimit; u += 1.0) 
	{
		glLineWidth(1.0);
		glBegin(GL_LINES);
		glVertex3f(u, (GLfloat)-0.15, 0.0);
		glVertex3f(u, (GLfloat)0.15, 0.0);
		glEnd();
	}
	if (DisplayUnit_X)
	{
		for (GLfloat u = 0.0; u <= maxLimit; u += unit)
		{
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3f(u, (GLfloat)-0.35, 0.0);
			glVertex3f(u, (GLfloat)0.35, 0.0);
			glEnd();
		}
	}

	//Dimensioning x axis throw -
	for (GLfloat u = 0.0; u >= minLimit; u += -1.0)
	{
		glLineWidth(1.0);
		glBegin(GL_LINES);
		glVertex3f(u, (GLfloat)-0.15, 0.0);
		glVertex3f(u, 0.15, 0.0);
		glEnd();
	}
	if (DisplayUnit_X)
	{
		for (GLfloat u = 0.0; u >= minLimit; u += -unit)
		{
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3f(u, (GLfloat)-0.35, 0.0);
			glVertex3f(u, (GLfloat)0.35, 0.0);
			glEnd();
		}
	}
}


/*-[ drawAxis_Y ]--------------------------------------------------------

This function draw and dimension y axis.
argument @unit define the calibration of dimension. By default it's equals 10.

June 2016 P7C.Sarl
--------------------------------------------------------------------------*/
void drawAxis_Y(GLfloat minLimit, GLfloat maxLimit, GLfloat LineWidth, GLfloat unit)
{
	//Draw y axis
	glColor3f(0.0, 0.0, 0.0); // black for y axis
	glLineWidth(LineWidth);
	glBegin(GL_LINES);
	glVertex3f(0, minLimit, 0);
	glVertex3f(0, maxLimit, 0);
	glEnd();

	//Dimensioning y axis throw +
	for (GLfloat u = 0.0; u <= maxLimit; u += 1.0)
	{
		glLineWidth(1.0);
		glBegin(GL_LINES);
		glVertex3f((GLfloat)-0.15, u, 0.0);
		glVertex3f((GLfloat)0.15, u, 0.0);
		glEnd();
	}
	if (DisplayUnit_Y)
	{
		for (GLfloat u = 0.0; u <= maxLimit; u += unit)
		{
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3f((GLfloat)-0.35, u, 0.0);
			glVertex3f((GLfloat)0.35, u, 0.0);
			glEnd();
		}
	}

	//Dimensioning y axis throw -
	for (GLfloat u = 0.0; u >= minLimit; u += -1.0)
	{
		glLineWidth(1.0);
		glBegin(GL_LINES);
		glVertex3f((GLfloat)-0.15, u, 0.0);
		glVertex3f((GLfloat)0.15, u, 0.0);
		glEnd();
	}
	if (DisplayUnit_Y)
	{
		for (GLfloat u = 0.0; u >= minLimit; u += -unit)
		{
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3f((GLfloat)-0.35, u, 0.0);
			glVertex3f((GLfloat)0.35, u, 0.0);
			glEnd();
		}
	}
}



/*-[ drawAxis_Z ]--------------------------------------------------------

This function draw and dimension z axis.
argument @unit define the calibration of dimension. By default it's equals 10.

June 2016 P7C.Sarl
--------------------------------------------------------------------------*/
void drawAxis_Z(GLfloat minLimit, GLfloat maxLimit, GLfloat LineWidth, GLfloat unit)
{
	//Draw z axis
	glColor3f(0.0, 0.0, 0.0); // black for z axis
	glLineWidth(LineWidth);
	glBegin(GL_LINES);
	glVertex3f(0, 0, minLimit);
	glVertex3f(0, 0, maxLimit);
	glEnd();

	//Dimensioning z axis throw +
	for (GLfloat u = 0.0; u <= maxLimit; u += 1.0)
	{
		glLineWidth(1.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, (GLfloat)-0.15, u);
		glVertex3f(0.0, (GLfloat)0.15, u);
		glEnd();
	}
	if (DisplayUnit_Z)
	{
		for (GLfloat u = 0.0; u <= maxLimit; u += unit)
		{
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3f(0.0, (GLfloat)-0.35, u);
			glVertex3f(0.0, (GLfloat)0.35, u);
			glEnd();
		}
	}

	//Dimensioning z axis throw -
	for (GLfloat u = 0.0; u >= minLimit; u += -1.0)
	{
		glLineWidth(1.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, (GLfloat)-0.15, u);
		glVertex3f(0.0, (GLfloat)0.15, u);
		glEnd();
	}
	if (DisplayUnit_Z)
	{
		for (GLfloat u = 0.0; u >= minLimit; u += -unit)
		{
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3f(0.0,(GLfloat)-0.35, u);
			glVertex3f(0.0, (GLfloat)0.35, u);
			glEnd();
		}
	}
}



/*-[ ReadCoordinates ]--------------------------------------------------------

This function read text area parameter respectively for:
- Min x, y and z value
- Max x, y and z value
- Scale representation x, y and z
Then, init the global variables
minLimit_X, maxLimit_X, Scala_X, minLimit_Y, maxLimit_Y, Scala_Y, minLimit_Z, maxLimit_Z, Scala_Z,
June 2016 P7C.Sarl
--------------------------------------------------------------------------*/
void ReadCoordinates()
{
	char xmin_buffer[65];
	char xmax_buffer[65];
	char xScala_buffer[65];

	char ymin_buffer[65];
	char ymax_buffer[65];
	char yScala_buffer[65];

	char zmin_buffer[65];
	char zmax_buffer[65];
	char zScala_buffer[65];


	char BandWith_buffer[65];

	int xminlen = GetWindowTextLength(hWndEdit_XMin);
	GetWindowTextA(hWndEdit_XMin, xmin_buffer, xminlen);
	float xminwert= (GLfloat)atof(xmin_buffer);
	minLimit_X = (GLfloat)xminwert;

	int xmaxlen = GetWindowTextLength(hWndEdit_XMax);
	GetWindowTextA(hWndEdit_XMax, xmax_buffer, xmaxlen);
	float xmaxwert = (GLfloat)atof(xmax_buffer);
	maxLimit_X = (GLfloat)xmaxwert;

	int xScalaLen = GetWindowTextLength(hWndEdit_XScala);
	GetWindowTextA(hWndEdit_XScala, xScala_buffer, xScalaLen);
	float xscalawert = (GLfloat)atof(xScala_buffer);
	Scala_X = (GLfloat)xscalawert;

	int yminlen = GetWindowTextLength(hWndEdit_YMin);
	GetWindowTextA(hWndEdit_YMin, ymin_buffer, yminlen);
	float yminwert = (GLfloat)atof(ymin_buffer);
	minLimit_Y = (GLfloat)yminwert;

	int ymaxlen = GetWindowTextLength(hWndEdit_YMax);
	GetWindowTextA(hWndEdit_YMax, ymax_buffer, ymaxlen);
	float ymaxwert = (GLfloat)atof(ymax_buffer);
	maxLimit_Y = (GLfloat)ymaxwert;

	int yScalaLen = GetWindowTextLength(hWndEdit_YScala);
	GetWindowTextA(hWndEdit_YScala, yScala_buffer, yScalaLen);
	float yscalawert = (GLfloat)atof(yScala_buffer);
	Scala_Y = (GLfloat)yscalawert;


	int zminlen = GetWindowTextLength(hWndEdit_ZMin);
	GetWindowTextA(hWndEdit_ZMin, zmin_buffer, zminlen);
	float zminwert = (GLfloat)atof(zmin_buffer);
	minLimit_Z = (GLfloat)zminwert;

	int zmaxlen = GetWindowTextLength(hWndEdit_ZMax);
	GetWindowTextA(hWndEdit_ZMax, zmax_buffer, zmaxlen);
	float zmaxwert = (GLfloat)atof(zmax_buffer);
	maxLimit_Z = (GLfloat)zmaxwert;

	int zScalaLen = GetWindowTextLength(hWndEdit_ZScala);
	GetWindowTextA(hWndEdit_ZScala, zScala_buffer, zScalaLen);
	float zscalawert = (GLfloat)atof(zScala_buffer);
	Scala_Z = (GLfloat)zscalawert;

	int Bandwidth = GetWindowTextLength(hWndCoord_BandWidtValue);
	GetWindowTextA(hWndCoord_BandWidtValue, BandWith_buffer, Bandwidth);
	float BandWidthwert = atof(BandWith_buffer);
	BandWidth = (GLfloat)BandWidthwert;
	
}


/*-[  DrawBackGround ]--------------------------------------------------------

This function draw the background of scene.

June 2016 P7C.Sarl
--------------------------------------------------------------------------*/
int DrawBackGround(BOOL draw, GLfloat MaxLimit)
{
	if (draw)
	{
		GLUquadricObj *quadric;
		quadric = gluNewQuadric();
		gluSphere(quadric, (GLint)0.2, (GLint)0.2, (GLint)0.2);
				
		glBegin(GL_QUADS);
		glColor3f(0.2f, 1.0f, 0.5f);
		glVertex3f(0.0f, 0.0f, 0.0f);     // Green
		glVertex3f(MaxLimit, 0.0f, 0.0f);
		glVertex3f(MaxLimit, 0.0f, MaxLimit);
		glVertex3f(0.0f, MaxLimit, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);     // Green
		glVertex3f(0.0f, 0.0f, MaxLimit);
		glVertex3f(0.0f, MaxLimit, MaxLimit);
		glVertex3f(0.0f, MaxLimit, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);     // Green
		glVertex3f(MaxLimit, 0.0f, 0.0f);
		glVertex3f(MaxLimit, 0.0f, MaxLimit);
		glVertex3f(0.0f, 0.0f, MaxLimit);
		glEnd();
	}
	else
	{
		// Background Environment no draw
	}
  return 0;	
}

INT ReadSensorFile_PTP(LPTSTR lpFile)
{
	FILE      *stream;
	errno_t   err;
	fpos_t    pos;
	_TCHAR    buffer[6 * MAX_PATH] = { 0 };
	INT       i;

	memset(ListOfPTPData, 0, sizeof(ListOfPTPData)); //Reset ListOfPTPData
	err = _tfopen_s(&stream, lpFile, _T("r+t, ccs=UNICODE"));
	_fgetts(buffer, sizeof(buffer) / sizeof(_TCHAR), stream);

	pos = 0;
	fsetpos(stream, &pos);
	i = 1;

	while (_fgetts(buffer, sizeof(buffer) / sizeof(_TCHAR), stream))
	{
		if (i > 11 )
		{
			switch (i)
			{
			case  1:
			case  2:
			case  3:
			case  4:
			case  5:
			case  6:
			case  7:
			case  8:
			case  9:
				break;
			default: // Zeilen Messwerte von i=1 bis SEC	

				_stscanf_s(buffer, _T("%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f\n"), &ListOfPTPData[numLines].Time, &ListOfPTPData[numLines].P1,
					&ListOfPTPData[numLines].P2, &ListOfPTPData[numLines].P3, &ListOfPTPData[numLines].P4, &ListOfPTPData[numLines].P5, &ListOfPTPData[numLines].P6,
					&ListOfPTPData[numLines].P7, &ListOfPTPData[numLines].P8, &ListOfPTPData[numLines].P9, &ListOfPTPData[numLines].P10, &ListOfPTPData[numLines].P11,
					&ListOfPTPData[numLines].P12, &ListOfPTPData[numLines].P13, &ListOfPTPData[numLines].P14, &ListOfPTPData[numLines].P15, &ListOfPTPData[numLines].P16,
					&ListOfPTPData[numLines].P17, &ListOfPTPData[numLines].P18, &ListOfPTPData[numLines].P19, &ListOfPTPData[numLines].P20, &ListOfPTPData[numLines].P21);

				GLfloat zero = 0.0;
				if (ListOfPTPData[numLines].P1 > zero)
				{
					DataProfil_1 = 1;
				}

				if (ListOfPTPData[numLines].P2 > zero)
				{
					DataProfil_2 = 1;
				}
				if (ListOfPTPData[numLines].P3 > zero)
				{
					DataProfil_3 = 1;
				}

				if (ListOfPTPData[numLines].P4 > zero)
				{
					DataProfil_4 = 1;
				}
				if (ListOfPTPData[numLines].P5 > zero)
				{
					DataProfil_5 = 1;
				}

				if (ListOfPTPData[numLines].P6 > zero)
				{
					DataProfil_6 = 1;
				}
				if (ListOfPTPData[numLines].P7 > zero)
				{
					DataProfil_7 = 1;
				}

				if (ListOfPTPData[numLines].P8 > zero)
				{
					DataProfil_8 = 1;
				}
				if (ListOfPTPData[numLines].P9 > zero)
				{
					DataProfil_9 = 1;
				}

				if (ListOfPTPData[numLines].P10 > zero)
				{
					DataProfil_10 = 1;
				}
				if (ListOfPTPData[numLines].P11 > zero)
				{
					DataProfil_11 = 1;
				}

				if (ListOfPTPData[numLines].P12 > zero)
				{
					DataProfil_12 = 1;
				}
				if (ListOfPTPData[numLines].P13 > zero)
				{
					DataProfil_13 = 1;
				}

				if (ListOfPTPData[numLines].P14 > zero)
				{
					DataProfil_14 = 1;
				}
				if (ListOfPTPData[numLines].P15 > zero)
				{
					DataProfil_15 = 1;
				}

				if (ListOfPTPData[numLines].P16 > zero)
				{
					DataProfil_16 = 1;
				}
				if (ListOfPTPData[numLines].P17 > zero)
				{
					DataProfil_17 = 1;
				}

				if (ListOfPTPData[numLines].P18 > zero)
				{
					DataProfil_18 = 1;
				}
				if (ListOfPTPData[numLines].P19 > zero)
				{
					DataProfil_19 = 1;
				}

				if (ListOfPTPData[numLines].P20 > zero)
				{
					DataProfil_20 = 1;
				}
				if (ListOfPTPData[numLines].P21 > zero)
				{
					DataProfil_21 = 1;
				}

				numLines++;
				break;
			}
		}
		i++;
	}
	fclose(stream);

	return 1;
}


/*---------------------------------------------------------------------------
Application handler.
---------------------------------------------------------------------------*/
LRESULT CALLBACK OpenGLDemoHandler(HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam) {

	switch (Msg) {
	case WM_CREATE: {											// WM_CREATE MESSAGE
		HWND hwndButton;
		HWND hwndButtonMinus;
		HWND hwndButtonProfileDistancePlus;
		HWND hwndButtonProfileDistanceMinus;
		HWND hwndButtonProfile1Display;
		HWND hwndButtonProfile2Display;
		HWND hwndButtonProfile3Display;
		HWND hwndButtonProfile4Display;
		HWND hwndButtonProfile5Display;
		HWND hwndButtonProfile6Display;
		HWND hwndButtonProfile7Display;
		HWND hwndButtonProfile8Display;
		HWND hwndButtonProfile9Display;
		HWND hwndButtonBackGround;

		//  First manually build a menu for a window
		HMENU SubMenu, Menu;
		Menu = CreateMenu();									// Create a menu and populate it

		//create menu File
		SubMenu = CreatePopupMenu();
		AppendMenu(SubMenu, MF_STRING, IDC_PTPLOAD, _T("&Load PTP"));
		AppendMenu(SubMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(SubMenu, MF_STRING, IDC_EXIT, _T("E&xit"));
		AppendMenu(Menu, MF_POPUP, (UINT_PTR)SubMenu, _T("&File"));

		//create menu setup
		/*SubMenu = CreatePopupMenu();
		AppendMenu(SubMenu, MF_STRING, IDC_TIMERSTART, _T("&Coordinates"));
		AppendMenu(SubMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(SubMenu, MF_STRING, IDC_EXIT, _T("&Background"));
		AppendMenu(Menu, MF_POPUP, (UINT_PTR)SubMenu, _T("&Setup"));*/


		SetMenu(Wnd, Menu);									// Set the menu to window

															// Make a data structure, initialize it and attach to Wnd
		GLDATABASE* db = (GLDATABASE*)malloc(sizeof(GLDATABASE)); // Allocate structure
		db->Rc = InitGL(Wnd);								// Initialize OpenGL and get render context
		db->glTexture = 0;									// Zero the texture
		db->xrot = 0.0f;									// Zero x rotation
		db->yrot = 0.0f;									// Zero y rotation
		db->zrot = 0.0f;									// Zero z rotation

		SetProp(Wnd, DATABASE_PROPERTY, (HANDLE)db);		// Set the database structure to a property on window
		ReSizeGLScene(Wnd);									// Rescale the OpenGL window

															//  Secondly manually build the tools button for a window

		hwndButton = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"ROTATION (L)",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,         // x position 
			10,         // y position 
			100,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_BUTTONPLUS,
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonMinus = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"RATATION (R)",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			120,         // x position 
			10,         // y position 
			100,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_BUTTONMINUS,
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonProfileDistancePlus = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"LINE WIDTH",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			270,         // x position 
			10,         // y position 
			100,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILEWIDTH,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.



		hwndButtonProfile1Display = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"P1",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			440,         // x position 
			10,         // y position 
			30,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILE_1_DISPLAY,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonProfile2Display = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"P2",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			480,         // x position 
			10,         // y position 
			30,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILE_2_DISPLAY,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonProfile3Display = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"P3",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			520,         // x position 
			10,         // y position 
			30,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILE_3_DISPLAY,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonProfile4Display = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"P4",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			560,         // x position 
			10,         // y position 
			30,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILE_4_DISPLAY,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonProfile5Display = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"P5",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			600,         // x position 
			10,         // y position 
			30,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILE_5_DISPLAY,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonProfile6Display = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"P6",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			640,         // x position 
			10,         // y position 
			30,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILE_6_DISPLAY,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonProfile7Display = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"P7",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			680,         // x position 
			10,         // y position 
			30,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILE_7_DISPLAY,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonProfile8Display = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"P8",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			720,         // x position 
			10,         // y position 
			30,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILE_8_DISPLAY,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonProfile9Display = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"P9",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			760,         // x position 
			10,         // y position 
			30,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILE_9_DISPLAY,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndButtonBackGround = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Background",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			800,         // x position 
			10,         // y position 
			100,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_BACKGROUND_DISPLAY,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		HWND hWndTitel = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_RIGHT | WS_BORDER,
			910, 10, //x,y positin 
			90, 20,	//Width height
			Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndTitel, TEXT("Description:"));

		HWND hWndMinTxt = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_RIGHT | WS_BORDER,
			910, 30, //x,y positin 
			90, 20,	//Width height
			Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndMinTxt, TEXT("Min:"));

		HWND hWndMaxTxt = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_RIGHT,
			910, 50, //x,y positin 
			90, 20,	//Width height
			Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndMaxTxt, TEXT("Max:"));

		HWND hWndScalaTxt = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_RIGHT,
			910, 70, //x,y positin 
			90, 20,	//Width height
			Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndScalaTxt, TEXT("Scala:"));


		HWND hWndLabek_X = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_CENTER,
			1020, 10, //x,y positin 
			70, 20,	//Width height
			Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndLabek_X, TEXT("X: Time(s)"));

		hWndEdit_XMin = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			 WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT ,
			1020, 30, //x,y positin 
			70, 20,	//Width height
			 Wnd,(HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndEdit_XMin, TEXT("0.0"));

		hWndEdit_XMax = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			1020, 50, //x,y positin 
			70, 20,	//Width height
			 Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndEdit_XMax, TEXT("6000.0"));

		hWndEdit_XScala = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			1020, 70, //x,y positin 
			70, 20,	//Width height
			 Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndEdit_XScala, TEXT("30.0"));


		hwndButtonProfileDistanceMinus = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"APPLY SCALE",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			1020,         // x position 
			100,         // y position 
			250,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_PROFILESCALE,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.


		HWND hWndLabek_Y = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_CENTER,
			1100, 10, //x,y positin 
			80, 20,	//Width height
			 Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndLabek_Y, TEXT("Y: Temp(°C)"));

		hWndEdit_YMin = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			1100, 30, //x,y positin 
			80, 20,	//Width height
			 Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndEdit_YMin, TEXT("-200.0"));

		hWndEdit_YMax = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			1100, 50, //x,y positin 
			80, 20,	//Width height
			 Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndEdit_YMax, TEXT("1650.0"));

		hWndEdit_YScala = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			1100, 70, //x,y positin 
			80, 20,	//Width height
			 Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndEdit_YScala, TEXT("30.0"));

		HWND hWndLabek_Z = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			1200, 10, //x,y positin 
			70, 20,	//Width height
			 Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndLabek_Z, TEXT("Z: Profile"));

		hWndEdit_ZMin = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			1200, 30, //x,y positin 
			70, 20,	//Width height
			 Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndEdit_ZMin, TEXT("0.0"));

		hWndEdit_ZMax = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			1200, 50, //x,y positin 
			70, 20,	//Width height
			 Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndEdit_ZMax, TEXT("20.0"));

		hWndEdit_ZScala = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			1200, 70, //x,y positin 
			70, 20,	//Width height
			 Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		SetWindowText(hWndEdit_ZScala, TEXT("1.0"));

		hWndCoord_X_MINUS = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"- X",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			1300,         // x position 
			10,         // y position 
			50,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_CORRD_X_MINUS,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hWndCoord_Y_MINUS = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"- Y",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			1370,         // x position 
			10,         // y position 
			50,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_CORRD_Y_MINUS,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hWndCoord_Z_MINUS = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"- Z",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			1440,         // x position 
			10,         // y position 
			50,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_CORRD_Z_MINUS,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hWndCoord_X_PLUS = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"+ X",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			1300,         // x position 
			70,         // y position 
			50,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_CORRD_X_PLUS,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hWndCoord_Y_PLUS = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"+ Y",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			1370,         // x position 
			70,         // y position 
			50,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_CORRD_Y_PLUS,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hWndCoord_Z_PLUS = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"+ Z",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			1440,         // x position 
			70,         // y position 
			50,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_CORRD_Z_PLUS,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hWndCoord_BandWidtTitel = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("Band Width"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			900, 100, //x,y positin 
			100, 20,	//Width height
			Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);
		// SetWindowText(hWndEdit_XScala, TEXT("Band Width"));

		hWndCoord_BandWidtValue = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("1.0"),
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT,
			900, 120, //x,y positin 
			100, 20,	//Width height
			Wnd, (HMENU)(int)IDC_PROFILEDISTANCE, NULL, NULL);

		hWndBtn_DisplayBand = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Display Band",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			900,         // x position 
			160,         // y position 
			100,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_DISPLAYBAND,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		hWndBtn_DisplayPlane = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Display Plane",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			1010,         // x position 
			160,         // y position 
			100,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_DISPLAYPLANE,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		hWndBtn_DisplayLine = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Display Profile",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			1120,         // x position 
			160,         // y position 
			100,        // Button width
			50,        // Button height
			Wnd,     // Parent window
			(HMENU)(int)IDC_DISPLAYPROFILE,       // No menu.
			(HINSTANCE)GetWindowLong(Wnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
	}
	break;

	case WM_DESTROY: {											// WM_DESTROY MESSAGE
																// We need to do some cleanups as program is going to exit	
		wglMakeCurrent(NULL, NULL);							// Make the rendering context not current 
		GLDATABASE* db = (GLDATABASE*)GetProp(Wnd, DATABASE_PROPERTY); // Fetch the data base
		if (db != 0) {
			if (db->Rc != 0) wglDeleteContext(db->Rc);		// If valid rendering context delete it
			if (db->glTexture != 0)
				glDeleteTextures(1, &db->glTexture);		// If valid gltexture delete it
			free(db);										// Release the data structure memory itself
		}
		PostQuitMessage(0);									// Post quit message
	}
	break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case IDC_PTPLOAD: {                                 // LOAD PTP-File COMMAND
			TCHAR FileName[256];
			int i = OpenFileDialog(&FileName[0], _countof(FileName),
				_T("PTP file:"), _T("PTP"), _T("PTP FILE TO LOAD"), Wnd);
			if (i != 0) {
				// Fetch that childs data base

				ReadSensorFile_PTP(&FileName[0]);
				InvalidateRect(Wnd, 0, TRUE);	// Force redraw of window
			}
		}
		break;



		case IDC_EXIT:										// EXIT COMMAND
			PostMessage(Wnd, WM_CLOSE, 0, 0);				// Post close message 
			break;



		case IDC_TIMERSTART: {							// Menu item: Timer-->Start timer
			SetTimer(Wnd,								// handle to main window 
				1,										// timer identifier 
				100,									// 100 ms interval 
				0);										// timer callback null
		}
		break;



		case IDC_TIMERSTOP: {							// Menu item: Timer-->Stop timer
			KillTimer(Wnd, 1);							// Kill the timer
		}

		//-----------Begin View configuration-------------------------------------------------------
		case IDC_BUTTONPLUS: {
			GLDATABASE* db = (GLDATABASE*)GetProp(Wnd, DATABASE_PROPERTY);// Fetch the data base
			//db->xrot += 5.0f;									// Inc x rotation
			db->yrot += 5.0f;									// Inc y rotation
			//db->zrot += 5.0f;									// Inc z rotation
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;

		case IDC_BUTTONMINUS: {
			GLDATABASE* db = (GLDATABASE*)GetProp(Wnd, DATABASE_PROPERTY);// Fetch the data base
			//db->xrot -= 5.0f;									// Inc x rotation
			db->yrot -= 5.0f;									// Inc y rotation
			//db->zrot -= 5.0f;									// Inc z rotation
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;
		//-------------End View Configuration-------------------------------------------
		//-------------NULL-Point-------------------------------------------------------
		case IDC_CORRD_X_MINUS: {
			X = X - 10;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;
		case IDC_CORRD_Y_MINUS: {
			Y = Y - 10;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;
		case IDC_CORRD_Z_MINUS: {
			Z = Z - 10;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;


		case IDC_CORRD_X_PLUS: {
			X = X + 10;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;
		case IDC_CORRD_Y_PLUS: {
			Y = Y + 10;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;
		case IDC_CORRD_Z_PLUS: {
			Z = Z + 10;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;
		
		//-------------END NULL POINT---------------------------------------------------


		//----------- Begin Profile Configuration---------------------------------------
		case IDC_PROFILEDISTANCE: {
			 	
		}
		break;
		case IDC_DISPLAYBAND: {
			if (DisplayBand)
				DisplayBand = FALSE;
			else
				DisplayBand = TRUE;
			InvalidateRect(Wnd, 0, TRUE);
		}
		break;
		case IDC_DISPLAYPLANE: {
			if (DisplayPlane)
				DisplayPlane = FALSE;
			else
				DisplayPlane = TRUE;
			InvalidateRect(Wnd, 0, TRUE);
		}
		break;
		case IDC_DISPLAYPROFILE: {
			if (DisplayProfile)
				DisplayProfile = FALSE;
			else
				DisplayProfile = TRUE;

			InvalidateRect(Wnd, 0, TRUE);
		}
		break;


		case IDC_PROFILEWIDTH: {
			if (IncreaseProfileWidth)
			{
				IncreaseProfileWidth = FALSE;
				ProfileWidth = 10.0f;
			}
			else {
				IncreaseProfileWidth = TRUE;
				ProfileWidth = 1.0f;
			}
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us
		}
		 break;


		case IDC_PROFILESCALE: {
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us
		}
		break;


		case IDC_PROFILE_1_DISPLAY: {
			if(DisplayProfil_1)
				DisplayProfil_1 = FALSE;
			else
				DisplayProfil_1 = TRUE;

			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;


		case IDC_PROFILE_2_DISPLAY: {
			if (DisplayProfil_2)
				DisplayProfil_2 = FALSE;
			else
				DisplayProfil_2 = TRUE;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break; 


		case IDC_PROFILE_3_DISPLAY: {
			if (DisplayProfil_3)
				DisplayProfil_3 = FALSE;
			else
				DisplayProfil_3 = TRUE;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;


		case IDC_PROFILE_4_DISPLAY: {
			if (DisplayProfil_4)
				DisplayProfil_4 = FALSE;
			else
				DisplayProfil_4 = TRUE;

			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;


		case IDC_PROFILE_5_DISPLAY: {
			if (DisplayProfil_5)
				DisplayProfil_5 = FALSE;
			else
				DisplayProfil_5 = TRUE;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;


		case IDC_PROFILE_6_DISPLAY: {
			if (DisplayProfil_6)
				DisplayProfil_6 = FALSE;
			else
				DisplayProfil_6 = TRUE;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;


		case IDC_PROFILE_7_DISPLAY: {
			if (DisplayProfil_7)
				DisplayProfil_7 = FALSE;
			else
				DisplayProfil_7 = TRUE;

			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;


		case IDC_PROFILE_8_DISPLAY: {
			if (DisplayProfil_8)
				DisplayProfil_8 = FALSE;
			else
				DisplayProfil_8 = TRUE;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;


		case IDC_PROFILE_9_DISPLAY: {
			if (DisplayProfil_9)
				DisplayProfil_9 = FALSE;
			else
				DisplayProfil_9 = TRUE;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;


		case IDC_BACKGROUND_DISPLAY: {
			if (DisplayBackground)
				DisplayBackground = FALSE;
			else
				DisplayBackground = TRUE;
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us	
		}
		break;
						
		//----------End Profile configuration-----------------------------------------------
								  
							  
		};
		break;


	case WM_PAINT: {											// WM_PAINT MESSAGE
		PAINTSTRUCT Ps;
		GLDATABASE* db = (GLDATABASE*)GetProp(Wnd, DATABASE_PROPERTY);// Fetch the data base
		BeginPaint(Wnd, &Ps);								// Begin paint
		DrawGLScene(db, Ps.hdc);							// Draw the OpenGL scene
		SwapBuffers(Ps.hdc);								// Swap buffers
		EndPaint(Wnd, &Ps);									// End paint
		return 0;
	}
	break;


	case WM_TIMER: {											// WM_TIMER MESSAGE
		GLDATABASE* db = (GLDATABASE*)GetProp(Wnd, DATABASE_PROPERTY);// Fetch the data base
		db->xrot += 1.0f;									// Inc x rotation
		db->yrot += 1.0f;									// Inc y rotation
		InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us			
	}
	break;


	case WM_WINDOWPOSCHANGED:									// WM_WINDOWPOSCHANGED
																// Check if window size has changed .. window move doesnt change aspect ratio
		if ((lParam == 0) || ((((PWINDOWPOS)lParam)->flags & SWP_NOSIZE) == 0)) {
			ReSizeGLScene(Wnd);									// Rescale the GL window							
			InvalidateRect(Wnd, 0, TRUE);						// We need a redraw now so invalidate us
		}
	break;


	case WM_ERASEBKGND:											// WM_ERASEBKGND MESSAGE
		return (FALSE);
	default: return DefWindowProc(Wnd, Msg, wParam, lParam);	// Default handler
	};// end switch case
	return 0;
};


 void ReadPTPDataFromPTPFile(TCHAR* FileName )
{
	HANDLE hFile;
	DWORD  dwBytesRead = 0;
	char   ReadBuffer[BUFFERSIZE] = { 0 };
	OVERLAPPED ol = { 0 };
	
	printf("\n");	

	hFile = CreateFile(FileName,               // file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING,         // existing file only
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // normal file
		NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE)
	{
		//DisplayError(TEXT("CreateFile"));
		_tprintf(TEXT("Terminal failure: unable to open file \"%s\" for read.\n"), FileName);
		return;
	}

	// Read one character less than the buffer size to save room for
	// the terminating NULL character. 
	 
	if (FALSE == ReadFileEx(hFile, ReadBuffer, BUFFERSIZE - 1, &ol, FileIOCompletionRoutine))
	{
		//DisplayError(TEXT("ReadFile"));
		printf("Terminal failure: Unable to read from file.\n GetLastError=%08x\n", GetLastError());
		CloseHandle(hFile);
		return;
	}
	SleepEx(5000, TRUE);
	dwBytesRead = g_BytesTransferred;
	// This is the section of code that assumes the file is ANSI text. 
	// Modify this block for other data types if needed.

	if (dwBytesRead > 0 && dwBytesRead <= BUFFERSIZE - 1)
	{
		ReadBuffer[dwBytesRead] = '\0'; // NULL character

		_tprintf(TEXT("Data read from %s (%d bytes): \n"), FileName, dwBytesRead);
		printf("%s\n", ReadBuffer);
	}
	else if (dwBytesRead == 0)
	{
		_tprintf(TEXT("No data read from file %s\n"), FileName);
	}
	else
	{
		printf("\n ** Unexpected value for dwBytesRead ** \n");
	}

	// It is always good practice to close the open file handles even though
	// the app will exit here and clean up open handles anyway.
	
	CloseHandle(hFile);
}

 void ReadFilePTP(TCHAR* FileName)
 {
	 HANDLE hout;
	 TCHAR buff2[BUF_SIZE] = { 'a','v' };
	 BOOL bResult = FALSE;

//	 TCHAR inBuffer[BUF_SIZE];
	 DWORD nBytesToRead = BUF_SIZE;
	 hout = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	 if (hout == INVALID_HANDLE_VALUE)
	 {
		 
	 }
	 DWORD nRead;
	 bResult=ReadFile(hout, buff2, nBytesToRead, &nRead, NULL);


	 if (bResult &&  nBytesToRead == 0)
	 {
//		 DWORD text = buff2;
	 }
	 else
	 {
//		 DWORD text = buff2;
	 }

	 CloseHandle(hout);
 }

 BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR pszFileName)
 {
	 HANDLE hFile;
	 BOOL bSuccess = FALSE;

	 hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	 if (hFile != INVALID_HANDLE_VALUE)
	 {
		 DWORD dwFileSize;
		 dwFileSize = GetFileSize(hFile, NULL);
		 if (dwFileSize != 0xFFFFFFFF)
		 {
			 LPTSTR pszFileText;
			 pszFileText = (LPTSTR)GlobalAlloc(GPTR, dwFileSize + 1);
			 if (pszFileText != NULL)
			 {
				 TCHAR buffer[437];
				 DWORD dwBytesRead;
				 BOOL bSuccess = ReadFile(hFile, &buffer, 436, &dwBytesRead, NULL);
				 buffer[436] = 0; //"\0";
				 if( SetWindowText(hEdit, buffer))
					 bSuccess = TRUE; // It worked!

				 if (!bSuccess)
				 {
					 //dwErrorCode = GetLastError();
				 }
				 while (bSuccess && dwBytesRead) // Hier sollen wir die Datei Zeile für Zeile lesen und  ListOfPTPData befühlen.
				 {
					 bSuccess = ReadFile(hFile, &buffer, 436, &dwBytesRead, NULL);
				 }				

				 //DWORD dwRead;
				 //if (ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
				 //{
					// pszFileText[dwFileSize] = 0; // Add null terminator
					// if (SetWindowText(hEdit, pszFileText))
					//	 bSuccess = TRUE; // It worked!
				 //}
				 GlobalFree(pszFileText);
			 }
		 }
		 CloseHandle(hFile);
	 }
	 return bSuccess;
 }

 BOOL LoadFileAndRetrieveProfile(HWND hEdit, LPCTSTR pszFileName)
 {
	 HANDLE hFile;
	 BOOL bSuccess = FALSE;
	 hFile = CreateFile(pszFileName, GENERIC_READ,
		 FILE_SHARE_READ, NULL,
		 OPEN_EXISTING, 0, NULL);
	 if (hFile != INVALID_HANDLE_VALUE)
	 {
		 DWORD dwFileSize;
		 LPTSTR pszFileText;
		 LPTSTR psHeader; //771 DWORD = 1542Bytes

		 dwFileSize = GetFileSize(hFile, NULL);
		 pszFileText = (TCHAR *)GlobalAlloc(GPTR, dwFileSize + 1);
		 psHeader = (TCHAR *)GlobalAlloc(GPTR, 218);
		 if (pszFileText != NULL)
		 {
			 DWORD dwRead;
			 if (ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
			 {
				 pszFileText[dwFileSize] = '\0';
				 for (int t = 0; t < 128; t++)
				 {
					 //test(pszFileText);
					 psHeader[t] = pszFileText[t];
				 }
				 //psHeader = pszFileText;
				 //test(pszFileText);
				 if (SetWindowText(hEdit, psHeader))
					 bSuccess = TRUE;
			 }
			 GlobalFree(pszFileText);
		 }
	 }
	 return bSuccess;
 }

/* ------------------------------------------------------------------------
The application entry point
-----------------------------------------------------------------------*/
#pragma argsused
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG Msg;
	RECT R;
	HWND Wnd;
	WNDCLASSEX WndClass;

	memset(&WndClass, 0, sizeof(WNDCLASSEX));						// Clear the class record
	WndClass.cbSize = sizeof(WNDCLASSEX);							// Size of this record
	WndClass.style = CS_OWNDC;										// Class styles
	WndClass.lpfnWndProc = OpenGLDemoHandler;						// Handler for this class
	WndClass.cbClsExtra = 0;										// No extra class data
	WndClass.cbWndExtra = 0;										// No extra window data
	WndClass.hInstance = GetModuleHandle(NULL);						// This instance
	WndClass.hIcon = LoadIcon(0, IDI_APPLICATION);					// Set icon
	WndClass.hCursor = LoadCursor(0, IDC_ARROW);					// Set cursor
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	// Set background brush
	WndClass.lpszMenuName = NULL;									// No menu yet
	WndClass.lpszClassName = AppClassName;							// Set class name
	RegisterClassEx(&WndClass);										// Register the class
	GetClientRect(GetDesktopWindow(), &R);							// Get desktop area					
	Wnd = CreateWindowEx(0, AppClassName, _T("PTP 3D"),
		WS_VISIBLE | WS_OVERLAPPEDWINDOW, R.left + 50, R.top + 50,
		R.right - R.left - 10, R.bottom - R.top - 100,
		0, 0, 0, NULL);												// Create a window
	while (GetMessage(&Msg, 0, 0, 0)) {								// Get messages
		TranslateMessage(&Msg);										// Translate each message
		DispatchMessage(&Msg);										// Dispatch each message
	};
	return (0);
}

