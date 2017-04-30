#include "mainwindow.h"

#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	m_pKeys=new QListWidget();
		m_pKeys->setMaximumWidth(100);
		connect(m_pKeys,&QListWidget::itemDoubleClicked,this,[this](QListWidgetItem *item){
			if(first){
				first=false;
				m_pTextArea->clear();
			}
			QString key=QString::number(item->data(Qt::UserRole).toInt(),2);
			QString d=QString::number((m_pDelay->value()*2)-1,2);
			while(key.length()<5) key="0"+key;
			m_pTextArea->append(d+key);
		});
	m_pDelay=new QSpinBox();
		m_pDelay->setMaximum(7);
		m_pDelay->setMinimum(1);
	m_pButton=new QPushButton("Generate code");
		connect(m_pButton,&QPushButton::clicked,this,&MainWindow::genCode);
	m_pTextArea=new QTextBrowser();
		m_pTextArea->setHtml(intro);
		m_pTextArea->setOpenExternalLinks(false);
		m_pTextArea->setReadOnly(false);
		m_pTextArea->setOpenLinks(false);
		connect(m_pTextArea,&QTextBrowser::anchorClicked,this,[this](const QUrl &link){
					QDesktopServices::openUrl(link);
		});

	setWindowTitle("AVR midi v0.1");
	QWidget* centrWidget=new QWidget(this);
		QGridLayout* box=new QGridLayout();
		box->addWidget(m_pDelay,0,0);
		box->addWidget(m_pKeys,1,0);
		box->addWidget(m_pButton,0,1);
		box->addWidget(m_pTextArea,1,1);
	centrWidget->setLayout(box);
	setCentralWidget(centrWidget);
	setKeys();
}
MainWindow::~MainWindow()
{
}
void MainWindow::genCode()
{
	if(gen){
		gen=false;
		m_pButton->setText("Generate code");
		m_pTextArea->clear();
		return;
	}else{
		gen=true;
		m_pButton->setText("Clear");
	}
	QString text="#include <avr/pgmspace.h>\n"
		"#include <avr/io.h>\n"
		"*/		The program was created by DrSmyrke\n"
		"*		https://github.com/DrSmyrke/AVR-midi\n"
		"*/		Thank you for choosing my application!\n"
		"void delay_note (unsigned int d){\n"
		"	unsigned int i;\n"
		"	for (i=0; i< d; i++) delay(100);\n"
		"}\n"
		"//Tables of frequencies of notes and durations\n"
		"unsigned int  notefreq[] PROGMEM = {0,4748,4480,4228,3992,3768,3556,3356,3168,2990,2822,2664,2514,2374,2240,2114,1996,1884,1778,1678,1584,1495,1411,1332,1257,1187,1120,1057,998,942,889,839,792};\n"
		"unsigned int  pausedelay[] PROGMEM = {32,64,128,256,512,1024,2048,4096};\n"
		"unsigned char melody[] PROGMEM = {\n"
		;
	for(auto elem:m_pTextArea->toPlainText().split("\n")){
		text+=QString::number(elem.toInt(nullptr,2))+",";
	}
	text+="0\n};\n"
		"void play(){\n"
		"	TCCR1A=0x00;\n"
		"	TCCR1B=0x09;\n"
		"	PORTB=0x00;\n"
		"	DDRB  |=  _BV(PB1);\n"
		"	PORTB &= ~_BV(PB1);\n"
		"	unsigned char freqnote;\n"
		"	unsigned char delaynote;\n"
		"	unsigned char tmp=1;\n"
		"	unsigned int offset=100;\n"
		"	int ch=0;\n"
		"	while((eeprom_read(offset+ch))!=0){\n"
		"		tmp=eeprom_read(offset+ch);\n"
		"		freqnote=tmp&0x1F;			// Code note\n"
		"		delaynote=(tmp>>5)&0x07;	// Code delay\n"
		"		if(freqnote!=0){			// If not pause\n"
		"			// включаем звук\n"
		"			OCR1A=pgm_read_word(&(notefreq[freqnote]));\n"
		"			TCCR1A=0x40;\n"
		"		}\n"
		"		delay_note(pgm_read_word(&(pausedelay[delaynote])));\n"
		"		TCCR1A=0x00;//sound off\n"
		"		delay_note(8);//pause\n"
		"		ch++;\n"
		"	}\n"
		"	DDRB  |=  _BV(PB1);\n"
		"	PORTB &= ~_BV(PB1);\n"
		"}";
	m_pTextArea->setText(text);
}
void MainWindow::setKeys()
{
	for(int i=0;i<=31;i++){
		QListWidgetItem* item=new QListWidgetItem(keys[i]+"-"+QString::number(i,2));
			item->setData(Qt::UserRole,i);
		m_pKeys->addItem(item);
	}
}
