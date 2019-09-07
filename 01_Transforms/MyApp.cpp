#include "MyApp.h"
#include "GLUtils.hpp"

#include <math.h>
#include<vector>
#include<ctime>

CMyApp::CMyApp(void)
{
	srand(time(NULL));

	m_vaoID = 0;
	m_vboID = 0;
	m_ibID = 0;
	m_programID = 0;
	for (size_t i = 0; i < 10; i++)
	{
		random[i] = rand() % 10000;
	}
	rotate = false;
}


CMyApp::~CMyApp(void)
{
}


glm::vec3 CMyApp::RandomPoints(float u, float v)
{
	u /= 10000.0f;
	v /= 10000.0f;
	u *= 2 * M_PI;
	v *= M_PI;

	float cu = cosf(u), su = sinf(u), cv = cosf(v), sv = sinf(v);
	float r = 5;

	/*std::cerr << "---------------" << std::endl;
	std::cerr << u * 180 / M_PI << " " << cu << " " << su << std::endl;
	std::cerr << v* 180 / M_PI << " " << cv << " " << sv << std::endl;*/

	return glm::vec3(r*cu*sv, r*cv, r*su*sv);
}

bool CMyApp::Init()
{
	// t�rl�si sz�n legyen k�kes
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_CULL_FACE); // kapcsoljuk be a hatrafele nezo lapok eldobasat
	glEnable(GL_DEPTH_TEST); // m�lys�gi teszt bekapcsol�sa (takar�s)
	glCullFace(GL_BACK); // GL_BACK: a kamer�t�l "elfel�" n�z� lapok, GL_FRONT: a kamera fel� n�z� lapok

	//
	// geometria letrehozasa
	//
	std::vector<Vertex> verticies;
	glm::vec3 colors[10];
	colors[0] = glm::vec3(1, 0, 0);
	colors[1] = glm::vec3(0, 1, 0);
	colors[2] = glm::vec3(0, 0, 1);
	colors[3] = glm::vec3(0, 1, 1);
	colors[4] = glm::vec3(1, 0.5f, 0);
	colors[5] = glm::vec3(1, 1, 0);
	colors[6] = glm::vec3(0.5f, 0, 1);
	colors[7] = glm::vec3(0.5f, 0.5f, 1);
	colors[8] = glm::vec3(0.5f, 1, 0.5f);
	colors[9] = glm::vec3(0.5f, 0.5f, 0.5f);

	verticies.push_back({ glm::vec3(0, 0, 0), glm::vec3(1, 1, 0) });
	for (int i = 9; i >= 0; --i) {
		verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * i) * 1.5, 0, cos(2 * M_PI / 9 * i) * 1.5) , colors[i] });
	}
	verticies.push_back({ glm::vec3(0,  0.5, 0), glm::vec3(1, 1, 1) });
	//-----------------------------------------------------------------------

	GLushort indices[] =
	{
		10,9,11,
		9,8,11,
		8,7,11,
		7,6,11,
		6,5,11,
		5,4,11,
		4,3,11,
		3,2,11,
		2,1,11,
	};

	/*verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 0) * 1.5, 0, cos(2 * M_PI / 9 * 0) * 1.5), glm::vec3(1, 0, 0) });
	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 1) * 1.5, 0, cos(2 * M_PI / 9 * 1) * 1.5), glm::vec3(1, 1, 0) });
	verticies.push_back({ glm::vec3(0,  0.5, 0), glm::vec3(1, 0, 1) });

	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 1) * 1.5, 0, cos(2 * M_PI / 9 * 1) * 1.5), glm::vec3(1, 0, 1) });
	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 2) * 1.5, 0, cos(2 * M_PI / 9 * 2) * 1.5), glm::vec3(1, 1, 0) });
	verticies.push_back({ glm::vec3(0,  0.5, 0), glm::vec3(1, 0, 1) });

	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 2) * 1.5, 0, cos(2 * M_PI / 9 * 2) * 1.5), glm::vec3(0, 1, 0) });
	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 3) * 1.5, 0, cos(2 * M_PI / 9 * 3) * 1.5), glm::vec3(1, 1, 0) });
	verticies.push_back({ glm::vec3(0,  0.5, 0), glm::vec3(1, 0, 1) });

	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 3) * 1.5, 0, cos(2 * M_PI / 9 * 3) * 1.5), glm::vec3(1, 0, 0) });
	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 4) * 1.5, 0, cos(2 * M_PI / 9 * 4) * 1.5), glm::vec3(1, 1, 1) });
	verticies.push_back({ glm::vec3(0,  0.5, 0), glm::vec3(1, 0, 1) });

	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 4) * 1.5, 0, cos(2 * M_PI / 9 * 4) * 1.5), glm::vec3(0, 1, 1) });
	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 5) * 1.5, 0, cos(2 * M_PI / 9 * 5) * 1.5), glm::vec3(1, 1, 0) });
	verticies.push_back({ glm::vec3(0,  0.5, 0), glm::vec3(1, 0, 1) });

	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 5) * 1.5, 0, cos(2 * M_PI / 9 * 5) * 1.5), glm::vec3(0, 1, 0) });
	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 6) * 1.5, 0, cos(2 * M_PI / 9 * 6) * 1.5), glm::vec3(1, 1, 0) });
	verticies.push_back({ glm::vec3(0,  0.5, 0), glm::vec3(1, 0, 1) });

	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 6) * 1.5, 0, cos(2 * M_PI / 9 * 6) * 1.5), glm::vec3(1, 1, 1) });
	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 7) * 1.5, 0, cos(2 * M_PI / 9 * 7) * 1.5), glm::vec3(1, 1, 0) });
	verticies.push_back({ glm::vec3(0,  0.5, 0), glm::vec3(1, 0, 1) });

	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 7) * 1.5, 0, cos(2 * M_PI / 9 * 7) * 1.5), glm::vec3(1, 0, 1) });
	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 8) * 1.5, 0, cos(2 * M_PI / 9 * 8) * 1.5), glm::vec3(1, 0, 1) });
	verticies.push_back({ glm::vec3(0,  0.5, 0), glm::vec3(1, 0, 1) });

	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 8) * 1.5, 0, cos(2 * M_PI / 9 * 8) * 1.5), glm::vec3(1, 1, 1) });
	verticies.push_back({ glm::vec3(sin(2 * M_PI / 9 * 9) * 1.5, 0, cos(2 * M_PI / 9 * 9) * 1.5), glm::vec3(1, 1, 1) });
	verticies.push_back({ glm::vec3(0,  0.5, 0), glm::vec3(1, 0, 1) });*/


	// 1 db VAO foglalasa
	glGenVertexArrays(1, &m_vaoID);
	// a frissen gener�lt VAO beallitasa akt�vnak
	glBindVertexArray(m_vaoID);

	// hozzunk l�tre egy �j VBO er�forr�s nevet
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID); // tegy�k "akt�vv�" a l�trehozott VBO-t
	// t�lts�k fel adatokkal az akt�v VBO-t
	glBufferData(GL_ARRAY_BUFFER,	// az akt�v VBO-ba t�lts�nk adatokat
		verticies.size() * sizeof(Vertex),		// ennyi b�jt nagys�gban
		&verticies[0],	// err�l a rendszermem�riabeli c�mr�l olvasva
		GL_STATIC_DRAW);	// �gy, hogy a VBO-nkba nem tervez�nk ezut�n �rni �s minden kirajzol�skor felhasnz�ljuk a benne l�v� adatokat


// VAO-ban jegyezz�k fel, hogy a VBO-ban az els� 3 float sizeof(Vertex)-enk�nt lesz az els� attrib�tum (poz�ci�)
	glEnableVertexAttribArray(0); // ez lesz majd a poz�ci�
	glVertexAttribPointer(
		0,				// a VB-ben tal�lhat� adatok k�z�l a 0. "index�" attrib�tumait �ll�tjuk be
		3,				// komponens szam
		GL_FLOAT,		// adatok tipusa
		GL_FALSE,		// normalizalt legyen-e
		sizeof(Vertex),	// stride (0=egymas utan)
		0				// a 0. index� attrib�tum hol kezd�dik a sizeof(Vertex)-nyi ter�leten bel�l
	);

	// a m�sodik attrib�tumhoz pedig a VBO-ban sizeof(Vertex) ugr�s ut�n sizeof(glm::vec3)-nyit menve �jabb 3 float adatot tal�lunk (sz�n)
	glEnableVertexAttribArray(1); // ez lesz majd a sz�n
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(sizeof(glm::vec3)));

	glGenBuffers(1, &m_ibID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0); // felt�lt�tt�k a VAO-t, kapcsoljuk le
	glBindBuffer(GL_ARRAY_BUFFER, 0); // felt�lt�tt�k a VBO-t is, ezt is vegy�k le
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//
	// shaderek bet�lt�se
	//
	GLuint vs_ID = loadShader(GL_VERTEX_SHADER, "myVert.vert");
	GLuint fs_ID = loadShader(GL_FRAGMENT_SHADER, "myFrag.frag");

	// a shadereket t�rol� program l�trehoz�sa
	m_programID = glCreateProgram();

	// adjuk hozz� a programhoz a shadereket
	glAttachShader(m_programID, vs_ID);
	glAttachShader(m_programID, fs_ID);

	// VAO-beli attrib�tumok hozz�rendel�se a shader v�ltoz�khoz
	// FONTOS: linkel�s el�tt kell ezt megtenni!
	glBindAttribLocation(m_programID,	// shader azonos�t�ja, amib�l egy v�ltoz�hoz szeretn�nk hozz�rendel�st csin�lni
		0,				// a VAO-beli azonos�t� index
		"vs_in_pos");	// a shader-beli v�ltoz�n�v
	glBindAttribLocation(m_programID, 1, "vs_in_col");

	// illessz�k �ssze a shadereket (kimen�-bemen� v�ltoz�k �sszerendel�se stb.)
	glLinkProgram(m_programID);

	// linkeles ellenorzese
	GLint infoLogLength = 0, result = 0;

	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (GL_FALSE == result)
	{
		std::vector<char> ProgramErrorMessage(infoLogLength);
		glGetProgramInfoLog(m_programID, infoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

		char* aSzoveg = new char[ProgramErrorMessage.size()];
		memcpy(aSzoveg, &ProgramErrorMessage[0], ProgramErrorMessage.size());

		std::cout << "[app.Init()] S�der Huba panasza: " << aSzoveg << std::endl;

		delete aSzoveg;
	}

	// mar nincs ezekre szukseg
	glDeleteShader(vs_ID);
	glDeleteShader(fs_ID);

	//
	// egy�b inicializ�l�s
	//

	// vet�t�si m�trix l�trehoz�sa
	m_matProj = glm::perspective(45.0f, 640 / 480.0f, 1.0f, 1000.0f);

	// shader-beli transzform�ci�s m�trixok c�m�nek lek�rdez�se
	m_loc_world = glGetUniformLocation(m_programID, "world");
	m_loc_view = glGetUniformLocation(m_programID, "view");
	m_loc_proj = glGetUniformLocation(m_programID, "proj");

	return true;
}

void CMyApp::Clean()
{
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);

	glDeleteProgram( m_programID );
}

void CMyApp::Update()
{
	m_matView = glm::lookAt(glm::vec3(0, 10, 20),
							glm::vec3( 0,  0,  0),		
							glm::vec3( 0,  1,  0));
}


void CMyApp::Render()
{
	// t�r�lj�k a frampuffert (GL_COLOR_BUFFER_BIT) �s a m�lys�gi Z puffert (GL_DEPTH_BUFFER_BIT)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// shader bekapcsolasa
	glUseProgram(m_programID);

	// shader parameterek be�ll�t�sa
	/*

	GLM transzform�ci�s m�trixokra p�ld�k:
		glm::rotate<float>( sz�g, glm::vec3(tengely_x, tengely_y, tengely_z) ) <- tengely_{xyz} k�r�li elforgat�s
		glm::translate<float>( glm::vec3(eltol_x, eltol_y, eltol_z) ) <- eltol�s
		glm::scale<float>( glm::vec3(s_x, s_y, s_z) ) <- l�pt�kez�s

	*/
	//m_matWorld = glm::mat4(1.0f);

	// majd k�ldj�k �t a megfelel� m�trixokat!
	glUniformMatrix4fv(m_loc_world,// erre a helyre t�lts�nk �t adatot
		1,			// egy darab m�trixot
		GL_FALSE,	// NEM transzpon�lva
		&(m_matWorld[0][0])); // innen olvasva a 16 x sizeof(float)-nyi adatot
	glUniformMatrix4fv(m_loc_view, 1, GL_FALSE, &(m_matView[0][0]));
	glUniformMatrix4fv(m_loc_proj, 1, GL_FALSE, &(m_matProj[0][0]));

	// kapcsoljuk be a VAO-t (a VBO j�n vele egy�tt)
	glBindVertexArray(m_vaoID);

	/*glDrawArrays(GL_TRIANGLE_FAN, 0, 11);
	glDrawElements(GL_TRIANGLES,
		27,					// hany csucspontot hasznalunk a kirajzolashoz
		GL_UNSIGNED_SHORT,	// indexek tipusa
		0);					// indexek cime*/
		//glDrawArrays(GL_TRIANGLES, 11, 27);				

	for (int i = 0; i < 5; ++i) {
		glm::mat4 extra = glm::mat4(1); //egysegmatrix
		float x = (sin((SDL_GetTicks() - tick) / 1000.0f * (2 * M_PI) / 6) * 0.75) + 1.25;
		if (rotate) {
			extra = glm::scale<float>(glm::vec3(x, 1, 1));
		}

		m_matWorld =

			glm::rotate<float>(SDL_GetTicks() / 1000.0f * (2 * M_PI) / 9, glm::vec3(0, 1, 0)) * // 9sec alatt menjen k�rbe
			glm::translate<float>(glm::vec3(8, 0, 0))* // 8 sugar� k�rtp�lya
			glm::translate<float>(RandomPoints((float)random[i * 2], (float)random[i * 2 + 1])) * //kirajzol�sa az 5 k�pnak
			extra; //scale


		glUniformMatrix4fv(m_loc_world, 1, GL_FALSE, &(m_matWorld[0][0]));
		glDrawArrays(GL_TRIANGLE_FAN, 0, 11);
		glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_SHORT, 0);
		//glDrawArrays(GL_TRIANGLES, 11, 27);
	}

	// VAO kikapcsolasa
	glBindVertexArray(0);

	// shader kikapcsolasa
	glUseProgram(0);
}

void CMyApp::KeyboardDown(SDL_KeyboardEvent& key)
{
	if (key.keysym.sym == SDLK_SPACE) {
		rotate = true;
		tick = SDL_GetTicks();

	}
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent& key)
{
}

void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse)
{

}

void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

// a k�t param�terbe az �j ablakm�ret sz�less�ge (_w) �s magass�ga (_h) tal�lhat�
void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h);

	m_matProj = glm::perspective(  45.0f,		// 90 fokos nyilasszog
									_w/(float)_h,	// ablakmereteknek megfelelo nezeti arany
									0.01f,			// kozeli vagosik
									100.0f);		// tavoli vagosik
}