#define WINNER 0x601
#include <afxwin.h>
#include <gl/Gl.h>

int angelX = 0;
int angelY = 0;
int angelZ = 0;

class MyPoint {
public:
	float x, y, z;
	MyPoint(float in_x, float in_y, float in_z) { x = in_x; y = in_y; z = in_z; }
};

// ласс приложени€
class MyApp : public CWinApp {
	virtual BOOL InitInstance();
};

MyApp app;	//глобальный объект приложени€

// ласс окна

class MyWindow : public CFrameWnd {
	DECLARE_MESSAGE_MAP()
	HGLRC glRC;
	void OnPaint();
	void OnSize(UINT nType, int cx, int cy);
public:
	MyWindow() : glRC(NULL) { Create(NULL, L"openGl"); }
	~MyWindow() { wglDeleteContext(glRC); }
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

BEGIN_MESSAGE_MAP(MyWindow, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

BOOL MyApp::InitInstance() {
	m_pMainWnd = new MyWindow;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return(TRUE);
}

void MyWindow::OnSize(UINT nType, int cx,int cy) {
	//вызов метода базового класса
	CFrameWnd::OnSize(nType, cx, cy);
	if (glRC != NULL) wglDeleteContext(glRC);
	CDC* dc = GetDC();
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32
	};
	pfd.cDepthBits = 24;
	int pixelFormat = ChoosePixelFormat(*dc, &pfd);
	SetPixelFormat(*dc, pixelFormat, &pfd);

	glRC = wglCreateContext(*dc);
	ReleaseDC(dc);

	Invalidate(FALSE);
}

void MyWindow::OnPaint() {
	CPaintDC dc(this);

	wglMakeCurrent(dc, glRC);

	CRect r;
	GetClientRect(&r);
	int width = r.Width(), height = r.Height();
	if (width < height) glViewport(0, (height - width) / 2, width, width);
	else glViewport((width - height) / 2, 0, height, height);

	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
;
	MyPoint pA(-1, 1, -1);
	MyPoint pB(1, 1, -1);
	MyPoint pC(1, -1, -1);
	MyPoint pD(-1, -1, -1);

	MyPoint pE(-1, 1, 1);
	MyPoint pG(1, 1, 1);
	MyPoint pW(1, -1, 1);
	MyPoint pF(-1, -1, 1);
	
	glEnable(GL_CULL_FACE);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2, 2, -2, 2, 5,11);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0,-8);
	glRotatef(angelX, 1, 0, 0);
	glRotatef(angelY, 0, 1, 0);

	glBegin(GL_QUADS);//GL_POLYGON
		glColor3d(0, 0, 1); glVertex3d(pF.x, pF.y, pF.z);
		glColor3d(1, 0, 0); glVertex3d(pW.x, pW.y, pW.z);
		glColor3d(1, 1, 0); glVertex3d(pG.x, pG.y, pG.z);
		glColor3d(0, 1, 0); glVertex3d(pE.x, pE.y, pE.z);

		
		glColor3d(1, 0, 0); glVertex3d(pW.x, pW.y, pW.z);
		glColor3d(0, 0, 1); glVertex3d(pC.x, pC.y, pC.z);
		glColor3d(0, 1, 0); glVertex3d(pB.x, pB.y, pB.z);
		glColor3d(1, 1, 0); glVertex3d(pG.x, pG.y, pG.z);
		
		glColor3d(0, 0, 1); glVertex3d(pC.x, pC.y, pC.z);
		glColor3d(1, 0, 0); glVertex3d(pD.x, pD.y, pD.z);
		glColor3d(1, 1, 0); glVertex3d(pA.x, pA.y, pA.z);
		glColor3d(0, 1, 0); glVertex3d(pB.x, pB.y, pB.z);

		glColor3d(1, 0, 0); glVertex3d(pD.x, pD.y, pD.z);
		glColor3d(0, 0, 1); glVertex3d(pF.x, pF.y, pF.z);
		glColor3d(0, 1, 0); glVertex3d(pE.x, pE.y, pE.z);
		glColor3d(1, 1, 0); glVertex3d(pA.x, pA.y, pA.z);

		//¬ерхн€€ крыЎка
		glColor3d(0, 1, 0); glVertex3d(pE.x, pE.y, pE.z);
		glColor3d(1, 1, 0); glVertex3d(pG.x, pG.y, pG.z);
		glColor3d(0, 1, 0); glVertex3d(pB.x, pB.y, pB.z);
		glColor3d(1, 1, 0); glVertex3d(pA.x, pA.y, pA.z);

		//Ќижн€€ крыЎка
		glColor3d(0, 0, 1); glVertex3d(pF.x, pF.y, pF.z);
		glColor3d(1, 0, 0); glVertex3d(pD.x, pD.y, pD.z);
		glColor3d(0, 0, 1); glVertex3d(pC.x, pC.y, pC.z);
		glColor3d(1, 0, 0); glVertex3d(pW.x, pW.y, pW.z);
	glEnd();

	glFlush();
	SwapBuffers(dc);

	wglMakeCurrent(NULL, NULL);
}

void MyWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (nChar == VK_UP) angelX += 10;
	else if (nChar == VK_DOWN) angelX -= 10;
	else if (nChar == VK_RIGHT)angelY += 10;
	else if (nChar == VK_LEFT) angelY -= 10;

	Invalidate(FALSE);
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
