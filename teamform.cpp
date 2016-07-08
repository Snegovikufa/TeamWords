#include "teamform.h"
#include "ui_teamform.h"
#include "mainapplication.h"
#include "applicationsettings.h"

TeamForm::TeamForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamForm)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onClick()));
    setWindowIcon(QIcon(QString("://images/png/icon32.png")));
}

TeamForm::~TeamForm()
{
    delete ui;
}

void TeamForm::onTextChanged(QString text)
{
    if (text.trimmed() == "")
    {
        ui->pushButton->setEnabled(false);
    }
    else
    {
        ui->pushButton->setEnabled(true);
    }
}

void TeamForm::onClick()
{
    ApplicationSettings::instance()->setTeamDomain(ui->lineEdit->text());
    MainApplication::instance()->getMainWindow()->show();
    close();
}
