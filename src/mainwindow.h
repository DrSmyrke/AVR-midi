#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>
#include <QLayout>
#include <QSpinBox>
#include <QListWidget>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
private slots:
	void genCode();
private:
	QTextBrowser* m_pTextArea;
	QPushButton* m_pButton;
	QListWidget* m_pKeys;
	QSpinBox* m_pDelay;
	void setKeys();
	bool gen=false;
	bool first=true;
	std::vector<QString> keys={"NULL","A4","G#4","G4","F#4","F4","E4","D#4","D4","C#4","C4",
							   "B5","A#5","A5","G#5","G5","F#5","F5","E5","D#5","D5","C#5","C5",
							   "B6","A#6","A6","G#6","G6","F#6","F6","E6","D#6","D6"};
	QString intro="The program was created by DrSmyrke<br>"
				  "<a href=\"https://github.com/DrSmyrke/AVR-midi\">https://github.com/DrSmyrke/AVR-midi</a><br>"
				  "Thank you for choosing my application!";
};

#endif // MAINWINDOW_H
