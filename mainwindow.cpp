#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   //capturamos variables de la interfaz
   QString Sultimo = ui->Sut->text();// captura el valor en qstring de la ventana de la interfaz.
   QString Syield = ui->Esfulti->text();// captura el valor en qstring de la ventana de la interfaz.
   QString LoadMax = ui->Cmax->text();
   QString LoadMin = ui->Cmin->text();
   // QString Elasticidad = ui->ModE->text();// captura el valor en qstring de la ventana de la interfaz.
   //QString Iner = ui->Inercia->text();// captura el valor en qstring de la ventana de la interfaz.
   QString dinter = ui->Rint->text();// captura el valor en qstring de la ventana de la interfaz.
   QString Dext = ui->Rext->text();// captura el valor en qstring de la ventana de la interfaz.
   //QString Longi = ui->LonTub->text();// captura el valor en qstring de la ventana de la interfaz.
   //QString Ciclos = ui->Ciclaje->text();// captura el valor en qstring de la ventana de la interfaz.
   //QString kgeometrico = ui->Kgeome->text();// captura el valor en qstring de la ventana de la interfaz.
   QString kfluctuante = ui->Kfluc->text();// captura el valor en qstring de la ventana de la interfaz.
   QString Confiabilidad = ui->confia->text();//
   QString Seprim = ui->Sepri->text();//
   QString Radinteres = ui->Rinte->text();//
   QString Temp = ui->Tc->text();//
   QString Ktorci = ui->ktorcion->text();//
   //definimos variables operativas
   double Sulti = Sultimo.toDouble(); //contiene el valor ingresado del usuario
   double Syie = Syield.toDouble(); //contiene el valor ingresado del usuario
   double LoaMax = LoadMax.toDouble();
   double LoaMin = LoadMin.toDouble();
  // double Elastic = Elasticidad.toDouble(); //contiene el valor ingresado del usuario
   //double Miner = Iner.toDouble(); //contiene el valor ingresado del usuario
   double Rinterno = dinter.toDouble(); //contiene el valor ingresado del usuario
   double Rexterno = Dext.toDouble(); //contiene el valor ingresado del usuario
   //double Cicl = Ciclos.toDouble(); //contiene el valor ingresado del usuario
   double Conf = Confiabilidad.toDouble();
   double Seprima = Seprim.toDouble();
   double RadioInteres = Radinteres.toDouble();
   double T = Temp.toDouble();
   double PI=3.14159265;
   double a=0;
   double inercia =0;
   double Mpolar=0;
   double Falt=0;
   double Fmed=0;
   double ejeNeutro=0;
   double Mmax=0;
   double Mmin=0;
   double Tmax=0;
   double Tmin=0;
   double Malternante=0;
   double Talternante=0;
   double Mmedio=0;
   double Tmedio=0;
   double A95=0;
   double Dequiv=0;
   double kf= kfluctuante.toDouble();
   double kfm=0;
   //Factor de carga
   double Ccarga=0;
   //factor de tamaño
   double Ctama=0;
   //factor de superficie
   double A=0;
   double b=0;
   double Csuper=0;
   //factor de confiabilidad
   double Cconf=0;
   //factor de temperatura
   double Ctemp=0;
   //limite de resistencia a la fatiga corregido
   double Se=0;
   //factor de Seguridad
   double FSone=0;
   double FStwo=0;
   double FSthree=0;
   double SigMas=0;
   double SigAs=0;
   double ZS=0;
   double OZ=0;
   double FSfour=0;
   double Dexte=0;
   double Dinte=0;
   double MmaxG=0;
   double TmaxG=0;
   double Sigmamax =0;
   double MminG =0;
   double TminG=0;
   double Sigmamin=0;
   double Sigmamedio=0;
   double ks= Ktorci.toDouble();
   double kfmt=0;
   double VmAlt=0;
   double VmMed=0;

   inercia = ((PI/4)*(pow(Rexterno,4)-pow(Rinterno,4)));
   ejeNeutro= Rexterno;
   Dexte= 2*Rexterno;
   Dinte= 2*Rinterno;

   if(ui->radioMacizo->isChecked())
   {
       Mpolar= ((PI/2)*pow(ejeNeutro,4));
   }else if(ui->radioHueco->isChecked())
   {
       Mpolar= ((PI/2)*(pow(Rexterno,4)-pow(Rinterno,4)));
   }

   Falt= ((LoaMax-LoaMin)/2);
   Fmed= ((LoaMax+LoaMin)/2);
   // Esfuerzo de flexión y torcion maximos y minimos
   Mmax = ((LoaMax*ejeNeutro)/inercia);
   Mmin = ((LoaMin*ejeNeutro)/inercia);
   Tmax= (((LoaMax*a)*ejeNeutro)/Mpolar);
   Tmin= (((LoaMin*a)*ejeNeutro)/Mpolar);
   // Esfuerzo de flexion y torcion alternante
   Malternante = ((Falt*ejeNeutro)/inercia);
   Talternante = ((Falt*a)/Mpolar);
   // Esfuerzo de flexion y torcion medio
   Mmedio = ((Fmed*ejeNeutro)/inercia);
   Tmedio = ((Fmed*a)/Mpolar);

   //vamos a cacular los sigma máximo global.
   MmaxG= kf*Mmax;
   TmaxG= kf*Tmax;
   Sigmamax= sqrt(pow(MmaxG,2)+pow(TmaxG,2));
   //sigmas minimos globales
   MminG= kf*Mmin;
   TminG= kf*Tmin;
   Sigmamin= sqrt(pow(MminG,2)+pow(TminG,2));
   //calculamos sigma medio
   Sigmamedio= sqrt(pow(Mmedio,2)+pow(Tmedio,2));

  // calculamos los factores de concentación de esfuerzos
   if(Sigmamax < Syie)
   {
       kfm=kf;
   }
   else {
       kfm= ((Syie-(kf*Sigmamin))/Sigmamedio);
   }

   if(Sigmamax < Syie)
   {
       kfmt=ks;
   }else
   {
       kfmt= ((Syie-(ks*Sigmamin))/Sigmamedio);
   }
   Talternante= Talternante*kfmt;
   Malternante = Malternante*kfm;
   Mmedio = Mmedio*kfm;
   Tmedio =Tmedio*kfmt;

   //ESFUERZOS DE VON MISSES
   VmAlt = sqrt((pow(Malternante,2)+6*pow(Talternante,2))/2);
   VmMed = sqrt((pow(Mmedio,2)+6*pow(Tmedio,2))/2);
   //Factor de carga
   if(ui->radioFlexion->isChecked())
   {
       Ccarga= 1;
   }else {
       if(ui->radioTraccion->isChecked())
       {
           Ccarga=0.7;
       }else {
           if(ui->radioTorsion->isChecked())
           {
               Ccarga=0.577;
           }
       }
   }

   //Factor de tamaño con mm
   A95= (0.0766*pow(Dexte,2));
   Dequiv=sqrt((A95/0.0766));
   if(Dequiv < 8)
   {
       Ctama= 1;
   }else {
       if(Dequiv >8 && Dexte < 250)
       {
           Ctama=(1.189*pow(Dequiv,(-0.097)));
       }else {
           if(Dequiv > 250)
           {
               Ctama=0.6;
           }
       }
   }

   //Factor de superficie
   if(ui->radioEsmer->isChecked())
   {
       A=1.58;
       b=(-0.085);
       Csuper= A*((pow(Sulti,b)));
   }else {
       if(ui->radiomaqui->isChecked())
       {
           A=4.51;
           b=(-0.265);
           Csuper= (A*(pow(Sulti,b)));
       }else {
           if(ui->radioRollCal->isChecked())
           {
               A=57.7;
               b=(-0.718);
               Csuper= A*(pow(Sulti,b));
           }else {
               if(ui->radioForja->isChecked())
                   {
                       A=272;
                       b=(-0.995);
                       Csuper= A*(pow(Sulti,b));
                   }
              }
       }
   }

   //factor de confiabilidad
   if(Conf==50)
   {
       Cconf=1;
   }else if(Conf==90)
   {
       Cconf=0.897;
   }else if(Conf==95){
       Cconf=0.868;
   }else if(Conf==99){
       Cconf=0.814;
   }else if(Conf==99.9){
       Cconf=0.753;
   }
   //factor de temperatura
   if(T<=450)
   {
       Ctemp=1;
   }else if(T > 450 && T <= 550 )
   {
       Ctemp= 1-(0.0058*(T-450));
   }
   //limite de resistencia a la fatiga corregido
   Se=Cconf*Ctemp*Csuper*Ccarga*Ctama*Seprima;
   //Factores de seguridad
   FSone=((Syie)/(VmMed))*(1-((VmAlt/Syie)));
   FStwo=((Se/VmAlt)*(1-(VmMed)/Sulti));
   FSthree=(((Se*Sulti))/((VmAlt*Sulti)+(VmMed*Se)));
   SigMas=(Sulti*(pow(Se,2)-(Se*VmAlt)+(Sulti*VmMed)))/(pow(Se,2)+pow(Sulti,2));
   SigAs=((-Se/Sulti)*SigMas)+Se;
   ZS=sqrt(pow((VmMed-SigMas),2)+pow((VmAlt-SigAs),2));
   OZ=sqrt(pow(VmAlt,2)+pow(VmMed,2));
   FSfour=(OZ+ZS)/OZ;

   //varibales iniciales
   ui->listWidget->addItem("VARIABLES INICIALES: ");
   ui->listWidget->addItem("Sut: "+QString::number(Sulti));
   ui->listWidget->addItem("Sy: "+QString::number(Syie));
   ui->listWidget->addItem("Carga Máxima: "+QString::number(LoaMax));
   ui->listWidget->addItem("Carga Mínima: "+QString::number(LoaMin));
   //ui->listWidget->addItem("Modulo Elástico: "+QString::number(Elastic));
   ui->listWidget->addItem("Diámetro interno: "+QString::number(Rinterno));
   ui->listWidget->addItem("Diámetro externo: "+QString::number(Rexterno));
  // ui->listWidget->addItem("Ciclaje: "+QString::number(Cicl));
   ui->listWidget->addItem("Confiabilidad: "+QString::number(Conf));
   //ui->listWidget->addItem("Radio del punto: "+QString::number(RadioInteres)+"\n");
   //variables calculadas

   ui->listWidget->addItem(("VON MISSES ALTERNANTE Y MEDIO: "));
   ui->listWidget->addItem("Von Misses Alternante: "+QString::number(VmAlt));
   ui->listWidget->addItem("Von Misses Medio: "+QString::number(VmMed)+"\n");
   //concentradores de esfuerzo
   ui->listWidget->addItem(("CONCENTRADORES DE ESFUERZOS: "));
   ui->listWidget->addItem("Kf: "+QString::number(kf));
   ui->listWidget->addItem("Kfm: "+QString::number(kfm));
   ui->listWidget->addItem("Kfmt: "+QString::number(kfmt)+"\n");
   //Factores C111
   ui->listWidget->addItem(("FACTORES C: "));
   ui->listWidget->addItem("Factor de Carga: "+QString::number(Ccarga));
   ui->listWidget->addItem("Factor de Tamaño: "+QString::number(Ctama));
   ui->listWidget->addItem("Factor de Superficie: "+QString::number(Csuper));
   ui->listWidget->addItem("Factor de Confiabilidad: "+QString::number(Cconf));
   ui->listWidget->addItem("Factor de Temperatura: "+QString::number(Ctemp)+"\n");
   //limite de resistencia a la fatiga corregido.
   ui->listWidget->addItem(("LIMITE DE RESISTENCIA A LA FATIGA: "));
   ui->listWidget->addItem("Se Corregido: "+QString::number(Se)+"\n");
   //Variables para calcular FS
   ui->listWidget->addItem(("VARIABLES PARA CALCULAR FS: "));
   ui->listWidget->addItem("Sigma M@S: "+QString::number(SigMas));
   ui->listWidget->addItem("Sigma a@s: "+QString::number(SigAs));
   ui->listWidget->addItem("ZS: "+QString::number(ZS));
   ui->listWidget->addItem("OZ: "+QString::number(OZ)+"\n");
   //Se del material y Se corregido
   ui->listWidget->addItem(("Se DEL MATERIA & Se CORREGIDO: "));
   ui->listWidget->addItem("Se del material: "+QString::number(Seprima));
   ui->listWidget->addItem("Se Corregido: "+QString::number(Se)+"\n");
   //factores de seguridad
   ui->listWidget->addItem(("FACTORES DE SEGURIDAD: "));
   ui->listWidget->addItem("Factor de seguridad 1: "+QString::number(FSone));
   ui->listWidget->addItem("Factor de seguridad 2: "+QString::number(FStwo));
   ui->listWidget->addItem("Factor de seguridad 3: "+QString::number(FSthree));
   ui->listWidget->addItem("Factor de seguridad 4: "+QString::number(FSfour));

   ui->listWidget->addItem("-------------------------------------------""\n");



}

