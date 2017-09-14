#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<QTextEdit>//提供多行文本框
#include<QPushButton>//提供按键
#include<QAction>//实现功能的动作
#include<QVector>//提供一个动态数组的模板类
class Calculator : public QWidget
{
  Q_OBJECT//所有Qt对象的基类

public:
  Calculator(QWidget *parent = 0);
  ~Calculator();
private:
  QTextEdit*  screenTextEdit;//屏幕文本框
  QPushButton*    button1;
  QPushButton*    button2;
  QPushButton*    button3;
  QPushButton*    button4;
  QPushButton*    button5;
  QPushButton*    button6;
  QPushButton*    button7;
  QPushButton*    button8;
  QPushButton*    button9;
  QPushButton*    button0;
  QPushButton*    buttonx;
  QPushButton*    buttondivide;//除
  QPushButton*    buttonadd;//加
  QPushButton*    buttonsub;//减
  QPushButton*    buttondot;//乘
  QPushButton*    buttonequal;//等于
  QPushButton*    buttonclear;
  QPushButton*    buttonback;
  QPushButton*    buttonLArc;
  QPushButton*    buttonRArc;
  bool isEnter;
  double sum ;
  int i;
  int j;
  double result;
  bool isPoint;
  bool isLArc;
  char sign;
  bool isTwoOptrsFlag;
  bool isEqualClicked;
  int f1[7];
  int f2[7];

  QVector<double>vectorOpnd;
  QVector<char>vectorOptr;
  QVector<char>vectorExp;

  bool isTwoOptr(QPushButton *button);
  void initConnect();
  void initVector();
  double operate(double a, char theat, double b);
  char precedeSign(char optr1, char optr2);
  int char2num(char optr);
  void initData();
  char button2char(QPushButton *button);
  void getDigital(char digital);
  void getSign(char ch);
  bool pickSign(char ch);
  bool pushVector(char optr);
  void getResult();
private slots:
  void getButton();
  void clearScreen();
  void myBackSpace();

};

#endif // CALCULATOR_H

