#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include<iostream>
#include <stdlib.h>
#include <chrono>
#include<GL/freeglut.h>
#define PI 3.14
using namespace std;

float k = 2;//大小参数
float carX = 0.0f;
float carY = -100.0f;
float blockX = 400.0f;
float blockY = -75.0f;
float roadX[10] = { 0 };
float treeX[3] = { 0,500,1000 };
float unbX[3] = { -400,0,400 };
float unbY[3] = { 0 };
float boatX = 0;
float boatY = 0;
//位移参数

float moveSpeed = 5.5f;
float bloackSpeed = 2.5;
float carSpeed = 2.5;
float boatSpeed = 1.5;
float treeSpeed = 10.5;
float unbSpeed = 3.5;
//速度参数

bool timeState = true;
float duration;
float moretime = 0;
int gameTime;
auto startTime = chrono::high_resolution_clock::now();
//时间参数

GLfloat R[6] = { 0 }, G[6] = { 0 }, B[6] = { 0 };
GLfloat BR, BG, BB;
GLfloat UR[3] = { 0.5 }, UG[3] = { 0.5 }, UB[3] = { 0.5 };
int randColor;
//颜色参数

int gameState = 0;
int lives = 3;
//状态参数


//碰撞检测
bool checkCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    return (x1 >= x2 && y1<y2 && y1 + h1> y2 - h2 && x1 - w1 < x2 + w2);
}

//开始
void StartMenu() {
    glBegin(GL_POLYGON);
    glColor3f(1, 0.64, 0.25);
    glVertex2f(-30.00f, 60.0f);
    glColor3f(0.88, 0.24, 0.74);
    glVertex2f(-30.00f, 113.0f);
    glVertex2f(-58.90f, 113.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-58.90f, 113.0f);
    glVertex2f(-30.00f, 113.0f);
    glVertex2f(-30.00f, 133.0f);
    glColor3f(0.2, 0.37, 0.81);
    glVertex2f(-50.00f, 170.0f);
    glVertex2f(-90.00f, 170.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 0.64, 0.25);
    glVertex2f(-30.00f, 60.0f);
    glColor3f(0.88, 0.24, 0.74);
    glVertex2f(-30.00f, 113.0f);
    glVertex2f(-1.10f, 113.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-1.10f, 113.0f);
    glVertex2f(-30.0f, 113.0f);
    glVertex2f(-30.00f, 133.0f);
    glColor3f(0.2, 0.37, 0.81);
    glVertex2f(-10.00f, 170.0f);
    glVertex2f(30.00f, 170.0f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1, 0.64, 0.25);
    glVertex2f(32.00f, 60.0f);
    glVertex2f(72.00f, 60.0f);
    glColor3f(0.88, 0.24, 0.74);
    glVertex2f(72.00f, 125.0f);
    glVertex2f(32.00f, 125.0f);
    glVertex2f(32.00f, 125.0f);
    glVertex2f(72.00f, 125.0f);
    glColor3f(0.2, 0.37, 0.81);
    glVertex2f(72.00f, 170.0f);
    glVertex2f(32.00f, 170.0f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    char stringG[] = "g  and";
    glRasterPos2f(-27, 131);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)stringG);

    char stringR[] = "R";
    glRasterPos2f(-16.5, 126.5);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)stringR);

    char stringT[] = "he  t";
    glRasterPos2f(-5, 111);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)stringT);

    char stringt[] = "t";
    glRasterPos2f(-13, 111);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)stringt);

    char stringF[] = "F";
    glRasterPos2f(18, 108);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)stringF);

    char stringA[] = "auto";
    glRasterPos2f(-19, 96);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)stringA);

    char stringS[] = "start";
    glRasterPos2f(-20, 0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)stringS);

    char stringE[] = "exit";
    glRasterPos2f(-17, -35);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)stringE);
}

//结束
void endMenu()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    char string1[] = "Game Time:";
    glRasterPos2f(-70, 10);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)string1);
    char string2[25] = {};
    glRasterPos2f(28, 10);
    _itoa(gameTime, string2, 10);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)string2);
    char stringE[] = "exit";
    glRasterPos2f(-17, -35);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)stringE);
}

//时间
void Time()
{
    auto currentTime = chrono::high_resolution_clock::now();
    if (timeState)
    {
        moretime = chrono::duration_cast<chrono::milliseconds>(currentTime - startTime).count();
        timeState = false;
    }
    if ((currentTime - startTime).count() % 1000 == 0) {
        float duration = chrono::duration_cast<chrono::milliseconds>(currentTime - startTime).count() - moretime;
        gameTime = int(duration / 1000);
    }
    char stringT[25];
    _itoa(gameTime, stringT, 10);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-340, 240);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)stringT);
}

//刷新
void update(int value)
{
    if (gameState == 1 && carX - 58 > -480)
    {
        blockX -= bloackSpeed, boatX -= boatSpeed;
        if (checkCollision(65.0 + carX, -16.4 + carY, 123, 30, blockX - 58, blockY + 1, 123, 9)) carX -= bloackSpeed;
        if (blockX < -470) blockX = 440, blockY = -float(rand() % 80 + 75), randColor = rand() % 7;
        for (int i = 0; i < 9; i++) {
            roadX[i] -= moveSpeed;
            if (-300 + i * 100 + roadX[i] <= -400) roadX[i] += 900;
        }
        for (int i = 0; i < 3; i++) {
            treeX[i] -= treeSpeed;
            unbX[i] -= unbSpeed;
            if (treeX[i] < -750) treeX[i] = 800;
            if (unbX[i] < -450) unbX[i] = 800, UR[i] = float(rand() % 11) / 10, UG[i] = float(rand() % 11) / 10, UB[i] = float(rand() % 11) / 10, unbY[i] = rand() % 40 - rand() % 10;
        }
        if (boatX < -480)boatX = 980, boatY = rand() % 50 - rand() % 40;
    }
    else if (gameState == 1 && carX - 58 <= -480) carX = 0, lives--;
    glutPostRedisplay();  // 请求重新绘制
    if (lives > 0) glutTimerFunc(16, update, 0);// 设置定时器，每16毫秒触发一次update函数

}

//主角车
void Car() {
    // 绘制汽车车身

    glColor3f(1.0f, 0.0f, 0.0f);  // 设置为红色
    glBegin(GL_POLYGON);
    glVertex2f(-29.00f * k + carX, -9.0f * k + carY);
    glVertex2f(-29.00f * k + carX, -0.50f * k + carY);
    glVertex2f(-8.00f * k + carX, -0.50f * k + carY);
    glVertex2f(-8.00f * k + carX, -9.0f * k + carY);
    glEnd();//后
    glBegin(GL_POLYGON);
    glVertex2f(-8.000f * k + carX, -9.0f * k + carY);
    glVertex2f(-8.00f * k + carX, -0.50f * k + carY);
    glVertex2f(-6.50f * k + carX, 6.50f * k + carY);
    glVertex2f(4.00f * k + carX, 6.50f * k + carY);
    glVertex2f(11.50f * k + carX, 0.0f * k + carY);
    glVertex2f(11.50f * k + carX, -9.0f * k + carY);
    glEnd();//中

    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-29.0f * k + carX, -0.50f * k + carY);
    glVertex2f(-27.0f * k + carX, 2.50f * k + carY);
    glVertex2f(-8.40f * k + carX, 2.50f * k + carY);
    glVertex2f(-8.00f * k + carX, -0.50f * k + carY);
    glEnd();//后上
    glColor3f(0.0f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(-8.00f * k + carX, -0.50f * k + carY);
    glVertex2f(-8.40f * k + carX, 2.50f * k + carY);
    glVertex2f(-5.80f * k + carX, 8.00f * k + carY);
    glVertex2f(-5.50f * k + carX, 6.50f * k + carY);
    glEnd();//后窗
    glColor3f(0.8f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-5.50f * k + carX, 6.50f * k + carY);
    glVertex2f(-5.80f * k + carX, 8.00f * k + carY);
    glVertex2f(4.50f * k + carX, 8.00f * k + carY);
    glVertex2f(4.00f * k + carX, 6.50f * k + carY);
    glEnd();//顶
    glColor3f(0.0f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(4.00f * k + carX, 6.50f * k + carY);
    glVertex2f(4.50f * k + carX, 8.00f * k + carY);
    glVertex2f(11.40f * k + carX, 3.00f * k + carY);
    glVertex2f(11.50f * k + carX, 0.0f * k + carY);
    glEnd();//前窗
    glColor3f(0.8f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(11.50f * k + carX, 0.0f * k + carY);
    glVertex2f(11.40f * k + carX, 3.00f * k + carY);
    glVertex2f(30.80f * k + carX, 1.00f * k + carY);
    glVertex2f(30.0f * k + carX, -1.50f * k + carY);
    glEnd();//盖
    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(30.0f * k + carX, -1.50f * k + carY);
    glVertex2f(30.80f * k + carX, 1.00f * k + carY);
    glVertex2f(33.70f * k + carX, -5.00f * k + carY);
    glVertex2f(33.20f * k + carX, -6.00f * k + carY);
    glVertex2f(32.00f * k + carX, -7.50f * k + carY);
    glEnd();//中网
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(31.00f * k + carX, 0.60f * k + carY);
    glVertex2f(31.10f * k + carX, -1.20f * k + carY);
    glVertex2f(31.70f * k + carX, -2.50f * k + carY);
    glVertex2f(32.30f * k + carX, -3.50f * k + carY);
    glVertex2f(33.50f * k + carX, -4.50f * k + carY);
    glVertex2f(33.60f * k + carX, -3.50f * k + carY);
    glVertex2f(33.0f * k + carX, -1.50f * k + carY);
    glVertex2f(32.0f * k + carX, -0.10f * k + carY);
    glEnd();//左灯
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(11.50f * k + carX, -9.0f * k + carY);
    glVertex2f(11.50f * k + carX, 0.0f * k + carY);
    glVertex2f(30.0f * k + carX, -1.50f * k + carY);
    glVertex2f(32.50f * k + carX, -6.50f * k + carY);
    glVertex2f(32.0f * k + carX, -7.50f * k + carY);
    glVertex2f(30.0f * k + carX, -9.0f * k + carY);
    glEnd();//前
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(30.0f * k + carX, -1.40f * k + carY);
    glVertex2f(29.80f * k + carX, -3.50f * k + carY);
    glVertex2f(30.70f * k + carX, -5.50f * k + carY);
    glVertex2f(31.30f * k + carX, -6.0f * k + carY);
    glVertex2f(32.50f * k + carX, -6.50f * k + carY);
    glVertex2f(32.60f * k + carX, -5.50f * k + carY);
    glVertex2f(32.0f * k + carX, -3.50f * k + carY);
    glVertex2f(31.0f * k + carX, -2.10f * k + carY);
    glEnd();//右灯
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-29.0f * k + carX, -4.0f * k + carY);
    glVertex2f(-29.0f * k + carX, -0.50f * k + carY);
    glVertex2f(-27.0f * k + carX, -0.50f * k + carY);
    glVertex2f(-27.0f * k + carX, -4.0f * k + carY);
    glEnd();//后灯
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-7.0f * k + carX, -8.70f * k + carY);
    glVertex2f(-7.0f * k + carX, -0.80f * k + carY);
    glVertex2f(-5.0f * k + carX, 5.70f * k + carY);
    glVertex2f(3.70f * k + carX, 5.70f * k + carY);
    glVertex2f(10.60f * k + carX, -0.80f * k + carY);
    glVertex2f(10.60f * k + carX, -8.70f * k + carY);
    glEnd();//门
    glColor3f(0.0f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(-6.0f * k + carX, 0.0f * k + carY);
    glVertex2f(-4.50f * k + carX, 5.20f * k + carY);
    glVertex2f(3.20f * k + carX, 5.20f * k + carY);
    glVertex2f(8.50f * k + carX, 0.0f * k + carY);
    glEnd();//窗
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-6.0f * k + carX, -2.50f * k + carY);
    glVertex2f(-3.0f * k + carX, -2.50f * k + carY);
    glEnd();//门把手
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(9.0f * k + carX, -1.0f * k + carY);
    glVertex2f(6.0f * k + carX, 1.20f * k + carY);
    glEnd();//杆
    glColor3f(0.4f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(7.0f * k + carX, 0.20f * k + carY);
    glVertex2f(5.0f * k + carX, 0.20f * k + carY);
    glVertex2f(5.0f * k + carX, 1.80f * k + carY);
    glVertex2f(7.0f * k + carX, 1.80f * k + carY);
    glEnd();//后视镜

    // 绘制汽车轮胎
    glColor3f(0.3f, 0.3f, 0.3f);  // 设置为黑色
    glBegin(GL_QUADS);
    glVertex2f(-10.5f * k + carX, -9.0f * k + carY);
    glVertex2f(-11.50f * k + carX, -3.3f * k + carY);
    glVertex2f(-19.50f * k + carX, -3.3f * k + carY);
    glVertex2f(-20.5f * k + carX, -9.0f * k + carY);

    glVertex2f(15.5f * k + carX, -9.0f * k + carY);
    glVertex2f(16.50f * k + carX, -3.3f * k + carY);
    glVertex2f(24.50f * k + carX, -3.3f * k + carY);
    glVertex2f(25.5f * k + carX, -9.0f * k + carY);
    glEnd();//

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f); // 红色
    for (int i = 0; i <= 360; ++i) {
        float angle = static_cast<float>(i) * (3.14f / 180.0f);
        float x = -15.6 * k + carX + 4.5f * k * cos(angle);
        float y = -8.2 * k + carY + 4.5f * k * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f); // 红色
    for (int i = 0; i <= 360; ++i) {
        float angle = static_cast<float>(i) * (3.14f / 180.0f);
        float x = 20.5 * k + carX + 4.5f * k * cos(angle);
        float y = -8.2 * k + carY + 4.5f * k * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(1);
    switch (abs((int)blockX) % 2)
    {

    case 0:
        glBegin(GL_LINES);
        glColor3f(0.5f, 0.5f, 0.5f); // 红色
        for (int i = 0; i < 5; ++i) {
            float angle = static_cast<float>(i) * (3.14f / 180.0f) * 72;
            float x1 = 20.5 * k + carX + 3.0f * k * cos(angle);
            float y1 = -8.2 * k + carY + 3.0f * k * sin(angle);
            glVertex2f(20.5 * k + carX, -8.2 * k + carY);
            glVertex2f(x1, y1);//前轮
            float x = -15.6 * k + carX + 3.0f * k * cos(angle);
            float y = -8.2 * k + carY + 3.0f * k * sin(angle);
            glVertex2f(-15.6 * k + carX, -8.2 * k + carY);
            glVertex2f(x, y);//后轮
        }
        glEnd();
        break;
    case 1:
        glBegin(GL_LINES);
        glColor3f(0.5f, 0.5f, 0.5f); // 红色
        for (int i = -1; i < 4; ++i) {
            float angle = static_cast<float>(i) * (3.14f / 180.0f) * 72;
            float x1 = 20.5 * k + carX + 3.0f * k * sin(angle + 60);
            float y1 = -8.2 * k + carY + 3.0f * k * cos(angle + 60);
            glVertex2f(20.5 * k + carX, -8.2 * k + carY);
            glVertex2f(x1, y1);//前轮
            float x = -15.6 * k + carX + 3.0f * k * sin(angle + 60);
            float y = -8.2 * k + carY + 3.0f * k * cos(angle + 60);
            glVertex2f(-15.6 * k + carX, -8.2 * k + carY);
            glVertex2f(x, y);//后轮
        }
        glEnd();
        break;
    default:
        break;
    }
}

//过路车
void BlockCar()
{
    switch (randColor)
    {
    case 0:BR = 0.0, BG = 0.0, BB = 0.0; break;
    case 1:BR = 1.0, BG = 0.0, BB = 0.0; break;
    case 2:BR = 0.0, BG = 1.0, BB = 0.0; break;
    case 3:BR = 0.0, BG = 0.0, BB = 1.0; break;
    case 4:BR = 1.0, BG = 1.0, BB = 0.0; break;
    case 5:BR = 0.0, BG = 1.0, BB = 1.0; break;
    case 6:BR = 1.0, BG = 0.0, BB = 1.0; break;
    }
    glColor3f(BR, BG, BB);  // 设置为红色
    glBegin(GL_POLYGON);
    glVertex2f(-29.00f * k + blockX, -9.0f * k + blockY);
    glVertex2f(-29.00f * k + blockX, -0.50f * k + blockY);
    glVertex2f(-8.00f * k + blockX, -0.50f * k + blockY);
    glVertex2f(-8.00f * k + blockX, -9.0f * k + blockY);
    glEnd();//后

    glBegin(GL_POLYGON);
    glVertex2f(-8.000f * k + blockX, -9.0f * k + blockY);
    glVertex2f(-8.00f * k + blockX, -0.50f * k + blockY);
    glVertex2f(-6.50f * k + blockX, 6.50f * k + blockY);
    glVertex2f(4.00f * k + blockX, 6.50f * k + blockY);
    glVertex2f(11.50f * k + blockX, 0.0f * k + blockY);
    glVertex2f(11.50f * k + blockX, -9.0f * k + blockY);
    glEnd();//中

    glColor3f(BR / 2.0, BG / 2.0, BB / 2.0);
    glBegin(GL_POLYGON);
    glVertex2f(-29.0f * k + blockX, -0.50f * k + blockY);
    glVertex2f(-27.0f * k + blockX, 2.50f * k + blockY);
    glVertex2f(-8.40f * k + blockX, 2.50f * k + blockY);
    glVertex2f(-8.00f * k + blockX, -0.50f * k + blockY);
    glEnd();//后上

    glColor3f(BR * 0.8, BG * 0.8, BB * 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(-5.50f * k + blockX, 6.50f * k + blockY);
    glVertex2f(-5.80f * k + blockX, 8.00f * k + blockY);
    glVertex2f(4.50f * k + blockX, 8.00f * k + blockY);
    glVertex2f(4.00f * k + blockX, 6.50f * k + blockY);
    glEnd();//顶

    glColor3f(BR * 0.8, BG * 0.8, BB * 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(11.50f * k + blockX, 0.0f * k + blockY);
    glVertex2f(11.40f * k + blockX, 3.00f * k + blockY);
    glVertex2f(30.80f * k + blockX, 1.00f * k + blockY);
    glVertex2f(30.0f * k + blockX, -1.50f * k + blockY);
    glEnd();//盖

    glColor3f(0.0f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(-8.00f * k + blockX, -0.50f * k + blockY);
    glVertex2f(-8.40f * k + blockX, 2.50f * k + blockY);
    glVertex2f(-5.80f * k + blockX, 8.00f * k + blockY);
    glVertex2f(-5.50f * k + blockX, 6.50f * k + blockY);
    glEnd();//后窗

    glColor3f(0.0f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(4.00f * k + blockX, 6.50f * k + blockY);
    glVertex2f(4.50f * k + blockX, 8.00f * k + blockY);
    glVertex2f(11.40f * k + blockX, 3.00f * k + blockY);
    glVertex2f(11.50f * k + blockX, 0.0f * k + blockY);
    glEnd();//前窗

    glColor3f(BR * 0.5, BG * 0.5, BB * 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(30.0f * k + blockX, -1.50f * k + blockY);
    glVertex2f(30.80f * k + blockX, 1.00f * k + blockY);
    glVertex2f(33.70f * k + blockX, -5.00f * k + blockY);
    glVertex2f(33.20f * k + blockX, -6.00f * k + blockY);
    glVertex2f(32.00f * k + blockX, -7.50f * k + blockY);
    glEnd();//中网

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(31.00f * k + blockX, 0.60f * k + blockY);
    glVertex2f(31.10f * k + blockX, -1.20f * k + blockY);
    glVertex2f(31.70f * k + blockX, -2.50f * k + blockY);
    glVertex2f(32.30f * k + blockX, -3.50f * k + blockY);
    glVertex2f(33.50f * k + blockX, -4.50f * k + blockY);
    glVertex2f(33.60f * k + blockX, -3.50f * k + blockY);
    glVertex2f(33.0f * k + blockX, -1.50f * k + blockY);
    glVertex2f(32.0f * k + blockX, -0.10f * k + blockY);
    glEnd();//左灯

    glColor3f(BR, BG, BB);
    glBegin(GL_POLYGON);
    glVertex2f(11.50f * k + blockX, -9.0f * k + blockY);
    glVertex2f(11.50f * k + blockX, 0.0f * k + blockY);
    glVertex2f(30.0f * k + blockX, -1.50f * k + blockY);
    glVertex2f(32.50f * k + blockX, -6.50f * k + blockY);
    glVertex2f(32.0f * k + blockX, -7.50f * k + blockY);
    glVertex2f(30.0f * k + blockX, -9.0f * k + blockY);
    glEnd();//前

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(30.0f * k + blockX, -1.40f * k + blockY);
    glVertex2f(29.80f * k + blockX, -3.50f * k + blockY);
    glVertex2f(30.70f * k + blockX, -5.50f * k + blockY);
    glVertex2f(31.30f * k + blockX, -6.0f * k + blockY);
    glVertex2f(32.50f * k + blockX, -6.50f * k + blockY);
    glVertex2f(32.60f * k + blockX, -5.50f * k + blockY);
    glVertex2f(32.0f * k + blockX, -3.50f * k + blockY);
    glVertex2f(31.0f * k + blockX, -2.10f * k + blockY);
    glEnd();//右灯

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-29.0f * k + blockX, -4.0f * k + blockY);
    glVertex2f(-29.0f * k + blockX, -0.50f * k + blockY);
    glVertex2f(-27.0f * k + blockX, -0.50f * k + blockY);
    glVertex2f(-27.0f * k + blockX, -4.0f * k + blockY);
    glEnd();//后灯

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-7.0f * k + blockX, -8.70f * k + blockY);
    glVertex2f(-7.0f * k + blockX, -0.80f * k + blockY);
    glVertex2f(-5.0f * k + blockX, 5.70f * k + blockY);
    glVertex2f(3.70f * k + blockX, 5.70f * k + blockY);
    glVertex2f(10.60f * k + blockX, -0.80f * k + blockY);
    glVertex2f(10.60f * k + blockX, -8.70f * k + blockY);
    glEnd();//门

    glColor3f(0.0f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(-6.0f * k + blockX, 0.0f * k + blockY);
    glVertex2f(-4.50f * k + blockX, 5.20f * k + blockY);
    glVertex2f(3.20f * k + blockX, 5.20f * k + blockY);
    glVertex2f(8.50f * k + blockX, 0.0f * k + blockY);
    glEnd();//窗

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-6.0f * k + blockX, -2.50f * k + blockY);
    glVertex2f(-3.0f * k + blockX, -2.50f * k + blockY);
    glEnd();//门把手

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(9.0f * k + blockX, -1.0f * k + blockY);
    glVertex2f(6.0f * k + blockX, 1.20f * k + blockY);
    glEnd();//杆

    glColor3f(BR * 0.4, BG * 0.4, BB * 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(7.0f * k + blockX, 0.20f * k + blockY);
    glVertex2f(5.0f * k + blockX, 0.20f * k + blockY);
    glVertex2f(5.0f * k + blockX, 1.80f * k + blockY);
    glVertex2f(7.0f * k + blockX, 1.80f * k + blockY);
    glEnd();//后视镜

    // 绘制汽车轮胎
    glColor3f(0.3f, 0.3f, 0.3f);  // 设置为黑色
    glBegin(GL_QUADS);
    glVertex2f(-10.5f * k + blockX, -9.0f * k + blockY);
    glVertex2f(-11.50f * k + blockX, -3.3f * k + blockY);
    glVertex2f(-19.50f * k + blockX, -3.3f * k + blockY);
    glVertex2f(-20.5f * k + blockX, -9.0f * k + blockY);

    glVertex2f(15.5f * k + blockX, -9.0f * k + blockY);
    glVertex2f(16.50f * k + blockX, -3.3f * k + blockY);
    glVertex2f(24.50f * k + blockX, -3.3f * k + blockY);
    glVertex2f(25.5f * k + blockX, -9.0f * k + blockY);
    glEnd();//

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f); // 红色
    for (int i = 0; i <= 360; ++i) {
        float angle = static_cast<float>(i) * (3.14f / 180.0f);
        float x = -15.6 * k + blockX + 4.5f * k * cos(angle);
        float y = -8.2 * k + blockY + 4.5f * k * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f); // 红色
    for (int i = 0; i <= 360; ++i) {
        float angle = static_cast<float>(i) * (3.14f / 180.0f);
        float x = 20.5 * k + blockX + 4.5f * k * cos(angle);
        float y = -8.2 * k + blockY + 4.5f * k * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glLineWidth(1);
    switch (abs((int)blockX) % 2)
    {

    case 0:
        glBegin(GL_LINES);
        glColor3f(0.5f, 0.5f, 0.5f); // 红色
        for (int i = 0; i < 5; ++i) {
            float angle = static_cast<float>(i) * (3.14f / 180.0f) * 72;
            float x1 = 20.5 * k + blockX + 3.0f * k * cos(angle);
            float y1 = -8.2 * k + blockY + 3.0f * k * sin(angle);
            glVertex2f(20.5 * k + blockX, -8.2 * k + blockY);
            glVertex2f(x1, y1);//前轮
            float x = -15.6 * k + blockX + 3.0f * k * cos(angle);
            float y = -8.2 * k + blockY + 3.0f * k * sin(angle);
            glVertex2f(-15.6 * k + blockX, -8.2 * k + blockY);
            glVertex2f(x, y);//后轮
        }
        glEnd(); break;
    case 1:
        glBegin(GL_LINES);
        glColor3f(0.5f, 0.5f, 0.5f); // 红色
        for (int i = -1; i < 4; ++i) {
            float angle = static_cast<float>(i) * (3.14f / 180.0f) * 72;
            float x1 = 20.5 * k + blockX + 3.0f * k * sin(angle + 60);
            float y1 = -8.2 * k + blockY + 3.0f * k * cos(angle + 60);
            glVertex2f(20.5 * k + blockX, -8.2 * k + blockY);
            glVertex2f(x1, y1);//前轮
            float x = -15.6 * k + blockX + 3.0f * k * sin(angle + 60);
            float y = -8.2 * k + blockY + 3.0f * k * cos(angle + 60);
            glVertex2f(-15.6 * k + blockX, -8.2 * k + blockY);
            glVertex2f(x, y);//后轮
        }
        glEnd(); break;
    default:
        break;
    }
}

//背景
void BackGround()
{

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-400, -180.0f);
    glVertex2f(-400, -300.0f);
    glVertex2f(400, -300.0f);
    glVertex2f(400, -180.0f);//草地

    glColor3f(1.0f, 0.95f, 0.75f);
    glVertex2f(-400.0, -70.0f);
    glVertex2f(-400.0, 0.0f);
    glVertex2f(400.0, 0.0f);
    glVertex2f(400.0, -70.0f);//沙滩

    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-400, -180.0f);
    glVertex2f(-400, -70.0f);
    glVertex2f(400, -70.0f);
    glVertex2f(400, -180.0f);//路

    glColor3f(1.0f, 0.36f, 0.0f);
    glVertex2f(-400, 120.0f);
    glVertex2f(400, 120.0f);
    glColor3f(0.88, 0.24, 0.74);
    glVertex2f(400, 240.0f);
    glVertex2f(-400, 240.0f);//天空3

    glVertex2f(-400, 240.0f);
    glVertex2f(400, 240.0f);
    glColor3f(0.2, 0.37, 0.81);
    glVertex2f(400, 300.0f);
    glVertex2f(-400, 300.0f);//天空4

    glColor3f(1.0f, 0.95f, 0.75f);
    glVertex2f(-400, 5.0f);
    glVertex2f(400, 5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(400, 0.0f);
    glVertex2f(-400, 0.0f);//海浪

    glVertex2f(-400, -5.0f);
    glVertex2f(400, -5.0f);
    glColor3f(0.0f, 0.7f, 0.95f);
    glVertex2f(400, 50.0f);
    glVertex2f(-400, 50.0f);//天空2

    glVertex2f(-400, 50.0f);
    glVertex2f(400, 50.0f);
    glColor3f(0.8f, 0.36f, 0.0f);
    glVertex2f(400, 120.0f);
    glVertex2f(-400, 120.0f);//天空1
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.00f, 0.26f, 0.0f); // 红色
    for (int i = 0; i <= 180; ++i) {
        float angle = (float)i * (3.14f / 180.0f);
        float x = 0.0 + 50.0f * cos(angle);
        float y = 120.0 + 50.0f * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();//太阳
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.36f, 0.4f); // 红色
    for (int i = 0; i <= 150; ++i) {
        float angle = (float)(i + 15) * -(3.14f / 180.0f);
        float x = 0.0 + 50.0f * cos(angle);
        float y = 128.0 + 30.0f * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();//倒影
    for (int i = 0; i < 3; i++) {
        glColor3f(0.5, 0.5, 0.5);
        glLineWidth(2);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f + unbX[i], -50.0f + unbY[i]);
        glVertex2f(0.0f + unbX[i], -30.0f + unbY[i]);
        glEnd();
        glBegin(GL_TRIANGLES);
        glColor3f(UR[i], UG[i], UB[i]);
        glVertex2f(-30.0f + unbX[i], -30.0f + unbY[i]);
        glVertex2f(30.0f + unbX[i], -30.0f + unbY[i]);
        glVertex2f(0.0f + unbX[i], -10.0f + unbY[i]);
        glEnd();
    }
    int i = 0;
    for (i = 0; i < 9; i++) {
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-325 + i * 100 + roadX[i], -124.0f);
        glVertex2f(-325 + i * 100 + roadX[i], -126.0f);
        glVertex2f(-375 + i * 100 + roadX[i], -126.0f);
        glVertex2f(-375 + i * 100 + roadX[i], -124.0f);
        glEnd();//路线
        if (i + 12 == 20) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(-400 + boatX, 80.0f + boatY);
            glVertex2f(-430 + boatX, 80.0f + boatY);
            glVertex2f(-450 + boatX, 120.0f + boatY);
            glVertex2f(-400 + boatX, 80.0f + boatY);
            glEnd();//船
        }
    }
}

//树
void Tree()
{
    for (int i = 0; i < 3; i++) {
        glBegin(GL_QUADS);
        glColor3f(0.5f, 0.2f, 0.2f);
        glVertex2f(-0.0f + treeX[i], -300.0f);
        glVertex2f(-30.0f + treeX[i], -300.0f);
        glVertex2f(-12.0f + treeX[i], -250.0f);
        glVertex2f(16.0f + treeX[i], -250.0f);

        glVertex2f(-12.0f + treeX[i], -250.0f);
        glVertex2f(16.0f + treeX[i], -250.0f);
        glVertex2f(40.0f + treeX[i], -200.0f);
        glVertex2f(14.0f + treeX[i], -200.0f);

        glVertex2f(40.0f + treeX[i], -200.0f);
        glVertex2f(14.0f + treeX[i], -200.0f);
        glVertex2f(42.0f + treeX[i], -150.0f);
        glVertex2f(65.0f + treeX[i], -150.0f);

        glVertex2f(65.0f + treeX[i], -150.0f);
        glVertex2f(42.0f + treeX[i], -150.0f);
        glVertex2f(75.0f + treeX[i], -100.0f);
        glVertex2f(92.0f + treeX[i], -100.0f);
        glEnd();

        glColor3f(0.2f, 0.7f, 0.2f);
        glBegin(GL_POLYGON);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glVertex2f(10.00f + treeX[i], -150.0f);
        glVertex2f(30.00f + treeX[i], -110.0f);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glEnd();//后
        glBegin(GL_POLYGON);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glVertex2f(90.00f + treeX[i], -170.0f);
        glVertex2f(110.00f + treeX[i], -140.0f);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glEnd();//后
        glBegin(GL_POLYGON);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glVertex2f(140.00f + treeX[i], -160.0f);
        glVertex2f(135.00f + treeX[i], -125.0f);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glEnd();//后
        glBegin(GL_POLYGON);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glVertex2f(160.00f + treeX[i], -120.0f);
        glVertex2f(145.00f + treeX[i], -90.0f);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glEnd();//后
        glBegin(GL_POLYGON);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glVertex2f(140.00f + treeX[i], -80.0f);
        glVertex2f(115.00f + treeX[i], -65.0f);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glEnd();//后
        glBegin(GL_POLYGON);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glVertex2f(30.00f + treeX[i], -90.0f);
        glVertex2f(70.00f + treeX[i], -80.0f);
        glVertex2f(84.0f + treeX[i], -100.0f);
        glEnd();//后
    }
}

//难度警星
void Star(){
    int i, n;
    float k;
    switch (gameTime){
    case 0:R[0] = 0.5, G[0] = 0.5, B[0] = 0.9; break;
    case 10:R[1] = 0.5, G[1] = 0.5, B[1] = 0.9, moveSpeed = 6.5, boatSpeed = 2.5; break;
    case 20:R[2] = 0.5, G[2] = 0.5, B[2] = 0.9, moveSpeed = 9.5, boatSpeed = 3.5; break;
    case 30:R[3] = 0.5, G[3] = 0.5, B[3] = 0.9, moveSpeed = 12.5, boatSpeed = 4.5; break;
    case 40:R[4] = 0.5, G[4] = 0.5, B[4] = 0.9, moveSpeed = 15.5, boatSpeed = 5.5; break;
    case 50:R[5] = 0.5, G[5] = 0.5, B[5] = 0.9, moveSpeed = 18.5, boatSpeed = 6.5; break;
    }
    carSpeed = boatSpeed + 1;
    bloackSpeed = moveSpeed - 3.0;
    treeSpeed = moveSpeed + 5.0;
    unbSpeed = moveSpeed - 2;
    for (n = 0, k = 0; n < 6; n++, k += 45) {
        glColor3f(R[n], G[n], B[n]);
        glBegin(GL_POLYGON);
        for (i = 0; i < 6; ++i) {
            float angle = (float)i * (3.14f / 180.0f) * 60;
            float x = 150.0 + 10.0f * cos(angle);
            float y = 180.0 + 10.0f * sin(angle);
            glVertex2f(x + k, y);
        }
        glEnd();
        glBegin(GL_TRIANGLES);
        for (i = 0; i < 6; ++i) {
            float angle1 = (float)i * (3.14f / 180.0f) * 60;
            float angle2 = (float)(i + 1) * (3.14f / 180.0f) * 60;
            float x1 = 150.0 + 10.0f * cos(angle1);
            float y1 = 180.0 + 10.0f * sin(angle1);
            float x2 = 150.0 + 10.0f * cos(angle2);
            float y2 = 180.0 + 10.0f * sin(angle2);
            glVertex2f(x1 + k, y1);
            glVertex2f(x2 + k, y2);
            glVertex2f(x1 + k + 10.0f * cos(angle2), y1 + 10.0f * sin(angle2));
        }
        glEnd();
    }
}

//生命
void Lives()
{
    float r, x, y, X, Y;
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++)
    {
        r = (float)(5 * (sin(PI * i / 180.0f) * sqrt(abs(cos(PI * i / 180.0f))) / (sin(PI * i / 180.0f) + 7.0f / 5.0f) - 2.0f * sin(PI * i / 180.0f) + 2.0f));
        x = (float)((r * cos(PI * i / 180)) + 330);
        y = (float)((r * sin(PI * i / 180)) + 230);
        X = (float)((r * cos(PI * (i + 1) / 180)) + 330);
        Y = (float)((r * sin(PI * (i + 1) / 180)) + 230);
        glVertex2f(x, y);
        glVertex2f(X, Y);
        glVertex2f(330, 230);
    }
    glEnd();
    char stringL[3];
    _itoa(lives, stringL, 10);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(350, 217);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)stringL);
}

//显示
void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    if (gameState == 0) StartMenu();
    if (gameState == 1 && carX - 58 > -480) {

        BackGround();
        if ((carY - blockY) < 0) {
            BlockCar();
            Car();
        }
        else
        {
            Car();
            BlockCar();
        }
        Time();
        Star();
        Lives();
        Tree();
    }
    if (lives == 0)
    {
        endMenu();
    }
    glutSwapBuffers(); // 使用双缓冲，交换缓冲区

}

//鼠标事件
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float xPos = x - 400;
        float yPos = -y + 300;
        cout << xPos << "\n" << yPos << "\n";
        if (xPos >= -21.0f && xPos <= 18.0f && yPos >= -7.0f && yPos <= 17.0f && gameState == 0) {
            gameState = 1;
        }
        if (xPos >= -21.0f && xPos <= 18.0f && yPos >= -40.0f && yPos <= -18.0f) {
            exit(0);
        }
        glutPostRedisplay();
    }
}

//键盘事件
void specialKey(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        if (carY < -70) carY += carSpeed;// 按左箭头键，向左移动
        if (checkCollision(65.0 + carX, -16.4 + carY, 123, 30, blockX - 58, blockY - 3, 123, 5) && 65.0 + carX > blockX - 58 && 65.0 + carX - 123 < blockX - 58 + 123)carY -= carSpeed;
        break;
    case GLUT_KEY_DOWN:
        if (carY > -153) carY -= carSpeed;  // 按右箭头键，向右移动
        if (checkCollision(65.0 + carX, -16.4 + carY, 123, 30, blockX - 58, blockY - 3, 123, 5) && 65.0 + carX > blockX - 58 && 65.0 + carX - 123 < blockX - 58 + 123)carY += carSpeed;
        break;
    }
    glutPostRedisplay();  // 请求重新绘制
}

//音乐
void Music()
{
    PlaySound(TEXT("love is a long road.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void Init()
{
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f); // 设置清除颜色为白色
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_2D);
}


void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    int screenPosX = (glutGet(GLUT_SCREEN_WIDTH) - 800) / 2;
    int screenPosY = (glutGet(GLUT_SCREEN_HEIGHT) - 600) / 2;
    glutInitWindowPosition(screenPosX, screenPosY);
    glutCreateWindow("Grand Theft Auto VI");
    Init();
    glutReshapeFunc(Reshape);
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutSpecialFunc(specialKey);
    glutMouseFunc(mouse);
    Music();
    glutMainLoop();
    return 0;
}