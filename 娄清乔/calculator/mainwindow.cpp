#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QDebug"


QString sym[5];//+-X÷符号
QString s;   //输入的字符

QString record[128];
int length;     //输入的字符串长度
int now;        //当前字符串长度

int i=0;
int k=0;        //i、k用于后面的判断中
double number[6];   //最多输入6位数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->textEdit->setText("0");   //初始化输入框
    ui->textEditBef->setText("null");   //初始化历史查询框
    QFont textEditFont ( "Microsoft YaHei", 25, 75);
    ui->textEdit->setFont(textEditFont);        //输入框字体字号
    connect(ui->pushButtonsubdot,&QPushButton::clicked,this,[=](){
       s=s+".";
       ui->textEdit->setText(s);        //点槽函数与信号连接
    });
    connect(ui->pushButtonplus,&QPushButton::clicked,this,[=](){        //加号槽函数与信号连接
       number[k]=s.toDouble();
       k=k+1;
       sym[i]="+";
       s="";
       ui->textEdit->setText(sym[i]);   //按下加号时输入框输入加号
       i=i+1;
    });
    connect(ui->pushButtonsub,&QPushButton::clicked,this,[=](){          //减号槽函数与信号连接
       number[k]=s.toDouble();
       k=k+1;
       sym[i]="-";
       s="";
       ui->textEdit->setText(sym[i]);
       i=i+1;
    });
    connect(ui->pushButtonmul,&QPushButton::clicked,this,[=](){         //乘号
       number[k]=s.toDouble();
       k=k+1;
       sym[i]="×";
       s="";
       ui->textEdit->setText("×");
       i=i+1;
    });
    connect(ui->pushButtondiv,&QPushButton::clicked,this,[=](){   //除号
       number[k]=s.toDouble();
       k=k+1;
       sym[i]="÷";
       s="";
       ui->textEdit->setText("÷");
       i=i+1;
    });

    //数字与信号连接
    connect(ui->pushButton1,&QPushButton::clicked,this,[=](){
       s=s+"1";
       ui->textEdit->setText(s);
    });
    connect(ui->pushButton2,&QPushButton::clicked,this,[=](){
       s=s+"2";
       ui->textEdit->setText(s);
    });
    connect(ui->pushButton3,&QPushButton::clicked,this,[=](){
       s=s+"3";
       ui->textEdit->setText(s);
    });
    connect(ui->pushButton4,&QPushButton::clicked,this,[=](){
       s=s+"4";
       ui->textEdit->setText(s);
    });
    connect(ui->pushButton5,&QPushButton::clicked,this,[=](){
       s=s+"5";
       ui->textEdit->setText(s);
    });
    connect(ui->pushButton6,&QPushButton::clicked,this,[=](){
       s=s+"6";
       ui->textEdit->setText(s);
    });
    connect(ui->pushButton7,&QPushButton::clicked,this,[=](){
       s=s+"7";
       ui->textEdit->setText(s);
    });
    connect(ui->pushButton8,&QPushButton::clicked,this,[=](){
       s=s+"8";
       ui->textEdit->setText(s);
    });
    connect(ui->pushButton9,&QPushButton::clicked,this,[=](){
       s=s+"9";
       ui->textEdit->setText(s);
    });
    connect(ui->pushButton0,&QPushButton::clicked,this,[=](){
       s=s+"0";
       ui->textEdit->setText(s);
    });

    //清零
    connect(ui->pushButtonac,&QPushButton::clicked,this,[=](){
       s=s+"0";
       ui->textEdit->setText(0);
       s="";
       for(int j=0;j<i;j++)  //如果前面输入过运算符，这里就不用输入
       {
           sym[j]="";
       }
       for(int j=0;j<k;j++)
       {
           number[j]=0;         //令输入的数等于0
       }
       i=0;
       k=0;
    });
    connect(ui->pushButtonequ,&QPushButton::clicked,this,&MainWindow::equala);  //等于号

    connect(ui->pushButtonnext,&QPushButton::clicked,this,[=](){        //下一次计算
        now=now+1;
       if(now>length)
       {
            ui->textEditBef->setText("There is no next item ");
            now=now-1;
       }
       else{
           ui->textEditBef->setText(record[now]);}

    });
    connect(ui->pushButtonlast,&QPushButton::clicked,this,[=](){        //上一次计算
        now=now-1;
       if(now<0)
       {
            ui->textEditBef->setText("There is no last item");
            now=now+1;
       }else{
           ui->textEditBef->setText(record[now]);}

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::equala(){              //等于号函数
       number[k]=s.toDouble();
       k=k+1;
       record[length]=record[length]+QString::number(number[0]);
       for(int z=0;z<i;z++)
       {
            record[length]=record[length]+sym[z];
            record[length]=record[length]+QString::number(number[z+1]);
       }
       for(int j=0;j<i;j++)             //判断是否输入运算符
       {

           if(sym[j]=="÷")         //除法
           {
               number[j]=number[j]/number[j+1];   //前面输入的数除以后面输入的数
               }

           if(sym[j]=="×")          //乘法
           {

               number[j]=number[j]*number[j+1];

       }
           }

       double sum=number[0];    //令和或差等于输入的第一个数
       for(int j=0;j<i;j++)
       {

           if(sym[j]=="+")                  //加法
           {
               sum=sum+number[j+1];
           }
           if(sym[j]=="-")              //减法
           {
               sum=sum-number[j+1];
               number[j+1] = sum;
           }
       }
       record[length]=record[length]+"="+QString::number(sum);
       qDebug() << record[length];
       length=length+1;
       now=length;
        ui->textEdit->setText(QString::number(sum) );
         s="";
    }
