#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <string>
#include <vector>

// Neuroscan API
#include "NSDevice.h"
#pragma comment (lib,"NSDevice.lib")
// LSL API
#include <lsl_cpp.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent, const std::string &config_file);
    ~MainWindow();
    
private slots:
    // config file dialog ops (from main menu)
    void load_config_dialog();
    void save_config_dialog();

    // start the Neuroscan connection
    void link_neuroscan();

    // close event (potentially disabled)
    void closeEvent(QCloseEvent *ev);
private:
    // background data reader thread
	void read_thread(int ampType, std::string address, int nRate, int nChannels, int nBlocks);

    // raw config file IO
    void load_config(const std::string &filename);
    void save_config(const std::string &filename);
	
    boost::shared_ptr<boost::thread> reader_thread_;	// our reader thread

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
