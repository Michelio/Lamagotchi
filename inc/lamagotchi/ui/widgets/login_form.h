#ifndef LOGIN_FORM_H
#define LOGIN_FORM_H

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

namespace Lamagotchi
{

namespace Ui
{

class LoginForm : public QWidget
{
    Q_OBJECT;

public:
    LoginForm(QWidget* parent = nullptr);

private:
    QGridLayout* m_mainLayout;
    QComboBox* m_accountsComboBox;
    QLabel* m_loginLabel;
    QLabel* m_passwordLabel;
    QLineEdit* m_loginLineEdit;
    QLineEdit* m_passwordLineEdit;
    QPushButton* m_loginButton;
    QCheckBox* m_saveCheckBox;
};

} // namespace Ui
} // namespace Lamagotchi

#endif // LOGIN_FORM_H
