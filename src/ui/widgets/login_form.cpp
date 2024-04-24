#include "ui/widgets/login_form.h"

namespace Lamagotchi
{

namespace Ui
{

LoginForm::LoginForm(QWidget* parent) : QWidget{parent}
{
    m_mainLayout = new QGridLayout{this};

    m_accountsComboBox = new QComboBox;
    m_accountsComboBox->setPlaceholderText("Account");

    m_loginLabel = new QLabel{"Login:"};
    m_loginLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_loginLineEdit = new QLineEdit{};
    m_loginLineEdit->setPlaceholderText("login");
    m_loginLineEdit->setMaxLength(14);
    m_loginLineEdit->setClearButtonEnabled(true);
    m_loginLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_passwordLabel = new QLabel{"Password:"};
    m_passwordLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_passwordLineEdit = new QLineEdit{};
    m_passwordLineEdit->setPlaceholderText("**********");
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    m_passwordLineEdit->setMaxLength(16);
    m_passwordLineEdit->setClearButtonEnabled(true);
    m_passwordLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_loginButton = new QPushButton{"Login"};
    m_loginButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_saveCheckBox = new QCheckBox{"Remember account"};
    m_saveCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_mainLayout->addWidget(m_accountsComboBox, 0, 0, 1, 2);
    m_mainLayout->addWidget(m_loginLabel, 1, 0, 1, 2);
    m_mainLayout->addWidget(m_loginLineEdit, 2, 0, 1, 2);
    m_mainLayout->addWidget(m_passwordLabel, 3, 0, 1, 2);
    m_mainLayout->addWidget(m_passwordLineEdit, 4, 0, 1, 2);
    m_mainLayout->addWidget(m_loginButton, 5, 0);
    m_mainLayout->addWidget(m_saveCheckBox, 5, 1);
}

} // namespace Ui
} // namespace Lamagotchi
