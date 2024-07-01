#ifndef LOGIN_FORM_H
#define LOGIN_FORM_H

#include <QCheckBox>
#include <QComboBox>
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
    ~LoginForm() = default;

signals:
    void credentialsReady(std::string login, std::string password);

private slots:
    void onLogInClicked();
    void onLoginSettingsClicked();

private:
    QComboBox* m_accountsComboBox;
    QPushButton* m_logInButton;
    QPushButton* m_loginSettingsButton;
    QLineEdit* m_loginLineEdit;
    QLineEdit* m_passwordLineEdit;
    QCheckBox* m_saveCheckBox;
};

} // namespace Ui
} // namespace Lamagotchi

#endif // LOGIN_FORM_H
