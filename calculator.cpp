#include "calculator.h"
#include<QGridLayout>//按比例设定布局

Calculator::Calculator(QWidget *parent)
  : QWidget(parent)
 {
  initData();//初始化
  setWindowTitle("计算器");
  setWindowIcon(QIcon(":/calculator.png"));
  screenTextEdit = new QTextEdit;//文本框
  screenTextEdit->setFixedHeight(50);
  screenTextEdit->setFont(QFont("Courier 10 Pitch", 18, QFont::Bold));
  screenTextEdit->setReadOnly(true);
  button1 = new QPushButton("1");
  button2 = new QPushButton("2");
  button3 = new QPushButton("3");
  button4 = new QPushButton("4");
  button5 = new QPushButton("5");
  button6 = new QPushButton("6");
  button7 = new QPushButton("7");
  button8 = new QPushButton("8");
  button9 = new QPushButton("9");
  button0 = new QPushButton("0");
  buttonx = new QPushButton("×");
  buttonadd = new QPushButton("+");
  buttonsub = new QPushButton("-");
  buttonback = new QPushButton("back");
  buttondivide = new QPushButton("/");
  buttondot = new QPushButton(".");
  buttonLArc = new QPushButton("(");
  buttonRArc = new QPushButton(")");
  buttonequal = new QPushButton("=");
  buttonclear = new QPushButton("clear");

  initConnect();

  QGridLayout *gridLayout = new QGridLayout;//设定布局后，重写的坐标
  gridLayout->addWidget(screenTextEdit, 0, 0, 2, 5);
  gridLayout->addWidget(button1, 2, 0, 1, 1);
  gridLayout->addWidget(button2, 2, 1, 1 ,1);
  gridLayout->addWidget(button3, 2, 2, 1, 1);
  gridLayout->addWidget(buttonadd, 2, 3, 1, 1);
  gridLayout->addWidget(buttonsub, 2, 4, 1, 1);
  gridLayout->addWidget(button4, 3, 0, 1, 1);
  gridLayout->addWidget(button5, 3, 1, 1, 1);
  gridLayout->addWidget(button6, 3, 2, 1, 1);
  gridLayout->addWidget(buttonx, 3, 3, 1, 1);
  gridLayout->addWidget(buttondivide, 3, 4, 1, 1);
  gridLayout->addWidget(button7, 4, 0, 1, 1);
  gridLayout->addWidget(button8, 4, 1, 1, 1);
  gridLayout->addWidget(button9, 4, 2, 1, 1);
  gridLayout->addWidget(buttonLArc, 4, 3, 1, 1);
  gridLayout->addWidget(buttonRArc, 4, 4, 1, 1);
  gridLayout->addWidget(button0, 5, 0, 1, 1);
  gridLayout->addWidget(buttondot, 5, 1, 1, 1);
  gridLayout->addWidget(buttonback, 5, 2, 1, 1);
  gridLayout->addWidget(buttonclear, 5, 3, 1, 1);
  gridLayout->addWidget(buttonequal, 5, 4, 1, 1);

  setLayout(gridLayout);
  initVector();
}
void Calculator::initConnect()//在线调整，测试
{
  connect(button0, &QPushButton::clicked, this, &Calculator::getButton);
  connect(button1, &QPushButton::clicked, this, &Calculator::getButton);
  connect(button2, &QPushButton::clicked, this, &Calculator::getButton);
  connect(button3, &QPushButton::clicked, this, &Calculator::getButton);
  connect(button4, &QPushButton::clicked, this, &Calculator::getButton);
  connect(button5, &QPushButton::clicked, this, &Calculator::getButton);
  connect(button6, &QPushButton::clicked, this, &Calculator::getButton);
  connect(button7, &QPushButton::clicked, this, &Calculator::getButton);
  connect(button8, &QPushButton::clicked, this, &Calculator::getButton);
  connect(button9, &QPushButton::clicked, this, &Calculator::getButton);
  connect(buttonx, &QPushButton::clicked, this, &Calculator::getButton);
  connect(buttonadd, &QPushButton::clicked, this, &Calculator::getButton);
  connect(buttondivide, &QPushButton::clicked, this, &Calculator::getButton);
  connect(buttondot, &QPushButton::clicked, this, &Calculator::getButton);
  connect(buttonsub, &QPushButton::clicked, this, &Calculator::getButton);
  connect(buttonRArc, &QPushButton::clicked, this, &Calculator::getButton);
  connect(buttonLArc, &QPushButton::clicked, this, &Calculator::getButton);

  connect(buttonback, &QPushButton::clicked, this, &Calculator::myBackSpace);
  connect(buttonclear, &QPushButton::clicked, this, &Calculator::clearScreen);
  connect(buttonequal, &QPushButton::clicked, this, &Calculator::getButton);
}

bool Calculator::isTwoOptr(QPushButton *button)//测试加减乘除
{
  if(button == buttonadd || button ==buttonsub
          || button == buttonx || button == buttondivide)
      return true;
  else
      return false;
}
void Calculator::myBackSpace()
{
  QTextCursor cursor = screenTextEdit->textCursor();
  cursor.deletePreviousChar();
  if(!isEqualClicked)
      vectorExp.pop_back();

}

void Calculator::getButton()
{
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  if(isTwoOptrsFlag && isTwoOptr(button))
  {

  }
  else{

      vectorExp.append(button2char(button));
      isEqualClicked = false;
      isTwoOptrsFlag = false;
      if(!isEnter)
          screenTextEdit->append("");
      screenTextEdit->insertPlainText(button->text());
      isEnter = true;
      if(button == buttonadd || button == buttonsub
          || button == buttonx || button == buttondivide)
      isTwoOptrsFlag = true;
  }

  if(button == buttonequal)
  {
      isEqualClicked = true;
      getResult();
  }
}

void Calculator::getResult()
{
  while(!vectorExp.isEmpty())
  {
      char ch = vectorExp.first();
      vectorExp.removeFirst();
      getDigital(ch);
      getSign(ch);
  }
}
void Calculator::getDigital(char digital)
{
  if(digital == '0' || digital == '1' || digital == '2'
          || digital == '3' || digital == '4' || digital == '5'
          || digital == '6' || digital == '7' || digital == '8'
          || digital == '9' )
  {
      if(isPoint)
          i *= 10;
      j = 0;
      sum = sum * 10 + (digital - '0');
      isLArc = false;

  }
  else if(digital == '.')
  {
      isPoint = true;
      isLArc = false;
  }
}

void Calculator::getSign(char ch)
{
  if(isLArc && ch != '(' && ch != ')')
  {
      sign = ch;
  }
  else if(ch == '+' || ch == '-'
          || ch == '*' || ch == '/'
          || ch == '=' ||  ch == '('
          || ch == ')')
  {
      if(ch == '(')
          isLArc = true;
      else
          isLArc = false;

      j++;
      if(j <=1)
      {
          if(sign == '-')
              sum = sum * (-1);
          sign = ' ';
          vectorOpnd.append(sum / i);
          isLArc = false;
          i = 1;
          sum = 0;
          isPoint = false;
      }
      pickSign(ch);

    }
}


bool Calculator::pickSign(char ch)
{
  char theta;
  double a, b;
  if(ch == '=')
  {
      while(vectorOptr.last() != '#')
      {
          do{
              theta = vectorOptr.last();
              vectorOptr.pop_back();
          }while(theta == '(' || theta == ')');

          if(theta != '#')//void 8(,9),8()
          {
              b = vectorOpnd.last();vectorOpnd.pop_back();
              a = vectorOpnd.last();vectorOpnd.pop_back();
              vectorOpnd.append(operate(a, theta, b));
          }
          else if(theta == '#')
                  vectorOptr.append('#');
      }
      result = vectorOpnd.last();
      screenTextEdit->insertPlainText(QString("%1").arg(result));
      vectorOpnd.clear();
      vectorOptr.clear();
      initVector();
      isEnter = false;
      return true;
  }
  pushVector(ch);
  return true;
}

bool Calculator::pushVector(char optr)
{
  char theta;
  double a, b;
  if(optr == ')')
  {
      do{
          theta = vectorOptr.last();
          vectorOptr.pop_back();
      }while(theta == '(' || theta == ')');
      if(theta != '#')// void 8(,9),8()
      {
          b = vectorOpnd.last();vectorOpnd.pop_back();
          a = vectorOpnd.last();vectorOpnd.pop_back();
          vectorOpnd.append(operate(a, theta, b));
      }
      else
      {
          vectorOptr.append('#');
      }
      return true;
  }

  switch(precedeSign(vectorOptr.last(),optr))
  {
  case '<':
      vectorOptr.append(optr);
      break;
  case '=':
      vectorOptr.pop_back();
      break;
  case '>':
      theta = vectorOptr.last();
      vectorOptr.pop_back();
      b = vectorOpnd.last();
      vectorOpnd.pop_back();
      a = vectorOpnd.last();
      vectorOpnd.pop_back();
      vectorOpnd.append(operate(a, theta, b));
      vectorOptr.append(optr);
      break;
  }
  return true;
}
void Calculator::clearScreen()
{
  screenTextEdit->clear();
  result = 0;
  isEnter = true;
}

double Calculator::operate(double a, char theta, double b)//函数实现加减乘除
{
  double sum1;
  switch (theta) {
  case '+':
      sum1 = a + b;    break;
  case '-':
      sum1 = a - b;    break;
  case '*':
      sum1 = a * b;    break;
  case '/':
      sum1 = a / b;    break;
  }
  return sum1;
}

char Calculator::button2char(QPushButton *button)//输入键
{
  char optr;
  if(button == buttonadd)
      optr = '+';
  else if(button == buttonsub)
      optr = '-';
  else if(button == buttonx)
      optr = '*';
  else if(button == buttondivide)
      optr = '/';
  else if(button == buttonLArc)
      optr = '(';
  else if(button == buttonRArc)
      optr = ')';
  else if(button == buttonequal)
      optr = '=';
  else if(button == button0)
      optr = '0';
  else if(button == button1)
      optr = '1';
  else if(button == button2)
      optr = '2';
  else if(button == button3)
      optr = '3';
  else if(button == button4)
      optr = '4';
  else if(button == button5)
      optr = '5';
  else if(button == button6)
      optr = '6';
  else if(button == button7)
      optr = '7';
  else if(button == button8)
      optr = '8';
  else if(button == button9)
      optr = '9';
  else if(button == buttondot)
      optr = '.';
  return optr;
}
char Calculator::precedeSign(char optr1, char optr2)
{
  char compare;
    int i1 = char2num(optr1);
  int i2 = char2num(optr2);

  if(f1[i1] > f2[i2])
      compare =  '>';
  else if(f1[i1] < f2[i2])
          compare =  '<';
  else
      compare  = '=';
  return compare;

}
int Calculator::char2num(char optr)
{
  int ii;
  switch(optr)
  {
  case '+':
      ii = 0;  break;
  case '-':
      ii = 1;  break;
  case '*':
      ii = 2;  break;
  case '/':
      ii = 3;  break;
  case '(':
      ii =  4;  break;
  case ')':
      ii =  5;  break;
  default:
      ii = 6;
  }
  return ii;
}
void Calculator::initData()
{
  i = 1;
  j = 0;
  sum = 0;
  f1[0] = f1[1] =3;    f1[2] = f1[3] = 5;  f1[4] = 1;
  f1[5] = 6;  f1[6] = 0;
  f2[0] = f2[1] = 2;  f2[2] = f2[3]  = 4; f2[4] = 6;
  f2[5] = 1;  f2[6] = 0;
  isPoint = false;
  isLArc = false;
  sign = ' ';
  isTwoOptrsFlag = false;
  isEqualClicked = false;
  isEnter = true;
}

void Calculator::initVector()
{
  vectorOptr.append('#');
  vectorOpnd.append(0);
  vectorOpnd.append(0);
  vectorOpnd.append(0);
}

Calculator::~Calculator()
{

}

