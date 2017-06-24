#ifndef PLAGIARISMDETECTORWIDGET_H
#define PLAGIARISMDETECTORWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QProgressBar>
#include <QListView>
#include <QStringListModel>
#include <QTextEdit>

#include "detector.h"

/******************************************************************************
 *
 * User Interface
 * Interface :
 *      radio button : to choose the mode : compare files or projects(folders)
 *      button read  : choose a file/folder for detecting
 *                     "read from input" is to read the paths from an input text
 *                     this text should be written as below :
 *                          "File" / "Project" : detect mode
 *                          path1
 *                          path2
 *      button detect: detect the chosen files/folders
 * Display :
 *      the chosen files/folders will be displayed on the right
 *      the rate of progress (by percent) and the result of the algorithm will be displayed below the files/folders
 *      the left two list views shows all the file names if project mode is chosen
 *      the right area shows the similarity table between the files if project mode is chosen
 * Author : czk
 *
 ******************************************************************************/
class PlagiarismDetectorWidget : public QWidget
{
    Q_OBJECT

public:
    PlagiarismDetectorWidget(QWidget *parent = 0);
    ~PlagiarismDetectorWidget();

public slots:
    void change_mode_to_file();
    void change_mode_to_project();

    void read_folder1();
    void read_folder2();
    void read_from_input_text();

    void detect();

private:
    enum {
        MODE_FILE = 1,
        MODE_PROJECT = 2
    };
    int m_mode;

    QGridLayout* m_layout;

    QRadioButton* m_input_file_radio_button;
    QRadioButton* m_input_project_radio_button;

    QPushButton* m_read_folder1_button;
    QPushButton* m_read_folder2_button;
    QPushButton* m_read_input_text_button;

    QLabel* m_display_folder1_label;
    QLabel* m_display_folder2_label;
    QListView* m_display_folder1_list_view;
    QListView* m_display_folder2_list_view;
    QStringListModel* m_string_list_model1;
    QStringListModel* m_string_list_model2;

    QPushButton* m_detect_button;

    QProgressBar* m_progress_bar;
    QProgressBar* m_result_bar;
    QLabel* m_progress_label;
    QLabel* m_result_label;

    QTextEdit* m_similarity_table;

    Detector* m_detector;

    QString m_path1;
    QString m_path2;

    void update_folder();
    void change_mode(int new_mode);
    void read_folder(QString& to_str);
};

#endif // PLAGIARISMDETECTORWIDGET_H
