void lists()
{
	GLint lid = glGenLists(10);

	glNewList(7, GL_COMPILE);  //²èºø
	glutSolidTeapot(1);
	glEndList();

	glNewList(3, GL_COMPILE);  //×À×Ó
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse00);
	////¶àÖØÎÆÀí
	//glActiveTextureARB(GL_TEXTURE0_ARB);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[1]);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	//glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_BLEND);

	//glActiveTextureARB(GL_TEXTURE1_ARB);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[2]);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	//glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_BLEND);

	//glRotatef(-90, 1, 0, 0);
	//glBegin(GL_QUADS);
	//glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
	//glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0);
	//glVertex3f(-2.51, 2.01, 4.001);
	//glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
	//glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0);
	//glVertex3f(-2.51, -2.01, 4.001);
	//glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
	//glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);
	//glVertex3f(2.51, -2.01, 4.001);
	//glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
	//glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1);
	//glVertex3f(2.51, 2.01, 4.001);
	//glEnd();
	//glDisable(GL_TEXTURE_2D);
	//glActiveTextureARB(GL_TEXTURE0_ARB);
	//glDisable(GL_TEXTURE_2D);

	glPushMatrix();  //×ÀÃæ
	float mat_diffuse1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();  //×ÀÍÈ
	float mat_diffuse2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	float mat_diffuse3[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	float mat_diffuse4[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();  //×ÀÍÈ
	float mat_diffuse5[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse5);
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();
	glEndList();

	glNewList(4, GL_COMPILE);    //ÁùÃæÇ½±Ú
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  //µØ°å
	float amb1[] = { 0.8, 0.8, 0.8, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amb1);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);   glVertex3f(-100.0, 0.0, 100.0);
	glTexCoord2f(0, 1);   glVertex3f(-100.0, 0.0, -130.0);
	glTexCoord2f(1, 1);   glVertex3f(100.0, 0.0, -130.0);
	glTexCoord2f(1, 0);   glVertex3f(100.0, 0.0, 100.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);  //Ìì»¨°å
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	float mat_diffuse11[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse11);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 1);   glVertex3f(-100.0, 35.0, 100.0);
	glTexCoord2f(1, 0);   glVertex3f(-100.0, 35.0, -130.0);
	glTexCoord2f(0, 0);   glVertex3f(100.0, 35.0, -130.0);
	glTexCoord2f(0, 1);   glVertex3f(100.0, 35.0, 100.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);  //Ç°·½Ç½±Ú
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);   glVertex3f(-100.0, 0.0, -130.0);
	glTexCoord2f(0, 1);   glVertex3f(-100.0, 35.0, -130.0);
	glTexCoord2f(1, 1);   glVertex3f(100.0, 35.0, -130.0);
	glTexCoord2f(1, 0);   glVertex3f(100.0, 0.0, -130.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);  //×ó·½Ç½±Ú
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);   glVertex3f(-100.0, 0.0, 100.0);
	glTexCoord2f(0, 1);   glVertex3f(-100.0, 35.0, 100.0);
	glTexCoord2f(1, 1);   glVertex3f(-100.0, 35.0, -130.0);
	glTexCoord2f(1, 0);   glVertex3f(-100.0, 0.0, -130.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);  //ÓÒ·½Ç½±Ú
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);   glVertex3f(100.0, 0.0, 100.0);
	glTexCoord2f(0, 1);   glVertex3f(100.0, 35.0, 100.0);
	glTexCoord2f(1, 1);   glVertex3f(100.0, 35.0, -130.0);
	glTexCoord2f(1, 0);   glVertex3f(100.0, 0.0, -130.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);  //ºó·½Ç½±Ú
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);   glVertex3f(-100.0, 0.0, 100.0);
	glTexCoord2f(0, 1);   glVertex3f(-100.0, 35.0, 100.0);
	glTexCoord2f(1, 1);   glVertex3f(100.0, 35.0, 100.0);
	glTexCoord2f(1, 0);   glVertex3f(100.0, 0.0, 100.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();

	glNewList(5, GL_COMPILE);  //Á½ÅÅÎïÌå
	GLUquadricObj *objCylinder = gluNewQuadric();
	gluQuadricNormals(objCylinder, GL_SMOOTH);
	gluQuadricTexture(objCylinder, TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	//float mat_diffuse21[] = { 0.5f, 0.3f, 0.6f, 1.0f };  //Ô²×¶
	float mat_diffuse21[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(40.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-40.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 5.0, 0.0, 15.0, 32, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Ì¨
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-55.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(55.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 3.0, 10.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //ÇòÌå
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //ÁíÒ»ÅÅÇòÌå
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(25.0, 5.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-25.0, 5.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	gluSphere(objCylinder, 5.0, 64, 64);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f }; //Á¢·½Ìå
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-88.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(88.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-88.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 7.0, 7.0, 10.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f }; //³¤·½Ìå
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(71.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-71.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluCylinder(objCylinder, 6.0, 6.0, 15.0, 4, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-10.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-11.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-12.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-10.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-10.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(10.0, 0.0, -15.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(11.0, 0.0, 5.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(12.0, 0.0, 25.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(10.0, 0.0, -35.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();
	//glutSolidTeapot(10);

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(10.0, 0.0, -55.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(10.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();

	glPushMatrix();
	//float mat_diffuse21[] = { 1.0f, 0.0f, 0.0f, 1.0f };  //Ô²Öù
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse21);
	glTranslatef(-10.0, 0.0, -75.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(objCylinder, 5.0, 5.0, 15.0, 32, 5);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEndList();

	glNewList(6, GL_COMPILE);    //NurbsÇúÃæ
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LEQUAL);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glEnable(GL_BLEND);
	glFrontFace(GL_CW);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	theNurb1 = gluNewNurbsRenderer();//´´½¨NURBS¶ÔÏótheNurb1
	gluNurbsProperty(theNurb1, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb1, GLU_DISPLAY_MODE, GLU_FILL);

	GLfloat knots[10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(30.0, 4.0, -135.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(10.0, 1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.0, 4.0, -135.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(10.0, 1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, -60.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, -40.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, -20.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, 0.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, 20.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(103.0, 10.0, 40.0);
	//glRotatef(0.0, 0.0, 0.0, 1.0);
	glRotatef(20.0, 0.0, 0.0, 1.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glScalef(5.0, 5.0, 5.0);
	gluBeginSurface(theNurb1);
	//gluNurbsSurface(theNurb1, 10, knots, 10, knots, 5 * 3, 3, &ctrlpoints[0][0][0], 5, 5, GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb1);
	glPopMatrix();

	glEndList();
}