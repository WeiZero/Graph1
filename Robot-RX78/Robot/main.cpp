#include "main.h"

vec3 camera = vec3(0,0,20);
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitContextVersion(4,3);//�HOpenGL version4.3���������
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);//�O�_�V�U�ۮe,GLUT_FORWARD_COMPATIBLE���䴩(?
	glutInitContextProfile(GLUT_CORE_PROFILE);

	//multisample for golygons smooth
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL 4.3 - Robot");

	glewExperimental = GL_TRUE; //�m��glewInit()���e
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
	ActionMenu = glutCreateMenu(ActionMenuEvents);//�إߥk����
	//�[�J�k�䪫��
	glutAddMenuEntry("idle",0);
	glutAddMenuEntry("walk",1);
	glutAddMenuEntry("dance", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p

	ModeMenu = glutCreateMenu(ModeMenuEvents);//�إߥk����
	//�[�J�k�䪫��
	glutAddMenuEntry("Line",0);
	glutAddMenuEntry("Fill",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p


	glutCreateMenu(menuEvents);//�إߥk����
	//�[�J�k�䪫��
	glutAddSubMenu("action",ActionMenu);
	glutAddSubMenu("mode",ModeMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	//�P�k�����p

	glutMouseFunc(Mouse);
	glutTimerFunc (75, idle, 0); 
	glutMainLoop();
	return 0;
}
void ChangeSize(int w,int h){
	if(h == 0) h = 1;
	glViewport(0,0,w,h);
	Projection = perspective(80.0f,(float)w/h,0.1f,100.0f);
}
void Mouse(int button,int state,int x,int y){
	if(button == 2) isFrame = false;
}
void idle(int dummy){
	isFrame = true;
	int out = 0;
	if(action == WALK){
		walk(dummy);
		out = dummy+1;
		if(out > 13) out = 0;
	}
	else if(action == IDLE){
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
		resetObj(1);
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
		angles[7] = -45;
		angles[8] = 30;
		break;
	case 7:
		angles[5] = 45;
		angles[6] = -55;
		angles[7] = -55;
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

void init(){
	isFrame = false;
	pNo = 0;
	for(int i = 0;i<PARTSNUM;i++)//��l�ƨ��װ}�C
		angles[i] = 0.0;

	//VAO
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "DSPhong_Material.vp" },//vertex shader
		{ GL_FRAGMENT_SHADER, "DSPhong_Material.fp" },//fragment shader
		{ GL_NONE, NULL }};
	program = LoadShaders(shaders);//Ū��shader

	glUseProgram(program);//uniform�ѼƼƭȫe������use shader
	
	MatricesIdx = glGetUniformBlockIndex(program,"MatVP");
	ModelID =  glGetUniformLocation(program,"Model");
    M_KaID = glGetUniformLocation(program,"Material.Ka");
	M_KdID = glGetUniformLocation(program,"Material.Kd");
	M_KsID = glGetUniformLocation(program,"Material.Ks");

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


	// for future 
	// now just test
	ShaderInfo gray_shader[] = {
		{ GL_VERTEX_SHADER, "gray.vp" },//vertex shader
		{ GL_FRAGMENT_SHADER, "gray.fp" },//fragment shader
		{ GL_NONE, NULL }};

	glClearColor(0.0,0.0,0.0,1);//black screen
}

#define DOR(angle) (angle*3.1415/180);
void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(VAO);
	glUseProgram(program);//uniform�ѼƼƭȫe������use shader
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
		//(location,vec3,type,�T�w�I,�s���I�������q,buffer point)
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
		//(location,vec2,type,�T�w�I,�s���I�������q,point)
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
		//(location,vec3,type,�T�w�I,�s���I�������q,point)
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
	glFlush();	//�j�����W����OpenGL commands
	glutSwapBuffers();	//�մ��e�x�M��xbuffer ,���Obuffer�e���M�e�xbuffer�洫�ϧڭ̬ݨ���
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
	//bind vbo ,�Ĥ@��bind�]�P���� create vbo 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//VBO��target�OGL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER,totalSize[0],NULL,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uVBO);//VBO��target�OGL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER,totalSize[1],NULL,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, nVBO);//VBO��target�OGL_ARRAY_BUFFER
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

void updateModels(){

	mat4 Rotatation[PARTSNUM];
	mat4 Translation[PARTSNUM];
	for(int i = 0 ; i < PARTSNUM;i++){
		Models[i] = mat4(1.0f);
		Rotatation[i] = mat4(1.0f);
		Translation[i] = mat4(1.0f); 
	}
	//=============================================================
	//	�Y(0)
	Rotatation[0] = rotate(angles[0], 0, 1, 0);
	Translation[0] = translate(0, -11, -1.5);
	Models[0] = Rotatation[0] * Translation[0] * Models[0];
	Translation[0] = translate(0, 11, 1.5);
	Models[0] = Translation[0] * Models[0];
	//=============================================================
	//	����(1)
	Rotatation[1] = rotate(angles[1], 0, 1, 0);
	Translation[1] = translate(0, -7, 0);
	Models[1] = Rotatation[1] * Translation[1] * Models[1];
	Translation[1] = translate(0, 7, 0);
	Models[1] = Translation[1] * Models[1];
	//=============================================================
	//	����(2)
	Rotatation[2] = rotate(angles[2], 0, 1, 0);
	Translation[2] = translate(0, -3.5, 0);
	Models[2] = Rotatation[2] * Translation[2] * Models[2];
	Translation[2] = translate(0, 3.5, 0);
	Models[2] = Translation[2] * Models[2];
	//=============================================================
	//	�k��(3)
	Rotatation[3] = rotate(angles[3], 1, 0, 0) * Rotatation[1];
	Translation[3] = translate(5, -9, -1.2);
	Models[3] = Rotatation[3] * Translation[3] * Models[3];
	Translation[3] = translate(-5, 9, 1.2);
	Models[3] = Translation[3] * Models[3];
	//=============================================================
	//	����(4)
	Rotatation[4] = rotate(angles[4], 1, 0, 0) * Rotatation[1];
	Translation[4] = translate(-5, -9, -1.2);
	Models[4] = Rotatation[4] * Translation[4] * Models[4];
	Translation[4] = translate(5, 9, 1.2);
	Models[4] = Translation[4] * Models[4];
	//=============================================================
	//	�k��(5)
	Rotatation[5] = rotate(hand_rotate[1], 0, 0, 1) * rotate(hand_rotate[0], 0, 1, 0) * rotate(angles[5], 1, 0, 0) * Rotatation[3];
	Translation[5] = translate(6.5, -5.5, -3);
	Models[5] = Rotatation[5] * Translation[5] * Models[5];
	Translation[5] = translate(-6.5, 5.5, 3);
	Models[5] = Translation[5] * Models[5];
	//=============================================================
	//	����(6)
	Rotatation[6] = rotate(hand_rotate[3], 0, 0, 1) * rotate(hand_rotate[2], 0, 1, 0) * rotate(angles[6], 1, 0, 0) * Rotatation[4];
	Translation[6] = translate(-6.5, -5.5, -3);
	Models[6] = Rotatation[6] * Translation[6] * Models[6];
	Translation[6] = translate(6.5, 5.5, 3);
	Models[6] = Translation[6] * Models[6];
	//=============================================================
	//	�k�}(7)
	Rotatation[7] = rotate(angles[7], 1, 0, 0) * Rotatation[2];
	Translation[7] = translate(1, -2.344, 0);
	Models[7] = Rotatation[7] * Translation[7] * Models[7];
	Translation[7] = translate(-1, 2.344, 0);
	Models[7] = Translation[7] * Models[7];

	//=============================================================
	//	���}(8)
	//	�����L�H�ɶ�¶��X��
	Rotatation[8] = rotate(angles[8], 1, 0, 0) * Rotatation[2];

	//	�첾medel��(0,0,0)�ϱorotate���P
	Translation[8] = translate(-1, -2.344, 0);

	//	����model
	Models[8] = Rotatation[8] * Translation[8] * Models[8];

	//	��model�^��쥻��m
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

	//(buffer type,data�_�l��m,data size,data first ptr)
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
	vec4 t = vec4(x,y,z,1);//w = 1 ,�hx,y,z=0�ɤ]��translate
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
	pNo = option;
}
