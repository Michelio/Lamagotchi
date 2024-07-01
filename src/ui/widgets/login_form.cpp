#include "ui/widgets/login_form.h"

#include <QGridLayout>
#include <QPainter>
#include <iostream>

namespace Lamagotchi
{

namespace Ui
{

LoginForm::LoginForm(QWidget* parent) : QWidget{parent}
{
    auto mainLayout = new QGridLayout{this};

    m_accountsComboBox = new QComboBox{this};
    m_accountsComboBox->setPlaceholderText("Account");

    m_loginSettingsButton = new QPushButton{this};
    QPixmap settingsIcon{"../assets/images/ui/settings-48px.svg"};
    m_loginSettingsButton->setIcon(settingsIcon.scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    m_loginSettingsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_loginSettingsButton->setFlat(true);

    auto loginLabel = new QLabel{"Login:", this};
    loginLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_loginLineEdit = new QLineEdit{this};
    m_loginLineEdit->setPlaceholderText("login");
    m_loginLineEdit->setMaxLength(14);
    m_loginLineEdit->setClearButtonEnabled(true);
    m_loginLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    auto passwordLabel = new QLabel{"Password:", this};
    passwordLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_passwordLineEdit = new QLineEdit{this};
    m_passwordLineEdit->setPlaceholderText("**********");
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    m_passwordLineEdit->setMaxLength(16);
    m_passwordLineEdit->setClearButtonEnabled(true);
    m_passwordLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_logInButton = new QPushButton{"Log In", this};
    m_logInButton->setMaximumWidth(200);
    m_logInButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_saveCheckBox = new QCheckBox{"Remember account", this};
    m_saveCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mainLayout->addWidget(m_accountsComboBox, 0, 0, 1, 2);
    mainLayout->addWidget(m_loginSettingsButton, 0, 2);
    mainLayout->addWidget(loginLabel, 1, 0, 1, 3);
    mainLayout->addWidget(m_loginLineEdit, 2, 0, 1, 3);
    mainLayout->addWidget(passwordLabel, 3, 0, 1, 3);
    mainLayout->addWidget(m_passwordLineEdit, 4, 0, 1, 3);
    mainLayout->addWidget(m_logInButton, 5, 0);
    mainLayout->addWidget(m_saveCheckBox, 5, 1, 1, 2, Qt::AlignRight);

    connect(m_logInButton, &QPushButton::clicked, this, &LoginForm::onLogInClicked);
    connect(m_loginSettingsButton, &QPushButton::clicked, this, &LoginForm::onLoginSettingsClicked);
}

void LoginForm::onLogInClicked()
{
    auto login = m_loginLineEdit->text();
    auto password = m_passwordLineEdit->text();

    if (login.isEmpty() || password.isEmpty())
    {
        // TODO: handle an error
        return;
    }

    emit credentialsReady(login.toStdString(), password.toStdString());
}

void LoginForm::onLoginSettingsClicked()
{
    std::cout << "Login settings clicked\n";
}

} // namespace Ui
} // namespace Lamagotchi
