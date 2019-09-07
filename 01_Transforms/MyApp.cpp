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
	// törlési szín legyen kékes
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_CULL_FACE); // kapcsoljuk be a hatrafele nezo lapok eldobasat
	glEnable(GL_DEPTH_TEST); // mélységi teszt bekapcsolása (takarás)
	glCullFace(GL_BACK); // GL_BACK: a kamerától "elfelé" nézõ lapok, GL_FRONT: a kamera felé nézõ lapok

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
	// a frissen generált VAO beallitasa aktívnak
	glBindVertexArray(m_vaoID);

	// hozzunk létre egy új VBO erõforrás nevet
	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID); // tegyük "aktívvá" a létrehozott VBO-t
	// töltsük fel adatokkal az aktív VBO-t
	glBufferData(GL_ARRAY_BUFFER,	// az aktív VBO-ba töltsünk adatokat
		verticies.size() * sizeof(Vertex),		// ennyi bájt nagyságban
		&verticies[0],	// errõl a rendszermemóriabeli címrõl olvasva
		GL_STATIC_DRAW);	// úgy, hogy a VBO-nkba nem tervezünk ezután írni és minden kirajzoláskor felhasnzáljuk a benne lévõ adatokat


// VAO-ban jegyezzük fel, hogy a VBO-ban az elsõ 3 float sizeof(Vertex)-enként lesz az elsõ attribútum (pozíció)
	glEnableVertexAttribArray(0); // ez lesz majd a pozíció
	glVertexAttribPointer(
		0,				// a VB-ben található adatok közül a 0. "indexû" attribútumait állítjuk be
		3,				// komponens szam
		GL_FLOAT,		// adatok tipusa
		GL_FALSE,		// normalizalt legyen-e
		sizeof(Vertex),	// stride (0=egymas utan)
		0				// a 0. indexû attribútum hol kezdõdik a sizeof(Vertex)-nyi területen belül
	);

	// a második attribútumhoz pedig a VBO-ban sizeof(Vertex) ugrás után sizeof(glm::vec3)-nyit menve újabb 3 float adatot találunk (szín)
	glEnableVertexAttribArray(1); // ez lesz majd a szín
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

	glBindVertexArray(0); // feltöltüttük a VAO-t, kapcsoljuk le
	glBindBuffer(GL_ARRAY_BUFFER, 0); // feltöltöttük a VBO-t is, ezt is vegyük le
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//
	// shaderek betöltése
	//
	GLuint vs_ID = loadShader(GL_VERTEX_SHADER, "myVert.vert");
	GLuint fs_ID = loadShader(GL_FRAGMENT_SHADER, "myFrag.frag");

	// a shadereket tároló program létrehozása
	m_programID = glCreateProgram();

	// adjuk hozzá a programhoz a shadereket
	glAttachShader(m_programID, vs_ID);
	glAttachShader(m_programID, fs_ID);

	// VAO-beli attribútumok hozzárendelése a shader változókhoz
	// FONTOS: linkelés elõtt kell ezt megtenni!
	glBindAttribLocation(m_programID,	// shader azonosítója, amibõl egy változóhoz szeretnénk hozzárendelést csinálni
		0,				// a VAO-beli azonosító index
		"vs_in_pos");	// a shader-beli változónév
	glBindAttribLocation(m_programID, 1, "vs_in_col");

	// illesszük össze a shadereket (kimenõ-bemenõ változók összerendelése stb.)
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

		std::cout << "[app.Init()] Sáder Huba panasza: " << aSzoveg << std::endl;

		delete aSzoveg;
	}

	// mar nincs ezekre szukseg
	glDeleteShader(vs_ID);
	glDeleteShader(fs_ID);

	//
	// egyéb inicializálás
	//

	// vetítési mátrix létrehozása
	m_matProj = glm::perspective(45.0f, 640 / 480.0f, 1.0f, 1000.0f);

	// shader-beli transzformációs mátrixok címének lekérdezése
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
	// töröljük a frampuffert (GL_COLOR_BUFFER_BIT) és a mélységi Z puffert (GL_DEPTH_BUFFER_BIT)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// shader bekapcsolasa
	glUseProgram(m_programID);

	// shader parameterek beállítása
	/*

	GLM transzformációs mátrixokra példák:
		glm::rotate<float>( szög, glm::vec3(tengely_x, tengely_y, tengely_z) ) <- tengely_{xyz} körüli elforgatás
		glm::translate<float>( glm::vec3(eltol_x, eltol_y, eltol_z) ) <- eltolás
		glm::scale<float>( glm::vec3(s_x, s_y, s_z) ) <- léptékezés

	*/
	//m_matWorld = glm::mat4(1.0f);

	// majd küldjük át a megfelelõ mátrixokat!
	glUniformMatrix4fv(m_loc_world,// erre a helyre töltsünk át adatot
		1,			// egy darab mátrixot
		GL_FALSE,	// NEM transzponálva
		&(m_matWorld[0][0])); // innen olvasva a 16 x sizeof(float)-nyi adatot
	glUniformMatrix4fv(m_loc_view, 1, GL_FALSE, &(m_matView[0][0]));
	glUniformMatrix4fv(m_loc_proj, 1, GL_FALSE, &(m_matProj[0][0]));

	// kapcsoljuk be a VAO-t (a VBO jön vele együtt)
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

			glm::rotate<float>(SDL_GetTicks() / 1000.0f * (2 * M_PI) / 9, glm::vec3(0, 1, 0)) * // 9sec alatt menjen körbe
			glm::translate<float>(glm::vec3(8, 0, 0))* // 8 sugarú körtpálya
			glm::translate<float>(RandomPoints((float)random[i * 2], (float)random[i * 2 + 1])) * //kirajzolása az 5 kúpnak
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

// a két paraméterbe az új ablakméret szélessége (_w) és magassága (_h) található
void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h);

	m_matProj = glm::perspective(  45.0f,		// 90 fokos nyilasszog
									_w/(float)_h,	// ablakmereteknek megfelelo nezeti arany
									0.01f,			// kozeli vagosik
									100.0f);		// tavoli vagosik
}