#include "plagiarism_detector_widget.h"
#include "monitor.h"

#include <QFileDialog>
#include <QMessageBox>

#include<string>
#include<cstring>
#include<cstdio>
using namespace std;

static QString undefined_string = QString("undefined");

PlagiarismDetectorWidget::PlagiarismDetectorWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400, 300);

    m_detector = NULL;
    m_path1 = m_path2 = undefined_string;

    m_layout = new QGridLayout(this);

    m_input_file_radio_button = new QRadioButton(tr("Compare Files"), this);
    m_input_project_radio_button = new QRadioButton(tr("Compare Folders"), this);
    m_input_project_radio_button ->setChecked(true);
    m_mode = MODE_PROJECT;
    connect(m_input_file_radio_button, SIGNAL(clicked()), this, SLOT(change_mode_to_file()));
    connect(m_input_project_radio_button, SIGNAL(clicked()), this, SLOT(change_mode_to_project()));

    m_read_folder1_button = new QPushButton(tr("Read file/folder 1"), this);
    m_read_folder2_button = new QPushButton(tr("Read file/folder 2"), this);
    connect(m_read_folder1_button, SIGNAL(clicked()), this, SLOT(read_folder1()));
    connect(m_read_folder2_button, SIGNAL(clicked()), this, SLOT(read_folder2()));

    m_display_folder1_label = new QLabel(tr("file/folder 1:") + undefined_string, this);
    m_display_folder2_label = new QLabel(tr("file/folder 2:") + undefined_string, this);

    m_read_input_text_button = new QPushButton(tr("Read from text"), this);
    connect(m_read_input_text_button, SIGNAL(clicked()), this, SLOT(read_from_input_text()));

    m_detect_button = new QPushButton(tr("Detect"), this);
    connect(m_detect_button, SIGNAL(clicked()), this, SLOT(detect()));

    m_progress_bar = new QProgressBar(this);
    m_progress_bar ->setMinimum(0);
    m_progress_bar ->setMaximum(100);
    m_progress_bar ->setValue(0);
    m_progress_bar ->setOrientation(Qt::Horizontal);
    m_result_bar = new QProgressBar(this);
    m_result_bar ->setMinimum(0);
    m_result_bar ->setMaximum(100);
    m_result_bar ->setValue(0);
    m_result_bar ->setOrientation(Qt::Horizontal);

    m_progress_label = new QLabel(tr("Progress:"), this);
    m_result_label = new QLabel(tr("Detect result:"), this);

    m_display_folder1_list_view = new QListView(this);
    m_display_folder2_list_view = new QListView(this);
    m_string_list_model1 = new QStringListModel(this);
    m_string_list_model2 = new QStringListModel(this);
    m_display_folder1_list_view ->setModel(m_string_list_model1);
    m_display_folder2_list_view ->setModel(m_string_list_model2);

    m_similarity_table = new QTextEdit(this);

    m_layout ->addWidget(m_input_file_radio_button, 0, 0);
    m_layout ->addWidget(m_input_project_radio_button, 1, 0);
    m_layout ->addWidget(m_read_folder1_button, 0, 1);
    m_layout ->addWidget(m_read_folder2_button, 1, 1);
    m_layout ->addWidget(m_display_folder1_label, 0, 2, 1, 2);
    m_layout ->addWidget(m_display_folder2_label, 1, 2, 1, 2);
    m_layout ->addWidget(m_detect_button, 2, 0);
    m_layout ->addWidget(m_read_input_text_button, 2, 1);
    m_layout ->addWidget(m_progress_label, 2, 2);
    m_layout ->addWidget(m_progress_bar, 2, 3);
    m_layout ->addWidget(m_result_label, 3, 2);
    m_layout ->addWidget(m_result_bar, 3, 3);
    m_layout ->addWidget(m_display_folder1_list_view, 3, 0, 6, 1);
    m_layout ->addWidget(m_display_folder2_list_view, 3, 1, 6, 1);
    m_layout ->addWidget(m_similarity_table, 4, 2, 5, 2);

    setLayout(m_layout);
}

PlagiarismDetectorWidget::~PlagiarismDetectorWidget()
{
    delete m_input_file_radio_button;
    delete m_input_project_radio_button;
    delete m_read_folder1_button;
    delete m_read_folder2_button;
    delete m_display_folder1_label;
    delete m_display_folder2_label;
    delete m_read_input_text_button;
    delete m_detect_button;
    delete m_progress_bar;
    delete m_progress_label;
    delete m_result_bar;
    delete m_result_label;
    delete m_display_folder1_list_view;
    delete m_display_folder2_list_view;
    delete m_string_list_model1;
    delete m_string_list_model2;
    delete m_similarity_table;
    delete m_layout;

    if (m_detector)
        delete m_detector;
}

void PlagiarismDetectorWidget::change_mode(int new_mode)
{
    if (m_mode != new_mode)
    {
        m_path1 = m_path2 = undefined_string;
        update_folder();
    }
    m_mode = new_mode;
}

void PlagiarismDetectorWidget::change_mode_to_file()
{
    change_mode(MODE_FILE);
}

void PlagiarismDetectorWidget::change_mode_to_project()
{
    change_mode(MODE_PROJECT);
}

void PlagiarismDetectorWidget::update_folder()
{
    m_display_folder1_label ->setText(QString("file/folder 1:") + m_path1);
    m_display_folder2_label ->setText(QString("file/folder 2:") + m_path2);
}

void PlagiarismDetectorWidget::read_from_input_text()
{
    QString input_text = QFileDialog::getOpenFileName(this, tr("Choose an input text"), "", tr("text file(*.txt)"));
    if (input_text.size() == 0)
        return;
    FILE * fin = fopen(input_text.toStdString().c_str(), "r");
    char mode[20], path1[1000], path2[1000];
    fscanf(fin,"%s\n%s\n%s\n", mode, path1, path2);
    fclose(fin);

    if (string(mode) == "Project")
        change_mode_to_project();
    else if (string(mode) == "File")
        change_mode_to_file();
    else
        return;

    m_path1 = QString::fromStdString(string(path1));
    m_path2 = QString::fromStdString(string(path2));
    update_folder();
}

void PlagiarismDetectorWidget::read_folder(QString &to_str)
{
    QString temp_str("");
    switch (m_mode)
    {
    case MODE_FILE:
        temp_str = QFileDialog::getOpenFileName(this, tr("Choose a file"), "", tr("C++ file(*.cpp *.cc *.cxx *.h *.hpp *.hxx)"));
        break;
    case MODE_PROJECT:
        temp_str = QFileDialog::getExistingDirectory(this, tr("Choose a directory"));
        break;
    }
    if (temp_str.size() == 0)
        return;
    to_str = temp_str;
    update_folder();
}

void PlagiarismDetectorWidget::read_folder1()
{
    read_folder(m_path1);
}

void PlagiarismDetectorWidget::read_folder2()
{
    read_folder(m_path2);
}

void PlagiarismDetectorWidget::detect()
{
    if (m_path1 == undefined_string || m_path2 == undefined_string)
    {
        QMessageBox::warning(this, tr("Warning!"), tr("path undefined"), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    switch (m_mode)
    {
    case MODE_FILE:
        m_detector = new FileDetector();
        break;
    case MODE_PROJECT:
        m_detector = new ProjectDetectorMonitor(m_string_list_model1, m_string_list_model2, m_progress_bar, m_similarity_table);
        break;
    }

    m_detector ->init(m_path1.toStdString().c_str(), m_path2.toStdString().c_str());
    m_progress_bar ->setValue(0);
    m_result_bar ->setValue(0);
    double result = m_detector ->compare();
    m_result_bar ->setValue(static_cast<int>(result * 100));
}
