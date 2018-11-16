#include "main.h"

vec3 camera = vec3(0,0,20);
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitContextVersion(4,3);//以OpenGL version4.3版本為基準
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);//是否向下相容,GLUT_FORWARD_COMPATIBLE不支援(?
	glutInitContextProfile(GLUT_CORE_PROFILE);

	//multisample for golygons smooth
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL 4.3 - Robot");

	glewExperimental = GL_TRUE; //置於glewInit()之前
	if (glewInit()) {
		std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;//c error
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(Keyboard);
	int ActionMenu,ModeMenu,ShaderMenu;
	ActionMenu = glutCreateMenu(ActionMenuEvents);//建立右鍵菜單
	//加入右鍵物件
	glutAddMenuEntry("idle",0);
	glutAddMenuEntry("walk",1);
	glutAddMenuEntry("dance", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯

	ModeMenu = glutCreateMenu(ModeMenuEvents);//建立右鍵菜單
	//加入右鍵物件
	glutAddMenuEntry("Line",0);
	glutAddMenuEntry("Fill",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯

	ShaderMenu = glutCreateMenu(ShaderMenuEvents);//建立右鍵菜單
	//加入右鍵物件
	glutAddMenuEntry("Base", BASE);
	glutAddMenuEntry("Gray", GRAY);
	glutAddMenuEntry("Negative", NEGATIVE);
	glutAddMenuEntry("Dither", DITHER);
	glutAddMenuEntry("Blur", BLUR);
	glutAddMenuEntry("Mosaic", MOSAIC);
	glutAddMenuEntry("Curve", CURVE);
	glutAddMenuEntry("7", 7);
	glutAddMenuEntry("8", 8);
	glutAddMenuEntry("9", 9);
	glutAddMenuEntry("10", 10);
	glutAddMenuEntry("11", 11);
	glutAddMenuEntry("12", 12);
	glutAddMenuEntry("13", 13);
	glutAddMenuEntry("14", 14);
	glutAddMenuEntry("15", 15);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutCreateMenu(menuEvents);//建立右鍵菜單
	//加入右鍵物件
	glutAddSubMenu("action",ActionMenu);
	glutAddSubMenu("mode",ModeMenu);
	glutAddSubMenu("shader", ShaderMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯

	glutMouseFunc(Mouse);
	glutTimerFunc (75, idle, 0); 
	glutMainLoop();
	return 0;
}
void ChangeSize(int w,int h){
	if(h == 0) h = 1;
	glViewport(0,0,w,h);
	Projection = perspective(80.0f,(float)w/h,0.1f,100.0f);

	/*
	glDeleteTextures(1, &textureColorbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, w, h);

	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);*/
}
void Mouse(int button,int state,int x,int y){
	if(button == 2) isFrame = false;
}
void idle(int dummy){
	isFrame = true;
	int out = 0;
	if (action == WALK) {
		walk(dummy);
		out = dummy + 1;
		if (out > 13) out = 0;
	}
	else if (action == IDLE) {
		resetObj(dummy);
		out = 0;
	}
	else if (action == DANCE) {
		dance(dummy);
		out = dummy + 1;
		if (out > 13) out = 0;
	}
	glutPostRedisplay();
	
	glutTimerFunc (75, idle, out); 
}

void resetObj(int f){
	for(int i = 0 ; i < PARTSNUM;i++)
		angles[i] = 0.0f;
	for (int i = 0; i < 4; i++)
		hand_rotate[i] = 0;
}

void walk(int frame){
	switch(frame){
	case 0:
		angles[5] = -55;
		angles[6] = 45;
		angles[7] = 45;
		angles[8] = -55;
		break;
	case 1:
		angles[5] = -45;
		angles[6] = 30;
		angles[7] = 30;
		angles[8] = -45;
		break;
	case 2:
		angles[5] = -30;
		angles[6] = 15;
		angles[7] = 15;
		angles[8] = -30;
		break;
	case 3:
		angles[5] = -15;
		angles[6] = 0;
		angles[7] = 0;
		angles[8] = -15;
		break;
	case 4:
		angles[5] = 0;
		angles[6] = -15;
		angles[7] = -15;
		angles[8] = 0;
		break;
	case 5:
		angles[5] = 15;
		angles[6] = -30;
		angles[7] = -30;
		angles[8] = 15;
		break;
	case 6:
		angles[5] = 30;
		angles[6] = -45;
		angles[8] = -45;
		angles[8] = 30;
		break;
	case 7:
		angles[5] = 45;
		angles[6] = -55;
		angles[8] = -55;
		angles[8] = 45;
		break;
	case 8:
		angles[5] = 30;
		angles[6] = -45;
		angles[7] = -45;
		angles[8] = 30;
		break;
	case 9:
		angles[5] = 15;
		angles[6] = -30;
		angles[7] = -30;
		angles[8] = 15;
		break;
	case 10:
		angles[5] = 0;
		angles[6] = -15;
		angles[7] = -15;
		angles[8] = 0;
		break;
	case 11:
		angles[5] = -15;
		angles[6] = 0;
		angles[7] = 0;
		angles[8] = -15;
		break;
	case 12:
		angles[5] = -30;
		angles[6] = 15;
		angles[7] = 15;
		angles[8] = -30;
		break;
	case 13:
		angles[5] = -45;
		angles[6] = 30;
		angles[7] = 30;
		angles[8] = -45;
		break;
	}
}
void dance(int frame) {

	switch (frame) {
	case 0:
		resetObj(1);
		angles[0] = -60;
		angles[1] = -30;
		angles[3] = 20;
		angles[5] = 50;
		hand_rotate[2] = -30;
		hand_rotate[3] = -30;
		break;
	case 1:
		angles[1] = -60;
		angles[3] = -15;
		angles[5] = 25;
		break;
	case 2:
		angles[3] = -30;
		hand_rotate[1] = -30;
		break;
	case 3:
		angles[3] = -60;
		break;
	case 4:
		angles[3] = -30;
		hand_rotate[1] = 0;
		break;
	case 5:
		angles[0] = -30;
		angles[1] = -30;
		angles[3] = -15;
		angles[5] = 15;
		break;
	case 6:
		angles[0] = 0;
		angles[1] = 0;
		angles[3] = 0;
		angles[5] = 0;
		hand_rotate[2] = 0;
		hand_rotate[3] = 0;
		break;
	case 7:
		angles[0] = 60;
		angles[1] = 30;
		angles[4] = 20;
		angles[6] = 50;
		hand_rotate[0] = -30;
		hand_rotate[1] = -30;
		break;
	case 8:
		angles[1] = 60;
		angles[4] = -15;
		angles[6] = 25;
		break;
	case 9:
		angles[4] = -30;
		hand_rotate[3] = -30;
		break;
	case 10:
		angles[4] = -60;
		break;
	case 11:
		angles[4] = -30;
		hand_rotate[3] = 0;
		break;
	case 12:
		angles[0] = -30;
		angles[1] = -30;
		angles[4] = -15;
		angles[6] = 15;
		break;
	case 13:
		angles[0] = 0;
		angles[1] = 0;
		angles[4] = 0;
		angles[6] = 0;
		hand_rotate[0] = 0;
		hand_rotate[1] = 0;
		break;
	}

}

 GLuint M_KaID;
 GLuint M_KdID;
 GLuint M_KsID;
 void initFBO() {
	 glGenFramebuffers(1, &framebuffer);
	 glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	 // create a color attachment texture

	 glGenTextures(1, &textureColorbuffer);
	 glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	 glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	 // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

	 glGenRenderbuffers(1, &renderbuffer);
	 glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	 glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600); // use a single renderbuffer object for both a depth AND stencil buffer.
	 glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer); // now actually attach it
																								   // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	 if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		 cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	 glBindFramebuffer(GL_FRAMEBUFFER, 0);
 }

 void initScreen() {

	 float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
							  // positions   // texCoords
		 -1.0f,  1.0f,  0.0f, 1.0f,
		 -1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		 -1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	 };

	 // screen quad VAO
	 glGenVertexArrays(1, &quadVAO);
	 glGenBuffers(1, &quadVBO);
	 glBindVertexArray(quadVAO);
	 glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	 glEnableVertexAttribArray(0);
	 glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	 glEnableVertexAttribArray(1);
	 glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

 }

 GLuint initShaders(string v,string f)
 {
	 ShaderInfo shaders[] = {
		 { GL_VERTEX_SHADER, v.c_str() },//vertex shader
		 { GL_FRAGMENT_SHADER, f.c_str() },//fragment shader
		 { GL_NONE, NULL } };
	return LoadShaders(shaders);//讀取shader
 }

void init(){
	isFrame = false;
	pNo = 0;
	for(int i = 0;i<PARTSNUM;i++)//初始化角度陣列
		angles[i] = 0.0;

	//VAO
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	program = initShaders("Shader/DSPhong_Material.vp", "Shader/DSPhong_Material.fp");

	programScreen[0] = initShaders("Shader/FBO_Screen.vs", "Shader/Base.fs");
	programScreen[1] = initShaders("Shader/FBO_Screen.vs", "Shader/gray.fs");
	programScreen[2] = initShaders("Shader/FBO_Screen.vs", "Shader/Negative.fs");
	programScreen[3] = initShaders("Shader/FBO_Screen.vs", "Shader/Dither.fs");
	programScreen[4] = initShaders("Shader/FBO_Screen.vs", "Shader/Blur.fs");
	programScreen[5] = initShaders("Shader/FBO_Screen.vs", "Shader/Mosaic.fs");
	programScreen[6] = initShaders("Shader/FBO_Screen.vs", "Shader/Curve.fs");
	glUseProgram(program);//uniform參數數值前必須先use shader
	
	MatricesIdx = glGetUniformBlockIndex(program,"MatVP");
	ModelID =  glGetUniformLocation(program,"Model");
    M_KaID = glGetUniformLocation(program,"Material.Ka");
	M_KdID = glGetUniformLocation(program,"Material.Kd");
	M_KsID = glGetUniformLocation(program,"Material.Ks");
	//or
	M_KdID = M_KaID+1;
	M_KsID = M_KaID+2;

	Projection = glm::perspective(80.0f,4.0f/3.0f,0.1f,100.0f);
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	View       = glm::lookAt(
		glm::vec3(0,10,25) , // Camera is at (0,10,25), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,1,0 to look upside-down)
		);

	Obj2Buffer();

	//UBO
	glGenBuffers(1,&UBO);
	glBindBuffer(GL_UNIFORM_BUFFER,UBO);
	glBufferData(GL_UNIFORM_BUFFER,sizeof(mat4)*2,NULL,GL_DYNAMIC_DRAW);
	//get uniform struct size
	int UBOsize = 0;
	glGetActiveUniformBlockiv(program, MatricesIdx, GL_UNIFORM_BLOCK_DATA_SIZE, &UBOsize);  
	//bind UBO to its idx
	glBindBufferRange(GL_UNIFORM_BUFFER,0,UBO,0,UBOsize);
	glUniformBlockBinding(program, MatricesIdx,0);

	initScreen();
	initFBO();
	glClearColor(0.0,0.0,0.0,1);//black screen

}

#define DOR(angle) (angle*3.1415/180);
void display(){
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	// make sure we clear the framebuffer's content
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(VAO);
	glUseProgram(program);//uniform參數數值前必須先use shader
	float eyey = DOR(eyeAngley);
	View       = lookAt(
		               vec3(eyedistance*sin(eyey),2,eyedistance*cos(eyey)) , // Camera is at (0,0,20), in World Space
		               vec3(0,0,0), // and looks at the origin
		               vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		                );
	updateModels();
	//update data to UBO for MVP
	glBindBuffer(GL_UNIFORM_BUFFER,UBO);
	glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(mat4),&View);
	glBufferSubData(GL_UNIFORM_BUFFER,sizeof(mat4),sizeof(mat4),&Projection);
	glBindBuffer(GL_UNIFORM_BUFFER,0);

	GLuint offset[3] = {0,0,0};//offset for vertices , uvs , normals
	for(int i = 0;i < PARTSNUM ;i++){
		glUniformMatrix4fv(ModelID,1,GL_FALSE,&Models[i][0][0]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,				//location
							  3,				//vec3
							  GL_FLOAT,			//type
							  GL_FALSE,			//not normalized
							  0,				//strip
							  (void*)offset[0]);//buffer offset
		//(location,vec3,type,固定點,連續點的偏移量,buffer point)
		offset[0] +=  vertices_size[i]*sizeof(vec3);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);//location 1 :vec2 UV
		glBindBuffer(GL_ARRAY_BUFFER, uVBO);
		glVertexAttribPointer(1, 
							  2, 
							  GL_FLOAT, 
							  GL_FALSE, 
							  0,
							  (void*)offset[1]);
		//(location,vec2,type,固定點,連續點的偏移量,point)
		offset[1] +=  uvs_size[i]*sizeof(vec2);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);//location 2 :vec3 Normal
		glBindBuffer(GL_ARRAY_BUFFER, nVBO);
		glVertexAttribPointer(2,
							  3, 
							  GL_FLOAT, 
							  GL_FALSE, 
							  0,
							  (void*)offset[2]);
		//(location,vec3,type,固定點,連續點的偏移量,point)
		offset[2] +=  normals_size[i]*sizeof(vec3);

		int vertexIDoffset = 0;	//glVertexID's offset 
		string mtlname;	//material name
		vec3 Ks = vec3(1,1,1);	//because .mtl excluding specular , so give it here.
		for(int j = 0;j <mtls[i].size() ;j++){//
			mtlname = mtls[i][j];	
			//find the material diffuse color in map:KDs by material name.
			glUniform3fv(M_KdID,1,&KDs[mtlname][0]);
			glUniform3fv(M_KsID,1,&Ks[0]);
			
			//          (primitive   , glVertexID base , vertex count    )
			glDrawArrays(GL_TRIANGLES, vertexIDoffset  , faces[i][j+1]*3);
			//we draw triangles by giving the glVertexID base and vertex count is face count*3
			vertexIDoffset += faces[i][j+1]*3;	//glVertexID's base offset is face count*3
		}	//end for loop for draw one part of the robot	
		
	}	//end for loop for updating and drawing model

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(programScreen[shader]);
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glFlush();	//強制執行上次的OpenGL commands
	glutSwapBuffers();	//調換前台和後台buffer ,當後臺buffer畫完和前台buffer交換使我們看見它
}

void Obj2Buffer(){
	std::vector<vec3> Kds;
	std::vector<vec3> Kas;
	std::vector<vec3> Kss;
	std::vector<std::string> Materials;//mtl-name
	std::string texture;
	loadMTL("Obj/body.mtl",Kds,Kas,Kss,Materials,texture);

	for(int i = 0;i<Materials.size();i++){
		string mtlname = Materials[i];
		//  name            vec3
		KDs[mtlname] = Kds[i];
	}

	
	load2Buffer("Obj/head.obj",0);
	load2Buffer("Obj/body.obj",1);
	load2Buffer("Obj/butt.obj",2);
	load2Buffer("Obj/arm_r.obj", 3);
	load2Buffer("Obj/arm_l.obj", 4);
	load2Buffer("Obj/hand_r.obj", 5);
	load2Buffer("Obj/hand_l.obj", 6);
	load2Buffer("Obj/leg_r.obj", 7);
	load2Buffer("Obj/leg_l.obj", 8);
	
	GLuint totalSize[3] = {0,0,0};
	GLuint offset[3] = {0,0,0};
	for(int i = 0;i < PARTSNUM ;i++){
		totalSize[0] += vertices_size[i]*sizeof(vec3);
		totalSize[1] += uvs_size[i] * sizeof(vec2);
		totalSize[2] += normals_size[i] * sizeof(vec3);
	}
	//generate vbo
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&uVBO);
	glGenBuffers(1,&nVBO);
	//bind vbo ,第一次bind也同等於 create vbo 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//VBO的target是GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER,totalSize[0],NULL,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uVBO);//VBO的target是GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER,totalSize[1],NULL,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, nVBO);//VBO的target是GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER,totalSize[2],NULL,GL_STATIC_DRAW);
	
	
	for(int i = 0;i < PARTSNUM ;i++){
		glBindBuffer(GL_COPY_WRITE_BUFFER,VBO);
		glBindBuffer(GL_COPY_READ_BUFFER, VBOs[i]);
		glCopyBufferSubData(GL_COPY_READ_BUFFER,GL_COPY_WRITE_BUFFER,0,offset[0],vertices_size[i]*sizeof(vec3));
		offset[0] += vertices_size[i]*sizeof(vec3);
		glInvalidateBufferData(VBOs[i]);//free vbo
		glBindBuffer(GL_COPY_WRITE_BUFFER,0);

		glBindBuffer(GL_COPY_WRITE_BUFFER,uVBO);
		glBindBuffer(GL_COPY_READ_BUFFER, uVBOs[i]);
		glCopyBufferSubData(GL_COPY_READ_BUFFER,GL_COPY_WRITE_BUFFER,0,offset[1],uvs_size[i]*sizeof(vec2));
		offset[1] += uvs_size[i]*sizeof(vec2);
		glInvalidateBufferData(uVBOs[i]);//free vbo
		glBindBuffer(GL_COPY_WRITE_BUFFER,0);

		glBindBuffer(GL_COPY_WRITE_BUFFER,nVBO);
		glBindBuffer(GL_COPY_READ_BUFFER, nVBOs[i]);
		glCopyBufferSubData(GL_COPY_READ_BUFFER,GL_COPY_WRITE_BUFFER,0,offset[2],normals_size[i]*sizeof(vec3));
		offset[2] += normals_size[i] * sizeof(vec3);
		glInvalidateBufferData(uVBOs[i]);//free vbo
		glBindBuffer(GL_COPY_WRITE_BUFFER,0);
	}
	glBindBuffer(GL_COPY_WRITE_BUFFER,0);


}
void updateModels() {

	mat4 Rotatation[PARTSNUM];
	mat4 Translation[PARTSNUM];
	for (int i = 0; i < PARTSNUM; i++) {
		Models[i] = mat4(1.0f);
		Rotatation[i] = mat4(1.0f);
		Translation[i] = mat4(1.0f);
	}
	//=============================================================
	//	頭(0)
	Rotatation[0] = rotate(angles[0], 0, 1, 0);
	Translation[0] = translate(0, -11, -1.5);
	Models[0] = Rotatation[0] * Translation[0] * Models[0];
	Translation[0] = translate(0, 11, 1.5);
	Models[0] = Translation[0] * Models[0];
	//=============================================================
	//	身體(1)
	Rotatation[1] = rotate(angles[1], 0, 1, 0);
	Translation[1] = translate(0, -7, 0);
	Models[1] = Rotatation[1] * Translation[1] * Models[1];
	Translation[1] = translate(0, 7, 0);
	Models[1] = Translation[1] * Models[1];
	//=============================================================
	//	屁股(2)
	Rotatation[2] = rotate(angles[2], 0, 1, 0);
	Translation[2] = translate(0, -3.5, 0);
	Models[2] = Rotatation[2] * Translation[2] * Models[2];
	Translation[2] = translate(0, 3.5, 0);
	Models[2] = Translation[2] * Models[2];
	//=============================================================
	//	右肩(3)
	Rotatation[3] = rotate(angles[3], 1, 0, 0) * Rotatation[1];
	Translation[3] = translate(5, -9, -1.2);
	Models[3] = Rotatation[3] * Translation[3] * Models[3];
	Translation[3] = translate(-5, 9, 1.2);
	Models[3] = Translation[3] * Models[3];
	//=============================================================
	//	左肩(4)
	Rotatation[4] = rotate(angles[4], 1, 0, 0) * Rotatation[1];
	Translation[4] = translate(-5, -9, -1.2);
	Models[4] = Rotatation[4] * Translation[4] * Models[4];
	Translation[4] = translate(5, 9, 1.2);
	Models[4] = Translation[4] * Models[4];
	//=============================================================
	//	右手(5)
	Rotatation[5] = rotate(hand_rotate[1], 0, 0, 1) * rotate(hand_rotate[0], 0, 1, 0) * rotate(angles[5], 1, 0, 0) * Rotatation[3];
	Translation[5] = translate(6.5, -5.5, -3);
	Models[5] = Rotatation[5] * Translation[5] * Models[5];
	Translation[5] = translate(-6.5, 5.5, 3);
	Models[5] = Translation[5] * Models[5];
	//=============================================================
	//	左手(6)
	Rotatation[6] = rotate(hand_rotate[3], 0, 0, 1) * rotate(hand_rotate[2], 0, 1, 0) * rotate(angles[6], 1, 0, 0) * Rotatation[4];
	Translation[6] = translate(-6.5, -5.5, -3);
	Models[6] = Rotatation[6] * Translation[6] * Models[6];
	Translation[6] = translate(6.5, 5.5, 3);
	Models[6] = Translation[6] * Models[6];
	//=============================================================
	//	右腳(7)
	Rotatation[7] = rotate(angles[7], 1, 0, 0) * Rotatation[2];
	Translation[7] = translate(1, -2.344, 0);
	Models[7] = Rotatation[7] * Translation[7] * Models[7];
	Translation[7] = translate(-1, 2.344, 0);
	Models[7] = Translation[7] * Models[7];

	//=============================================================
	//	左腳(8)
	//	先讓他隨時間繞著X轉
	Rotatation[8] = rotate(angles[8], 1, 0, 0) * Rotatation[2];

	//	位移medel到(0,0,0)使得rotate輕鬆
	Translation[8] = translate(-1, -2.344, 0);

	//	旋轉model
	Models[8] = Rotatation[8] * Translation[8] * Models[8];

	//	使model回到原本位置
	Translation[8] = translate(1, 2.344, 0);
	Models[8] = Translation[8] * Models[8];
	//=============================================================
}

void load2Buffer(char* obj,int i){
	std::vector<vec3> vertices;
	std::vector<vec2> uvs;
	std::vector<vec3> normals; // Won't be used at the moment.
	std::vector<unsigned int> materialIndices;

	bool res = loadOBJ(obj, vertices, uvs, normals,faces[i],mtls[i]);
	if(!res) printf("load failed\n");

	//glUseProgram(program);

	glGenBuffers(1,&VBOs[i]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
	glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(vec3),&vertices[0],GL_STATIC_DRAW);
	vertices_size[i] = vertices.size();

	//(buffer type,data起始位置,data size,data first ptr)
	//vertices_size[i] = glm_model->numtriangles;
	
	//printf("vertices:%d\n",vertices_size[);

	glGenBuffers(1,&uVBOs[i]);
	glBindBuffer(GL_ARRAY_BUFFER, uVBOs[i]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
	uvs_size[i] = uvs.size();

	glGenBuffers(1,&nVBOs[i]);
	glBindBuffer(GL_ARRAY_BUFFER, nVBOs[i]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
	normals_size[i] = normals.size();
}
mat4 translate(float x,float y,float z){
	vec4 t = vec4(x,y,z,1);//w = 1 ,則x,y,z=0時也能translate
	vec4 c1 = vec4(1,0,0,0);
	vec4 c2 = vec4(0,1,0,0);
	vec4 c3 = vec4(0,0,1,0);
	mat4 M = mat4(c1,c2,c3,t);
	return M;
} 
mat4 scale(float x,float y,float z){
	vec4 c1 = vec4(x,0,0,0);
	vec4 c2 = vec4(0,y,0,0);
	vec4 c3 = vec4(0,0,z,0);
	vec4 c4 = vec4(0,0,0,1);
	mat4 M = mat4(c1,c2,c3,c4);
	return M;
}

mat4 rotate(float angle,float x,float y,float z){
	float r = DOR(angle);
	mat4 M = mat4(1);

	vec4 c1 = vec4(cos(r)+(1-cos(r))*x*x,(1-cos(r))*y*x+sin(r)*z,(1-cos(r))*z*x-sin(r)*y,0);
	vec4 c2 = vec4((1-cos(r))*y*x-sin(r)*z,cos(r)+(1-cos(r))*y*y,(1-cos(r))*z*y+sin(r)*x,0);
	vec4 c3 = vec4((1-cos(r))*z*x+sin(r)*y,(1-cos(r))*z*y-sin(r)*x,cos(r)+(1-cos(r))*z*z,0);
	vec4 c4 = vec4(0,0,0,1);
	M = mat4(c1,c2,c3,c4);
	return M;
}
void Keyboard(unsigned char key, int x, int y){
	switch(key){
	case '1':
		angle += 5;
		if(angle>=360) angle = 0;
		printf("beta:%f\n",angle);
		break;
	case '2':
		angle -= 5;
		if(angle<=0) angle = 360;
		printf("beta:%f\n",angle);
		break;
	case 'w':
		eyedistance -= 0.2;
		break;
	case 's':
		eyedistance += 0.2;
		break;
	case 'a':
		eyeAngley -=10;
		break;
	case 'd':
		eyeAngley +=10;
		break;
	case 'r':
		angles[1] -= 5; 
		if(angles[1] == -360) angles[1] = 0;
		movey = 0;
		movex = 0;
		break;
	case 't':
		angles[2] -= 5;
		if(angles[2] == -360) angles[2] = 0;
		movey = 0;
		movex = 0;
		break;
	case 'q':
		break;
	case 'e':
		break;
	}
	glutPostRedisplay();
}
void menuEvents(int option){}
void ActionMenuEvents(int option){
	switch(option){
	case 0:
		action = IDLE;
		break;
	case 1:
		action = WALK;
		break;
	case 2:
		action = DANCE;
		break;
	}
}
void ModeMenuEvents(int option){
	switch(option){
	case 0:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 1:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
}
void ShaderMenuEvents(int option){
	if (shader != option)
		shader = option;
}
